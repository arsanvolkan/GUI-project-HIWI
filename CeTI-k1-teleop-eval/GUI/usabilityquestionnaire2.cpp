#include "usabilityquestionnaire2.h"
#include "ui_usabilityquestionnaire2.h"
#include "usabilityquestionnaire3.h"
#include "ui_usabilityquestionnaire3.h"
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

UsabilityQuestionnaire2::UsabilityQuestionnaire2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UsabilityQuestionnaire2)
{
    ui->setupUi(this);
    whiteboard.load("../GUI/pictures/whiteboard.png");
    logos.load("../GUI/pictures/CeTi_TUM_Logo_images.png");
}

void UsabilityQuestionnaire2::paintEvent(QPaintEvent *)
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

UsabilityQuestionnaire2::~UsabilityQuestionnaire2()
{
    delete ui;
}

void UsabilityQuestionnaire2::on_NextButton_clicked()
{

    // Read Parameters from Config file
    ConfigFile cfg("../StiffnessDiscrimination_VE_2Device/Slave/bin/win-x64/cfg/config.cfg");
    std::string Username = cfg.getValueOfKey<std::string>("UserName");
    QString UsernameAsString = QString::fromUtf8(Username.c_str());

    // Output in txt File
    QFile file("../GUI/SurveyUserAnswers/" + UsernameAsString + "_usability_questionnaire.txt");
    QTextStream out(&file);

    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        if(ui->radioButton->isChecked()){
            out << "Awareness: " << "-3" << Qt::endl;
        }
        if(ui->radioButton_2->isChecked()){
            out << "Awareness: " << "-2" << Qt::endl;
        }
        if(ui->radioButton_3->isChecked()){
            out << "Awareness: " << "-1" << Qt::endl;
        }
        if(ui->radioButton_4->isChecked()){
            out << "Awareness: " << "0" << Qt::endl;
        }
        if(ui->radioButton_5->isChecked()){
            out << "Awareness: " << "+1" << Qt::endl;
        }
        if(ui->radioButton_6->isChecked()){
            out << "Awareness: " << "+2" << Qt::endl;
        }
        if(ui->radioButton_7->isChecked()){
            out << "Awareness: " << "+3" << Qt::endl;
        }
        if(ui->radioButton_8->isChecked()){
            out << "Reality: " << "-3" << Qt::endl;
        }
        if(ui->radioButton_9->isChecked()){
            out << "Reality: " << "-2" << Qt::endl;
        }
        if(ui->radioButton_10->isChecked()){
            out << "Reality: " << "-1" << Qt::endl;
        }
        if(ui->radioButton_11->isChecked()){
            out << "Reality: " << "0" << Qt::endl;
        }
        if(ui->radioButton_12->isChecked()){
            out << "Reality: " << "+1" << Qt::endl;
        }
        if(ui->radioButton_13->isChecked()){
            out << "Reality: " << "+2" << Qt::endl;
        }
        if(ui->radioButton_14->isChecked()){
            out << "Reality: " << "+3" << Qt::endl;
        }
        if(ui->radioButton_15->isChecked()){
            out << "Sense of acting: " << "-3" << Qt::endl;
        }
        if(ui->radioButton_16->isChecked()){
            out << "Sense of acting: " << "-2" << Qt::endl;
        }
        if(ui->radioButton_17->isChecked()){
            out << "Sense of acting: " << "-1" << Qt::endl;
        }
        if(ui->radioButton_18->isChecked()){
            out << "Sense of acting: " << "0" << Qt::endl;
        }
        if(ui->radioButton_19->isChecked()){
            out << "Sense of acting: " << "+1" << Qt::endl;
        }
        if(ui->radioButton_20->isChecked()){
            out << "Sense of acting: " << "+2" << Qt::endl;
        }
        if(ui->radioButton_21->isChecked()){
            out << "Sense of acting: " << "+3" << Qt::endl;
        }
        if(ui->radioButton_22->isChecked()){
            out << "Consistency: " << "-3" << Qt::endl;
        }
        if(ui->radioButton_23->isChecked()){
            out << "Consistency: " << "-2" << Qt::endl;
        }
        if(ui->radioButton_24->isChecked()){
            out << "Consistency: " << "-1" << Qt::endl;
        }
        if(ui->radioButton_25->isChecked()){
            out << "Consistency: " << "0" << Qt::endl;
        }
        if(ui->radioButton_26->isChecked()){
            out << "Consistency: " << "+1" << Qt::endl;
        }
        if(ui->radioButton_27->isChecked()){
            out << "Consistency: " << "+2" << Qt::endl;
        }
        if(ui->radioButton_28->isChecked()){
            out << "Consistency: " << "+3" << Qt::endl;
        }


        // Space between two entries
        out << "----------------------------------------------------" << Qt::endl;
        out << "----------------------------------------------------" << Qt::endl;


    }

    file.close();
    qDebug() << "Saved";

    // Opening the next questionnaire window
    this->close();
    UsabilityQuestionnaire3 usabilityquestionnaire3;
    usabilityquestionnaire3.setModal(true);
    usabilityquestionnaire3.exec();

}

