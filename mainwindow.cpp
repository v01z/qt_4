#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      file(new QFile())
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    if (file->isOpen())
        file->close();
    delete file;

    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    QString filePath { QFileDialog::getOpenFileName(this,
        "Choose file to open", QDir::current().path(),
            trUtf8("Text file(*.txt)")) };

    if (filePath.length())
    {
         int index = filePath.indexOf(".txt");
         if (index != -1 && filePath.length() - 4 == index)
         {
             if (file->isOpen())
                    file->close();

             file->setFileName(filePath);
             if (file->open(QFile::ReadWrite | QFile::ExistingOnly))
             {
                 QTextStream stream(file);

                 disableSave(false);

                 ui->plainTextEdit->setPlainText(
                    stream.readAll());

                 ui->statusbar->showMessage(file->fileName());
             }
             else //!open
                 QMessageBox::warning(this, "File not found",
                    "Can't open file " + filePath);

         }

    }

}


void MainWindow::on_actionOpen_read_only_mode_triggered()
{

    QString filePath { QFileDialog::getOpenFileName(this,
        "Choose file to open", QDir::current().path(),
            trUtf8("Text file(*.txt)")) };

    if (filePath.length())
    {
         int index = filePath.indexOf(".txt");
         if (index != -1 && filePath.length() - 4 == index)
         {
             if (file->isOpen())
                    file->close();

             file->setFileName(filePath);
             if (file->open(QFile::ReadOnly | QFile::ExistingOnly))
             {
                 QTextStream stream(file);

                 ui->plainTextEdit->setPlainText(
                    stream.readAll());

                 file->close();

                 disableSave(true);

                 ui->statusbar->showMessage("File " + file->fileName() +
                    " has been opened in read-only mode.");

             }
             else //!open
                 QMessageBox::warning(this, "File not found",
                    "Can't open file " + filePath);

         }
    }

}


void MainWindow::on_actionSave_triggered()
{
    if (file->isOpen())
    {
        QTextStream stream(file);

        stream << ui->plainTextEdit->toPlainText();

        ui->statusbar->showMessage("File " + file->fileName() +
            " has been saved.");

    }
    else
        //на случай, если юзер захочет вывести help-text
        //в файл, а также создать новый текст и сохранить его
        on_actionSaveAs_triggered();
}



void MainWindow::on_actionSaveAs_triggered()
{
    if (file->isOpen()) file->close();

    QString filePath { QFileDialog::getSaveFileName(this,
         "Save file as", QDir::current().path(),
            trUtf8("Text file(*.txt)")) };

    if (filePath.length())
    {
        QString ext { QString { &(filePath.data()
            [ filePath.length() - 4 ])}};

        file->setFileName(filePath);
        if (file->open(QFile::WriteOnly | QFile::NewOnly))
         {
           QTextStream stream(file);

           stream << ui->plainTextEdit->toPlainText();

           ui->statusbar->showMessage("File saved as " + file->fileName() + '.');
         }
        else //!open
        {
        QMessageBox::warning(this, "File not found",
             "Can't open file " + filePath);

        }

    }
}


void MainWindow::on_actionExit_triggered()
{
   QApplication::quit();
}


void MainWindow::on_actionHelp_triggered()
{

    if (file->isOpen()) file->close();

    QString filePath { ":help.txt" };

    file->setFileName(filePath);
    if (file->open(QFile::ReadOnly | QFile::ExistingOnly))
    {
     QTextStream stream(file);

     ui->plainTextEdit->setPlainText(stream.readAll());

     ui->statusbar->showMessage("Help is shown.");

     file->close();
    }
    else
        QMessageBox::warning(this, "File not found",
            "Can't open resource " + filePath);
}



void MainWindow::on_actionClose_triggered()
{
   if (file->isOpen())
       file->close();

   disableSave(false);

   ui->plainTextEdit->clear();

   ui->statusbar->clearMessage();
}

void MainWindow::disableSave(bool disableIt)
{
    if(disableIt)
    {
        ui->actionSave->setEnabled(false);
        ui->actionSaveAs->setEnabled(false);
    }
    else
    {
        ui->actionSave->setEnabled(true);
        ui->actionSaveAs->setEnabled(true);

    }
}

