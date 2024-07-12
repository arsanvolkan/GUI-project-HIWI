#ifndef ENDSTIFFNESS_H
#define ENDSTIFFNESS_H

#include <QDialog>
#include <QWidget>

namespace Ui {
class endstiffness;
}

class endstiffness : public QDialog
{
    Q_OBJECT

public:
    explicit endstiffness(QWidget *parent = nullptr);
    ~endstiffness();

private slots:
    void on_Usability_QuestionnaireButton_clicked();

    void on_MenuButton_clicked();

private:
    Ui::endstiffness *ui;
    QPixmap whiteboard;
    QPixmap logos;
protected:
        void paintEvent(QPaintEvent *);
};

#endif // ENDSTIFFNESS_H
