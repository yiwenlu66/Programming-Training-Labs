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
    static const int MAX_ROW_COL = 20;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateDimensions();

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);

private:
    static const int GRID_SIZE = 20;
    Ui::MainWindow *ui;
    int m_rows = -1;
    int m_cols = -1;
    bool highlighted[MAX_ROW_COL * MAX_ROW_COL];
};

#endif // MAINWINDOW_H
