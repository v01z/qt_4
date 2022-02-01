#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTranslator>

const QString FILE_NOT_FOUND { QObject::tr("Файл не найден") };
const QString TXT_FILE_ONLY { QObject::tr ("Текстовый файл(*.txt)") };
const QString CHOOSE_FILE_TO_OPEN { QObject::tr("Выберите файл для открытия") };
const QString CANT_OPEN_FILE { QObject::tr("Не могу открыть файл ") };
const QString FILE_SPACE { QObject::tr("Файл ") };

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      file(new QFile())
{
    ui->setupUi(this);

    setWindowTitle(tr("Домашняя работа №4"));

    ui->menuFile->setTitle(tr("Файл"));
    ui->actionOpen->setText(tr("Открыть"));
    ui->actionOpen_read_only_mode->setText(tr("Открыть только для чтения"));
    ui->actionClose->setText(tr("Закрыть"));
    ui->actionSave->setText(tr("Сохранить"));
    ui->actionSaveAs->setText(tr("Сохранить как"));
    ui->actionExit->setText(tr("Выход"));

    ui->menuSettings->setTitle(tr("Настройки"));
    ui->menuLanguage->setTitle(tr("Язык"));

    ui->actionKey_bindings->setText(tr("Сочетания клавиш"));

    ui->actionHelp->setText(tr("Помощь"));


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
        CHOOSE_FILE_TO_OPEN, QDir::current().path(),
            TXT_FILE_ONLY) };

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
                 QMessageBox::warning(this, FILE_NOT_FOUND,
                    CANT_OPEN_FILE + filePath);

         }

    }

}


void MainWindow::on_actionOpen_read_only_mode_triggered()
{

    QString filePath { QFileDialog::getOpenFileName(this,
        CHOOSE_FILE_TO_OPEN, QDir::current().path(),
            TXT_FILE_ONLY) };

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

                 ui->statusbar->showMessage(FILE_SPACE + file->fileName() +
                    tr(" открыт в режиме \'только для чтения\'."));

             }
             else //!open
                 QMessageBox::warning(this, FILE_NOT_FOUND,
                    CANT_OPEN_FILE + filePath);

         }
    }

}


void MainWindow::on_actionSave_triggered()
{
    if (file->isOpen())
    {
        QTextStream stream(file);

        stream << ui->plainTextEdit->toPlainText();

        ui->statusbar->showMessage(FILE_SPACE + file->fileName() +
            tr(" сохранён."));

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
         tr("Сохранить файл как"), QDir::current().path(),
            TXT_FILE_ONLY) };

    if (filePath.length())
    {
        QString ext { QString { &(filePath.data()
            [ filePath.length() - 4 ])}};

        file->setFileName(filePath);
        if (file->open(QFile::WriteOnly | QFile::NewOnly))
         {
           QTextStream stream(file);

           stream << ui->plainTextEdit->toPlainText();

           ui->statusbar->showMessage(tr("Файл сохранён как ") + file->fileName() + '.');
         }
        else //!open
        {
        QMessageBox::warning(this, FILE_NOT_FOUND,
             CANT_OPEN_FILE + filePath);

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

    ui->plainTextEdit->setPlainText(tr("Для открытия текстового файла нажмите \'Файл->Открыть\'.\n" \
        "Для открытия его в режимя \'только для чтения\' нажмите соответствующий пункт меню.\n" \
        "Далее более кратко:\n" \
        "\'Сохранить\' и \'Сохранить как\' - сохранить файл со старым, либо новым именем "\
        "соответственно.\n " \
        "\'Выход\' - выход из программы\n" \
        "\'Настройки->Язык\' - возможность сменить язык приложения.\n" \
        "\'Сочетания клавиш\' - изменить комбинации клавиш по вкусу.\n" \
        "\'?->Помощь\' - вывести эту справку."));


     ui->statusbar->showMessage(tr("Краткая справка показана."));

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


void MainWindow::on_actionRussian_triggered()
{
         QTranslator translator;

         QString lang { "./QtLanguage_ru" };

         translator.load(lang);

         QApplication::installTranslator(&translator);

         ui->actionEnglish->setChecked(false);
         ui->actionRussian->setChecked(true);

         ui->retranslateUi(this);

}


void MainWindow::on_actionEnglish_triggered()
{
         QTranslator translator;

         QString lang { "./QtLanguage_en" };

         translator.load(lang);

         QApplication::installTranslator(&translator);

         ui->actionEnglish->setChecked(true);
         ui->actionRussian->setChecked(false);

         ui->retranslateUi(this);
}

