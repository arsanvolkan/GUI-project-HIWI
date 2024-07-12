#ifndef USABILITYQUESTIONNAIRE3_H
#define USABILITYQUESTIONNAIRE3_H

#include <QDialog>

namespace Ui {
class UsabilityQuestionnaire3;
}

class UsabilityQuestionnaire3 : public QDialog
{
    Q_OBJECT

public:
    explicit UsabilityQuestionnaire3(QWidget *parent = nullptr);
    ~UsabilityQuestionnaire3();

private slots:
    void on_NextButton_clicked();

private:
    Ui::UsabilityQuestionnaire3 *ui;
    QPixmap whiteboard;
    QPixmap logos;
protected:
        void paintEvent(QPaintEvent *);
};

#endif // USABILITYQUESTIONNAIRE3_H
