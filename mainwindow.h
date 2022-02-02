#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QVector>
#include <functional>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


struct KeyBind {
    Qt::KeyboardModifier mod1;
    Qt::KeyboardModifier mod2;
    Qt::Key key;
   // int keyCode;

};
//struct KeyBind;

class MainWindow : public QMainWindow
{

    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionOpen_read_only_mode_triggered();

    void on_actionSaveAs_triggered();

    void on_actionExit_triggered();

    void on_actionHelp_triggered();

    void on_actionSave_triggered();

    void on_actionClose_triggered();

    void on_actionRussian_triggered();

    void on_actionEnglish_triggered();

    void on_actionKey_bindings_triggered();

private:
    Ui::MainWindow *ui;
    QFile *file;

    bool canSave;
    void disableSave(bool);

    QVector<KeyBind> keys;

protected:
    void keyReleaseEvent(QKeyEvent*) override;

};

/*
struct KeyBind {
    Qt::KeyboardModifier mod1;
    Qt::KeyboardModifier mod2;
    Qt::Key key;
//    void (MainWindow::*action)(void);
    std::function<void> MainWindow::*action();

};
*/

//struct KeyBind {
  //  Qt::KeyboardModifier mod1;
   // Qt::KeyboardModifier mod2;
  //  int keyCode;
//    void (*action)();
//    std::function<void> action()const;
//    void (MainWindow::*action)();
//    std::function<void()> MainWindow::*action();
//    void (MainWindow::*action)(void);

//};

#endif // MAINWINDOW_H
