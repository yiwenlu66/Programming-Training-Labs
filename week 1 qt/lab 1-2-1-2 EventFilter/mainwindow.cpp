#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QTextStream>
#include <QtDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->installEventFilter(this);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->lineEdit && event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        QString log;
        QTextStream(&log) << "key press " << keyEvent->key() << " captured";
        printLog(log);
        return true;
    }
    return false;
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    QString log;
    QTextStream(&log) << "mouse click at (" << e->x() << "," << e->y() << ")";
    printLog(log);
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    switch (QMessageBox::warning(this, "Warning", "Do you really want to exit?", QMessageBox::Yes, QMessageBox::No)) {
    case QMessageBox::Yes:
        e->accept();
        break;
    case QMessageBox::No:
        e->ignore();
        printLog("close event ignored");
        break;
    }
}

void MainWindow::printLog(const QString &log)
{
    qDebug() << log;
    ui->textEdit_log->append(log);
}

MainWindow::~MainWindow()
{
    delete ui;
}
