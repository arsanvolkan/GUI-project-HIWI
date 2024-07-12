#include "mainwindow.h"
#include "background.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>
#include <QDialog>
#include <QProcess>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <QPixmap>
#include <QFrame>
#include <QPaintEvent>
#include <QPainter>
#include <QFile>
#include <QTextStream>
#include "config.h"
#include <QScreen>
#include <QApplication>
#include <QVBoxLayout>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "config.h"
#include "QSettings"
#include <unistd.h>
#include <QRandomGenerator>
#include <QChar>
#include <QString>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{

    // Get height and width of the windows on screen
    QList<QScreen*> screens = qApp->screens();
    QRect screenGeometry = screens.at(0)->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    qDebug() << "Screen Size:" << ""<< width << "x" << height;


    // Set the layout as the central widget of the window
    QMainWindow window;
    QWidget *centralWidget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    centralWidget->setLayout(layout);
    window.setCentralWidget(centralWidget);

    QFrame *framelogo = new QFrame;
    int xlogo = (width - 531) / 2;
    int ylogo = height - ((height - 600) / 2);
    framelogo->setGeometry(xlogo, ylogo, 531, 61);

    ui->setupUi(this);

    //move(QGuiApplication::screens().at(0)->geometry().center() - frameGeometry().center());
    //int pos_x = width-(width - int(ui->frame->width())/2.4);
    //int pos_y = height/4;

    //setGeometry(pos_x,50,ui->frame->width(),ui->frame->height());


    whiteboard.load("../GUI/pictures/whiteboard.png");
    logos.load("../GUI/pictures/CeTi_TUM_Logo_images.png");

    // Adding a ComboBox for height, age and weight
    // Fill the items of the ComboBox
    // Weight
    ui->comboBox->addItem("-Bitte auswählen-/-Please Select-");
    // Height
    ui->comboBox_2->addItem("-Bitte auswählen-/-Please Select-");
    // Age
    ui->comboBox_3->addItem("-Bitte auswählen-/-Please Select-");
    for(int i = 30; i < 201; i++)
    {
        // Weight
        ui->comboBox->addItem(QString::number(i) + "kg");
    }
    for(int i = 130; i < 251; i++)
    {
        // Height
        ui->comboBox_2->addItem(QString::number(i) + "cm");
    }
    for(int i = 0; i < 121; i++)
    {
        // Age
        ui->comboBox_3->addItem(QString::number(i));
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{

    // Get height and width of the windows on screen
    QList<QScreen*> screens = qApp->screens();
    QRect screenGeometry = screens.at(0)->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();

    int xlogo = (width - 531) / 2;
    int ylogo = height - ((height - 600) / 2);

    int xframe = (width - 871) / 2;
    int yframe = 30;


    ui->frame->setGeometry(xframe, yframe, 871, 751);

    QPainter painter1(this);
    int x1 = ui->frame->pos().x();
    int y1 = ui->frame->pos().y();
    painter1.drawPixmap(xframe,yframe,width,height,whiteboard);
    //painter1.drawPixmap(x1,y1,ui->frame->width(),ui->frame->height(),whiteboard);

    QPainter painter4(this);
    int x4 = ui->frame_4->pos().x();
    int y4 = ui->frame_4->pos().y();
    painter4.drawPixmap(x4,y4,width,height,whiteboard);

    QPainter painter2(this);
    //int x2 = ui->frame_2->pos().x();
    //int y2 = ui->frame_2->pos().y();
    //painter2.drawPixmap(x2,y2,width,height,logos);
    painter2.drawPixmap(xlogo,ylogo,ui->frame_2->width(),ui->frame_2->height(),logos);

}



void MainWindow::Back()
{
    this->show();
}

// Function for Saving the user survey and move to window selecttask & questionnaire window
void MainWindow::on_NextButton_clicked()
{

    // User input lines
    QString str, str2, str3, str4, str5, height, weight, age, vision, visiontype;
    str = ui->lineEdit->text();
    str2 = ui->lineEdit_2->text();
    weight = ui->comboBox->currentText();
    height = ui->comboBox_2->currentText();
    age = ui->comboBox_3->currentText();
    vision = ui->comboBox_4->currentText();
    visiontype = ui->comboBox_5->currentText();
    //str3 = ui->lineEdit_3->text();
    //str4 = ui->lineEdit_4->text();
    str5 = ui->lineEdit_5->text();
    QString ID_number = str2;
    //QString leftSideLastname = str.left(3);
    //QString leftSideFirstname = str2.left(3);


    // Generate a random number between 0 and 99
    //int randomNumber = QRandomGenerator::global()->bounded(1000000);
    if (str2.isEmpty()) {
        // The line edit is empty
        // Open background
        //this->close();
        background background;
        background.setModal(true);
        background.exec();
    }
    else {



    // Config file
    QFile fileconfig("../StiffnessDiscrimination_VE_2Device/Slave/bin/win-x64/cfg/config.cfg");

    // Save UserName in config.cfg
    if(fileconfig.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream username(&fileconfig);
        //username << "UserName = " << leftSideLastname << leftSideFirstname << ";" << Qt::endl ;
        username << "UserName = " << ID_number << ";" << Qt::endl ;
    }
    fileconfig.close();

    // Config file
    QFile fileconfig_("../Paint_VE_2Device_GravityCompensated/Slave/bin/win-x64/cfg/config.cfg");

    // Save UserName in config.cfg
    if(fileconfig_.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream username(&fileconfig_);
        //username << "UserName = " << leftSideLastname << leftSideFirstname << ";" << Qt::endl ;
        username << "UserName = " << ID_number << ";" << Qt::endl ;
    }
    fileconfig.close();


    // SurveyUserInfo
    //QFile file1("../GUI/SurveyUserInfo/" + leftSideLastname + leftSideFirstname + ID_number + "_info_survey.txt");
    QFile file1("../GUI/SurveyUserInfo/" + ID_number + "_info_survey.txt");
    if(file1.open(QIODevice::WriteOnly | QIODevice::Text))
    {

        QTextStream out(&file1);

        out << "Username: " << str << Qt::endl;
        out << "ID Number: " << str2 << Qt::endl;

        //Gender
        if(ui->radioButton->isChecked()){
            out << "Gender: " << "Female" << Qt::endl;
        }
        if(ui->radioButton_2->isChecked()){
            out << "Gender: " << "Male" << Qt::endl;
        }

        // Dominant Hand
        if(ui->radioButton_3->isChecked()){
            out << "Hand: " << "Left" << Qt::endl;
        }
        if(ui->radioButton_4->isChecked()){
            out << "Hand: " << "Right" << Qt::endl;
        }

        out << "Weight: " << weight << Qt::endl;
        out << "Height: " << height << Qt::endl;
        out << "Age: " << age << Qt::endl;
        out << "Normal or corrected vision: " << vision << Qt::endl;
        out << "Vision Type: " << visiontype << Qt::endl;

        //Hearing problems
        if(ui->radioButton_14->isChecked()){
            out << "Hearing problems: " << "Yes" << Qt::endl;
        }
        if(ui->radioButton_15->isChecked()){
            out << "Hearing problems: " << "No" << Qt::endl;
        }
        //Tactile Sensation problems
        if(ui->radioButton_16->isChecked()){
            out << "Tactile sensation problems: " << "Yes" << Qt::endl;
        }
        if(ui->radioButton_17->isChecked()){
            out << "Tactile sensation problems: " << "No" << Qt::endl;
        }

        //Haptic Device Experience
        if(ui->radioButton_5->isChecked()){
            out << "Haptic exp: " << "Yes" << Qt::endl;
            out << "In which context?: " << str5 << Qt::endl;
        }
        if(ui->radioButton_6->isChecked()){
            out << "Haptic exp: " << "No" << Qt::endl;
        }

        //VR Experience
        if(ui->radioButton_7->isChecked()){
            out << "VR exp: " << "Yes" << Qt::endl;
        }
        if(ui->radioButton_8->isChecked()){
            out << "VR exp: " << "No" << Qt::endl;
        }

        //VR Experience Scale

        if(ui->radioButton_9->isChecked()){
            out << "Exp Scale: " << "1" << Qt::endl;
        }
        if(ui->radioButton_10->isChecked()){
            out << "Exp Scale: " << "2" << Qt::endl;
        }
        if(ui->radioButton_11->isChecked()){
            out << "Exp Scale: " << "3" << Qt::endl;
        }
        if(ui->radioButton_12->isChecked()){
            out << "Exp Scale: " << "4" << Qt::endl;
        }
        if(ui->radioButton_13->isChecked()){
            out << "Exp Scale: " << "5" << Qt::endl;
        }

        file1.seek(30);
        file1.close();
    }
    else
        file1.close();

    //qDebug() << "Saved";



    /////////////////////////////////////////////////////////////
    // Initialize Paint Trial Answers CSV & Paint Answers
    /////////////////////////////////////////////////////////////
    ConfigFile cfg("../Paint_VE_2Device_GravityCompensated/Slave/bin/win-x64/cfg/config.cfg");
    std::string Username = cfg.getValueOfKey<std::string>("UserName");
    QString UsernameAsString = QString::fromUtf8(Username.c_str());

    // Output in csv File
    QFile filecsv_p("../GUI/SurveyUserAnswers/" + UsernameAsString + "_paint_answers_trial.csv");
    QTextStream csvout_p(&filecsv_p);
    if (filecsv_p.open(QFile::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        csvout_p << "ForceDeadbandParameter," << "VelocityDeadbandParameter," << "ForceDelay," << "CommandDelay,"<<
                  "FlagVelocityKalmanFilter," << "TDPAon,"<< "Rating," << "Distortion," <<"Accuracy," << "Difficulty" <<  Qt::endl;
    }
    filecsv_p.close();

    // Output in csv File
    QFile filecsv_p_("../GUI/SurveyUserAnswers/" + UsernameAsString + "_paint_answers.csv");
    QTextStream csvout_p_(&filecsv_p_);
    if (filecsv_p_.open(QFile::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        csvout_p_ << "ForceDeadbandParameter," << "VelocityDeadbandParameter," << "ForceDelay," << "CommandDelay,"<<
                  "FlagVelocityKalmanFilter," << "TDPAon,"<< "RepetitionNum," <<  "Rating," <<"Distortion," << "Accuracy," << "Difficulty" <<  Qt::endl;
    }
    filecsv_p_.close();

    /////////////////////////////////////////////////////////////
    // Initialize Stiffness Trial Answers CSV & Stiffness Answers
    /////////////////////////////////////////////////////////////
    // Output in csv File
    QFile filecsv_s("../GUI/SurveyUserAnswers/" + UsernameAsString + "_stiffness_answers_trial.csv");
    QTextStream csvout_s(&filecsv_s);
    if (filecsv_s.open(QFile::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        csvout_s << "ForceDeadbandParameter," << "VelocityDeadbandParameter," << "ForceDelay," << "CommandDelay,"<<
                    "FlagVelocityKalmanFilter," << "TDPAon,"<< "RefStiffness," <<  "Yellow stiffness value,"  <<
                       "Rating," << "Distortion," << "Accuracy," << "Difficulty," <<Qt::endl;
    }
    filecsv_s.close();

    // Output in csv File
    QFile filecsv_s_("../GUI/SurveyUserAnswers/" + UsernameAsString + "_stiffness_answers.csv");
    QTextStream csvout_s_(&filecsv_s_);
    if (filecsv_s_.open(QFile::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        csvout_s_ << "ForceDeadbandParameter," << "VelocityDeadbandParameter," << "ForceDelay," << "CommandDelay,"<<
                  "FlagVelocityKalmanFilter," << "TDPAon,"<< "RefStiffness," <<"RepetitionNum," <<   "Yellow stiffness value,"  <<
                     "Rating," << "Distortion," <<"Accuracy," << "Difficulty," <<Qt::endl;

    }
    filecsv_s_.close();


    // Showing Start Task UI  and Questionnaire UI
    this->hide();
    emit showSelecttask();
}
}
