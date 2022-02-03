#include "keybinddialog.h"
#include "ui_keybinddialog.h"

KeyBindDialog::KeyBindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyBindDialog)
{
    ui->setupUi(this);
}

KeyBindDialog::KeyBindDialog(QVector<KeyBind> *iKeysVec) :
    KeyBindDialog()
//    keyBind { iKeysVec }
{
//    keyBind = new KeyBind;
    keyBind = iKeysVec;


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

    ui->cbAction->setCurrentIndex(0);
    assert(ui->cbAction->currentText() == actionsIndexes[0].second);

    updateInterface(0);

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

void KeyBindDialog::updateInterface(int index) const
{

 //   int modIndx{};
    for (int i{}; i < modsTranslator.size(); ++i)
    {
       //if (keyBind[index]->mod1 == modsTranslator[i].first)
       if (keyBind->at(index).mod1 == modsTranslator[i].first)
       {
           ui->cbMod1->setCurrentText(modsTranslator[i].second);
           break;
       }
    }

    for (int i{}; i < modsTranslator.size(); ++i)
    {
       //if (keyBind[index].mod2 == modsTranslator[i].first)
       if (keyBind->at(index).mod2 == modsTranslator[i].first)
       {
           ui->cbMod2->setCurrentText(modsTranslator[i].second);
           break;
       }
    }

    for (int i{}; i < keyTranslator.size(); ++i)
    {
       //if (keyBind[index].key == keyTranslator[i].first)
       if (keyBind->at(index).key == keyTranslator[i].first)
       {
           ui->cbKey->setCurrentText(keyTranslator[i].second);
           break;
       }
    }
}

void KeyBindDialog::on_cbAction_activated(const QString &arg1)
{
    updateInterface(ui->cbAction->currentIndex());
}


void KeyBindDialog::on_btnOk_clicked()
{
 //   KeyBind tempKey{};

    for (int i{}; i < modsTranslator.size(); ++i)
    {
        if (modsTranslator[i].second == ui->cbMod1->currentText())
        {
            newKeyBind.mod1 = modsTranslator[i].first;
            break;
        }
    }

    for (int i{}; i < modsTranslator.size(); ++i)
    {
        if (modsTranslator[i].second == ui->cbMod2->currentText())
        {
            newKeyBind.mod2 = modsTranslator[i].first;
            break;
        }
    }

    for (int i{}; i < keyTranslator.size(); ++i)
    {
        if (keyTranslator[i].second == ui->cbAction->currentText())
        {
            newKeyBind.key = keyTranslator[i].first;
            break;
        }
    }

    //keyBind[ui->cbAction->currentIndex()] = tempKey;
//    keyBind->at(ui->cbAction->currentIndex()) = tempKey;

    /*
    keyBind->at(ui->cbAction->currentIndex()).mod1 = tempKey.mod1;
    keyBind->at(ui->cbAction->currentIndex()).mod2 = tempKey.mod2;
    keyBind->at(ui->cbAction->currentIndex()).key = tempKey.key;
    */

}

const KeyBind &KeyBindDialog::getNewBinding() const {
   return newKeyBind;
}
