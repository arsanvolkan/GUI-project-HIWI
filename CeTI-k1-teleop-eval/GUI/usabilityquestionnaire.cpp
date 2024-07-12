#include "usabilityquestionnaire.h"
#include "ui_usabilityquestionnaire.h"
#include "usabilityquestionnaire2.h"
#include "ui_usabilityquestionnaire2.h"
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

UsabilityQuestionnaire::UsabilityQuestionnaire(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UsabilityQuestionnaire)
{
    ui->setupUi(this);
    whiteboard.load("../GUI/pictures/whiteboard.png");
    logos.load("../GUI/pictures/CeTi_TUM_Logo_images.png");
}

void UsabilityQuestionnaire::paintEvent(QPaintEvent *)
{

    QPainter painter1(this);
    int x1 = ui->frame->pos().x();
    int y1 = ui->frame->pos().y();
    painter1.drawPixmap(x1,y1,ui->frame->width(),ui->frame->height(), whiteboard);

    QPainter painter2(this);
    int x2 = ui->frame_2->pos().x();
    int y2 = ui->frame_2->pos().y();
    painter2.drawPixmap(x2,y2,ui->frame_2->width(),ui->frame_2->height(), logos);

}

UsabilityQuestionnaire::~UsabilityQuestionnaire()
{
    delete ui;
}

void UsabilityQuestionnaire::on_nextButton_clicked()
{
    // Read Parameters from Config file
    ConfigFile cfg("../StiffnessDiscrimination_VE_2Device/Slave/bin/win-x64/cfg/config.cfg");
    std::string Username = cfg.getValueOfKey<std::string>("UserName");
    QString UsernameAsString = QString::fromUtf8(Username.c_str());

    // Output in txt File
    QFile file1("../GUI/SurveyUserAnswers/" + UsernameAsString + "_usability_questionnaire.txt");
    QTextStream out(&file1);

    if(file1.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {

        if(ui->checkBox->isChecked()){
            out << "1) " << "1" << Qt::endl;
        }
        if(ui->checkBox_2->isChecked()){
            out << "1) " << "2" << Qt::endl;
        }
        if(ui->checkBox_3->isChecked()){
            out << "1) " << "3" << Qt::endl;
        }
        if(ui->checkBox_4->isChecked()){
            out << "1) " << "4" << Qt::endl;
        }
        if(ui->checkBox_5->isChecked()){
            out << "1) " << "5" << Qt::endl;
        }
        if(ui->checkBox_6->isChecked()){
            out << "2) " << "1" << Qt::endl;
        }
        if(ui->checkBox_7->isChecked()){
            out << "2) " << "2" << Qt::endl;
        }
        if(ui->checkBox_8->isChecked()){
            out << "2) " << "3" << Qt::endl;
        }
        if(ui->checkBox_9->isChecked()){
            out << "2) " << "4" << Qt::endl;
        }
        if(ui->checkBox_10->isChecked()){
            out << "2) " << "5" << Qt::endl;
        }
        if(ui->checkBox_11->isChecked()){
            out << "3) " << "1" << Qt::endl;
        }
        if(ui->checkBox_12->isChecked()){
            out << "3) " << "2" << Qt::endl;
        }
        if(ui->checkBox_13->isChecked()){
            out << "3) " << "3" << Qt::endl;
        }
        if(ui->checkBox_14->isChecked()){
            out << "3) " << "4" << Qt::endl;
        }
        if(ui->checkBox_15->isChecked()){
            out << "3) " << "5" << Qt::endl;
        }
        if(ui->checkBox_16->isChecked()){
            out << "4) " << "1" << Qt::endl;
        }
        if(ui->checkBox_17->isChecked()){
            out << "4) " << "2" << Qt::endl;
        }
        if(ui->checkBox_18->isChecked()){
            out << "4) " << "3" << Qt::endl;
        }
        if(ui->checkBox_19->isChecked()){
            out << "4) " << "4" << Qt::endl;
        }
        if(ui->checkBox_20->isChecked()){
            out << "4) " << "5" << Qt::endl;
        }
        if(ui->checkBox_21->isChecked()){
            out << "5) " << "1" << Qt::endl;
        }
        if(ui->checkBox_22->isChecked()){
            out << "5) " << "2" << Qt::endl;
        }
        if(ui->checkBox_23->isChecked()){
            out << "5) " << "3" << Qt::endl;
        }
        if(ui->checkBox_24->isChecked()){
            out << "5) " << "4" << Qt::endl;
        }
        if(ui->checkBox_25->isChecked()){
            out << "5) " << "5" << Qt::endl;
        }
        if(ui->checkBox_26->isChecked()){
            out << "6) " << "1" << Qt::endl;
        }
        if(ui->checkBox_27->isChecked()){
            out << "6) " << "2" << Qt::endl;
        }
        if(ui->checkBox_28->isChecked()){
            out << "6) " << "3" << Qt::endl;
        }
        if(ui->checkBox_29->isChecked()){
            out << "6) " << "4" << Qt::endl;
        }
        if(ui->checkBox_30->isChecked()){
            out << "6) " << "5" << Qt::endl;
        }
        if(ui->checkBox_31->isChecked()){
            out << "7) " << "1" << Qt::endl;
        }
        if(ui->checkBox_32->isChecked()){
            out << "7) " << "2" << Qt::endl;
        }
        if(ui->checkBox_33->isChecked()){
            out << "7) " << "3" << Qt::endl;
        }
        if(ui->checkBox_34->isChecked()){
            out << "7) " << "4" << Qt::endl;
        }
        if(ui->checkBox_35->isChecked()){
            out << "7) " << "5" << Qt::endl;
        }
        if(ui->checkBox_36->isChecked()){
            out << "8) " << "1" << Qt::endl;
        }
        if(ui->checkBox_37->isChecked()){
            out << "8) " << "2" << Qt::endl;
        }
        if(ui->checkBox_38->isChecked()){
            out << "8) " << "3" << Qt::endl;
        }
        if(ui->checkBox_39->isChecked()){
            out << "8) " << "4" << Qt::endl;
        }
        if(ui->checkBox_40->isChecked()){
            out << "8) " << "5" << Qt::endl;
        }
        // Space between two entries
        out << "----------------------------------------------------" << Qt::endl;
        out << "----------------------------------------------------" << Qt::endl;


    }
    file1.close();
    qDebug() << "Saved";

    // Opening the next questionnaire window
    this->close();
    UsabilityQuestionnaire2 usabilityquestionnaire2;
    usabilityquestionnaire2.setModal(true);
    usabilityquestionnaire2.exec();

}

