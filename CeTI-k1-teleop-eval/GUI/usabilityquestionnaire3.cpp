#include "usabilityquestionnaire3.h"
#include "ui_usabilityquestionnaire3.h"
#include "endtask.h"
#include "ui_endtask.h"
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

UsabilityQuestionnaire3::UsabilityQuestionnaire3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UsabilityQuestionnaire3)
{
    ui->setupUi(this);
    whiteboard.load("../GUI/pictures/whiteboard.png");
    logos.load("../GUI/pictures/CeTi_TUM_Logo_images.png");
}

void UsabilityQuestionnaire3::paintEvent(QPaintEvent *)
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

UsabilityQuestionnaire3::~UsabilityQuestionnaire3()
{
    delete ui;
}

void UsabilityQuestionnaire3::on_NextButton_clicked()
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
            out << "Feeling present: " << "-3" << Qt::endl;
        }
        if(ui->radioButton_2->isChecked()){
            out << "Feeling present: " << "-2" << Qt::endl;
        }
        if(ui->radioButton_3->isChecked()){
            out << "Feeling present: " << "-1" << Qt::endl;
        }
        if(ui->radioButton_4->isChecked()){
            out << "Feeling present: " << "0" << Qt::endl;
        }
        if(ui->radioButton_5->isChecked()){
            out << "Feeling present: " << "+1" << Qt::endl;
        }
        if(ui->radioButton_6->isChecked()){
            out << "Feeling present: " << "+2" << Qt::endl;
        }
        if(ui->radioButton_7->isChecked()){
            out << "Feeling present: " << "+3" << Qt::endl;
        }
        if(ui->radioButton_8->isChecked()){
            out << "Being there: " << "-3" << Qt::endl;
        }
        if(ui->radioButton_9->isChecked()){
            out << "Being there: " << "-2" << Qt::endl;
        }
        if(ui->radioButton_10->isChecked()){
            out << "Being there: " << "-1" << Qt::endl;
        }
        if(ui->radioButton_11->isChecked()){
            out << "Being there: " << "0" << Qt::endl;
        }
        if(ui->radioButton_12->isChecked()){
            out << "Being there: " << "+1" << Qt::endl;
        }
        if(ui->radioButton_13->isChecked()){
            out << "Being there: " << "+2" << Qt::endl;
        }
        if(ui->radioButton_14->isChecked()){
            out << "Being there: " << "+3" << Qt::endl;
        }
        if(ui->radioButton_15->isChecked()){
            out << "More realistic: " << "-3" << Qt::endl;
        }
        if(ui->radioButton_16->isChecked()){
            out << "More realistic: " << "-2" << Qt::endl;
        }
        if(ui->radioButton_17->isChecked()){
            out << "More realistic: " << "-1" << Qt::endl;
        }
        if(ui->radioButton_18->isChecked()){
            out << "More realistic: " << "0" << Qt::endl;
        }
        if(ui->radioButton_19->isChecked()){
            out << "More realistic: " << "+1" << Qt::endl;
        }
        if(ui->radioButton_20->isChecked()){
            out << "More realistic: " << "+2" << Qt::endl;
        }
        if(ui->radioButton_21->isChecked()){
            out << "More realistic: " << "+3" << Qt::endl;
        }
        if(ui->radioButton_22->isChecked()){
            out << "Attention: " << "-3" << Qt::endl;
        }
        if(ui->radioButton_23->isChecked()){
            out << "Attention: " << "-2" << Qt::endl;
        }
        if(ui->radioButton_24->isChecked()){
            out << "Attention: " << "-1" << Qt::endl;
        }
        if(ui->radioButton_25->isChecked()){
            out << "Attention: " << "0" << Qt::endl;
        }
        if(ui->radioButton_26->isChecked()){
            out << "Attention: " << "+1" << Qt::endl;
        }
        if(ui->radioButton_27->isChecked()){
            out << "Attention: " << "+2" << Qt::endl;
        }
        if(ui->radioButton_28->isChecked()){
            out << "Attention: " << "+3" << Qt::endl;
        }


        // Space between two entries
        out << "----------------------------------------------------" << Qt::endl;
        out << "----------------------------------------------------" << Qt::endl;


    }

    file.close();
    qDebug() << "Saved";

    // Opening the end task window
    this->close();
    endtask endtask;
    endtask.setModal(true);
    endtask.exec();

}

