#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_3_triggered()
{
    QString filePath { QFileDialog::getOpenFileName(this,
        "Choose file to open", QDir::current().path(),
            trUtf8("Text file(*.txt)")) };

    if (filePath.length())
    {
         int index = filePath.indexOf(".txt");
         if (index != -1 && filePath.length() - 4 == index)
         {
             QFile file { filePath };
             if (file.open(QFile::ReadOnly | QFile::ExistingOnly))
             {
                 QTextStream stream(&file);
                 ui->plainTextEdit->setPlainText(
                    stream.readAll());
                 file.close();
             }
             else //!open
                 QMessageBox::warning(this, "File not found",
                    "Can't open file " + filePath);
         }

    }

}


void MainWindow::on_actionOpen_read_only_mode_2_triggered()
{

}


void MainWindow::on_actionSave_2_triggered()
{
    QString filePath { QFileDialog::getSaveFileName(this,
         "Save file as", QDir::current().path(),
            trUtf8("Text file(*.txt)")) };

    if (filePath.length())
    {
        QString ext { QString { &(filePath.data()
            [ filePath.length() - 4 ])}};

        QFile file { filePath };
        if (file.open(QFile::WriteOnly | QFile::NewOnly))
         {
           QTextStream stream(&file);
           stream << ui->plainTextEdit->toPlainText();
           file.close();
         }
        else //!open
        {
        QMessageBox::warning(this, "File not found",
             "Can't open file " + filePath);

        }

    }
}


void MainWindow::on_actionExit_2_triggered()
{
   QApplication::quit();
}


void MainWindow::on_actionHelp_triggered()
{
   QString filePath { ":help.txt" };

    QFile file { filePath };
    if (file.open(QFile::ReadOnly | QFile::ExistingOnly))
    {
     QTextStream stream(&file);
     ui->plainTextEdit->setPlainText(stream.readAll());
     file.close();
    }
    else //if !file.open()
        QMessageBox::warning(this, "File not found",
            "Can't open resource " + filePath);
}

