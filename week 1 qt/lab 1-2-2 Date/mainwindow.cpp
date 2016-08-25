#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datedialog.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionDate_Dialog, SIGNAL(triggered(bool)), this, SLOT(showDateDialog()));
}

void MainWindow::showDateDialog()
{
    DateDialog dlg(this);
    dlg.exec();
    qDebug() << dlg.year() << "-" << dlg.month() << "-" << dlg.day();
}

MainWindow::~MainWindow()
{
    delete ui;
}
