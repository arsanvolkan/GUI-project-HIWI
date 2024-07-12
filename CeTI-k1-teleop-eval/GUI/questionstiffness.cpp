#include "questionstiffness.h"
#include "ui_questionstiffness.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "selecttask.h"
#include "ui_selecttask.h"
#include "endstiffness.h"
#include "ui_endstiffness.h"
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



// Parameter randomization
/*double deadbandset[5] ={0.0, 0.05, 0.1, 0.2, 0.3};
double timedelayset[5] ={0, 50, 100, 150, 200};
double stiffnessset [9] = {15, 30, 45, 60, 75, 90, 105, 120, 135};
QString reference_stiffness[9] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
double nbtrialsset [5] = {1, 2, 3, 4, 5};
int deadbandset_size = (sizeof(deadbandset)/sizeof(*deadbandset));
int timedelayset_size = (sizeof(timedelayset)/sizeof(*timedelayset));
int stiffness_size = (sizeof(stiffnessset)/sizeof(*stiffnessset));
int nbtrials_size = (sizeof(nbtrialsset)/sizeof(*nbtrialsset));
int setsize = deadbandset_size*timedelayset_size*stiffness_size*nbtrials_size;   // total number of combinations
bool paramlist[1125] = {0}; // set all to 0*/

double deadbandset[1] ={0.1};
double timedelayset[2] ={50, 200};
double stiffnessset[1] = {75};
QString reference_stiffness[1] = {"1"};
double nbtrialsset[5] = {1, 2, 3, 4, 5};
int deadbandset_size = (sizeof(deadbandset)/sizeof(*deadbandset));
int timedelayset_size = (sizeof(timedelayset)/sizeof(*timedelayset));
int stiffness_size = (sizeof(stiffnessset)/sizeof(*stiffnessset));
int nbtrials_size = (sizeof(nbtrialsset)/sizeof(*nbtrialsset));
int setsize = deadbandset_size*timedelayset_size*stiffness_size*nbtrials_size;   // total number of combinations
bool paramlist[10] = {0}; // set all to 0



/*
// Parameter randomization
double deadbandset[1] ={0.0};
double timedelayset[2] ={0, 50};
double stiffnessset [1] = {60};
int setsize = 2;   // total number of combinations
int deadbandset_size = (sizeof(deadbandset)/sizeof(*deadbandset));
int timedelayset_size = (sizeof(timedelayset)/sizeof(*timedelayset));
int stiffness_size = (sizeof(stiffnessset)/sizeof(*stiffnessset));
bool paramlist[2] = {0}; // set all to 0*/


questionstiffness::questionstiffness(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::questionstiffness)
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

void questionstiffness::paintEvent(QPaintEvent *)
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

questionstiffness::~questionstiffness()
{
    delete ui;
}

void questionstiffness::receivelogin(){

    this->show();

}

void questionstiffness::on_NextButton_clicked()
{
    // Kill the old slave running
    system ("taskkill /T /F /IM HapticSlave.exe");

    // Wait till slave is killed
    usleep(1000000);

    // Read Parameters from Config file
    ConfigFile cfg("../StiffnessDiscrimination_VE_2Device/Slave/bin/win-x64/cfg/config.cfg");
    std::string Username = cfg.getValueOfKey<std::string>("UserName");
    double ForceDeadbandParameter = cfg.getValueOfKey<double>("ForceDeadbandParameter");
    double VelocityDeadbandParameter = cfg.getValueOfKey<double>("VelocityDeadbandParameter");
    double ForceDelay = cfg.getValueOfKey<double>("ForceDelay");
    double CommandDelay = cfg.getValueOfKey<double>("CommandDelay");
    double TDPAon = cfg.getValueOfKey<double>("TDPAon");
    double RefStiffness = cfg.getValueOfKey<double>("RefStiffness");
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
    QString TDPAonAsString = QString::number(TDPAon);
    QString RefStiffnessAsString = QString::number(RefStiffness);
    QString RepetitionNumAsString = QString::number(RepetitionNum);
    QString FlagVelocityKalmanFilterAsString = QString::number(FlagVelocityKalmanFilter);

    // Output in csv File
    QFile filecsv("../GUI/SurveyUserAnswers/" + UsernameAsString + "_stiffness_answers.csv");
    QTextStream csvout(&filecsv);
    QString  yellowspinvalue, accuracy, rating, difficulty, distortion;
    if (filecsv.open(QFile::WriteOnly | QIODevice::Append | QIODevice::Text))
    {

        // 1 to 9 stiffness levels for springs yellow and red
        yellowspinvalue = ui->spinBox->text();
        rating = ui->spinBox_2->text();
        accuracy = ui->spinBox_3->text();
        difficulty = ui->spinBox_4->text();
        distortion = ui->spinBox_5->text();
// ///////////////////////////////////////////////////////////
        // Changing reference stiffness values to user numbers
        for (int i=0; i<stiffness_size; i++)
        {
            if (RefStiffness == stiffnessset[i])
            {
                RefStiffnessAsString = reference_stiffness[i];
            }
        }
// ///////////////////////////////////////////////////////////
        csvout << ForceDeadbandParameterAsString << "," << VelocityDeadbandParameterAsString <<"," << ForceDelayAsString << ","
               << CommandDelayAsString <<"," << FlagVelocityKalmanFilterAsString << "," <<  TDPAonAsString <<"," << RefStiffnessAsString <<","
               << RepetitionNumAsString << "," << yellowspinvalue << "," << rating << "," << distortion << "," << accuracy <<"," << difficulty << Qt::endl;
    }
    filecsv.close();
    qDebug() << "Saved";


    /*////////////////////////////////////////////////////////////////*/

    // Get UserName from config file
    ConfigFile cfg_("../StiffnessDiscrimination_VE_2Device/Slave/bin/win-x64/cfg/config.cfg");
    std::string Username_ = cfg_.getValueOfKey<std::string>("UserName");
    QString Username_Qstring = QString::fromUtf8(Username_.c_str());

    // Config file
    QFile fileconfig("../StiffnessDiscrimination_VE_2Device/Slave/bin/win-x64/cfg/config.cfg");

    if(fileconfig.open(QIODevice::ReadWrite | QIODevice::Text))
    {

        // Parameter Randomization //
        srand(time(NULL));
        int random_param = rand() % setsize;

        // Check if all parameters have been performed
        int checksum=0;
        for (int i=0; i<setsize; ++i){
            if(paramlist[i] == true){
                checksum = checksum+1;
            }
        }
        if(checksum == setsize){
            qDebug() << "All parameters completed";

            // Send signal to close master
            QFile file_m_restart("../StiffnessDiscrimination_VE_2Device/Slave/bin/win-x64/cfg/m_restart.cfg");
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
            endstiffness endstiffness;
            endstiffness.setModal(true);
            endstiffness.showMaximized();
            endstiffness.exec();
        }

        // If that random param tested before get the new one
        while (paramlist[random_param] == true) {
            random_param = rand() % setsize;
        }

        // Update paramlist
        paramlist[random_param] = true;

        // Get parameters
        int k = floor(random_param/(timedelayset_size*deadbandset_size*nbtrials_size));   // Select stiffness
        int i = floor((random_param-k*timedelayset_size*deadbandset_size*nbtrials_size)/(timedelayset_size*nbtrials_size)); // Select deadband
        int j = floor((random_param-k*timedelayset_size*deadbandset_size*nbtrials_size - i*timedelayset_size*nbtrials_size)/nbtrials_size); // Select time delay
        int r = random_param-k*timedelayset_size*deadbandset_size*nbtrials_size - i*timedelayset_size*nbtrials_size -j*nbtrials_size; // Select repetition
        double deadband = deadbandset[i];
        double delay = timedelayset[j];
        double stiffness = stiffnessset[k];
        double repetition = nbtrialsset[r];

        //Write parameters on config.cfg (original values)
        QTextStream conf(&fileconfig);
        conf << "UserName = " << Username_Qstring << ";"<< Qt::endl << Qt::endl;
        conf << "RecordSignals = " << 1 << ";"<< Qt::endl << Qt::endl;
        conf << "ForceDeadbandParameter = " << deadband << ";"<< Qt::endl << Qt::endl;
        conf << "VelocityDeadbandParameter = " << deadband << ";" << Qt::endl << Qt::endl;
        conf << "ForceDelay = " << delay<< ";" << Qt::endl << Qt::endl;
        conf << "CommandDelay = " << delay<< ";" << Qt::endl << Qt::endl;
        conf << "FlagVelocityKalmanFilter    = " << 0 << ";"<< Qt::endl << Qt::endl;
        conf << "MasterIP   = " << "192.168.0.2"<< ";" << Qt::endl << Qt::endl;
        conf << "SlaveIP   = " << "192.168.0.1" << ";"<< Qt::endl << Qt::endl;
        conf << "TDPAon = " << 1 << ";"<< Qt::endl << Qt::endl;
        conf << "RefStiffness  = " << stiffness << ";"<< Qt::endl << Qt::endl;
        conf << "Repetition = " << repetition << ";"<< Qt::endl << Qt::endl;
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

}

void questionstiffness::on_Repeat_clicked()
{
    // Kill the old slave running
    system ("taskkill /T /F /IM HapticSlave.exe");

    // Wait till slave is killed
    usleep(1000000);

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
}

void questionstiffness::on_Pause_clicked()
{
    // Kill the old slave running
    system ("taskkill /T /F /IM HapticSlave.exe");

    // Wait till slave is killed
    usleep(1000000);

    // Send signal to close master
    QFile file_m_restart("../StiffnessDiscrimination_VE_2Device/Slave/bin/win-x64/cfg/m_restart.cfg");
    if(file_m_restart.open(QIODevice::ReadWrite | QIODevice::Text))
    {

        //Write parameters on config.cfg (original values)
        QTextStream conf(&file_m_restart);
        conf << "m_restart = " << 2 << ";"<< Qt::endl << Qt::endl;

    }
    // close the config file
    file_m_restart.close();


}
