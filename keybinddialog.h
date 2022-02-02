#ifndef KEYBINDDIALOG_H
#define KEYBINDDIALOG_H

#include <QDialog>
#include "main.h"

namespace Ui {
class KeyBindDialog;
}

/*
struct DataToView{
    KeyBind kbData;
    QPair<int, QString> viewPair;
};
*/

class KeyBindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KeyBindDialog(QWidget *parent = nullptr);
    explicit KeyBindDialog(QVector<KeyBind>&);
    ~KeyBindDialog();

private slots:
    void on_btnCancel_clicked();

private:
    Ui::KeyBindDialog *ui;
//    QVector<KeyBind> *keysVec;
//    KeyBind *keyBind;
};

const QVector <QPair <int, QString> > actionsIndexes = {
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
//const QMap<Qt::KeyboardModifier, QString> modsTranslator  {
const QVector<QPair<Qt::KeyboardModifier, QString>> modsTranslator  {
//const std::map<Qt::KeyboardModifier, QString> modsTranslator  {
    { Qt::NoModifier, QObject::tr("Пусто") },
    { Qt::ControlModifier, "Cntrl" },
    { Qt::ShiftModifier, "Shift" }
};

//Тут тоже пока не вся клава
//const QPair <Qt::Key, QString> keysTranslator [] = {
//const QMap <Qt::Key, QString> keyTranslator  {
const QVector<QPair<Qt::Key, QString>> keyTranslator  {
//const std::map <Qt::Key, QString> keyTranslator  {
//const QVector <QPair<Qt::Key, QString> > keyTranslator  {
//const std::vector<QPair<Qt::Key, QString> > keyTranslator  {
    { Qt::Key_A, "A" },
    { Qt::Key_B, "B" },
    { Qt::Key_C, "C" },
    { Qt::Key_D, "D" },
    { Qt::Key_E, "E" },
    { Qt::Key_H, "H" },
    { Qt::Key_O, "O" },
    { Qt::Key_Q, "Q" },
    { Qt::Key_R, "R" },
    { Qt::Key_X, "X" },
    { Qt::Key_F1, "F1" },
    { Qt::Key_F2, "F2" },
    { Qt::Key_F3, "F3" }
};

#endif // KEYBINDDIALOG_H
