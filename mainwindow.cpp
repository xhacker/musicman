#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setHidden(true);
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
    ui->graphicsView->setHidden(false);
    hide_buttons();
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
