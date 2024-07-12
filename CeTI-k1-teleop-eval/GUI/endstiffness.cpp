#include "endstiffness.h"
#include "ui_endstiffness.h"
#include "selecttask.h"
#include "ui_selecttask.h"
#include "usabilityquestionnaire.h"
#include "ui_usabilityquestionnaire.h"
#include <QPaintEvent>
#include <QPainter>

endstiffness::endstiffness(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::endstiffness)
{
    ui->setupUi(this);
    whiteboard.load("../GUI/pictures/whiteboard.png");
    logos.load("../GUI/pictures/CeTi_TUM_Logo_images.png");
}

void endstiffness::paintEvent(QPaintEvent *)
{

    // Set position of the windows on screen
    QList<QScreen*> screens = qApp->screens();
    QRect screenGeometry = screens.at(0)->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();


    int xframe = (width - ui->frame->width()) / 2;
    int yframe = (height - ui->frame->height()) / 2;

    int xlogo = (width - ui->frame_2->width()) / 2;
    int ylogo = height/2 + ui->frame->height()/2; //height - ((height - ui->frame_2->height() - ui->Usability_QuestionnaireButton->height()*2) / 2);

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

endstiffness::~endstiffness()
{
    delete ui;
}

void endstiffness::on_MenuButton_clicked()
{
    this->close();
    SelectTask selecttask1;
    selecttask1.setModal(true);
    selecttask1.showMaximized();
    selecttask1.exec();

}


void endstiffness::on_Usability_QuestionnaireButton_clicked()
{
    this->close();
    UsabilityQuestionnaire usabilityquestionnaire;
    usabilityquestionnaire.setModal(true);
    usabilityquestionnaire.exec();

}

