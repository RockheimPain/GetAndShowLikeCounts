#include "timerrequest.h"

TimerRequest::TimerRequest(QObject *parent)
    : QObject{parent}
{

}

void TimerRequest::sendRequest()
{
    while(true) {
        QThread::msleep(10000);
        emit requestTime();
    }
}
