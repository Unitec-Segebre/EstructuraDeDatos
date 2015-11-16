#include "game.h"

Game::Game()
{
    score = 0;
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    log = new Log();
    Piezas * pieza = new Piezas();
    pieza->setBrush(Qt::red);
    scene->addItem(pieza);
    log->label->move(1000, 0);
    log->label->adjustSize();
    proxyWidget = scene->addWidget(log->label);

    //quitamos las scroll bars
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(1500,1000);
    view->show();
    scene->setSceneRect(0, 0, 1500, 1000);
}

void Game::update()
{
    log->addPuntos(2, score);
    Piezas * pieza = new Piezas();
    pieza->setBrush(* new QBrush(Qt::red));
    scene->addItem(pieza);
    pieza->setFocus();
    int eliminar = check();
    if(eliminar != -1)
        removeLine(eliminar);
}

int Game::check()
{
    for(int i = 9; i >= 0; i--)
    {
        for(int j = 0; j < 10; j++)
        {
            if(scene->itemAt(j*100+50, i*100+50, QTransform()) == 0)
                break;
            if(j == 9)
                return i;
        }
    }
    return -1;
}

void Game::removeLine(int row)
{
    QGraphicsItem * block;
    score+=10;
    //elimina los bloques
    for(int i = 0; i < 10; i++)
    {
        block = scene->itemAt(i*100+50, row*100+50, QTransform());
        if(block != 0)
            scene->removeItem(block);
    }

    //corre los bloques
    QList<QGraphicsItem *> cubitos = scene->items();
    cout<<cubitos.size()<<endl;
    for(int i = 0; i < cubitos.size(); i++)
    {
        if(cubitos[i]->x() < 1000)
        {
            if(cubitos[i]->y() < row*100)
                cubitos[i]->setPos(cubitos[i]->x(), cubitos[i]->y()+100);
        }
    }
    log->eliminoFila(row, score);
    log->label->adjustSize();
}

void Game::over()
{
    //cout<<"termino"<<endl;
    score = 0;
    scene->clear();
    Piezas * pieza = new Piezas();
    pieza->setBrush(Qt::red);
    scene->addItem(pieza);
    log = new Log();
    log->label->move(1000, 0);
    log->label->adjustSize();
    proxyWidget = scene->addWidget(log->label);
}


