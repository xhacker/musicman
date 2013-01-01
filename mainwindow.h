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
    void play_music();
    void stop_music();
    void setGuitarMuted(bool);
    void game_finished();

private slots:
    void menu_sound_finished();

    void redraw_canvas();

    void on_tutorialButton_clicked();

    void on_playButton_clicked();

    void on_quitButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    Canvas *canvas;
    void hide_buttons();
    void show_buttons();

    Phonon::MediaObject *music_guitar;
    Phonon::AudioOutput *music_guitar_output;
    Phonon::MediaObject *music_song;
    Phonon::AudioOutput *music_song_output;
    Phonon::MediaObject *sound_menu;
};

#endif // MAINWINDOW_H
