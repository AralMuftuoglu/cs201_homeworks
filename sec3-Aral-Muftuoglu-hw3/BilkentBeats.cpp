//
// Aral Müftüoğlu
// 22201566
// Section 3
//

#include "BilkentBeats.h"

BilkentBeats::BilkentBeats() {
}

BilkentBeats::~BilkentBeats() {
}

//Users
//add user
void BilkentBeats::addUser(const int userId, const string userName) {
    bool ableToAdd = true;

    for (int i = 1; i <= users.getLength(); i++) {
        if (userId == users.getItem(i).getId()) {
            ableToAdd = false;
            break;
        }
    }

    if (ableToAdd) {
        User newUser(userName, userId);
        int indexToInsert = -1;

        //it is the first element in list
        if (users.getLength() == 0) {
            indexToInsert = 1;
            users.insert(indexToInsert, newUser);
        } else {
            //find the bigger number
            for (int i = 1; i <= users.getLength(); i++) {
                if (userId < users.getItem(i).getId()) {
                    indexToInsert = i;
                    break;
                }
            }

            //for the condition that it is the biggest
            if (indexToInsert == -1) {
                indexToInsert = users.getLength() + 1;
            }

            users.insert(indexToInsert, newUser);
        }

        cout << "Added user " << userId <<"."<< endl;
    } else {
        cout << "Cannot add user. There is already a user with ID " << userId << "." << endl;
    }
}

//remove user method
void BilkentBeats::removeUser(const int userId) {

    bool ableToRemove = false;
    int indexToRemove = -1;

    for (int i = 1; i <= users.getLength(); i++) {
        if (userId == users.getItem(i).getId()) {
            ableToRemove = true;
            indexToRemove = i;
            break;
        }
    }

    if(!ableToRemove) {
        cout << "Cannot remove user. There is no user with ID " << userId <<"."<<endl;
    }
    else {
        int playlistIndexToRemove = -1;
        int playlistIDToRemove = 0;

        for (int i = 1; i <= users.getItem(indexToRemove).getPlaylists().getLength(); i++) {
            playlistIDToRemove = users.getItem(indexToRemove).getPlaylists().getItem(i).getPlayListID();

            //remove the user's playlists from all playlists list
            for (int j = 1; j <= playlists.getLength(); j++) {
                if (playlistIDToRemove == playlists.getItem(j).getPlayListID()) {
                    playlistIndexToRemove = j;
                    playlists.remove(playlistIndexToRemove);
                    break;
                }
            }
        }

        //remove playlists from users own playlists list
        User newUser = users.getItem(indexToRemove);
        newUser.getPlaylists().clear();
        users.replace(indexToRemove, newUser);

        //remove user from users
        users.remove(indexToRemove);

        cout << "Removed user " << userId <<"."<<endl;
    }
}

//print users method
void BilkentBeats::printUsers() const {
    bool ableToPrint = false;

    if (users.getLength() > 0) {
        ableToPrint = true;
    }

    if (!ableToPrint) {
        cout<<"There are no users to show."<<endl;
    }
    else {

        cout<<"Users in the system:"<<endl;

        for (int i = 1; i <= users.getLength(); i++) {
            cout<<"User ID : "<<users.getItem(i).getId()<<", Name : "<<users.getItem(i).getName()<<", Playlist IDs : ";

            if(users.getItem(i).getPlaylists().getLength() > 0) {
                cout<<"["<<users.getItem(i).getPlaylists().getItem(1).getPlayListID();

                if(users.getItem(i).getPlaylists().getLength() > 1) {
                    for (int j = 2; j <= users.getItem(i).getPlaylists().getLength(); j++) {
                        cout<<","<<users.getItem(i).getPlaylists().getItem(j).getPlayListID();
                    }
                }

                cout<<"]"<<endl;
            }
            else {
                cout<<"None"<<endl;
            }
        }
    }
}


//Songs
//add song method
void BilkentBeats::addSong(const int songID, const string songName, const string artists) {
    bool ableToAdd = true;

    for (int i = 1; i <= songs.getLength(); i++) {
        if (songID == songs.getItem(i).getId()) {
            ableToAdd = false;
            break;
        }
    }

    if (ableToAdd) {
        Song newSong(songID, songName, artists);

        int indexToInsert = -1;

        //it is the first element in list
        if (songs.getLength() == 0) {
            indexToInsert = 1;
            songs.insert(indexToInsert, newSong);
        } else {
            //find the bigger number
            for (int i = 1; i <= songs.getLength(); i++) {
                if (songID < songs.getItem(i).getId()) {
                    indexToInsert = i;
                    break;
                }
            }

            //for the condition that it is the biggest
            if (indexToInsert == -1) {
                indexToInsert = songs.getLength() + 1;
            }

            songs.insert(indexToInsert, newSong);
        }

        cout << "Added song " << songID <<"."<< endl;
    } else {
        cout << "Cannot add song. BilkentBeats already contains song " << songID << "." << endl;
    }
}

//remove song method
void BilkentBeats::removeSong(const int songID) {
    bool ableToRemove = false;
    int indexToRemove = -1;

    for (int i = 1; i <= songs.getLength(); i++) {
        if (songID == songs.getItem(i).getId()) {
            ableToRemove = true;
            indexToRemove = i;
            break;
        }
    }

    if (ableToRemove) {
        //remove the song from all playlists
        for (int i = 1; i <= playlists.getLength(); i++) {
            for (int j = 1; j <= playlists.getItem(i).getSongs().getLength(); j++) {
                if (playlists.getItem(i).getSongs().getItem(j).getId() == songID) {

                    Playlist new_playlist = playlists.getItem(i);
                    new_playlist.getSongs().remove(j);
                    playlists.replace(i, new_playlist);
                }
            }
        }

        //remove the song from songs list
        songs.remove(indexToRemove);
        cout << "Removed song " << songID << "." << endl;
    } else {
        cout << "Cannot remove song. There is no song with ID " << songID << "." << endl;
    }
}

//print songs method
void BilkentBeats::printSongs() const {

    bool ableToPrint = false;

    if (songs.getLength() > 0) {
        ableToPrint = true;
    }

    if (!ableToPrint) {
        cout<<"Cannot print songs. There is no song in the music library."<<endl;
    }
    else {
        cout<<"Music Library:"<<endl;

        for (int i = 1; i <= songs.getLength(); i++) {
            cout << "Song " << songs.getItem(i).getId() << " : " << songs.getItem(i).getName() << " - " << songs.getItem(i).
                    getArtists() << endl;
        }
    }

}

//Playlists
//add playlist method
void BilkentBeats::addPlaylist(const int userId, const int playlistId) {
    bool ableToAdd = false;
    int index = -1; //to silence the compiler

    for (int i = 1; i <= users.getLength(); i++) {
        if (userId == users.getItem(i).getId()) {
            ableToAdd = true;
            index = i;
            break;
        }
    }

    if (!ableToAdd) {
        cout << "Cannot add playlist. There is no user with ID " << userId << "." << endl;
    } else {
        for (int i = 1; i <= playlists.getLength(); i++) {
            if (playlistId == playlists.getItem(i).getPlayListID()) {
                ableToAdd = false;
                break;
            }
        }

        if (ableToAdd) {
            Playlist newPlayList(playlistId, userId);
            playlists.insert(playlists.getLength() + 1, newPlayList);

            User newUser = users.getItem(index);
            newUser.getPlaylists().insert(newUser.getPlaylists().getLength()+1, newPlayList);
            users.replace(index, newUser);

            cout << "Added playlist " << playlistId << " to user " << userId << "." << endl;
        } else {
            cout << "Cannot add playlist. There is a user having a playlist with ID " << playlistId << "." << endl;
        }
    }


}

//remove playlist method
void BilkentBeats::removePlaylist(const int userId, const int playlistId) {
    bool ableToRemove = false;
    int indexToRemove = -1;
    int playListIndex = -1;

    for (int i = 1; i <= users.getLength(); i++) {
        if (userId == users.getItem(i).getId()) {
            ableToRemove = true;
            indexToRemove = i;
            break;
        }
    }

    if (!ableToRemove) {
        cout << "Cannot remove playlist. There is no user with ID " << userId << "." << endl;
    } else {
        for (int i = 1; i <= users.getItem(indexToRemove).getPlaylists().getLength(); i++) {
            if (playlistId == users.getItem(indexToRemove).getPlaylists().getItem(i).getPlayListID()) {
                playListIndex = i;
                break;
            }
        }
        //that playlist does not exist in the user
        if (playListIndex == -1) {
            ableToRemove = false;
        }

        if (ableToRemove) {

            User newUser = users.getItem(indexToRemove);
            newUser.getPlaylists().remove(playListIndex);
            users.replace(indexToRemove, newUser);

            cout << "Removed playlist " << playlistId << " from user " << userId << "." << endl;

            int indexAtAllPlaylists = -1;
            for (int i = 1; i <= playlists.getLength(); i++) {
                if (playlistId == playlists.getItem(i).getPlayListID()) {
                    indexAtAllPlaylists = i;
                    break;
                }
            }
            //remove it from all playlists
            playlists.remove(indexAtAllPlaylists);
        } else {
            cout << "Cannot remove playlist. User " << userId << " does not have a playlist with ID " << playlistId << "."
                    << endl;
        }
    }


}

//Playlists and songs
//add song to playlist method
void BilkentBeats::addSongToPlaylist(const int playlistId, const int songId) {
    bool ableToAdd = false;
    int playlistIndex = -1;
    int songIndex = -1;

    for (int i = 1; i <= playlists.getLength(); i++) {
        if (playlistId == playlists.getItem(i).getPlayListID()) {
            ableToAdd = true;
            playlistIndex = i;
            break;
        }
    }

    if (!ableToAdd) {
        cout << "Cannot add song. There is no playlist with ID " << playlistId << "." << endl;
    } else {
        ableToAdd = false; //change the condition for checking existence of the song
        for (int i = 1; i <= songs.getLength(); i++) {
            if (songs.getItem(i).getId() == songId) {
                ableToAdd = true;
                songIndex = i;
                break;
            }
        }

        if (!ableToAdd) {
            cout << "Cannot add song. There is no song with ID " << songId << "." << endl;
        } else {
            for (int i = 1; i <= playlists.getItem(playlistIndex).getSongs().getLength(); i++) {
                if (playlists.getItem(playlistIndex).getSongs().getItem(i).getId() == songId) {
                    ableToAdd = false;
                    break;
                }
            }

            if (ableToAdd) {

                int index = playlists.getItem(playlistIndex).getSongs().getLength() + 1;

                Playlist newPlayList = playlists.getItem(playlistIndex);
                newPlayList.getSongs().insert (index, songs.getItem(songIndex));
                playlists.replace(playlistIndex, newPlayList);

                cout << "Added song " << songId << " to playlist " << playlistId << "." << endl;
            } else {
                cout << "Cannot add song. The playlist already contains song " << songId << "." << endl;
            }
        }
    }
}

//remove song from playlist method
void BilkentBeats::removeSongFromPlaylist(const int playlistId, const int songId) {
    bool ableToRemove = false;
    int playlistIndex = -1;
    int songIndexAtThePlaylist = -1;

    for (int i = 1; i <= playlists.getLength(); i++) {
        if (playlistId == playlists.getItem(i).getPlayListID()) {
            ableToRemove = true;
            playlistIndex = i;
            break;
        }
    }

    if (!ableToRemove) {
        cout << "Cannot remove song. There is no playlist with ID " << playlistId << "." << endl;
    } else {
        ableToRemove = false; //check for existence of the song

        for (int i = 1; i <= playlists.getItem(playlistIndex).getSongs().getLength(); i++) {
            if (playlists.getItem(playlistIndex).getSongs().getItem(i).getId() == songId) {
                ableToRemove = true;
                songIndexAtThePlaylist = i;
                break;
            }
        }

        if (!ableToRemove) {
            cout << "Cannot remove song. There is no song " << songId << " in playlist " << playlistId << "." << endl;
        } else {

            Playlist newPlayList = playlists.getItem(playlistIndex);
            newPlayList.getSongs().remove(songIndexAtThePlaylist);
            playlists.replace(playlistIndex, newPlayList);

            cout << "Removed song " << songId << " from playlist " << playlistId << "." << endl;
        }
    }
}

//print songs in playlist method
void BilkentBeats::printSongsInPlaylist(const int playlistId) const {
    bool ableToPrint = false;
    int playlistIndex = -1;

    for (int i = 1; i <= playlists.getLength(); i++) {
        if (playlistId == playlists.getItem(i).getPlayListID()) {
            ableToPrint = true;
            playlistIndex = i;
            break;
        }
    }

    if(!ableToPrint) {
        cout << "Cannot print songs. There is no playlist with ID " << playlistId << "." << endl;
    }
    else {
        ableToPrint = false; //check for empty playlist
        if (playlists.getItem(playlistIndex).getSongs().getLength() > 0) {
            ableToPrint = true;
        }

        if (!ableToPrint) {
        cout<<"There are no songs to show in playlist "<<playlistId<<"."<<endl;
        }
        else {
            cout<<"Songs in playlist "<<playlistId<<":"<<endl;
            for (int i = 1; i <= playlists.getItem(playlistIndex).getSongs().getLength(); i++) {
            cout << "Song " << playlists.getItem(playlistIndex).getSongs().getItem(i).getId() << " : " << playlists.
                    getItem(playlistIndex).getSongs().getItem(i).getName() << " - " << playlists.getItem(playlistIndex).
                    getSongs().getItem(i).getArtists() << endl;
            }
        }
    }
}

