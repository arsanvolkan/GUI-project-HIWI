#ifndef QUESTIONLETTER_TRIAL_H
#define QUESTIONLETTER_TRIAL_H

#include <QDialog>

namespace Ui {
class questionletter_trial;
}

class questionletter_trial : public QDialog
{
    Q_OBJECT

public:
    explicit questionletter_trial(QWidget *parent = nullptr);
    ~questionletter_trial();

private:
    Ui::questionletter_trial *ui;
    QPixmap whiteboard;
    QPixmap logos;
    QPixmap paint_image;
protected:
        void paintEvent(QPaintEvent *);

private slots:
    void receivelogin();
    void on_TryAgain_clicked();
    void on_MainMenu_clicked();

signals:
    void showSelecttask();
    void showEndLetter();
};

#endif // QUESTIONLETTER_TRIAL_H
