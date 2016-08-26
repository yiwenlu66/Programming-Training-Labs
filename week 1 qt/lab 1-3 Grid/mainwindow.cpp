#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dimensiondialog.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>

const int MainWindow::MAX_ROW_COL;
const int MainWindow::GRID_SIZE;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for (int i = 0; i < MAX_ROW_COL * MAX_ROW_COL; ++i) {
        highlighted[i] = false;
    }
    connect(ui->actionSet_Row_Column, SIGNAL(triggered(bool)), this, SLOT(updateDimensions()));
}

void MainWindow::updateDimensions()
{
    DimensionDialog dlg;
    if (0 < m_rows && m_rows < MAX_ROW_COL && 0 < m_cols && m_cols < MAX_ROW_COL) {
        dlg.setRows(m_rows);
        dlg.setCols(m_cols);
    }
    if (dlg.exec() == QDialog::Accepted) {
        if (m_rows != dlg.rows() || m_cols != dlg.cols()) {
            for (int i = 0; i < MAX_ROW_COL * MAX_ROW_COL; ++i) {
                highlighted[i] = false;
            }
            m_rows = dlg.rows();
            m_cols = dlg.cols();
            update();
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    for (int i = 0; i <= m_rows; ++i) {
        painter.save();
        painter.translate(0, i * GRID_SIZE);
        painter.drawLine(0, 0, m_cols * GRID_SIZE, 0);
        painter.restore();
    }
    for (int i = 0; i <= m_cols; ++i) {
        painter.save();
        painter.translate(i * GRID_SIZE, 0);
        painter.drawLine(0, 0, 0, m_rows * GRID_SIZE);
        painter.restore();
    }
    for (int i = 0; i < m_rows * m_cols; ++i) {
        if (highlighted[i]) {
            int x = i % m_cols;
            int y = i / m_cols;
            painter.save();
            painter.setBrush(Qt::red);
            painter.translate(x * GRID_SIZE, y * GRID_SIZE);
            painter.drawRect(0, 0, GRID_SIZE, GRID_SIZE);
            painter.restore();
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int x = event->x() / GRID_SIZE;
    int y = event->y() / GRID_SIZE;
    if (0 <= x && x < m_cols && 0 <= y && y < m_rows) {
        QMessageBox::information(this, "clicked", QString("(%1, %2)").arg(x).arg(y), QMessageBox::Ok);
        int i = y * m_cols + x;
        highlighted[i] = !highlighted[i];
        update();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
