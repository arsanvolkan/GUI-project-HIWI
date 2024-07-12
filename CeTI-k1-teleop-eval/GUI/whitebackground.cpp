#include "whitebackground.h"
#include "ui_whitebackground.h"
#include <QFrame>
#include <QPaintEvent>
#include <QPainter>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>
#include <QProcess>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <QPixmap>
#include <QFrame>
#include <QFile>

whitebackground::whitebackground(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::whitebackground)
{
    ui->setupUi(this);
    whitebackground.load("../GUI/pictures/whiteboard.png");
}

whitebackground::~whitebackground()
{
    delete ui;
}
