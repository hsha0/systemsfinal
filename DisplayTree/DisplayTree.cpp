#include "DisplayTree.h"
#include "ui_DisplayTree.h"
#include <QtOpenGL>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void QWidget::paintEvent(QPaintEvent *)
{
    QPainter p;
}
