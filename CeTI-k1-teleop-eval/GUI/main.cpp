/***********  Haptic Communication Teleoperation Test GUI  *****************
* Software License Agreement (BSD License)                                *
*                                                                         *
*  Copyright (c) 2022,				                                      *
*  Lehrstuhl für Medientechnik                                            *
*  Technische Universität München, Germany                                *
*  All rights reserved.                                                   *
*                                                                         *
*  Redistribution and use in source and binary forms, with or without     *
*  modification, are permitted provided that the following conditions     *
*  are met:                                                               *
*                                                                         *
*  - Redistributions of source code must retain the above copyright       *
*     notice, this list of conditions and the following disclaimer.       *
*  - Redistributions in binary form must reproduce the above              *
*     copyright notice, this list of conditions and the following         *
*     disclaimer in the documentation and/or other materials provided     *
*     with the distribution.                                              *
*  - Neither the name of Technische Universität München nor the names of  *
*     its contributors may be used to endorse or promote products derived *
*     from this software without specific prior written permission.       *
*                                                                         *
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS    *
*  'AS IS' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT      *
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS      *
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE         *
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,    *
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,   *
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;       *
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER       *
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT     *
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN      *
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE        *
*  POSSIBILITY OF SUCH DAMAGE.                                            *
***************************************************************************
*
* Description : This is a demo application for a virtual haptic teleoperation
* to illustrate how the IEEE P1918.1.1 haptic codec standard works.
*
* Version 1.0 July 2022 - features:
* 1. Stiffness Discriminination & Letter Writing taks
* 2. User Info Survey & Usability Questionnaires
*
* Authors: Basak Gülecyüz, Volkan Arsan
* e-mail: basak.guelecyuez@tum.de, volkan.arsan@tum.de
*
*
* IMPORTANT NOTE: The author of this code doesn't guarantee you safety on your hardware
* even it is the same hardware configuration. It is your responsibility to take care
* of safety issues in case you copy and use this application
*/

//==============================================================================


#include "mainwindow.h"
#include "selecttask.h"
#include "questionletter.h"
#include "questionstiffness.h"
#include "questionletter_trial.h"
#include "questionstiffness_trial.h"
#include "endstiffness.h"
#include "endpaint.h"
#include "ui_endstiffness.h"
#include "background.h"
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <config.h>
#include <QFileDialog>
#include <cstdlib>
#include <QDebug>
#include <QScreen>
#include <QMainWindow>
//#include <QDesktopWidget>

//==============================================================================

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);

    // Whiteboard background
    background w0;

    //w0.setWindowState(Qt::WindowMaximized);
    //w0.showFullScreen();
    //w0.show();

    // User survey window
    //QDesktopWidget dw;
    //int x=dw.width();
    //int y=dw.height();
    //w.setFixedSize(x,y);
    MainWindow w;
    //w.showFullScreen();
    w.setWindowState(Qt::WindowMaximized);
    QObject::connect(&w0, SIGNAL(showSelecttask()), &w, SLOT(receivelogin()));
    w.show();
/*
    // Get the desktop widget
    QDesktopWidget *desktop = QApplication::desktop();
    // Get the available geometry of the primary screen
    QRect screenGeometry = desktop->availableGeometry(desktop->primaryScreen());
    // Calculate the center point of the screen
    QPoint center = screenGeometry.center();
    // Move the window to the center of the screen
    w.move(center.x() - w.width() / 2, center.y() - w.height() / 2);
*/

    //w.showFullScreen(); ---> This option limits user to exit the window (to use it, comment w.setWindowState and w.show)

    // Select Task
    SelectTask w2;
    w2.setWindowState(Qt::WindowMaximized);
    //w2.showFullScreen();
    QObject::connect(&w, SIGNAL(showSelecttask()), &w2, SLOT(receivelogin()));

    // Questionnaire for Stiffness Discrimination
    questionstiffness w3;
    QObject::connect(&w2, SIGNAL(showQuestionStiff()), &w3, SLOT(receivelogin()));
    QObject::connect(&w3, SIGNAL(showQuestionStiff()), &w2, SLOT(receivelogin()));

    // Questionnaire for Letter Writing
    questionletter w4;
    QObject::connect(&w2, SIGNAL(showQuestionLetter()), &w4, SLOT(receivelogin()));
    QObject::connect(&w4, SIGNAL(showQuestionLetter()), &w2, SLOT(receivelogin()));

    // Questionnaire for Stiffness Discrimination Trial
    questionstiffness_trial w5;
    QObject::connect(&w2, SIGNAL(showQuestionStiff()), &w5, SLOT(receivelogin()));
    QObject::connect(&w5, SIGNAL(showQuestionLetter()), &w2, SLOT(receivelogin()));

    // Questionnaire for Letter
    questionletter_trial w6;
    QObject::connect(&w2, SIGNAL(showQuestionStiff()), &w6, SLOT(receivelogin()));
    QObject::connect(&w6, SIGNAL(showQuestionLetter()), &w2, SLOT(receivelogin()));

    endpaint w7;
    w7.setWindowState(Qt::WindowMaximized);
    //w7.show();
    endstiffness w8;
    w8.setWindowState(Qt::WindowMaximized);
    //w8.show();
    // Execute code
    return a.exec();

}
