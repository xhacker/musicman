#include <Phonon>
#include <QKeyEvent>
#include <QTimer>
#include <QDir>
#include <QString>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvas.h"
#include "midi.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->verticalLayout->setAlignment(Qt::AlignCenter);

    timer = new QTimer(this);

    sound_menu = new Phonon::MediaObject(this);
    createPath(sound_menu, new Phonon::AudioOutput(Phonon::MusicCategory, this));
    sound_menu->setCurrentSource(Phonon::MediaSource(":/sound/menu.mp3"));
    QObject::connect(sound_menu, SIGNAL(aboutToFinish()), SLOT(menu_sound_finished()));
    sound_menu->setTransitionTime(-270);
    sound_menu->play();
}

void MainWindow::menu_sound_finished()
{
    sound_menu->enqueue(Phonon::MediaSource(":/sound/menu.mp3"));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

void MainWindow::play_music()
{
    music_guitar->play();
    music_song->play();
}

void MainWindow::stop_music()
{
    music_guitar->stop();
    music_song->stop();
}

void MainWindow::setGuitarMuted(bool muted)
{
    if (muted)
        music_guitar_output->setVolume(0.4);
    else
        music_guitar_output->setVolume(1.0);
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

    sound_menu->stop();
    Phonon::MediaObject *sound_start = new Phonon::MediaObject(this);
    createPath(sound_start, new Phonon::AudioOutput(Phonon::MusicCategory, this));
    sound_start->setCurrentSource(Phonon::MediaSource(":/sound/start.mp3"));
    sound_start->play();

    QDir songdir(QDir::home().absoluteFilePath(".musicman/songs/Hello/"));

    music_guitar = new Phonon::MediaObject(this);
    music_guitar->setCurrentSource(Phonon::MediaSource(songdir.absoluteFilePath("guitar.mp3")));
    music_guitar_output =
        new Phonon::AudioOutput(Phonon::MusicCategory, this);
    Phonon::createPath(music_guitar, music_guitar_output);

    music_song = new Phonon::MediaObject(this);
    music_song->setCurrentSource(Phonon::MediaSource(songdir.absoluteFilePath("song.mp3")));
    music_song_output =
        new Phonon::AudioOutput(Phonon::MusicCategory, this);
    Phonon::createPath(music_song, music_song_output);

    Midi midi(songdir.absoluteFilePath("notes.musicman").toStdString());
    midi.parse();
    canvas->setMidi(midi);

    canvas->setTotalTime(music_song->totalTime());
    connect(timer, SIGNAL(timeout()), SLOT(redraw_canvas()));
    timer->start(20);
}

void MainWindow::redraw_canvas()
{
    if(!canvas->isFinished())
    {
        canvas->animate();
    }
    else
    {
        game_finished();
    }
}

void MainWindow::game_finished()
{
    timer->stop();
    stop_music();
    delete canvas;
    show_buttons();
    sound_menu->play();
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

void MainWindow::show_buttons()
{
    ui->playButton->setHidden(false);
    ui->tutorialButton->setHidden(false);
    ui->quitButton->setHidden(false);
}
