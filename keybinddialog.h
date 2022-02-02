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

#endif // KEYBINDDIALOG_H
