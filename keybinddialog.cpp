#include "keybinddialog.h"
#include "ui_keybinddialog.h"

KeyBindDialog::KeyBindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyBindDialog)
{
    ui->setupUi(this);
}

KeyBindDialog::KeyBindDialog(QVector<KeyBind> &iKeysVec) :
    KeyBindDialog(),
    keysVec{}
{

    /*
    for (int i{}; i < keysVec.size(); ++i)
    {
        ui->cbAction->addItem(keysVec[i].);
    }
    */
}

KeyBindDialog::~KeyBindDialog()
{
    delete ui;
}

void KeyBindDialog::on_btnCancel_clicked()
{
   close();
}

