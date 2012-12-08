#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvas.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->verticalLayout->setAlignment(Qt::AlignCenter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tutorialButton_clicked()
{
}

void MainWindow::on_playButton_clicked()
{
    hide_buttons();
    canvas = new Canvas(this);
    canvas->resize(this->size());
    canvas->show();
}

void MainWindow::on_quitButton_clicked()
{
    QApplication::quit();
}

void MainWindow::hide_buttons()
{
    ui->playButton->setHidden(true);
    ui->tutorialButton->setHidden(true);
    ui->quitButton->setHidden(true);
}
