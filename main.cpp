#include "motoupdater.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MotoUpdater w;
    w.show();
    return a.exec();
}
