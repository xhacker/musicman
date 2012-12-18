#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <Phonon>
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
    void play();

private slots:
    void on_tutorialButton_clicked();

    void on_playButton_clicked();

    void on_quitButton_clicked();

private:
    Ui::MainWindow *ui;
    Canvas *canvas;
    void hide_buttons();

    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    Phonon::MediaObject *music_guitar;
    Phonon::MediaObject *music_song;
    Phonon::AudioOutput *music_song_output;
};

#endif // MAINWINDOW_H
