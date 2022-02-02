#include "keybinddialog.h"
#include "ui_keybinddialog.h"

KeyBindDialog::KeyBindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyBindDialog)
{
    ui->setupUi(this);
}

KeyBindDialog::KeyBindDialog(QVector<KeyBind> &iKeysVec) :
    KeyBindDialog()
//    keysVec{}
{
//    keyBind = new KeyBind;

    for (int i{}; i < iKeysVec.size(); ++i)
    {
        ui->cbAction->addItem(actionsIndexes[i].second);
        ui->cbMod1->addItem(iKeysVec[i].mod1);
    }
}

KeyBindDialog::~KeyBindDialog()
{
  //  delete keyBind;
    delete ui;
}

void KeyBindDialog::on_btnCancel_clicked()
{
   close();
}

