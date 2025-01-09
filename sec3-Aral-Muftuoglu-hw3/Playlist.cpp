//
// Aral Müftüoğlu
// 22201566
// Section 3
//

#include "Playlist.h"

Playlist::Playlist() {
    playlistID = 0;
    userID = 0;
}

Playlist::~Playlist(){}

Playlist::Playlist(int ID, int userId) {
    playlistID = ID;
    userID = userId;
}
int Playlist::getPlayListID() {
    return playlistID;
}

LinkedList<Song>& Playlist::getSongs() {
    return songsInPlaylist;
}

Playlist& Playlist::operator=(const Playlist& other) {
    if (this != &other) {
        playlistID = other.playlistID;
        userID = other.userID;
        songsInPlaylist = other.songsInPlaylist;
    }
    return *this;
}

