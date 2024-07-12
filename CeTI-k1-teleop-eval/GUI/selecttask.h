#ifndef SELECTTASK_H
#define SELECTTASK_H

#include <QDialog>
#include <QWidget>

namespace Ui {
class SelectTask;
}

class SelectTask : public QDialog
{
    Q_OBJECT

public:
    explicit SelectTask(QWidget *parent = nullptr);
    ~SelectTask();

private:
    Ui::SelectTask *ui;
    QPixmap background_image;
    QPixmap whiteboard;
    QPixmap logos;
    QPixmap stiff_image;
    QPixmap paint_image;

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void receivelogin();
    void on_StartStiffnessButton_clicked();
    void on_StartLetterButton_clicked();
    void on_tryStiff_clicked();
    void on_tryLetter_clicked();

signals:
    void showStarttask();
    void showMainWindow();
    void showQuestionStiff();
    void showQuestionLetter();
};

#endif // SELECTTASK_H
