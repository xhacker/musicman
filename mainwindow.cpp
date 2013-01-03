#include <iostream>
#include <QKeyEvent>
#include <QTimer>
#include <QDir>
#include <QString>
#include <QListWidget>
#include <Phonon>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvas.h"
#include "midi.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    cur_scene(main)
{
    ui->setupUi(this);
    ui->verticalLayout->setAlignment(Qt::AlignCenter);

    setStyleSheet(QString("font-family: 'Avenir Next';"));
    setStyleSheet(QString("QPushButton { font-size: 40px; font-weight: bold; }"));

    timer = new QTimer(this);

    sound_menu = new Phonon::MediaObject(this);
    createPath(sound_menu, new Phonon::AudioOutput(Phonon::MusicCategory, this));
    sound_menu->setCurrentSource(Phonon::MediaSource(":/sound/menu.mp3"));
    QObject::connect(sound_menu, SIGNAL(aboutToFinish()), SLOT(menu_sound_finished()));
    sound_menu->setTransitionTime(-270);
    sound_menu->play();

    musiclist = new QListWidget(this);
    musiclist->show();
    musiclist->setVisible(false);
    musiclist->setStyleSheet(QString("font-size: 40px; font-weight: bold;"));

    ui->scoreLabel->setVisible(false);
    ui->nameEdit->setVisible(false);
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
    cur_scene = list;
    hide_buttons();
    musiclist->setVisible(true);
    musiclist->setFocus();

    QDir dir_songs(QDir::home().absoluteFilePath(".musicman/songs/"));
    musiclist->clear();
    musiclist->addItems(dir_songs.entryList(QDir::Dirs | QDir::NoDotAndDotDot));
    if (musiclist->count() > 0)
        musiclist->setCurrentItem(musiclist->item(0));
}

void MainWindow::start_game(QString music_name)
{
    cur_scene = game;

    sound_menu->stop();
    Phonon::MediaObject *sound_start = new Phonon::MediaObject(this);
    createPath(sound_start, new Phonon::AudioOutput(Phonon::MusicCategory, this));
    sound_start->setCurrentSource(Phonon::MediaSource(":/sound/start.mp3"));
    sound_start->play();

    QDir dir_music(QDir::home().absoluteFilePath(QString(".musicman/songs/%1/").arg(music_name)));

    music_guitar = new Phonon::MediaObject(this);
    music_guitar->setCurrentSource(Phonon::MediaSource(dir_music.absoluteFilePath("guitar.mp3")));
    music_guitar_output =
        new Phonon::AudioOutput(Phonon::MusicCategory, this);
    Phonon::createPath(music_guitar, music_guitar_output);

    music_song = new Phonon::MediaObject(this);
    music_song->setCurrentSource(Phonon::MediaSource(dir_music.absoluteFilePath("song.mp3")));
    music_song_output =
        new Phonon::AudioOutput(Phonon::MusicCategory, this);
    Phonon::createPath(music_song, music_song_output);

    canvas = new Canvas(this);
    Midi midi(dir_music.absoluteFilePath("notes.musicman").toStdString());
    midi.parse();
    canvas->setMidi(midi);
    canvas->setTotalTime(music_song->totalTime());
    canvas->resize(this->size());
    canvas->show();

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

    // score
    cur_scene = score;
    ui->scoreLabel->setText(QString("Score: %1").arg(canvas->getScore()));
    ui->scoreLabel->setVisible(true);
    ui->nameEdit->setVisible(true);

    delete canvas;
    setFocus();
    ui->nameEdit->setFocus();
}

void MainWindow::on_nameEdit_returnPressed()
{
    // highscore
    cur_scene = highscore;
    ui->scoreLabel->setVisible(false);
    ui->nameEdit->setVisible(false);

    // return to main
    cur_scene = main;
//    musiclist->setVisible(true);
    show_buttons();
    sound_menu->play();
}

void MainWindow::on_quitButton_clicked()
{
    QApplication::quit();
}

void MainWindow::hide_buttons()
{
    ui->playButton->setVisible(false);
    ui->tutorialButton->setVisible(false);
    ui->quitButton->setVisible(false);
}

void MainWindow::show_buttons()
{
    ui->playButton->setVisible(true);
    ui->tutorialButton->setVisible(true);
    ui->quitButton->setVisible(true);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
    {
        if (cur_scene == list)
        {
            musiclist->setVisible(false);
            start_game(musiclist->currentItem()->text());
        }
    }
    else if (event->key() == Qt::Key_Escape)
    {
        if (cur_scene == list)
        {
            musiclist->setVisible(false);
            show_buttons();
            cur_scene = main;
        }
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    musiclist->resize(size());
}
