#ifndef MP3PLAYER_H
#define MP3PLAYER_H
#include <QMediaPlayer>
#include <QDir>
#include <librarymanager.h>
#include <QMediaMetaData>
#include <QObject>
#include <QWidget>
using namespace std;
enum MP3_PLAYER_ERRORS{FILE_NOT_FOUND};

class mp3Player : public QObject
{
    Q_OBJECT
public:
    //sole responsibility of playing music

    mp3Player(QObject* parent=0);
    ~mp3Player();
    void connectSignalSlots();


    void play(const QString& file);     //file: full directory of file name
    void togglePlay();

private:
    bool paused;
    QMediaPlayer player;

private slots:
    void output_meta_data();

};

#endif // MP3PLAYER_H
