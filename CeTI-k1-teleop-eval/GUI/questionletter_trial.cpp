#include "questionletter_trial.h"
#include "ui_questionletter_trial.h"
#include "selecttask.h"
#include "ui_selecttask.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "endstiffness.h"
#include "ui_endstiffness.h"
#include "endpaint.h"
#include "ui_endpaint.h"
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>
#include <QProcess>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "config.h"
#include "QSettings"
#include <QPaintEvent>
#include <QPainter>
#include <unistd.h>


questionletter_trial::questionletter_trial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::questionletter_trial)
{
    // Set position of the windows on screen
    QList<QScreen*> screens = qApp->screens();
    QRect screenGeometry = screens.at(0)->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();

    ui->setupUi(this);

    int pos_x = width/2;
    int pos_y = 0;

    setGeometry(pos_x,pos_y,width/2,height);

    // Background & Logos
    whiteboard.load("../GUI/pictures/whiteboard.png");
    logos.load("../GUI/pictures/CeTi_TUM_Logo_images.png");

}

void questionletter_trial::paintEvent(QPaintEvent *)
{

    // Set position of the windows on screen
    QList<QScreen*> screens = qApp->screens();
    QRect screenGeometry = screens.at(0)->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();


    int xframe = ((width/2 - ui->frame->width()) / 2);
    int yframe = 0;

    int xlogo = (width/2 - ui->frame_2->width()) / 2;
    int ylogo = (height - (ui->frame_2->height() *2));

    ui->frame->setGeometry(xframe, yframe, ui->frame->width(),ui->frame->height());
    ui->frame_2->setGeometry(xlogo, ylogo, ui->frame_2->width(),ui->frame_2->height()); //Bottom Logo

    QPainter painter1(this);
    //int x1 = ui->frame->pos().x();
    //int y1 = ui->frame->pos().y();
    painter1.drawPixmap(0,0,width,height, whiteboard);

    QPainter painter2(this);
    //int x2 = ui->frame_2->pos().x();
    //int y2 = ui->frame_2->pos().y();
    painter2.drawPixmap(xlogo,ylogo,ui->frame_2->width(),ui->frame_2->height(), logos);

   }

questionletter_trial::~questionletter_trial()
{
    delete ui;
}

void questionletter_trial::receivelogin(){
    this->show();
}

void questionletter_trial::on_TryAgain_clicked()
{

    // Kill the old slave running
    system ("taskkill /T /F /IM HapticSlave.exe");

    // Wait till slave is killed
    usleep(1000000);

    // Read Parameters from Config file
    ConfigFile cfg("../Paint_VE_2Device_GravityCompensated/Slave/bin/win-x64/cfg/config.cfg");
    std::string Username = cfg.getValueOfKey<std::string>("UserName");
    double ForceDeadbandParameter = cfg.getValueOfKey<double>("ForceDeadbandParameter");
    double VelocityDeadbandParameter = cfg.getValueOfKey<double>("VelocityDeadbandParameter");
    double ForceDelay = cfg.getValueOfKey<double>("ForceDelay");
    double CommandDelay = cfg.getValueOfKey<double>("CommandDelay");
    double TDPAon = cfg.getValueOfKey<double>("TDPAon");
    double FlagVelocityKalmanFilter = cfg.getValueOfKey<double>("FlagVelocityKalmanFilter");
    std::string IP_master = cfg.getValueOfKey<std::string>("MasterIP");
    std::string IP_slave = cfg.getValueOfKey<std::string>("SlaveIP");

    // Convert to QString
    QString UsernameAsString = QString::fromUtf8(Username.c_str());
    QString ForceDeadbandParameterAsString = QString::number(ForceDeadbandParameter);
    QString VelocityDeadbandParameterAsString = QString::number(VelocityDeadbandParameter);
    QString ForceDelayAsString = QString::number(ForceDelay);
    QString CommandDelayAsString = QString::number(CommandDelay);
    QString TDPAonAsString = QString::number(TDPAon);
    QString FlagVelocityKalmanFilterAsString = QString::number(FlagVelocityKalmanFilter);

    // Output in csv File
    QFile filecsv("../GUI/SurveyUserAnswers/" + UsernameAsString + "_paint_answers_trial.csv");
    QTextStream csvout(&filecsv);
    QString accuracy, difficulty, rating, distortion;
    if (filecsv.open(QFile::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        // 1 to 9 stiffness levels for springs yellow and red
        rating = ui->spinBox->text();
        accuracy = ui->spinBox_2->text();
        difficulty = ui->spinBox_3->text();
        distortion = ui->spinBox_4->text();

        csvout << ForceDeadbandParameterAsString << "," << VelocityDeadbandParameterAsString <<"," << ForceDelayAsString << ","
               << CommandDelayAsString <<"," << FlagVelocityKalmanFilterAsString << "," <<  TDPAonAsString << "," << rating << "," << distortion << ","
               << accuracy << "," << difficulty <<  Qt::endl;
    }
    filecsv.close();
    qDebug() << "Answers Saved";

    // Start the task
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

}

void questionletter_trial::on_MainMenu_clicked()
{

    // Kill the old slave running
    system ("taskkill /T /F /IM HapticSlave.exe");

    // Wait till slave is killed
    usleep(1000000);

    // Read Parameters from Config file
    ConfigFile cfg("../Paint_VE_2Device_GravityCompensated/Slave/bin/win-x64/cfg/config.cfg");
    std::string Username = cfg.getValueOfKey<std::string>("UserName");
    double ForceDeadbandParameter = cfg.getValueOfKey<double>("ForceDeadbandParameter");
    double VelocityDeadbandParameter = cfg.getValueOfKey<double>("VelocityDeadbandParameter");
    double ForceDelay = cfg.getValueOfKey<double>("ForceDelay");
    double CommandDelay = cfg.getValueOfKey<double>("CommandDelay");
    double TDPAon = cfg.getValueOfKey<double>("TDPAon");
    double FlagVelocityKalmanFilter = cfg.getValueOfKey<double>("FlagVelocityKalmanFilter");
    std::string IP_master = cfg.getValueOfKey<std::string>("MasterIP");
    std::string IP_slave = cfg.getValueOfKey<std::string>("SlaveIP");

    // Convert to QString
    QString UsernameAsString = QString::fromUtf8(Username.c_str());
    QString ForceDeadbandParameterAsString = QString::number(ForceDeadbandParameter);
    QString VelocityDeadbandParameterAsString = QString::number(VelocityDeadbandParameter);
    QString ForceDelayAsString = QString::number(ForceDelay);
    QString CommandDelayAsString = QString::number(CommandDelay);
    QString TDPAonAsString = QString::number(TDPAon);
    QString FlagVelocityKalmanFilterAsString = QString::number(FlagVelocityKalmanFilter);

    // Output in csv File
    QFile filecsv("../GUI/SurveyUserAnswers/" + UsernameAsString + "_paint_answers_trial.csv");
    QTextStream csvout(&filecsv);
    QString accuracy, difficulty, rating, distortion;
    if (filecsv.open(QFile::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        // 1 to 9 stiffness levels for springs yellow and red
        rating = ui->spinBox->text();
        accuracy = ui->spinBox_2->text();
        difficulty = ui->spinBox_3->text();
        distortion = ui->spinBox_4->text();

        csvout << ForceDeadbandParameterAsString << "," << VelocityDeadbandParameterAsString <<"," << ForceDelayAsString << ","
               << CommandDelayAsString <<"," << FlagVelocityKalmanFilterAsString << "," <<  TDPAonAsString << "," << rating << "," << distortion << ","
               << accuracy << "," << difficulty <<  Qt::endl;
            }
    filecsv.close();
    qDebug() << "Answers Saved";

    // Send signal to close master
    QFile file_m_restart("../Paint_VE_2Device_GravityCompensated/Slave/bin/win-x64/cfg/m_restart.cfg");
    if(file_m_restart.open(QIODevice::ReadWrite | QIODevice::Text))
    {

        //Write parameters on config.cfg (original values)
        QTextStream conf(&file_m_restart);
        conf << "m_restart = " << 2 << ";"<< Qt::endl << Qt::endl;

    }
    // close the config file
    file_m_restart.close();

    // Showing Start Task UI and closing Questionnaire UI
    //this->hide();
    //emit showSelecttask();

    // Close the trial task & questionnaire and go back to main menu
    this->close();
    SelectTask selecttask1;
    selecttask1.setModal(true);
    selecttask1.showMaximized();

    selecttask1.exec();
}
