#include "questionletter.h"
#include "ui_questionletter.h"
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

/*
// Parameter randomization
double deadbandset_letter[5] ={0.0, 0.05, 0.1, 0.2, 0.3};
double timedelayset_letter[5] ={0, 50, 100, 150, 200};
int setsize_letter = 25;   // total number of combinations
int deadbandset_size_letter = (sizeof(deadbandset_letter)/sizeof(*deadbandset_letter));
int timedelayset_size_letter = (sizeof(timedelayset_letter)/sizeof(*timedelayset_letter));
bool paramlist_letter[25] = {0}; // set all to 0
*/

// Parameter randomization -- Testing --
double deadbandset_letter[1] ={0.1};
double timedelayset_letter[2] ={50, 200};
double nbtrialsset_letter[5] = {1, 2, 3, 4, 5};
int deadbandset_size_letter = (sizeof(deadbandset_letter)/sizeof(*deadbandset_letter));
int timedelayset_size_letter = (sizeof(timedelayset_letter)/sizeof(*timedelayset_letter));
int nbtrialsset_letter_size = (sizeof(nbtrialsset_letter)/sizeof(*nbtrialsset_letter));
int setsize_letter = deadbandset_size_letter*timedelayset_size_letter*nbtrialsset_letter_size;   // total number of combinations
bool paramlist_letter[10] = {0}; // set all to 0


questionletter::questionletter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::questionletter)
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

void questionletter::paintEvent(QPaintEvent *)
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

questionletter::~questionletter()
{
    delete ui;
}

void questionletter::receivelogin(){
    this->show();
}

void questionletter::on_NextButton_clicked()
{

    // Kill the old slave running
    system ("taskkill /T /IM HapticSlave.exe");

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
        double RepetitionNum = cfg.getValueOfKey<double>("Repetition");
        double FlagVelocityKalmanFilter = cfg.getValueOfKey<double>("FlagVelocityKalmanFilter");
        std::string IP_master = cfg.getValueOfKey<std::string>("MasterIP");
        std::string IP_slave = cfg.getValueOfKey<std::string>("SlaveIP");

        // Convert to QString
        QString UsernameAsString = QString::fromUtf8(Username.c_str());
        QString ForceDeadbandParameterAsString = QString::number(ForceDeadbandParameter);
        QString VelocityDeadbandParameterAsString = QString::number(VelocityDeadbandParameter);
        QString ForceDelayAsString = QString::number(ForceDelay);
        QString CommandDelayAsString = QString::number(CommandDelay);
        QString RepetitionNumAsString = QString::number(RepetitionNum);
        QString TDPAonAsString = QString::number(TDPAon);
        QString FlagVelocityKalmanFilterAsString = QString::number(FlagVelocityKalmanFilter);

        // Output in csv File
        QFile filecsv("../GUI/SurveyUserAnswers/" + UsernameAsString + "_paint_answers.csv");
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
                   << CommandDelayAsString <<"," << FlagVelocityKalmanFilterAsString << "," <<  TDPAonAsString <<","
                   << RepetitionNumAsString << "," << rating << "," << distortion << "," << accuracy << "," << difficulty <<  Qt::endl;
        }
        filecsv.close();
        qDebug() << "Answers Saved";


    /*////////////////////////////////////////////////////////////////*/

    // Get UserName from config file
    ConfigFile cfg_("../Paint_VE_2Device_GravityCompensated/Slave/bin/win-x64/cfg/config.cfg");
    std::string Username_ = cfg_.getValueOfKey<std::string>("UserName");
    QString Username_Qstring = QString::fromUtf8(Username_.c_str());

    // Config file
    QFile fileconfig("../Paint_VE_2Device_GravityCompensated/Slave/bin/win-x64/cfg/config.cfg");

    if(fileconfig.open(QIODevice::ReadWrite | QIODevice::Text))
    {

        // Parameter Randomization //
        srand(time(NULL));
        int random_param = rand() % setsize_letter;

        // Check if all parameters have been performed
        int checksum=0;
        for (int i=0; i<setsize_letter; ++i){
            if(paramlist_letter[i] == true){
                checksum = checksum+1;
            }
        }
        if(checksum == setsize_letter){
            qDebug() << "All parameters completed";

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


            // To-Do: Task completed go back to main menu
            this->hide();
            endpaint endpaint;
            endpaint.setModal(true);
            endpaint.showMaximized();
            endpaint.exec();
        }

        // If that random param tested before get the new one
        while (paramlist_letter[random_param] == true) {
            random_param = rand() % setsize_letter;
        }

        // Update paramlist
        paramlist_letter[random_param] = true;

        // Get parameters

        int k = floor(random_param/(timedelayset_size_letter*nbtrialsset_letter_size));   // Select deadband
        int i = floor((random_param-k*timedelayset_size_letter*nbtrialsset_letter_size)/(nbtrialsset_letter_size)); // Select time delay
        int j = random_param-k*timedelayset_size_letter*nbtrialsset_letter_size - i*nbtrialsset_letter_size; // Select time delay
        double deadband = deadbandset_letter[k];
        double delay = timedelayset_letter[i];
        double repetition = nbtrialsset_letter[j];


        qDebug() << "Random param: "<< random_param;

        //Write parameters on config.cfg (original values)
        QTextStream conf(&fileconfig);
        conf << "UserName = " << Username_Qstring << ";"<< Qt::endl << Qt::endl;
        conf << "RecordSignals = " << 1 << ";"<< Qt::endl << Qt::endl;
        conf << "ForceDeadbandParameter = " << deadband << ";"<< Qt::endl << Qt::endl;
        conf << "VelocityDeadbandParameter = " << deadband << ";" << Qt::endl << Qt::endl;
        conf << "PositionDeadbandParameter   = " << deadband << ";" << Qt::endl << Qt::endl;
        conf << "ForceDelay = " << delay<< ";" << Qt::endl << Qt::endl;
        conf << "CommandDelay = " << delay<< ";" << Qt::endl << Qt::endl;
        conf << "MasterIP   = " << "192.168.0.2"<< ";" << Qt::endl << Qt::endl;
        conf << "SlaveIP   = " << "192.168.0.1" << ";"<< Qt::endl << Qt::endl;
        conf << "TDPAon = " << 1 << ";"<< Qt::endl << Qt::endl;
        conf << "Repetition = " << repetition << ";"<< Qt::endl << Qt::endl;
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




}

void questionletter::on_Repeat_clicked()
{

    // Kill the old slave running
    system ("taskkill /T /IM HapticSlave.exe");

    // Wait till slave is killed
    usleep(1000000);


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

void questionletter::on_Pause_clicked()
{

    // Kill the old slave running
    system ("taskkill /T /IM HapticSlave.exe");

    // Wait till slave is killed
    usleep(1000000);


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

}
