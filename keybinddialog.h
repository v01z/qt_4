#ifndef KEYBINDDIALOG_H
#define KEYBINDDIALOG_H

#include <QDialog>

namespace Ui {
class KeyBindDialog;
}

class KeyBindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KeyBindDialog(QWidget *parent = nullptr);
    ~KeyBindDialog();

private:
    Ui::KeyBindDialog *ui;
};

#endif // KEYBINDDIALOG_H
