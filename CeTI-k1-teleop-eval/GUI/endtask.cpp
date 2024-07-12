#include "endtask.h"
#include "ui_endtask.h"
#include <QPaintEvent>
#include <QPainter>

endtask::endtask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::endtask)
{
    ui->setupUi(this);
    whiteboard.load("../GUI/pictures/whiteboard.png");
    logos.load("../GUI/pictures/CeTi_TUM_Logo_images.png");
}

void endtask::paintEvent(QPaintEvent *)
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

endtask::~endtask()
{
    delete ui;
}

void endtask::on_EndButton_clicked()
{

    QApplication::quit();
}

