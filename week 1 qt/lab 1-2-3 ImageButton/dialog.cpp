#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_ImagePaths({ ":/images/img1.jpg", ":/images/img2.jpg", ":/images/img3.jpg" })
{
    ui->setupUi(this);
    ui->pushButton->setFlat(true);
    ui->pushButton->setAutoFillBackground(true);
    updateImage();
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(updateImage()));
}

void Dialog::updateImage()
{
    m_idx = (m_idx + 1) % m_ImagePaths.length();
    QPixmap pixmap(m_ImagePaths[m_idx]);
    QIcon icon(pixmap);
    ui->pushButton->setIcon(icon);
}

Dialog::~Dialog()
{
    delete ui;
}
