#include "timerrequest.h"

TimerRequest::TimerRequest(QObject *parent)
    : QObject{parent}
{
    flag = true;
}

void TimerRequest::sendRequest()
{
    while(true && flag) {
        QThread::msleep(10000);
        emit requestTime();
    }
}

void TimerRequest::setFlag(bool flag)
{
    this->flag = flag;
}
