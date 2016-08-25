#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void degCChanged(int);
    void degFChanged(int);

signals:
    void changeDegC(int);
    void changeDegF(int);

private:
    Ui::MainWindow *ui;

    static int cToF(int c);
    static int fToC(int f);
};

#endif // MAINWINDOW_H
