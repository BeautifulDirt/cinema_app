#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QCursor>
#include <QFile>

bool click=true;
bool n = false;
QString stroka;
int m = 0;
double kres[55][5];
double kreslo[55][5];


MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->action_2, SIGNAL(triggered(bool)), this, SLOT(baza()) );
    connect(ui->action_3, SIGNAL(triggered(bool)), this, SLOT(file()) );

    startTimer(10);
        //подключение к БД!
        sdb=QSqlDatabase::addDatabase("QMYSQL");
            sdb.setHostName("localhost");
            sdb.setDatabaseName("vkino");
            sdb.setUserName("root");
            sdb.setPassword("pass");
            sdb.open();

    int k=1;
    for (int i=1; i<=12; i++)
    {
        stroka = (QString) (k + 48);
        label[i] = new QLabel("<font size=4> <span style=color:#365c4b> <b>"+stroka, this);
        if (i==6) k = 0;
        k++;
    }
    stroka = "Вкинотеатре";
    label[13] = new QLabel("<font size=6> <span style=color:#365c4b> <b>"+stroka, this);

    label[14] = new QLabel("<font size=4> <span style=color:#365c4b> <b>Количество выбранных мест: ", this);
    label[15] = new QLabel("<font size=4> <span style=color:#365c4b> <b>0", this);
    label[16] = new QLabel("<font size=4> <span style=color:#365c4b> <b>Ваша сумма составляет:", this);
    label[17] = new QLabel("<font size=4> <span style=color:#365c4b> <b>0", this);
    label[18] = new QLabel("<font size=4> <span style=color:#365c4b> <b>рублей.", this);
    label[19] = new QLabel("<font size=3> <span style=color:#365c4b> <b>Заказать", this);
    label[20] = new QLabel("<font size=3> <span style=color:#365c4b> <b>Сбросить", this);

    importdata();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::importdata() // ввод значений
{
    if (click == true)
    {
    //Выводим знасения из запроса
    QSqlQuery query;
    query.exec("SELECT mesto, bron FROM kol");
    while (query.next()) kres[query.value(0).toInt()][4]=query.value(1).toInt();
    }
    else {
        QFile file("data.txt");//Путь к файлу
            file.open(QFile::ReadOnly);//Открыли
            QString str=QString(file.readAll());
            file.close();//Закрыли
            //Считывание строки и информации о бронировании места
            int a=0;
            for (int i=1;i<=54;i++)
            {
                if (str[a]=='0') kres[i][4]=0;
                if (str[a]=='1') kres[i][4]=1;
                if (str[a]=='2') kres[i][4]=2;
                a=a+1;//Следующий символ (бронь)
            }
          }

}

void MainWindow::baza()
{
    click=true;
}

void MainWindow::file()
{
    click=false;
}


void MainWindow::exportdata(int i, QString pologenie) //вывод значений
{
   double d = pologenie.toDouble();
   if (click == true)
   {
    QSqlQuery query;
    query.prepare("UPDATE kol SET bron=? WHERE mesto=? ");
    query.addBindValue(d);
    query.addBindValue(i);
    query.exec();
   }
   else {
       QFile file("data.txt");//Путь к файлу
           file.open(QFile::WriteOnly );//Открыли
           for (int i=1;i<=54;i++)
           {
               if (kres[i][4] == 0) file.write("0");
               if (kres[i][4] == 1) file.write("1");
               if (kres[i][4] == 2) file.write("2");
           }
           file.close();//Закрыли
         }
}

void MainWindow::kinozal()
{

    double  a=20,x,y;
    QPainter painter(this);
    QConicalGradient gradient(width() / 2, height() / 2, 0);
    gradient.setColorAt(0.0, QColor(255, 255, 255));
    gradient.setColorAt(0.4, QColor(200, 200, 200));
    gradient.setColorAt(0.8, QColor(150, 150, 150));
    gradient.setColorAt(1.0, QColor(255, 255, 255));
    painter.setBrush(gradient);
    painter.drawRect(rect());

    QPainter ekran(this);
    ekran.setBrush(QColor(148, 204, 147));
    QPolygon kekran;
    kekran<<QPoint(40,75)<<QPoint(640,75)<<QPoint(640,70)<<QPoint(40,70);
    ekran.drawPolygon(kekran);

    QPainter knopka1(this);
    knopka1.setBrush(QColor(83, 166, 159));
    QPolygon zknopka;
    zknopka<<QPoint(530,425)<<QPoint(615,425)<<QPoint(615,455)<<QPoint(530,455);
    knopka1.drawPolygon(zknopka);

    QPainter knopka2(this);
    knopka2.setBrush(QColor(83, 166, 159));
    QPolygon sknopka;
    sknopka<<QPoint(530,465)<<QPoint(615,465)<<QPoint(615,495)<<QPoint(530,495);
    knopka2.drawPolygon(sknopka);

    x=100;y=130;
    QPainter kreslo(this);
    kreslo.setBrush(QColor(152, 99, 173));
    for (int i=1;i<=54;i++)
    {

        QPolygon poly;
        poly<<QPoint(x-a,y-a)<<QPoint(x+a,y-a)<<QPoint(x+a,y+a)<<QPoint(x-a,y+a);
        kreslo.drawPolygon(poly);

        kres[i][0] = x-a;
        kres[i][1] = y-a;
        kres[i][2] = x+a;
        kres[i][3] = y+a;

        x+=60;
        if (i%9==0)
        {
            y+=47;
            x=100;
        }
    }
    x=50;y=130;
    for (int i = 1; i <= 12; i++)
    {
        label[i]->setGeometry(QRect(QPoint(x-5,y-10),QSize(12,21)));
        y+=47;
        if (i==6)
        {
            y=130;
            x+=580;
        }
    }
    label[13]->setGeometry(QRect(QPoint(250,20),QSize(190,50)));
    label[14]->setGeometry(QRect(QPoint(30,435),QSize(300,21)));
    label[15]->setGeometry(QRect(QPoint(350,435),QSize(50,21)));
    label[16]->setGeometry(QRect(QPoint(30,470),QSize(250,21)));
    label[17]->setGeometry(QRect(QPoint(350,470),QSize(57,21)));
    label[18]->setGeometry(QRect(QPoint(412,470),QSize(90,21)));
    label[19]->setGeometry(QRect(QPoint(540,430),QSize(70,21)));
    label[20]->setGeometry(QRect(QPoint(540,470),QSize(70,21)));

    n = true;

}

void MainWindow::kup1()
{
    for (int i=1;i<=54;i++)
    {
        if (kres[i][4] == 1)
        {
            QPainter zakaz(this);
            zakaz.setBrush(QColor(174, 232, 74));
            QPolygon poly1;
            poly1<<QPoint(kres[i][0],kres[i][1])<<QPoint(kres[i][2],kres[i][1])
            <<QPoint(kres[i][2],kres[i][3])<<QPoint(kres[i][0],kres[i][3]);
            zakaz.drawPolygon(poly1);
            n = false;
        }
    }
}

void MainWindow::kup2()
{

    for (int i=1;i<=54;i++)
    {
        if (kres[i][4] == 2)
        {
            QPainter zakaz(this);
            zakaz.setBrush(QColor(199, 60, 60));
            QPolygon poly1;
            poly1<<QPoint(kres[i][0],kres[i][1])<<QPoint(kres[i][2],kres[i][1])
            <<QPoint(kres[i][2],kres[i][3])<<QPoint(kres[i][0],kres[i][3]);
            zakaz.drawPolygon(poly1);
        }
    }

}


void MainWindow::paintEvent(QPaintEvent *event)
{
    importdata();
    kinozal();
    if (n == true) kup1();
    kup2();

}

void MainWindow::mousePressEvent(QMouseEvent * ev)
{
ev->accept();
    QPoint p=ev->pos();
    double x=p.x(),y=p.y();

    for(int i = 1;i <= 54;i++)
    {

        if ( (x>kres[i][0]) && (y>kres[i][1]) && (x<kres[i][2]) &&
             (y<kres[i][3]) && kres[i][4] == 0)
        {
            kres[i][4] = 1;
            kreslo[i][4] = 1;
            exportdata(i,"1");
            n = true;
            m++;
            label[15]->setText("<font size=4> <span style=color:#365c4b><b>"+QString::number(m));
            label[17]->setText("<font size=4> <span style=color:#365c4b><b>"+QString::number(m*350));
            update();
            break;
        }
        if ( (x>kres[i][0]) && (y>kres[i][1]) && (x<kres[i][2]) &&
             (y<kres[i][3]) && kres[i][4] == 1 &&  kreslo[i][4] == 1)
        {
            kres[i][4] = 0;
            kreslo[i][4] = 0;
            exportdata(i,"0");
            m--;
            label[15]->setText("<font size=4> <span style=color:#365c4b><b>"+QString::number(m));
            label[17]->setText("<font size=4> <span style=color:#365c4b><b>"+QString::number(m*350));
            update();
        }
    }

    if ( (x>530) && (y>425) && (x<615) && (y<455) )
    {
        for(int i = 1;i <= 54;i++)
        {
            if (kreslo[i][4] == 1)
            {
                kres[i][4] = 2;
                kreslo[i][4] = 2;
                exportdata(i,"2");
            }

            m = 0;
            label[15]->setText("<font size=4> <span style=color:#365c4b><b>"+QString::number(0));
            label[17]->setText("<font size=4> <span style=color:#365c4b><b>"+QString::number(0));
            update();
        }
    }

    if ( (x>530) && (y>465) && (x<615) && (y<495) )
    {
        for (int i=1;i<=54;i++)
        {
            kres[i][4] = 0;
            if (click == true)
            {
            QSqlQuery query;
            query.prepare ("UPDATE kol SET bron=0 WHERE mesto=?");
            query.addBindValue(i);
            query.exec();
            }
            else {
                QFile file("data.txt");
                file.open(QFile::WriteOnly );
                file.write("0");
                file.close();
            }

            QCursor oCursor(Qt::WaitCursor);
            setCursor(oCursor);
        }
        QCursor oCursor(Qt::ArrowCursor);
        setCursor(oCursor);
        update();
    }

}

void MainWindow::closeEvent(QCloseEvent *event)
{
   if (click == true)
    for (int i=1;i<=54;i++)
    {
        if (kres[i][4] == 1 && kreslo[i][4] == 1)
        {
            QSqlQuery query;
            query.prepare("UPDATE kol SET bron=0 WHERE mesto=? ");
            query.addBindValue(i);
            query.exec();
        }
    }
   else {
    QFile file("data.txt");
    file.open(QFile::WriteOnly );
    for (int i=1;i<=54;i++)
    {
        if (kres[i][4] == 0) file.write("0");
        if (kres[i][4] == 1) file.write("0");
        if (kres[i][4] == 2) file.write("2");
    }
    file.close();
    for (int i=1;i<=54;i++) {  kreslo[i][4] = 0;}
   }
}

void MainWindow::timerEvent(QTimerEvent *)
{
    update();
}
