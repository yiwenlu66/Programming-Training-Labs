#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->dial_c, SIGNAL(valueChanged(int)), this, SLOT(degCChanged(int)));
    connect(ui->dial_f, SIGNAL(valueChanged(int)), this, SLOT(degFChanged(int)));
    connect(this, SIGNAL(changeDegC(int)), ui->dial_c, SLOT(setValue(int)));
    connect(this, SIGNAL(changeDegF(int)), ui->dial_f, SLOT(setValue(int)));
}

void MainWindow::degCChanged(int c)
{
    qDebug() << "degC changed to" << c;
    if (c == ui->lcdNumber_c->intValue()) {
        return;
    }
    ui->lcdNumber_c->display(c);
    emit changeDegF(cToF(c));
}

void MainWindow::degFChanged(int f)
{
    qDebug() << "degF changed to" << f;
    if (f == ui->lcdNumber_f->intValue()) {
        return;
    }
    ui->lcdNumber_f->display(f);
    emit changeDegC(fToC(f));
}

int MainWindow::cToF(int c)
{
    return (int)(1.0 * c * 9 / 5 + 32);
}

int MainWindow::fToC(int f)
{
    return (int)((1.0 * f - 32) * 5 / 9);
}

MainWindow::~MainWindow()
{
    delete ui;
}
