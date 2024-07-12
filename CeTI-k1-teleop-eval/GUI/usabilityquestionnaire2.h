#ifndef USABILITYQUESTIONNAIRE2_H
#define USABILITYQUESTIONNAIRE2_H

#include <QDialog>

namespace Ui {
class UsabilityQuestionnaire2;
}

class UsabilityQuestionnaire2 : public QDialog
{
    Q_OBJECT

public:
    explicit UsabilityQuestionnaire2(QWidget *parent = nullptr);
    ~UsabilityQuestionnaire2();

private slots:
    void on_NextButton_clicked();

private:
    Ui::UsabilityQuestionnaire2 *ui;
    QPixmap whiteboard;
    QPixmap logos;
protected:
        void paintEvent(QPaintEvent *);
};

#endif // USABILITYQUESTIONNAIRE2_H
