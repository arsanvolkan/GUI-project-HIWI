#ifndef ENDPAINT_H
#define ENDPAINT_H

#include <QDialog>
#include <QWidget>

namespace Ui {
class endpaint;
}

class endpaint : public QDialog
{
    Q_OBJECT

public:
    explicit endpaint(QWidget *parent = nullptr);
    ~endpaint();

private slots:
    void on_MenuButton_clicked();

    void on_Usability_QuestionnaireButton_clicked();

private:
    Ui::endpaint *ui;
    QPixmap whiteboard;
    QPixmap logos;
protected:
        void paintEvent(QPaintEvent *);
};

#endif // ENDPAINT_H
