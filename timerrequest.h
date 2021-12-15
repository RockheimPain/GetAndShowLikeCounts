#ifndef TIMERREQUEST_H
#define TIMERREQUEST_H

#include <QObject>
#include <QThread>
#include <QDebug>

class TimerRequest : public QObject
{
    Q_OBJECT
public:
    explicit TimerRequest(QObject *parent = nullptr);

signals:
    void requestTime();

private slots:
    void sendRequest();

    void setFlag(bool flag);

private:
    bool flag;
};

#endif // TIMERREQUEST_H
