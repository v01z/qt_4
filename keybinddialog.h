#ifndef KEYBINDDIALOG_H
#define KEYBINDDIALOG_H

#include <QDialog>
#include "main.h"

namespace Ui {
class KeyBindDialog;
}

class KeyBindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KeyBindDialog(QWidget *parent = nullptr);
    explicit KeyBindDialog(QVector<KeyBind>*);
    ~KeyBindDialog();

    void updateInterface(int) const;

    const QPair<KeyBind, int> &getNewBinding() const;

private slots:
    void on_btnCancel_clicked();

    void on_cbAction_activated(const QString);

    void on_btnOk_clicked();

private:
    Ui::KeyBindDialog *ui;
    QVector<KeyBind> *keyBind;
    QPair<KeyBind, int> newKeyBind;
};

//Warning: The order should be the same as filling QVector
//in MainWindow constructor. Later I will decide how to
//manage it more properly.
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

/*
//Пока тут будет три модификатора, потом можно дополнить
const QVector<QPair<Qt::KeyboardModifier, QString>> modsTranslator  {
    { Qt::NoModifier, QObject::tr("Пусто") },
    { Qt::ControlModifier, "Cntrl" },
    { Qt::ShiftModifier, "Shift" }
};

/*
static const char *greeting_strings[] = {
        QT_TR_NOOP("Пусто"),
    };
const QVector<QPair<Qt::KeyboardModifier, QString>> modsTranslator  {
    { Qt::NoModifier, QObject::tr(greeting_strings[0]) },
    { Qt::ControlModifier, "Cntrl" },
    { Qt::ShiftModifier, "Shift" }
};
*/
const QVector<QPair<Qt::KeyboardModifier, QString>> modsTranslator  {
    { Qt::NoModifier, QObject::tr(QT_TR_NOOP("Пусто")) },
    { Qt::ControlModifier, "Cntrl" },
    { Qt::ShiftModifier, "Shift" }
};

//Тут тоже пока не вся клава
const QVector<QPair<Qt::Key, QString>> keyTranslator  {
//const std::map <Qt::Key, QString> keyTranslator  {
    { Qt::Key_A, "A" },
    { Qt::Key_B, "B" },
    { Qt::Key_C, "C" },
    { Qt::Key_D, "D" },
    { Qt::Key_E, "E" },
    { Qt::Key_H, "H" },
    { Qt::Key_K, "K" },
    { Qt::Key_O, "O" },
    { Qt::Key_Q, "Q" },
    { Qt::Key_R, "R" },
    { Qt::Key_S, "S" },
    { Qt::Key_X, "X" },
    { Qt::Key_F1, "F1" },
    { Qt::Key_F2, "F2" },
    { Qt::Key_F3, "F3" }
};

#endif // KEYBINDDIALOG_H
