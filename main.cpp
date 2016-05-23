#include "picdealmain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PicDealMain w;
    w.show();

    return a.exec();
}
