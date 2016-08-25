#include "datedialog.h"
#include "ui_datedialog.h"
#include <QRegExpValidator>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QtDebug>

DateDialog::DateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DateDialog)
{
    ui->setupUi(this);
    QRegExp monthRegExp("^(0?[1-9]|1[012])$");
    QRegExpValidator* monthValidator = new QRegExpValidator(monthRegExp, this);
    ui->lineEdit->setValidator(monthValidator);
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(checkRegExpLegal()));
    connect(ui->spinBox_month, SIGNAL(valueChanged(int)), this, SLOT(updateLegalDaysOfMonth()));
    connect(ui->spinBox_year, SIGNAL(valueChanged(int)), this, SLOT(updateLegalDaysOfMonth()));
}

int DateDialog::year()
{
    return (int)ui->spinBox_year->value();
}

int DateDialog::month()
{
    return (int)ui->spinBox_month->value();
}

int DateDialog::day()
{
    return (int)ui->spinBox_day->value();
}

void DateDialog::showEvent(QShowEvent *)
{
    if (!initialized) {
        initialized = true;
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

void DateDialog::checkRegExpLegal()
{
    qDebug() << "checking";
    if (ui->lineEdit->hasAcceptableInput()) {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    } else {
        qDebug() << "not acceptable";
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

void DateDialog::updateLegalDaysOfMonth()
{
    ui->spinBox_day->setMaximum(getNumLegalDaysOfMonth(
                                    ui->spinBox_year->value(),
                                    ui->spinBox_month->value()));
}

int DateDialog::getNumLegalDaysOfMonth(int year, int month)
{
    switch (month) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 2:
        if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) {
            return 29;
        }
        return 28;
    default:
        return 1;
    }
}

DateDialog::~DateDialog()
{
    delete ui;
}
