#include "background.h"
#include "ui_background.h"
#include "mainwindow.h"
#include <QDebug>
#include <random>
#include <QPaintEvent>
#include <QPainter>
#include <unistd.h>
#include <QApplication>
#include <QtCore>
#include <QtGui>
#include "string.h"
#include "config.h"
#include "QFrame"
#include "QLabel"
#include "QPushButton"
#include <QSettings>
#include <QDebug>
#include <random>
#include <QPaintEvent>
#include <QPainter>
#include <unistd.h>
#include <QtCore>
#include <QtGui>
#include <QPushButton>
#include <QGridLayout>
#include <QFileDialog>
#include <QProcess>
#include <QDialog>

background::background(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::background)
{
    ui->setupUi(this);
    whiteboard.load("../GUI/pictures/whiteboard.png");
}

void background::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    int x = ui->frame->pos().x();
    int y = ui->frame->pos().y();
    painter.drawPixmap(x,y,ui->frame->width()*100,ui->frame->height()*100, whiteboard);

}


void background::receivelogin()
{
    this->show();
}


void background::on_pushButton_clicked()
{
    // Close the background window and open mainwindow again
    this->hide();
}


background::~background()
{
    delete ui;
}
