#ifndef USABILITYQUESTIONNAIRE_H
#define USABILITYQUESTIONNAIRE_H

#include <QDialog>

namespace Ui {
class UsabilityQuestionnaire;
}

class UsabilityQuestionnaire : public QDialog
{
    Q_OBJECT

public:
    explicit UsabilityQuestionnaire(QWidget *parent = nullptr);
    ~UsabilityQuestionnaire();

private:
    Ui::UsabilityQuestionnaire *ui;
    QPixmap whiteboard;
    QPixmap logos;
protected:
        void paintEvent(QPaintEvent *);
private slots:
        void on_nextButton_clicked();
};

#endif // USABILITYQUESTIONNAIRE_H
