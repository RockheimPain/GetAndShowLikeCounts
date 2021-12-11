#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    init();
}

void MainWindow::init()
{
    testVal = 0;
    currURL = "";

    ui->setupUi(this);
    ui->lbl_numOfLikes->setStyleSheet("background-color: red; color: white; border-radius: 7%");
    ui->ln_url->setStyleSheet("border-radius: 5%");

    manager = new QNetworkAccessManager();

    tmrReq = new TimerRequest();
    tmrReq->moveToThread(&timerThread);

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(managerFinished(QNetworkReply*)));
    connect(&timerThread, SIGNAL(finished()), tmrReq, SLOT(deleteLater()));
    connect(this, SIGNAL(operate()), tmrReq, SLOT(sendRequest()));
    connect(tmrReq, SIGNAL(requestTime()), this, SLOT(updateLikeCount()));

    timerThread.start();
    emit operate();
}


MainWindow::~MainWindow()
{
    delete ui;

    timerThread.quit();
    timerThread.wait();
}

void MainWindow::on_ln_url_textChanged(const QString &url)
{
    if (!url.isEmpty()) {
        QStringList tmpStrs = QString(url).split("watch?v=");

        if (tmpStrs.size() == 2) {
            currURL = STATISTICS_LINK + tmpStrs.last() + API_KEY;
        }

        updateLikeCount();
    }
}

void MainWindow::managerFinished(QNetworkReply *reply) {
    if (reply->error()) {
        qDebug() << reply->errorString();
        int v = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << "v  '" << v << "'";
        return;
    }

    QString answer = reply->readAll();

    QJsonDocument jDoc = QJsonDocument::fromJson(answer.toLatin1());
    QJsonObject jObj = jDoc.object();

    if (jObj.contains("items")) {
        if (jObj["items"].isArray()) {
            QJsonArray jArr = jObj.take("items").toArray();
            if (jArr.count() != 0) {
                jObj = jArr.takeAt(0).toObject();

                jObj = jObj.take("statistics").toObject();

                ui->lbl_numOfLikes->setText("Like count: " + jObj.value("likeCount").toString());
            } else {
                ui->lbl_numOfLikes->setText("Like count: 0");
            }
        }
    }
}

void MainWindow::updateLikeCount()
{
    if (!currURL.isEmpty()) {
        qDebug() << ++testVal;

        QNetworkRequest request((QUrl(currURL)));
        reply = manager->get(request);
    }
}
