#ifndef DATEDIALOG_H
#define DATEDIALOG_H

#include <QDialog>

namespace Ui {
class DateDialog;
}

class DateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DateDialog(QWidget *parent = 0);
    ~DateDialog();
    int year();
    int month();
    int day();

public slots:
    void checkRegExpLegal();
    void updateLegalDaysOfMonth();

protected:
    virtual void showEvent(QShowEvent *);

private:
    Ui::DateDialog *ui;
    bool initialized = false;
    int getNumLegalDaysOfMonth(int year, int month);
};

#endif // DATEDIALOG_H
