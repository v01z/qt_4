#include "keybinddialog.h"
#include "ui_keybinddialog.h"

KeyBindDialog::KeyBindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyBindDialog),
    keyBind { nullptr }
{
    ui->setupUi(this);
}

KeyBindDialog::KeyBindDialog(QVector<KeyBind> *iKeysVec) :
    KeyBindDialog()
{
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

    ui->cbAction->setCurrentIndex(0);
    assert(ui->cbAction->currentText() == actionsIndexes[0].second);
    updateInterface(0);

}

KeyBindDialog::~KeyBindDialog()
{
    delete ui;
}

void KeyBindDialog::on_btnCancel_clicked()
{
   close();
}

void KeyBindDialog::updateInterface(int index) const
{

    for (int i{}; i < modsTranslator.size(); ++i)
    {
       if (keyBind->at(index).mod1 == modsTranslator[i].first)
       {
           ui->cbMod1->setCurrentText(modsTranslator[i].second);
           break;
       }
    }

    for (int i{}; i < modsTranslator.size(); ++i)
    {
       if (keyBind->at(index).mod2 == modsTranslator[i].first)
       {
           ui->cbMod2->setCurrentText(modsTranslator[i].second);
           break;
       }
    }

    for (int i{}; i < keyTranslator.size(); ++i)
    {
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

    newKeyBind.second = ui->cbAction->currentIndex();

    for (int i{}; i < modsTranslator.size(); ++i)
    {
        if (modsTranslator[i].second == ui->cbMod1->currentText())
        {
            newKeyBind.first.mod1 = modsTranslator[i].first;
            qDebug() << "From dialog class: mod1: " << newKeyBind.first.mod1;
            break;
        }
    }

    for (int i{}; i < modsTranslator.size(); ++i)
    {
        if (modsTranslator[i].second == ui->cbMod2->currentText())
        {
            newKeyBind.first.mod2 = modsTranslator[i].first;
            qDebug() << "From dialog class: mod2:" << newKeyBind.first.mod2;
            break;
        }
    }

    for (int i{}; i < keyTranslator.size(); ++i)
    {
        if (keyTranslator[i].second == ui->cbAction->currentText())
        {
            newKeyBind.first.key = keyTranslator[i].first;
            qDebug() << "From dialog class: " << newKeyBind.first.key;
            break;
        }
    }

    qDebug() << newKeyBind.second << " ----> from dialog class";
    close();
}

const QPair<KeyBind, int> &KeyBindDialog::getNewBinding() const {

   return newKeyBind;
}
