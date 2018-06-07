#include "playlistmanager.h"

playListManager::playListManager()
{

}

void playListManager::add_new_playlist(const QString& name)
{

    vector<QString> newList;
    playListContainer[name] = newList;
}

//add new song(file path) to existing playlist
void playListManager::add_new_song_to(const QString& playListName, const QString &filePath)
{
    QString newFile = filePath;
    playListContainer[playListName].push_back(newFile);
}

//save a playlist
void playListManager::save_this_list(const QString& playListName, const QString& path)
{
    QString filename=playListName;
    QString _path = QDir::currentPath() + QString::fromStdString("/");
    QFile file( _path + filename + playList_extension);
    cout << (_path + filename + playList_extension).toStdString() << endl;
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream(&file);
        for(int i=0; i<playListContainer[playListName].size(); i++)
            stream << playListContainer[playListName][i] << endl;
        file.close();
    }
    //else: throw an error here!!

}

//save all playlists
void playListManager::save_all_playlists()
{
    //loop through the whole map
    // save each vector into a separate file
    QMap<QString, vector<QString>>::iterator i;
    for(i=playListContainer.begin(); i!=playListContainer.end(); ++i)
    {
        QString filename=i.key();
        QFile file(filename+playList_extension);
        if (file.open(QIODevice::ReadWrite))
        {
            QTextStream stream(&file);
            for(int j=0; j<i.value().size(); j++)
            {   //loop through this vector
                stream << i.value()[j] << endl;
            }
            file.close();
        }
    }
}

//load an existing playlist(into playListContainer so that mp3Player class can load from it)
void playListManager::load_this_playlist(const QString& filePath)
{
    int pos = filePath.lastIndexOf(playList_extension);
    QString playListName = filePath.left(pos);  //chop the extension off
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw BAD_FILE_PATH;
    vector<QString> this_list;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        this_list.push_back(line);
    }
    playListContainer[playListName] = this_list;
}

//getter for playListContainer(returns a reference)
QMap<QString, vector<QString>>&  playListManager:: get_play_list_container()
{
    return playListContainer;
}
