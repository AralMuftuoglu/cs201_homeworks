//
// Aral Müftüoğlu
// 22201566
// Section 3
//

#include "Song.h"

Song::Song() {
    songName = "";
    artistName = "";
    songID = 0;
}
Song::Song(int id, string name, string artists) {
    songName = name;
    artistName = artists;
    songID = id;
}

Song::~Song() {}

string Song::getArtists() {
    return artistName;
}
string Song::getName() {
    return songName;
}
int Song::getId() {
    return songID;
}
void Song::setName(string name) {
    songName = name;
}
void Song::setId(int id) {
    songID = id;
}
void Song::setArtists(string artists) {
    artistName = artists;
}
