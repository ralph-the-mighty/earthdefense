#include "ingame.h"
#include "client.h"
#include "host.h"

using namespace std;

InGame::InGame(QMainWindow *parent, QString initLoadGameFile, string netstat, int initDifficulty) :
    QMainWindow(parent),
    ui(new Ui::InGame),
    netstatus(netstat),
    difficulty(initDifficulty)
{
    ui->setupUi(this);

    //start gamemodel

    GameModel::getInstance().setObserver(this);
    if (initLoadGameFile.size() != 0) {
        GameModel::getInstance().loadGame(initLoadGameFile);
    }

    GameModel::getInstance().setDifficulty(difficulty);

    GameModel::getInstance().initializeGame();

    //init player widget
    pl = new PlayerWidget(this);
    pl->setAttribute(Qt::WA_TranslucentBackground, true); //Transparency!!! :D
    GameModel::getInstance().getPlayer()->setDir(0);
    pl->show();

    //start timer
    fpsTimer = new QTimer(this);
    fpsTimer->setInterval(1000/60.0);
    connect(fpsTimer, &QTimer::timeout, this, &InGame::updateView);
    fpsTimer->start();

    //server-client setup
    if(netstat == "client"){
        Client::getInstance().connectToServer();
    }else if(netstat == "host"){
        Host::getInstance().start();

    }
}

InGame::~InGame()
{
    delete ui;
}


/* * * * * * * * * * * * * * * * * * * * * * * * *
 *               INPUT HANDLERS                  *
 * * * * * * * * * * * * * * * * * * * * * * * * */

// Matt, Can you try to abstract input handling away from the slots and into the
// model?  basicall, instead of acting directly on a keydown or up, just call the
// appropriate method in the input manager to set the flag.  Then, inside the model
// check the input managers state, and perform the appropriate action.

void InGame::keyPressEvent(QKeyEvent *ev){

    if (ev->key() == 0x01000012){ //left key pressed
        GameModel::getInstance().getPlayer()->setDir(-1);
        if(netstatus == "client") {Client::getInstance().sendMessage("left down");}
        //InputManager::getInstance().keyDown("left");

    }else if (ev->key() == 0x01000014){ //right key pressed
        GameModel::getInstance().getPlayer()->setDir(1);
        if(netstatus == "client") {Client::getInstance().sendMessage("right down");}
        //InputManager::getInstance().keyDown("right");


    }else if (ev->key() == 0x20){ // space key pressed
        int x = GameModel::getInstance().getPlayer()->getPos().x() + 22;
        int y = GameModel::getInstance().getPlayer()->getPos().y() - 10;

        GameModel::getInstance().create("projectile", x, y);
        if(netstatus == "client") {Client::getInstance().sendMessage("fire down");}
        //InputManager::getInstance().keyDown("fire");


    }
}

void InGame::keyReleaseEvent(QKeyEvent *ev) {

    if (ev->key() == 0x01000012){ // left key released
        GameModel::getInstance().getPlayer()->setDir(0);     // OLD
         if(netstatus == "client") {Client::getInstance().sendMessage("fire up");}
        //InputManager::getInstance().keyUp("left");              // NEW
    }else if (ev->key() == 0x01000014){ // right key released
        GameModel::getInstance().getPlayer()->setDir(0);     // OLD
         if(netstatus == "client") {Client::getInstance().sendMessage("fire up");}
        //InputManager::getInstance().keyUp("right");             // NEW
    }else if (ev->key() == 0x20){ // space key released
         if(netstatus == "client") {Client::getInstance().sendMessage("fire up");}
        //InputManager::getInstance().keyUp("fire");
    }
}

/* * * * * * * * * * * * * * * * * * * * *
 *         MAIN UPDATE FUNCTION          *
 * * * * * * * * * * * * * * * * * * * * */

void InGame::updateView() {
    //set score label
    ui->scorelbl->setText(QString::number(GameModel::getInstance().getScore()));


    //update game depending on whether game is multiplayer or singlplayer, host or client;
    if(netstatus == "client"){
        GameModel::getInstance().slaveUpdate();
    }else{
        GameModel::getInstance().masterUpdate();
        if(netstatus == "host"){
            Host::getInstance().sendMessage(QString::fromStdString(GameModel::getInstance().state()));
        }
    }

    /* Update PlayerWidget Position ---- MIGHT HAVE TO IMPLEMENT SAME AS BELOW WHEN WE INTRODUCE MULTIPLAYER SINCE THERE WILL BE MORE THAN
     *                                   ONE PLAYER ON THE SCREEN AT ONE TIME */
    pl->setGeometry(QRect(pl->getPlayer()->getPos().x(),
                          pl->getPlayer()->getPos().y(),
                          50, 50));
    pl->show();



    vector<Entity*> entities = GameModel::getInstance().getEntities();


    for(Entity* entity : entities){
        if(entity->getJustCreated()){
                EntityWidget* temp = new EntityWidget(this, entity);
                ewidgets.push_back(temp);

                temp->setGeometry(QRect(entity->getPos().x(),
                                        entity->getPos().y(),
                                        entity->width,
                                        entity->height));
                temp->setAttribute(Qt::WA_TranslucentBackground, true);

                //check for type in order to set proper image
                if(temp->getEntity()->toString().find("projectile") == 0){
                    QPixmap projectile(":/resources/images/projectile.png");
                    temp->setPixmap(projectile);
                } else if (temp->getEntity()->toString().find("trackingprojectile") == 0){
                    QPixmap trprojectile(":/resources/images/trackingmissle.png");
                    temp->setPixmap(trprojectile);
                } else if (temp->getEntity()->toString().find("enemy") == 0){
                    QPixmap enemy(":/resources/images/alien1.png");
                    temp->setPixmap(enemy);
                } else if (temp->getEntity()->toString().find("trackingenemy") == 0) {
                    QPixmap trenemy(":/resources/images/trackingenemy.png");
                    temp->setPixmap(trenemy);
                }
                temp->setScaledContents(true);
                temp->show();
                entity->setJustCreated(false);  //make sure we know that entity is no longer new.
        }
    }

    //update each remaining widget

    for(size_t i = 0; i < ewidgets.size(); i++){
        EntityWidget *wdgt = ewidgets.at(i);
        if (wdgt->getEntity()->isAlive() == false){     //destroy widget if corresponding entity is dead
            ewidgets.erase(ewidgets.begin()+i);
            delete wdgt;
        }else{
            wdgt->move(wdgt->getEntity()->getPos().x(),wdgt->getEntity()->getPos().y());
            wdgt->show();
        }
    }
}

void InGame::gameOver(){
    fpsTimer->stop();
}

void InGame::advanceLevel() {
    ui->lblLevel->setText(QString(GameModel::getInstance().getCurrentLvl()));
}

/* * * * * * * * * * * *
 *       SLOTS         *
 * * * * * * * * * * * */

void InGame::on_btnSaveGame_clicked()
{

    GameModel::getInstance().saveGame("savegame");
}

void InGame::on_btnStartOver_clicked()
{
    this->hide();
    this->fpsTimer->stop();
    GameModel::getInstance().reset();
    GameModel::getInstance().initializeGame();
    InGame* newGameScreen = new InGame(this, "", netstatus, difficulty);
    newGameScreen->show();
    newGameScreen->setEnabled(true);
}
