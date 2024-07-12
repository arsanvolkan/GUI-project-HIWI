#ifndef QUESTIONSTIFFNESS_TRIAL_H
#define QUESTIONSTIFFNESS_TRIAL_H

#include <QDialog>


namespace Ui {
class questionstiffness_trial;
}

class questionstiffness_trial : public QDialog
{
    Q_OBJECT

public:
    explicit questionstiffness_trial(QWidget *parent = nullptr);
    ~questionstiffness_trial();

private:
    Ui::questionstiffness_trial *ui;
    QPixmap whiteboard;
    QPixmap logos;
    QPixmap stiff_image;
protected:
        void paintEvent(QPaintEvent *);

private slots:
    void receivelogin();
    void on_MainMenu_clicked();
    void on_TryAgain_clicked();

signals:
    void showSelecttask();
    void backHome();
    void showEndStiffness();
    void showMainWindow();
    void showQuestionStiff();
    void showQuestionLetter();
};



#endif // QUESTIONSTIFFNESS_TRIAL_H
