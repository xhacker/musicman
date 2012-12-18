#include <Phonon>
#include <QKeyEvent>
#include <QTimer>
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

void MainWindow::on_tutorialButton_clicked()
{
}

void MainWindow::on_playButton_clicked()
{
    hide_buttons();
    canvas = new Canvas(this);
    canvas->resize(this->size());
    canvas->show();

    music_guitar = Phonon::createPlayer(Phonon::MusicCategory,
      Phonon::MediaSource("/Users/xhacker/Dropbox/Project/musicman-build-Desktop-Debug/Feelings/guitar.mp3"));
    music_guitar->play();

    music_song = new Phonon::MediaObject(this);
    music_song->setCurrentSource(Phonon::MediaSource("/Users/xhacker/Dropbox/Project/musicman-build-Desktop-Debug/Feelings/song.mp3"));
    music_song_output =
        new Phonon::AudioOutput(Phonon::MusicCategory, this);
    Phonon::Path path = Phonon::createPath(music_song, music_song_output);
    music_song->play();
    music_song_output->setMuted(true);
    Midi midi("/Users/xhacker/Dropbox/Project/musicman-build-Desktop-Debug/Feelings/notes.mid");
//    canvas->setNotes(midi.parse());

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), canvas, SLOT(animate()));
    timer->start(25);
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

void MainWindow::keyPressEvent(QKeyEvent *event)
{
   if (event->key() >= Qt::Key_1 && event->key() <= Qt::Key_5)
   {
       music_song_output->setMuted(false);
       canvas->setPressing(event->key() - Qt::Key_1 + 1, true);
   }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
   if (event->key() >= Qt::Key_1 && event->key() <= Qt::Key_5)
   {
       music_song_output->setMuted(true);
       canvas->setPressing(event->key() - Qt::Key_1 + 1, false);
   }
}
