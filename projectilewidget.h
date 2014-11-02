#ifndef PROJECTILEWIDGET_H
#define PROJECTILEWIDGET_H

#include "projectile.h"
#include "gamemodel.h"
#include <QLabel>

class ProjectileWidget : public QLabel
{
    Q_OBJECT
private:
    //pointer to GameModel player
    Projectile* projectile;
    QPixmap image;

public:
    explicit ProjectileWidget(QWidget *parent = 0, Projectile *init_projectile = nullptr);

    Projectile* getProjectile() { return projectile; }

    //getters, setters
    QPixmap getImage() { return image; }

signals:

public slots:

};

#endif // PROJECTILEWIDGET_H
