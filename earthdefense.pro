#-------------------------------------------------
#
# Project created by QtCreator 2014-10-20T19:40:51
#
#-------------------------------------------------

QT       += core gui widgets network

QMAKE_CXXFLAGS += -std=c++0x # Singleton (specifically 'nullptr')

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = earthdefense
TEMPLATE = app


SOURCES += main.cpp\
           mainwindow.cpp \
           highscore.cpp \
           gamemodel.cpp \
           ingame.cpp \
           entity.cpp \
           player.cpp \
           enemy.cpp \
           projectile.cpp \
           playerwidget.cpp \
	   host.cpp \
    entitywidget.cpp \
    utils.cpp \
    client.cpp \
    trackingprojectile.cpp \
    inputmanager.cpp \
    trackingenemy.cpp \
    gameover.cpp

HEADERS  += mainwindow.h \
            gamemodel.h \
            highscore.h \
            ingame.h \
            entity.h \
            player.h \
	    enemy.h \
            projectile.h \
            playerwidget.h \
	    host.h \
    score.h \
    entitywidget.h \
    objectobserver.h \
    worldobserver.h \
    utils.h \
    client.h \
    trackingprojectile.h \
    inputmanager.h \
    trackingenemy.h \
    gameover.h

FORMS    += mainwindow.ui \
            ingame.ui \
    gameover.ui

RESOURCES += \
    resources.qrc
