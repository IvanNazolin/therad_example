#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QThread>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Worker:public QThread
{
    Q_OBJECT

public:
    Worker(QObject* parent = nullptr);
signals:
    void currState(int );
public slots:
    void startThread(QString str, int i);

private:
    //функция с полезной нагрузкой
    void playload(QString str,int i);


    // QThread interface
protected:
    void run();
};


class Widget : public QWidget
{
    Q_OBJECT

public:
    Worker* _work;
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

signals:
    void startInThread(QString,int);


public slots:
    void receiverClick();
    void receiverState(int );

};
#endif // WIDGET_H
