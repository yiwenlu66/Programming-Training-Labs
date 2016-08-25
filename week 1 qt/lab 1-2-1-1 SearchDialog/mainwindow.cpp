#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_dialog(new SearchDialog(this))
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(showDialog()));
}

void MainWindow::showDialog()
{
    m_dialog->exec();
    qDebug() << "text:" << m_dialog->text();
    qDebug() << "isBackward:" << m_dialog->isBackward();
}

MainWindow::~MainWindow()
{
    delete m_dialog;
    delete ui;
}
