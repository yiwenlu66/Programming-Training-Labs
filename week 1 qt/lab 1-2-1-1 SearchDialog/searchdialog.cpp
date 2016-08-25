#include "searchdialog.h"
#include "ui_searchdialog.h"

SearchDialog::SearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);
}

void SearchDialog::setText(const QString& str)
{
    ui->lineEdit->setText(str);
}

void SearchDialog::setIsBackward(bool isBackward)
{
    if (isBackward) {
        ui->radioButton_backward->setChecked(true);
    } else {
        ui->radioButton_forward->setChecked(true);
    }
}

QString SearchDialog::text() const
{
    return ui->lineEdit->text();
}

bool SearchDialog::isBackward() const
{
    return ui->radioButton_backward->isChecked();
}

SearchDialog::~SearchDialog()
{
    delete ui;
}
