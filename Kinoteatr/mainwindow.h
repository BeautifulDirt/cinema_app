#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QPainter>
#include <QLabel>
#include <QLineEdit>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void kinozal();
    void kup1();
    void kup2();
    void exportdata(int i, QString pologenie); // отправить данные
    void importdata(); // считать данные
    void baza();
    void file();


protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *);
    void closeEvent(QCloseEvent *event);


protected:
    virtual void mousePressEvent(QMouseEvent * ev);

private:
    QLabel *label[20];
    QSqlDatabase sdb;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H


