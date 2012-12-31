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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::play()
{
    music_guitar->play();
    music_song->play();
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

    QDir songdir(QDir::home().absoluteFilePath(".musicman/songs/Escape from Chaosland/"));

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

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), canvas, SLOT(animate()));
    timer->start(20);
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
