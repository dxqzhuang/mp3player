#ifndef MP3PLAYER_H
#define MP3PLAYER_H
#include <QMediaPlayer>
using namespace std;
enum MP3_PLAYER_ERRORS{FILE_NOT_FOUND};
class mp3Player
{
public:
    mp3Player();

    void play(const QString& file); //file: full directory of file name
    void togglePlay();

private:
    bool paused;
    QMediaPlayer player;

};

#endif // MP3PLAYER_H
