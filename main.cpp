#include "mainwindow.h"

#include <QApplication>
#include <QResource>

//All pathes like this depend on IDE settings:
const QString resFilePath { QStringLiteral ( "../qt_4/resources.rcc" ) };

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile resFile { resFilePath };
    if (!resFile.exists())
    {
        QMessageBox::warning(nullptr, "File not found",
            "Can't open resourses file " + resFilePath +
                ".\nDont forget to issue next command beforehand:\n" +
                             "rcc -binary res/resources.qrc -o resources.rcc");

        return -1;
    }

    QResource::registerResource(resFilePath);

    MainWindow w;
    w.show();
    return a.exec();
}
