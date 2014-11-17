#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnNewGame_clicked()
{
    QString initIp, netstat;
    if(ui->rbHostGame->isChecked()){
        netstat = "host";
    }else if(ui->rbJoinGame->isChecked()){
        netstat = "client";
        initIp = ui->leIP->text();
    }else{
        netstat = "single";
    }


    int initDifficulty;
    if (ui->cbDifficulty->currentIndex() == 0) {
        initDifficulty = 1;
    } else if (ui->cbDifficulty->currentIndex() == 1) {
        initDifficulty = 2;
    } else {
        initDifficulty = 3;
    }

    bool cheat;
    if (ui->cbCheat->isChecked()){
        cheat = true;
    } else {
        cheat = false;
    }

    InGame* gameWindow = new InGame(this, netstat, "", initDifficulty, initIp, cheat);
    gameWindow->show();
    gameWindow->setEnabled(true);
    this->hide();
}

void MainWindow::on_btnLoadGame_clicked()
{
    QString netstat, initIp;

    if(ui->rbHostGame->isChecked()){
        netstat = "host";
    }else if(ui->rbJoinGame->isChecked()){
        netstat = "client";
        initIp = ui->leIP->text();
    }else{
        netstat = "single";
    }

    bool cheat;
    if (ui->cbCheat->isChecked()){
        cheat = true;
    } else {
        cheat = false;
    }

    int initDifficulty;
    if (ui->cbDifficulty->currentIndex() == 0) {
        initDifficulty = 1;
    } else if (ui->cbDifficulty->currentIndex() == 1) {
        initDifficulty = 2;
    } else {
        initDifficulty = 3;
    }

    InGame* gameWindow = new InGame(this, netstat, "savegame", initDifficulty, initIp, cheat);
    gameWindow->show();
    gameWindow->setEnabled(true);
    this->hide();

}

void MainWindow::on_btnInstructions_clicked()
{
    QMessageBox instructions;
    instructions.information(this, "Instructions", "<p style='color:orange;font-weight:bold;font-size:20px'>Use the arrow keys to move your space ship left and right," \
                             "use the space bar to shoot.  Shoot all the aliens before they invade our planet " \
                             "and destroy life as we know it.  We are all doomed if you cannot save us from " \
                             "impending disaster! P.S. Watch out for the ship seeking bullets.</p>");

}


void MainWindow::on_rbSinglePlayer_clicked()
{

}

void MainWindow::on_rbMultiplayer_clicked()
{

}


void MainWindow::on_rbEasy_clicked()
{

}
