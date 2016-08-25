#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_signalMapper(new QSignalMapper(this))
{
    ui->setupUi(this);
    connect(ui->pushButton_0, SIGNAL(clicked()), m_signalMapper, SLOT(map()));
    connect(ui->pushButton_1, SIGNAL(clicked()), m_signalMapper, SLOT(map()));
    connect(ui->pushButton_2, SIGNAL(clicked()), m_signalMapper, SLOT(map()));
    connect(ui->pushButton_3, SIGNAL(clicked()), m_signalMapper, SLOT(map()));
    connect(ui->pushButton_4, SIGNAL(clicked()), m_signalMapper, SLOT(map()));
    connect(ui->pushButton_5, SIGNAL(clicked()), m_signalMapper, SLOT(map()));
    connect(ui->pushButton_6, SIGNAL(clicked()), m_signalMapper, SLOT(map()));
    connect(ui->pushButton_7, SIGNAL(clicked()), m_signalMapper, SLOT(map()));
    connect(ui->pushButton_8, SIGNAL(clicked()), m_signalMapper, SLOT(map()));
    connect(ui->pushButton_9, SIGNAL(clicked()), m_signalMapper, SLOT(map()));
    m_signalMapper->setMapping(ui->pushButton_0, 0);
    m_signalMapper->setMapping(ui->pushButton_1, 1);
    m_signalMapper->setMapping(ui->pushButton_2, 2);
    m_signalMapper->setMapping(ui->pushButton_3, 3);
    m_signalMapper->setMapping(ui->pushButton_4, 4);
    m_signalMapper->setMapping(ui->pushButton_5, 5);
    m_signalMapper->setMapping(ui->pushButton_6, 6);
    m_signalMapper->setMapping(ui->pushButton_7, 7);
    m_signalMapper->setMapping(ui->pushButton_8, 8);
    m_signalMapper->setMapping(ui->pushButton_9, 9);
    connect(m_signalMapper, SIGNAL(mapped(int)), this, SLOT(appendDigit(int)));
}

void MainWindow::appendDigit(int i)
{
    qDebug() << i << "clicked";
    ui->lcdNumber->display(QString::number(ui->lcdNumber->intValue()) + QString::number(i));
}

MainWindow::~MainWindow()
{
    delete m_signalMapper;
    delete ui;
}
