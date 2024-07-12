#ifndef WHITEBACKGROUND_H
#define WHITEBACKGROUND_H

#include <QDialog>

namespace Ui {
class whitebackground;
}

class whitebackground : public QDialog
{
    Q_OBJECT

public:
    explicit whitebackground(QWidget *parent = nullptr);
    ~whitebackground();

private:
    Ui::whitebackground *ui;
    QPixmap whiteboard;

protected:
    void paintEvent(QPaintEvent *);
};

#endif // WHITEBACKGROUND_H
