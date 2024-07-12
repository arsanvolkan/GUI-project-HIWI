#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QDialog>

namespace Ui {
class background;
}

class background : public QDialog
{
    Q_OBJECT

public:
    explicit background(QWidget *parent = nullptr);
    ~background();

private:
    Ui::background *ui;
    QPixmap whiteboard;

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_clicked();
    void receivelogin();

signals:
    void showMainWindow();
};

#endif // BACKGROUND_H
