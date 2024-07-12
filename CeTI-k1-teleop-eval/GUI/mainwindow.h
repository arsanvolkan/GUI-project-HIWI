#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QSpinBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QWidget>
#include <QtGlobal>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString str; // Note the important use of extern!
    QString str2;



private slots:

    void on_NextButton_clicked();

    void Back();


private:
       void saveToFile();
       void loadFromFile();



private:
    Ui::MainWindow *ui;

    QPixmap whiteboard;
    QPixmap logos;

protected:
        void paintEvent(QPaintEvent *);

signals:
    void showStarttask();
    void showQuestion();
    void showSelecttask();
};
#endif // MAINWINDOW_H
