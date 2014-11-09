#ifndef INGAME_H
#define INGAME_H

#include <QLabel>
#include <QTimer>
#include <QMainWindow>
#include <QWidget>
#include <QKeyEvent>
#include <iostream>
#include <typeinfo>
#include "ui_ingame.h"

#include "playerwidget.h"
#include "entitywidget.h"

namespace Ui {
class InGame;
}

class InGame : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit InGame(QMainWindow *parent = 0, QString initLoadGameFile = 0);
    ~InGame();

private slots:

    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);
    void updateView();
    
    void on_pushButton_clicked();

private:
    Ui::InGame *ui;
    PlayerWidget *pl;               // Pointer to the Player Widget in model

    vector<EntityWidget*> ewidgets;
    QTimer *fpsTimer;               // Timer that drives the InGame UI
    QString loadGameFile;

};

#endif // INGAME_H
