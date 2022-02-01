#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_3_triggered();

    void on_actionOpen_read_only_mode_2_triggered();

    void on_actionSave_2_triggered();

    void on_actionExit_2_triggered();

    void on_actionHelp_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
