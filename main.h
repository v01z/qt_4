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
    { 1, QObject::tr("Русский") },
    { 2, QObject::tr("Открыть для чтения") },
    { 3, QObject::tr("Закрыть") },
    { 4, QObject::tr("Сохранить как") },
    { 5, QObject::tr("Сохранить") },
    { 6, QObject::tr("Выход") },
    { 7, QObject::tr("Английский") },
    { 8, QObject::tr("Помощь") },
    { 9, QObject::tr("Забиндить клавиши") },

};

//Пока тут будет два модификатора, потом можно дополнить
const QPair <Qt::KeyboardModifier, QString> modsTranslator [] = {
    { Qt::ControlModifier, "Cntrl" },
    { Qt::ShiftModifier, "Shift" }
};

//Тут тоже пока не вся клава
const QPair <Qt::Key, QString> keysTranslator [] = {
    { Qt::Key_A, "A" },
    { Qt::Key_B, "B" },
    { Qt::Key_C, "C" },
    { Qt::Key_D, "D" },
    { Qt::Key_E, "E" },
    { Qt::Key_F1, "F1" },
    { Qt::Key_F2, "F2" },
    { Qt::Key_F3, "F3" }
};

#endif // MAIN_H
