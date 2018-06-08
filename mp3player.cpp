#include "mp3player.h"

mp3Player::mp3Player(QObject *parent) :
    QObject(parent)
{
    paused = false;
}

mp3Player::~mp3Player()
{

}


void mp3Player::connectSignalSlots()
{

}

void mp3Player::play(const QString& file)
{
    player.setMedia(QUrl::fromLocalFile(file));

    QObject::connect(&player,
                     SIGNAL(mediaStatusChanged(QMediaPlayer::LoadedMedia)),
                     this,
                     SLOT(output_meta_data()));
    player.setVolume(50);
    player.play();
}

void mp3Player::togglePlay()
{
    if(paused)
        player.play();
    else
        player.pause();
    paused = !paused;
}

void mp3Player::output_meta_data()
{
    QString author = player.metaData(QMediaMetaData::Author).toString();
    cout << "author: " << author.toStdString() << endl;
}
