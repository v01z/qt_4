#ifndef MAIN_H
#define MAIN_H

#include <QTranslator>
#include <QVector>
//#include <QPair>

struct KeyBind {
    Qt::KeyboardModifier mod1;
    Qt::KeyboardModifier mod2;
    Qt::Key key;
};


const QPair <int, QString> actionsIndexes [] = {
    { 0, QObject::tr("Открыть") },
    { 1, QObject::tr("Открыть для чтения") }
};

#endif // MAIN_H
