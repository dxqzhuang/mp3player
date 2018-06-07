#ifndef PLAYLISTMANAGER_H
#define PLAYLISTMANAGER_H
#include <QString>
#include <vector>
#include <QMap>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QDir>
using namespace std;

enum ERRORS{PLAYLIST_NOT_EXIST, BAD_FILE_PATH, UNKNOWN_ERROR};

class playListManager
{
    //each playlist file contains paths to mp3 files.
    // each line is full directory to mp3 file followed by new line.
public:
    playListManager();
    //add new playlist
    void add_new_playlist(const QString& name);
    //add new song(file path) to existing playlist
    void add_new_song_to(const QString& playListName, const QString& filePath);
    //save a playlist
    void save_this_list(const QString& playListName,const QString& path="");
    //save all playlists
    void save_all_playlists();
    //load an existing playlist(into playListContainer so that mp3Player class can load from it)
    void load_this_playlist(const QString& filePath);
    //getter for playListContainer(returns a reference)
    QMap<QString, vector<QString>>& get_play_list_container();

private:
    //container of playlists. each playlist contains the directories of files
    /**
      FORMAT AS FOLLOWING:
     *  [   //map
     *   {"list1", {"filename1", "filename2", "filename3"}}, //key value pair: list name, list
     *   ["list2", {"filename1", "filename2", "filename3"}],
     *   ...
     *  ]
     */

    const QString playList_extension = QString::fromStdString(".playlist");
    QMap<QString, vector<QString>> playListContainer;

};

#endif // PLAYLISTMANAGER_H
