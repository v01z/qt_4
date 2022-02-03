#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QTranslator>
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
    //Warning: Do not change the order of pushing elements. It corresponds
    //vector 'actionsIndexes' (see keybinddialog.h). To avoid mismatches the
    //vector 'keys' has to be initialized from vector 'actionsIndexes' somehow.
    keys.push_back( { Qt::ControlModifier, Qt::NoModifier, Qt::Key_O} );    // 0 - Open
    keys.push_back( { Qt::ControlModifier, Qt::ShiftModifier, Qt::Key_R} ); // 1 - Rus
    keys.push_back( { Qt::ControlModifier, Qt::NoModifier, Qt::Key_R} );	// 2 - read-only
    keys.push_back( { Qt::ControlModifier, Qt::NoModifier, Qt::Key_X} ); 	// 3 - close
    keys.push_back( { Qt::ControlModifier, Qt::ShiftModifier, Qt::Key_S} ); // 4 - save as
    keys.push_back( { Qt::ControlModifier, Qt::NoModifier, Qt::Key_S} );    // 5 - save
    keys.push_back( { Qt::ControlModifier, Qt::NoModifier, Qt::Key_Q} );    // 6 - quit
    keys.push_back( { Qt::ControlModifier, Qt::ShiftModifier, Qt::Key_E} ); // 7 - Eng
    keys.push_back( { Qt::ControlModifier, Qt::NoModifier, Qt::Key_H} );    // 8 - help
    keys.push_back( { Qt::ControlModifier, Qt::ShiftModifier, Qt::Key_K} ); // 9 - bindings

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

    bool weHaveThisKey{ false };
    int i{};

    for (; i < keys.size(); ++i)
    {
        if ((event->key() == keys[i].key) && event->modifiers().testFlag(keys[i].mod1) &&
            event->modifiers().testFlag(keys[i].mod2))

            {
                weHaveThisKey = true;
                break;
            }
        else if ((event->key() == keys[i].key) &&
                  (event->modifiers().testFlag(keys[i].mod1)) &&
                    (keys[i].mod2 == Qt::NoModifier))
            {
                weHaveThisKey = true;
                break;
            }
        else if ((event->key() == keys[i].key) &&
                  (event->modifiers().testFlag(keys[i].mod2)) &&
                    (keys[i].mod1 == Qt::NoModifier))
            {
                weHaveThisKey = true;
                break;
            }

    }

    weHaveThisKey?
                actionChoosing(i):
                ui->statusbar->showMessage(": " + event->text());
}

void MainWindow::actionChoosing(int vectorIndex)
{
    switch (vectorIndex)
    {
        case 0:
            on_actionOpen_triggered();
            break;
        case 1:
            on_actionRussian_triggered();
            break;
        case 2:
            on_actionOpen_read_only_mode_triggered();
            break;
        case 3:
            on_actionClose_triggered();
            break;
        case 4:
            on_actionSaveAs_triggered();
            break;
        case 5:
            on_actionSave_triggered();
            break;
        case 6:
            on_actionExit_triggered();
            break;
        case 7:
            on_actionEnglish_triggered();
            break;
        case 8:
            on_actionHelp_triggered();
            break;
        case 9:
            on_actionKey_bindings_triggered();
            break;
        }
}

void MainWindow::on_actionKey_bindings_triggered()
{
    KeyBindDialog dialog(&keys);
    dialog.setModal(true);
    dialog.exec();

//    qDebug() << dialog.getNewBinding().second;
    //keys.at(dialog.getNewBinding().second) = dialog.getNewBinding().first;

    keys[dialog.getNewBinding().second] = dialog.getNewBinding().first;
}

