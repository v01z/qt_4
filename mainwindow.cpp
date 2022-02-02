#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTranslator>
#include "keybinddialog.h"
#include <QDebug>

const QString FILE_NOT_FOUND { QObject::tr("Файл не найден") };
const QString TXT_FILE_ONLY { QObject::tr ("Текстовый файл(*.txt)") };
const QString CHOOSE_FILE_TO_OPEN { QObject::tr("Выберите файл для открытия") };
const QString CANT_OPEN_FILE { QObject::tr("Не могу открыть файл ") };
const QString FILE_SPACE { QObject::tr("Файл ") };

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      file(new QFile()), canSave(true)
{
    //keys.push_back( KeyBind(Qt::ControlModifier, nullptr, Qt::Key_O,
//    keys.push_back( KeyBind(Qt::ControlModifier, Qt::ShiftModifier, Qt::Key_O,
    //keys.push_back((this->*on_actionOpen_triggered)());
//        on_actionOpen_triggered()));
    //keys.push_back((*on_actionOpen_triggered)());
    //keys.push_back((this->*on_actionOpen_triggered)());

    keys.push_back( {Qt::ControlModifier, Qt::NoModifier, Qt::Key_O,
                    this->*on_actionOpen_triggered
                    } );

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
    ui->actionRussian->setText(tr("Русский"));
    ui->actionEnglish->setText(tr("Английский"));

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
//             if (file->open(QFile::ReadWrite | QFile::ExistingOnly | QIODevice::Truncate | QIODevice::Text))
             if (file->open(QFile::ReadWrite | QFile::ExistingOnly))
             {
                 QTextStream stream(file);

                 disableSave(false);

                 ui->plainTextEdit->setPlainText(
                    stream.readAll());

                 ui->actionClose->setEnabled(true);
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

                 ui->actionClose->setEnabled(true);

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
     //   QTextStream stream(file, QIODevice::ReadWrite | QIODevice::Truncate);
//        QTextStream stream(file, QIODevice::ReadWrite | QIODevice::Truncate);

        //file.write(mystring.toUtf8());
        stream << ui->plainTextEdit->toPlainText();

        //works like <<
        /*
        file->write(ui->plainTextEdit->toPlainText().toUtf8(),
            ui->plainTextEdit->toPlainText().toUtf8().length());
            */

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

   ui->actionClose->setEnabled(false);

   ui->statusbar->clearMessage();
}

void MainWindow::disableSave(bool disableIt)
{
    if(disableIt)
    {
        canSave = false;
        ui->actionSave->setEnabled(false);
        ui->actionSaveAs->setEnabled(false);
    }
    else
    {
        canSave = true;
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

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{

    if (event->modifiers().testFlag(Qt::ControlModifier))
    {
        switch (event->key())
        {
            case Qt::Key_O:
                on_actionOpen_triggered();
                break;
            case Qt::Key_R:
                if (event->modifiers().testFlag(Qt::ShiftModifier))
                    on_actionRussian_triggered();
                else
                    on_actionOpen_read_only_mode_triggered();
                break;
            case Qt::Key_X:
                on_actionClose_triggered();
                break;
            case Qt::Key_S:
                if (!canSave) break;
                if (event->modifiers().testFlag(Qt::ShiftModifier))
                    on_actionSaveAs_triggered();
                else
                    on_actionSave_triggered();
                break;
            case Qt::Key_Q:
                on_actionExit_triggered();
                break;
            case Qt::Key_E:
                if (event->modifiers().testFlag(Qt::ShiftModifier))
                    on_actionEnglish_triggered();
                break;
            case Qt::Key_H:
                on_actionHelp_triggered();
                break;
            case Qt::Key_K:
                if (event->modifiers().testFlag(Qt::ShiftModifier))
                    on_actionKey_bindings_triggered();
                break;
        }
    }

    if (event->key() == Qt::Key_F3)
        on_actionOpen_read_only_mode_triggered();
}





void MainWindow::on_actionKey_bindings_triggered()
{
    KeyBindDialog dialog;
    dialog.setModal(true);
    dialog.exec();
}

