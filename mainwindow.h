#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>

#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#define API_KEY "&key=" + "AIzaSyDrihkZIWkr25yrTLEkn6jEdhbxbHlhrgQ";
#define STATISTICS_LINK "https://www.googleapis.com/youtube/v3/videos?part=statistics&id="

#include <QThread>

#include "timerrequest.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void operate();

    void stopTimer(bool flag);

private slots:
    void on_ln_url_textChanged(const QString &arg1);

    void managerFinished(QNetworkReply *reply);

    void updateLikeCount();

private:
    void init();

    Ui::MainWindow *ui;
    QString currURL;

    QNetworkAccessManager *manager;
    QNetworkReply *reply;

    TimerRequest *tmrReq;
    QThread timerThread;

    int testVal;
};
#endif // MAINWINDOW_H
