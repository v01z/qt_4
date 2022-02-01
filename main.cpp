#include "mainwindow.h"

#include <QApplication>

//All pathes like this depend on IDE settings:
const QString resFilePath { QStringLiteral ( "../qt_3/resources.rcc" ) };

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
