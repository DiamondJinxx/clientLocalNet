#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);
    server = new QTcpSocket(this);
    server->isOpen();
}

Client::~Client()
{
    delete ui;
}


void Client::on_btnConnect_clicked()
{
    if(server)
    {
        server->connectToHost(QHostAddress::LocalHost, port,QIODevice::WriteOnly);
        if(server->waitForConnected(1000) == false )
            QMessageBox::critical(this, "Error","Server is not allowed");
        else
            qDebug() << "COnnection successfully to " <<
                        QString::number(QHostAddress::LocalHost) <<" "<< QString::number(this->port);
    }
}

void Client::on_btnSend_clicked()
{
    if(server->isOpen())
    {
        QByteArray m;
        m.append(ui->tLine->text());
        server->write(m);
        server->waitForBytesWritten(-1);
    }
    else
        QMessageBox::warning(this,"Warning!","You didn't connect to server.");
}
