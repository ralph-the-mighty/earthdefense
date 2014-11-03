#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include "player.h"
#include "gamemodel.h"
#include <QLabel>

class PlayerWidget : public QLabel
{
    Q_OBJECT
private:
    //pointer to GameModel player
    Player* player;
    QPixmap image;

public:
    explicit PlayerWidget(QWidget *parent = 0);
    ~PlayerWidget();

    Player* getPlayer() { return player; }

    //getters, setters
    QPixmap getImage() { return image; }
    
signals:
    
public slots:
    
};

#endif // PLAYERWIDGET_H
