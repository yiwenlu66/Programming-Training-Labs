#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:
    void updateImage();

private:
    Ui::Dialog *ui;
    QStringList m_ImagePaths;
    int m_idx = 0;
};

#endif // DIALOG_H
