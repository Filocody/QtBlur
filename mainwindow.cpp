#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    auto file = QFileDialog::getOpenFileName(nullptr, "Open image", "", "Image Files (*.png *.jpg *.bmp)");
    image = QImage(file);
    ui->label->setPixmap(file);
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->label->setPixmap(QPixmap::fromImage(blurImage(image, value).scaled(
                                                ui->label->width(),
                                                ui->label->height(), Qt::KeepAspectRatio)));
}

QImage MainWindow::blurImage(QImage source, int value)
{
    if (source.isNull()) return QImage();
    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    item.setPixmap(QPixmap::fromImage(source));

    auto *blur = new QGraphicsBlurEffect;
    blur->setBlurRadius(value);
    item.setGraphicsEffect(blur);
    scene.addItem(&item);
    QImage result(source.size(), QImage::Format_ARGB32);
    result.fill(Qt::transparent);
    QPainter painter(&result);
    scene.render(&painter, QRectF(), QRectF(0, 0, source.width(), source.height()));

    return result;
}
