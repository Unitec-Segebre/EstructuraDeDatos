#ifndef PIEZAS_H
#define PIEZAS_H
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QObject>
#include <QTimer>
#include <QKeyEvent>
#include <QList>
#include <typeinfo>
#include "arbolexpr.h"

class Piezas : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Piezas();
    ArbolExp * arbol;
    int tamano;
    void keyPressEvent(QKeyEvent *event);
    bool llego;

signals:

public slots:
    void move();
};

#endif // PIEZAS_H