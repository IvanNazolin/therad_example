#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>
#include <QDebug>
#include <QThread>
#include <QDateTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(0);
    _work = new Worker(this);
    //создаем поток
    //необходимо завершить поток перед тем как он удалится
    connect(this,SIGNAL(destroyed(QObject*)),_work,SLOT(quit()));
    // воркер не должен иметь родителя, в противном случае будет предупреждение
   connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(receiverClick()));
   connect(_work,SIGNAL(currState(int)), this, SLOT(receiverState(int)));


    _work->moveToThread(_work);
   //запускаем цикл обработки событий

//   // connect(ui->pushButton,&QPushButton::clicked,this,&Widget::receiverClick);
//    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(receiverClick_33()));
//    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(receiverClick()));

}

void Widget::receiverClick()
{
   if(_work->isRunning())
   {
        _work->requestInterruption();
   }

   _work->start();
   emit startInThread(QString("START IN THREAD"), 20);
}

void Widget::receiverState(int i)
{
   qDebug() << "State" << i;
   ui->progressBar->setValue(i);
}

Widget::~Widget()
{
   _work->requestInterruption();
   _work->wait(10000);
   delete _work;
    delete ui;
}




Worker::Worker(QObject* parent)
    : QThread(parent)
{

}

void Worker::startThread(QString str, int i)
{
    playload(str,i);
}

void Worker::playload(QString str, int i)
{
    qDebug() << str << i;
    QThread::sleep(1);
    emit currState(5);
    QThread::sleep(1);
    emit currState(10);
    if(this->isInterruptionRequested())
    {
        return;
    }
    QThread::sleep(1);
    emit currState(15);
    QThread::sleep(1);
    emit currState(20);
    QThread::sleep(1);
    emit currState(30);
    QThread::sleep(1);
    emit currState(40);
    QThread::sleep(1);
    if(this->isInterruptionRequested())
    {
        return;
    }
    emit currState(50);
    QThread::sleep(1);
    if(this->isInterruptionRequested())
    {
        return;
    }
    emit currState(60);
    QThread::sleep(1);
    if(this->isInterruptionRequested())
    {
        return;
    }
    emit currState(70);
    QThread::sleep(1);
    emit currState(80);
    QThread::sleep(1);
    emit currState(90);
    QThread::sleep(1);
    emit currState(100);

}


void Worker::run()
{
    qDebug() << "Start thread";
    playload(QString("Thread start"),20);
    qDebug() << "Thread Finish";
}
