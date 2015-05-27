#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMultimedia>
#include <QMediaPlayer>
#include "assemble_all.h"
#include <QString>
#include <sstream>
#include <QTime>
#include <QDebug>
//std::string std_str;
void delay( int millisecondsToWait );

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QMediaPlayer    player;
QMediaPlayer player2;
static std::string std_str;

void MainWindow::on_pushButton_clicked()
{
    player.stop();
    float number;
    std::istringstream iss(std_str);
    iss >> number ;

    int num = number *1000;
    player.setMedia(QUrl::fromLocalFile("Zigzan.wav"));
    player.setVolume(100);
    player.play();

    delay(num+2);
    qDebug() << num << endl;
    player2.setMedia(QUrl::fromLocalFile("Zigzan_69.wav"));
    player2.setVolume(100);
    player2.play();
}

void delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

void out () {

    std_str = run_all();
}

void MainWindow::on_pushButton_2_clicked()
{


    QString str = QString::fromStdString(std_str) ;
    ui->textEdit->setText("the delay is " + str);
    player.stop();
    player2.stop();
}

void MainWindow::on_pushButton_3_clicked()
{
    player2.stop();
    float number;
    std::istringstream iss(std_str);
    iss >> number ;

    int num = number *1000;
    player.setMedia(QUrl::fromLocalFile("Zigzan.wav"));
    player.setVolume(100);
    player.play();


    qDebug() << num << endl;
    player2.setMedia(QUrl::fromLocalFile("Zigzan_69.wav"));
    player2.setVolume(100);
    player2.play();
}
