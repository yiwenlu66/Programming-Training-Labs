#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QByteArray>
#include <QDataStream>
#include <QHostAddress>
#include <QIODevice>
#include <QtGlobal>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_udpSocket(new QUdpSocket(this))
{
    ui->setupUi(this);
    connect(ui->pushButton_bind, SIGNAL(clicked(bool)), this, SLOT(bind()));
    connect(ui->pushButton_send, SIGNAL(clicked(bool)), this, SLOT(sendMessage()));
    connect(m_udpSocket, SIGNAL(readyRead()), this, SLOT(receiveMessage()));
}

void MainWindow::bind()
{
    m_udpSocket->bind(ui->spinBox_srcPort->value());
    m_port = ui->spinBox_srcPort->value();
}

void MainWindow::sendMessage()
{
    if (ui->lineEdit_send->text().isEmpty()) {
        return;
    }
    QByteArray datagram = ui->lineEdit_send->text().toUtf8();
    m_udpSocket->writeDatagram(datagram, QHostAddress("127.0.0.1"), ui->spinBox_dstPort->value());
    ui->plainTextEdit_receive->appendPlainText(ui->lineEdit_send->text());
    ui->lineEdit_send->clear();
}

void MainWindow::receiveMessage()
{
    while (m_udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        m_udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        QString textToDisplay;
        QTextStream(&textToDisplay, QIODevice::WriteOnly) << senderPort << " : " << QString(datagram);
        ui->plainTextEdit_receive->appendPlainText(textToDisplay);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
