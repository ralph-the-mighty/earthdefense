#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QDebug>
#include <QWidget>

#include <QFile>

#include <QString>
#include <vector>
#include <sstream>

#include "client.h"
#include "host.h"

#include "trackingenemy.h"
#include "projectile.h"
#include "trackingprojectile.h"
#include "gamemodel.h"
#include "enemy.h"
#include "player.h"
#include "entity.h"
#include "sstream"
#include "worldobserver.h"

using namespace std;

//abstract game model class
class GameModel {
private:
    WorldObserver* observer;
    vector<Entity*> entities;
    Player* player;
    Player* player2;
    int window_height, window_width; //these two variables set in intitializer
    int score, spawnCountDown, currentLvl, difficulty;
    int cooldown;
    bool cheat;
    string netstatus;

public:
    ~GameModel();

    void initializeGame(string netstat);
    void gameOver();
    void reset();

    string state();
    void loadGame(QString filename);
    void saveGame(string filename);

    bool checkForNextLevel();
    void advanceLevel();

    void masterUpdate();
    void slaveUpdate();

    void setCooldown(int i){cooldown = i;}
    int getCooldown(){return cooldown;}

    Entity* create(string type, int x, int y, int dir=-1);
    Entity* getById(int id);
    Entity* destroy(int id);

    //getters and setters
    Player*         getPlayer()     { return player;}
    Player*         getPlayer2()    { return player2;}
    vector<Entity*>& getEntities()  { return entities;}    //return reference for efficiency
    int             getScore()      { return score;}
    int             getCurrentLvl() { return currentLvl; }
    int             getDifficulty() { return difficulty; }
    int             getWinHeight()  { return window_height; }
    int             getWinWidth()   { return window_width; }

    void setScore(int s)                { score = s; }
    void setObserver(WorldObserver* o)  { observer = o; }
    void setLevel(int initLvl)          { currentLvl = initLvl; }
    void setDifficulty(int i)           { difficulty = i; }
    void setCheat(bool b){cheat = b;}
    bool getCheat(){return cheat;}

    string getNetStatus(){return netstatus;}

    /***  singleton implementation ***/
private:
    static GameModel instance;
    GameModel();
public:
    static GameModel &getInstance() { return instance; }
};

#endif // GAMEMODEL_H
