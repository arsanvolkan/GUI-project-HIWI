#ifndef QUESTIONSTIFFNESS_H
#define QUESTIONSTIFFNESS_H

#include <QDialog>

namespace Ui {
class questionstiffness;
}

class questionstiffness : public QDialog
{
    Q_OBJECT

public:
    explicit questionstiffness(QWidget *parent = nullptr);
    ~questionstiffness();

private:
    Ui::questionstiffness *ui;
    QPixmap whiteboard;
    QPixmap logos;
    QPixmap stiff_image;
protected:
        void paintEvent(QPaintEvent *);

private slots:
    void receivelogin();

    void on_NextButton_clicked();
    void on_Repeat_clicked();
    void on_Pause_clicked();


signals:
    void showSelecttask();
    void backHome();
    void showEndStiffness();
};

#endif // QUESTIONSTIFFNESS_H
