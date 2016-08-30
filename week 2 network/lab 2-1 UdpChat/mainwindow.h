#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QtNetwork/QUdpSocket>

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
    void bind();
    void sendMessage();
    void receiveMessage();

private:
    Ui::MainWindow *ui;
    int m_port;
    QUdpSocket* m_udpSocket;
};

#endif // MAINWINDOW_H
