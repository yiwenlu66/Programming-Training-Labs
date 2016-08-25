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
    bool eventFilter(QObject *watched, QEvent *event);
    void mousePressEvent(QMouseEvent* e);
    void closeEvent(QCloseEvent* e);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void printLog(const QString& log);
};

#endif // MAINWINDOW_H
