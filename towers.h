#ifndef TOWERS_H
#define TOWERS_H

#include <QLabel>

struct tower {
    int damage;
    int attackSpeed;
    int angle;
    bool canSpawn;

    int x, y;
    QLabel *label;
};

#endif // TOWERS_H
