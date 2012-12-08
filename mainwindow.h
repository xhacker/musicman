#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "canvas.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_tutorialButton_clicked();

    void on_playButton_clicked();

    void on_quitButton_clicked();

private:
    Ui::MainWindow *ui;
    Canvas *canvas;
    void hide_buttons();
};

#endif // MAINWINDOW_H
