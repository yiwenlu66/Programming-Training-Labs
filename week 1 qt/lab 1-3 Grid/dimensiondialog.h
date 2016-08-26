#ifndef DIMENSIONDIALOG_H
#define DIMENSIONDIALOG_H

#include <QDialog>
#include <QIntValidator>

namespace Ui {
class DimensionDialog;
}

class DimensionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DimensionDialog(QWidget *parent = 0);
    int rows() const;
    int cols() const;
    void setRows(int);
    void setCols(int);
    ~DimensionDialog();

protected:
    virtual void showEvent(QShowEvent *);

public slots:
    void checkLegal();

private:
    Ui::DimensionDialog *ui;
    QIntValidator* m_validator;
    bool initialized = false;
};

#endif // DIMENSIONDIALOG_H
