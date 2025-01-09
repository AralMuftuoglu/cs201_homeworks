//
// Aral Müftüoğlu
// 22201566
// Section 3
//

#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <string>

#include "LinkedList.h"
#include "Song.h"
using namespace std;


class Playlist {
public:
    Playlist();
    Playlist(int ID, int userId);
    ~Playlist();
    int getPlayListID();
    LinkedList<Song>& getSongs();
    Playlist& operator=(const Playlist& other);
private:
    int playlistID;
    int userID;
    LinkedList<Song> songsInPlaylist;
};



#endif //PLAYLIST_H
