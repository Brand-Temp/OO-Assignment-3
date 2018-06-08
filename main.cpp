#include <QApplication>
#include "facade.h"

int main(int argc, char *argv[])
{
    QApplication c(argc, argv);

    Facade game(argc, argv);
    game.makeGame();
    game.showGame();

    return c.exec();

}
