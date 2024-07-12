#ifndef QUESTIONLETTER_H
#define QUESTIONLETTER_H

#include <QDialog>

namespace Ui {
class questionletter;
}

class questionletter : public QDialog
{
    Q_OBJECT

public:
    explicit questionletter(QWidget *parent = nullptr);
    ~questionletter();

private:
    Ui::questionletter *ui;
    QPixmap whiteboard;
    QPixmap logos;
    QPixmap paint_image;
protected:
        void paintEvent(QPaintEvent *);

private slots:
    void receivelogin();

    void on_NextButton_clicked();
    void on_Repeat_clicked();
    void on_Pause_clicked();

signals:
    void showSelecttask();
    void showEndLetter();
};

#endif // QUESTIONLETTER_H
