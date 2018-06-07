#include <QApplication>
#include "facade.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Facade game;
    game.makeGame();
    game.showGame();

    return a.exec();

}
