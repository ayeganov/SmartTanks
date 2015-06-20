#include "gameview.h"
#include "globals.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameView gv;
    gv.show();

    return a.exec();
}
