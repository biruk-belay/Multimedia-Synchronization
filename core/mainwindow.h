#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "assemble_all.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
};

void out ();
void delay( int millisecondsToWait );
#endif // MAINWINDOW_H
