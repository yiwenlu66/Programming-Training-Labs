#include "dimensiondialog.h"
#include "ui_dimensiondialog.h"
#include "mainwindow.h"
#include <QPushButton>

DimensionDialog::DimensionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DimensionDialog),
    m_validator(new QIntValidator(1, MainWindow::MAX_ROW_COL, this))
{
    ui->setupUi(this);
    ui->lineEdit_rows->setValidator(m_validator);
    ui->lineEdit_cols->setValidator(m_validator);
    connect(ui->lineEdit_rows, SIGNAL(textChanged(QString)), this, SLOT(checkLegal()));
    connect(ui->lineEdit_cols, SIGNAL(textChanged(QString)), this, SLOT(checkLegal()));
}

int DimensionDialog::rows() const
{
    return ui->lineEdit_rows->text().toInt();
}

int DimensionDialog::cols() const
{
    return ui->lineEdit_cols->text().toInt();
}

void DimensionDialog::setRows(int rows)
{
    ui->lineEdit_rows->setText(QString::number(rows));
}

void DimensionDialog::setCols(int cols)
{
    ui->lineEdit_cols->setText(QString::number(cols));
}

void DimensionDialog::showEvent(QShowEvent *)
{
    if (!initialized) {
        initialized = true;
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

void DimensionDialog::checkLegal()
{
    if (ui->lineEdit_rows->hasAcceptableInput() && ui->lineEdit_cols->hasAcceptableInput()) {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    } else {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

DimensionDialog::~DimensionDialog()
{
    delete ui;
    delete m_validator;
}
