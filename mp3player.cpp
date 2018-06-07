#include "mp3player.h"

mp3Player::mp3Player()
{
    paused = false;
}


void mp3Player::play(const QString& file)
{
    player.setMedia(QUrl::fromLocalFile(file));
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
