#ifndef ENDTASK_H
#define ENDTASK_H

#include <QDialog>

namespace Ui {
class endtask;
}

class endtask : public QDialog
{
    Q_OBJECT

public:
    explicit endtask(QWidget *parent = nullptr);
    ~endtask();

private slots:
    void on_EndButton_clicked();

private:
    Ui::endtask *ui;
    QPixmap whiteboard;
    QPixmap logos;
protected:
        void paintEvent(QPaintEvent *);
};

#endif // ENDTASK_H
