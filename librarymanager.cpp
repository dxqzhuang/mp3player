#include "librarymanager.h"

libraryManager::libraryManager()
{

}

//push new song into songs list
void libraryManager::add_new_song(const QString& path)
{
    QString new_song_path = path;
    songs.push_back(new_song_path);
}

//add the selected group of songs(indexes) into a playlist with specified name
void libraryManager::group_these_into_play_list(vector<int> indeces, const QString& playList_name)
{
    playList_manager.add_new_playlist(playList_name);
    for(int i=0; i<indeces.size(); i++)
    {
        int index = indeces[i];
        QString song_path_name = songs[index];
        playList_manager.add_new_song_to(playList_name,song_path_name);
    }
}

//save a given playlist
void libraryManager::save_this_list(const QString& listName, const QString& path)
{
    playList_manager.save_this_list(listName, path);
}

//load a playlist with specified name!! DO THIS
void libraryManager::load_this_list(const QString list_path)
{

    //load into playlistmanager first
    playList_manager.load_this_playlist(list_path);
    //then push all of the loaded paths into songs vector
    for(int i=0; i<playList_manager.get_play_list_container().last().size(); i++)
        songs.push_back(playList_manager.get_play_list_container().last()[i]);

    //to be completed!!!
}

vector<QString>& libraryManager::get_songs(){
    return songs;
}
