#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>

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
    void appendDigit(int i);

private:
    Ui::MainWindow *ui;
    QSignalMapper* m_signalMapper;
};

#endif // MAINWINDOW_H
