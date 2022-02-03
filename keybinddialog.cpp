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


    //Unite these four to one function
    for (int i{}; i < actionsIndexes.size(); ++i)
        ui->cbAction->addItem(actionsIndexes[i].second);

    for (int i{}; i < modsTranslator.size(); ++i)
        ui->cbMod1->addItem(modsTranslator[i].second);

    for (int i{}; i < modsTranslator.size(); ++i)
        ui->cbMod2->addItem(modsTranslator[i].second);

    for (int i{}; i < keyTranslator.size(); ++i)
        ui->cbKey->addItem(keyTranslator[i].second);

    //Create func that takes one argument - KeyBind and update all interface исходя из этого
//    ui->cbAction->setCurrentIndex();
//    ui->cbMod1->setCurrentIndex();
//    ui->cbKey->setCurrentIndex(3);
//    ui->cbAction->setCurrentIndex(0);
 //   ui->cbMod1->setCurrentIndex();
    updateInterface(iKeysVec);

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

void KeyBindDialog::updateInterface(QVector<KeyBind> &iKeyBind)
{
    ui->cbAction->setCurrentIndex(0);
    assert(ui->cbAction->currentText() == actionsIndexes[0].second);

//    ui->cbMod1->setCurrentText();
}
