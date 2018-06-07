#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H
#include <vector>
#include <QString>
#include <playlistmanager.h>
using namespace std;

class libraryManager
{
    //interact with mp3player class and playListManager class
    //mainly does the following:
    //manages ALL songs, whether they are in playlist or not
public:
    libraryManager();
    //push new song into songs list
    void add_new_song(const QString& path);

    //add the selected group of songs(indexes) into a playlist with specified name
    void group_these_into_play_list(vector<int> indeces, const QString& playList_name);

    //save a given playlist
    void save_this_list(const QString& listName, const QString& path="");

    //load a playlist with specified name
    void load_this_list(const QString list_path);

    vector<QString>& get_songs();



private:
    playListManager playList_manager;
    vector<QString> songs;  //all the songs the user has selected
};

#endif // LIBRARYMANAGER_H
