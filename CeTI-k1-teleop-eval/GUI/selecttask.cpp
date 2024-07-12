#include "selecttask.h"
#include "questionstiffness.h"
#include "questionstiffness_trial.h"
#include "ui_selecttask.h"
#include "mainwindow.h"
#include "questionletter.h"
#include "questionletter_trial.h"
#include "string.h"
#include "config.h"
#include "QFrame"
#include "QLabel"
#include "QPushButton"
#include <QSettings>
#include <QtCore>
#include <QDebug>
#include <random>
#include <QPaintEvent>
#include <QPainter>
#include <unistd.h>
#include <QApplication>
#include <QtCore>
#include <QtGui>
#include <QPushButton>
#include <QGridLayout>


SelectTask::SelectTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectTask)
{
    // Set position of the windows on screen
    QList<QScreen*> screens = qApp->screens();
    QRect screenGeometry = screens.at(0)->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();

    ui->setupUi(this);

    // Center point
    int pos_x = (width - 879) / 2;
    int pos_y = (height - 585) / 2;


    setGeometry(pos_x,pos_y,width/2,height);



    whiteboard.load("../GUI/pictures/whiteboard.png");
    logos.load("../GUI/pictures/CeTi_TUM_Logo_images.png");
    stiff_image.load("../GUI/pictures/stiffness_task.png");
    paint_image.load("../GUI/pictures/paint_task.png");
}

void SelectTask::paintEvent(QPaintEvent *)
{

    // Get height and width of the windows on screen
    QList<QScreen*> screens = qApp->screens();
    QRect screenGeometry = screens.at(0)->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();

    int xframe = (width - 951) / 2;
    int yframe = (height - 621) / 2;

    int xframe_toplogo = (width - 521) / 2;
    int yframe_toplogo = height - ((height - 60));

    int xframe_leftlogo = ((width - 951) / 2) + 951/2 - 400;
    int yframe_leftlogo = (height - 201) / 2;

    int xframe_rightlogo = xframe_leftlogo + 470; //((width - 951) / 2) + 951/2 + 60;
    int yframe_rightlogo = (height - 201) / 2;

    int xframe_leftlabel = xframe_leftlogo;
    int yframe_leftlabel = yframe_leftlogo - 50;

    int xframe_rightlabel = xframe_rightlogo; //((width - 951) / 2) + 951/2 + 60;
    int yframe_rightlabel = yframe_rightlogo - 50;

    ui->frame->setGeometry(xframe, yframe, 951, 621);
    ui->frame_4->setGeometry(xframe_toplogo, yframe_toplogo, 521, 61); //Top Logo

    ui->frame_5->setGeometry(xframe_leftlogo, yframe_leftlogo, 301, 231); //Stiffness Logo
    ui->frame_2->setGeometry(xframe_rightlogo, yframe_rightlogo, 301, 231); //Letter Logo

    //ui->label_2->setGeometry(xframe_leftlabel, yframe_leftlabel, 251, 30); //Stiffness Label
    //ui->label_3->setGeometry(xframe_rightlabel, yframe_rightlabel, 251, 30); //Letter Label

    QPainter painter6(this);
    int x6 = ui->frame_6->pos().x();
    int y6 = ui->frame_6->pos().y();
    painter6.drawPixmap(x6,y6,width,height,whiteboard);
/*
    QPainter painter3(this);
    int x3 = ui->frame_3->pos().x();
    int y3 = ui->frame_3->pos().y();
    painter3.drawPixmap(x3,y3,ui->frame_3->width()*10,ui->frame_3->height()*10, whiteboard);
*/
    QPainter painter4(this);
    int x4 = ui->frame_4->pos().x();
    int y4 = ui->frame_4->pos().y();
    painter4.drawPixmap(x4,y4,ui->frame_4->width(),ui->frame_4->height(), logos);

    QPainter painter5(this);
    int x5 = ui->frame_5->pos().x();
    int y5 = ui->frame_5->pos().y();
    painter5.drawPixmap(x5,y5,ui->frame_5->width(),ui->frame_5->height(), stiff_image);
    QPainter painter2(this);
    int x2 = ui->frame_2->pos().x();
    int y2 = ui->frame_2->pos().y();
    painter2.drawPixmap(x2,y2,ui->frame_2->width(),ui->frame_2->height(), paint_image);

}

SelectTask::~SelectTask()
{
    delete ui;
}

void SelectTask::receivelogin()
{

    this->show();
}

/////////////////////////////////////////////////////////////////////
/// \brief SelectTask::on_tryStiff_clicked
/////////////////////////////////////////////////////////////////////

void SelectTask::on_tryStiff_clicked()
{

    // Kill the old slave running
    system ("taskkill /T /F /IM HapticSlave.exe");

    // Wait till slave is killed
    usleep(1000000);

    // Get UserName from config file
    ConfigFile cfg_("../StiffnessDiscrimination_VE_2Device/Slave/bin/win-x64/cfg/config.cfg");
    std::string Username_ = cfg_.getValueOfKey<std::string>("UserName");
    QString Username_Qstring = QString::fromUtf8(Username_.c_str());

    // Open config file to write parameters
    QFile fileconfig("../StiffnessDiscrimination_VE_2Device/Slave/bin/win-x64/cfg/config.cfg");
    if(fileconfig.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        //Write parameters on config.cfg (original values)
        QTextStream conf(&fileconfig);
        conf << "UserName = " << Username_Qstring << ";"<< Qt::endl << Qt::endl;
        conf << "RecordSignals = " << 1 << ";"<< Qt::endl << Qt::endl;
        conf << "ForceDeadbandParameter = " << 0 << ";"<< Qt::endl << Qt::endl;
        conf << "VelocityDeadbandParameter = " << 0 << ";" << Qt::endl << Qt::endl;
        conf << "ForceDelay = " << 0  << ";" << Qt::endl << Qt::endl;
        conf << "CommandDelay = " << 0 << ";" << Qt::endl << Qt::endl;
        conf << "FlagVelocityKalmanFilter    = " << 0 << ";"<< Qt::endl << Qt::endl;
        conf << "MasterIP   = " << "192.168.0.2"<< ";" << Qt::endl << Qt::endl;
        conf << "SlaveIP   = " << "192.168.0.1" << ";"<< Qt::endl << Qt::endl;
        conf << "TDPAon = " << 1 << ";"<< Qt::endl << Qt::endl;
        conf << "RefStiffness = " << 60 << ";"<< Qt::endl << Qt::endl;
        conf << "start_x = " << 0.0 << ";"<< Qt::endl << Qt::endl;
        conf << "start_y = " << -0.12 << ";"<< Qt::endl << Qt::endl;
        conf << "start_z = " << 0.01 << ";"<< Qt::endl << Qt::endl;
    }
    // close the config file
    fileconfig.close();

    qDebug() << "Starting Task...";
    system("cd ../StiffnessDiscrimination_VE_2Device/Slave/bin/win-x64 && start HapticSlave.exe");

    // Send signal to start master
    QFile file_m_restart("../StiffnessDiscrimination_VE_2Device/Slave/bin/win-x64/cfg/m_restart.cfg");
    if(file_m_restart.open(QIODevice::ReadWrite | QIODevice::Text))
    {

        //Write parameters on config.cfg (original values)
        QTextStream conf(&file_m_restart);
        conf << "m_restart = " << 1 << ";"<< Qt::endl << Qt::endl;

    }
    // close the config file
    file_m_restart.close();


    // Close the select task window and open questions
    this->close();
    questionstiffness_trial questionstiffness_trial;
    questionstiffness_trial.setModal(true);
    questionstiffness_trial.exec();

}

/////////////////////////////////////////////////////////////////////
/// \brief SelectTask::on_tryLetter_clicked
/////////////////////////////////////////////////////////////////////
void SelectTask::on_tryLetter_clicked()
{
    // Kill the old slave running
    system ("taskkill /T /F /IM HapticSlave.exe");

    // Wait till slave is killed
    usleep(1000000);

    // Get UserName from config file
    ConfigFile cfg_("../Paint_VE_2Device_GravityCompensated/Slave/bin/win-x64/cfg/config.cfg");
    std::string Username_ = cfg_.getValueOfKey<std::string>("UserName");
    QString Username_Qstring = QString::fromUtf8(Username_.c_str());

    // Open config file to write parameters
    QFile fileconfig("../Paint_VE_2Device_GravityCompensated/Slave/bin/win-x64/cfg/config.cfg");
    if(fileconfig.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        //Write parameters on config.cfg (original values)
        QTextStream conf(&fileconfig);
        conf << "UserName = " << Username_Qstring << ";"<< Qt::endl << Qt::endl;
        conf << "RecordSignals = " << 1 << ";"<< Qt::endl << Qt::endl;
        conf << "ForceDeadbandParameter = " << 0 << ";"<< Qt::endl << Qt::endl;
        conf << "VelocityDeadbandParameter = " << 0 << ";" << Qt::endl << Qt::endl;
        conf << "ForceDelay = " << 0 << ";" << Qt::endl << Qt::endl;
        conf << "CommandDelay = " << 0 << ";" << Qt::endl << Qt::endl;
        conf << "FlagVelocityKalmanFilter    = " << 0 << ";"<< Qt::endl << Qt::endl;
        conf << "MasterIP   = " << "192.168.0.2"<< ";" << Qt::endl << Qt::endl;
        conf << "SlaveIP   = " << "192.168.0.1" << ";"<< Qt::endl << Qt::endl;
        conf << "TDPAon = " << 1 << ";"<< Qt::endl << Qt::endl;
        conf << "start_x = " << -0.05 << ";"<< Qt::endl << Qt::endl;
        conf << "start_y = " << 0.01 << ";"<< Qt::endl << Qt::endl;
        conf << "start_z = " << 0.025 << ";"<< Qt::endl << Qt::endl;
    }
    // close the config file
    fileconfig.close();

    qDebug() << "Starting Task...";
    system("cd ../Paint_VE_2Device_GravityCompensated/Slave/bin/win-x64 && start HapticSlave.exe");

    // Send signal to start master
    QFile file_m_restart("../Paint_VE_2Device_GravityCompensated/Slave/bin/win-x64/cfg/m_restart.cfg");
    if(file_m_restart.open(QIODevice::ReadWrite | QIODevice::Text))
    {

        //Write parameters on config.cfg (original values)
        QTextStream conf(&file_m_restart);
        conf << "m_restart = " << 1 << ";"<< Qt::endl << Qt::endl;

    }
    // close the config file
    file_m_restart.close();

    // Close the select task window and open questions
    this->close();
    questionletter_trial questionletter_trial;
    questionletter_trial.setModal(true);
    questionletter_trial.exec();
}

/////////////////////////////////////////////////////////////////////
/// \brief SelectTask::on_StartStiffnessButton_clicked
/////////////////////////////////////////////////////////////////////

void SelectTask::on_StartStiffnessButton_clicked()
{

    // Kill the old slave running
    system ("taskkill /T /F /IM HapticSlave.exe");

    // Wait till slave is killed
    usleep(1000000);

    // Get UserName from config file
    ConfigFile cfg_("../StiffnessDiscrimination_VE_2Device/Slave/bin/win-x64/cfg/config.cfg");
    std::string Username_ = cfg_.getValueOfKey<std::string>("UserName");
    QString Username_Qstring = QString::fromUtf8(Username_.c_str());

    // Config file
    QFile fileconfig("../StiffnessDiscrimination_VE_2Device/Slave/bin/win-x64/cfg/config.cfg");
    if(fileconfig.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        //Write parameters on config.cfg (original values)
        QTextStream conf(&fileconfig);
        conf << "UserName = " << Username_Qstring << ";"<< Qt::endl << Qt::endl;
        conf << "RecordSignals = " << 1 << ";"<< Qt::endl << Qt::endl;
        conf << "ForceDeadbandParameter = " << 0 << ";"<< Qt::endl << Qt::endl;
        conf << "VelocityDeadbandParameter = " << 0 << ";" << Qt::endl << Qt::endl;
        conf << "ForceDelay = " << 0 << ";" << Qt::endl << Qt::endl;
        conf << "CommandDelay = " << 0 << ";" << Qt::endl << Qt::endl;
        conf << "FlagVelocityKalmanFilter    = " << 0 << ";"<< Qt::endl << Qt::endl;
        conf << "MasterIP   = " << "192.168.0.2"<< ";" << Qt::endl << Qt::endl;
        conf << "SlaveIP   = " << "192.168.0.1" << ";"<< Qt::endl << Qt::endl;
        conf << "TDPAon = " << 1 << ";"<< Qt::endl << Qt::endl;
        conf << "RefStiffness = " << 60 << ";"<< Qt::endl << Qt::endl;
        conf << "Repetition = " << 1 << ";"<< Qt::endl << Qt::endl;
        conf << "start_x = " << 0.0 << ";"<< Qt::endl << Qt::endl;
        conf << "start_y = " << -0.12 << ";"<< Qt::endl << Qt::endl;
        conf << "start_z = " << 0.01 << ";"<< Qt::endl << Qt::endl;
    }
    // close the config file
    fileconfig.close();

    qDebug() << "Starting Task...";
    system("cd ../StiffnessDiscrimination_VE_2Device/Slave/bin/win-x64 && start HapticSlave.exe");


    // Wait a little to start master
    usleep(100000);

    // Send signal to start master
    QFile file_m_restart("../StiffnessDiscrimination_VE_2Device/Slave/bin/win-x64/cfg/m_restart.cfg");
    if(file_m_restart.open(QIODevice::ReadWrite | QIODevice::Text))
    {

        //Write parameters on config.cfg (original values)
        QTextStream conf(&file_m_restart);
        conf << "m_restart = " << 1 << ";"<< Qt::endl << Qt::endl;

    }
    // close the config file
    file_m_restart.close();

    // Close the select task window and open questions
    this->close();
    questionstiffness questionstiffness;
    questionstiffness.setModal(true);
    questionstiffness.exec();

}

/////////////////////////////////////////////////////////////////////
/// \brief SelectTask::on_StartLetterButton_clicked
/////////////////////////////////////////////////////////////////////

void SelectTask::on_StartLetterButton_clicked()
{
    // Kill the old slave running
    system ("taskkill /T /IM HapticSlave.exe");

    // Wait till slave is killed
    usleep(1000000);

    // Get UserName from config file
    ConfigFile cfg_("../Paint_VE_2Device_GravityCompensated/Slave/bin/win-x64/cfg/config.cfg");
    std::string Username_ = cfg_.getValueOfKey<std::string>("UserName");
    QString Username_Qstring = QString::fromUtf8(Username_.c_str());

    // Open config file to write parameters
    QFile fileconfig("../Paint_VE_2Device_GravityCompensated/Slave/bin/win-x64/cfg/config.cfg");
    if(fileconfig.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        //Write parameters on config.cfg (original values)
        QTextStream conf(&fileconfig);
        conf << "UserName = " << Username_Qstring << ";"<< Qt::endl << Qt::endl;
        conf << "RecordSignals = " << 1 << ";"<< Qt::endl << Qt::endl;
        conf << "ForceDeadbandParameter = " << 0 << ";"<< Qt::endl << Qt::endl;
        conf << "VelocityDeadbandParameter = " << 0 << ";" << Qt::endl << Qt::endl;
        conf << "ForceDelay = " << 0 << ";" << Qt::endl << Qt::endl;
        conf << "CommandDelay = " << 0 << ";" << Qt::endl << Qt::endl;
        conf << "FlagVelocityKalmanFilter    = " << 0 << ";"<< Qt::endl << Qt::endl;
        conf << "MasterIP   = " << "192.168.0.2"<< ";" << Qt::endl << Qt::endl;
        conf << "SlaveIP   = " << "192.168.0.1" << ";"<< Qt::endl << Qt::endl;
        conf << "TDPAon = " << 1 << ";"<< Qt::endl << Qt::endl;
        conf << "Repetition = " << 1 << ";"<< Qt::endl << Qt::endl;
        conf << "start_x = " << -0.05 << ";"<< Qt::endl << Qt::endl;
        conf << "start_y = " << 0.01 << ";"<< Qt::endl << Qt::endl;
        conf << "start_z = " << 0.025 << ";"<< Qt::endl << Qt::endl;
    }
    // close the config file
    fileconfig.close();

    qDebug() << "Starting Task...";
    system("cd ../Paint_VE_2Device_GravityCompensated/Slave/bin/win-x64 && start HapticSlave.exe");

    // Wait a little to start master
    usleep(100000);

    // Send signal to start master
    QFile file_m_restart("../Paint_VE_2Device_GravityCompensated/Slave/bin/win-x64/cfg/m_restart.cfg");
    if(file_m_restart.open(QIODevice::ReadWrite | QIODevice::Text))
    {

        //Write parameters on config.cfg (original values)
        QTextStream conf(&file_m_restart);
        conf << "m_restart = " << 1 << ";"<< Qt::endl << Qt::endl;

    }
    // close the config file
    file_m_restart.close();

    // Close the select task window and open questions
    this->close();
    questionletter questionletter;
    questionletter.setModal(true);
    questionletter.exec();

}



