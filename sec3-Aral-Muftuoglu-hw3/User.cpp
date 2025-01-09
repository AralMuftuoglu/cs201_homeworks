//
// Aral Müftüoğlu
// 22201566
// Section 3
//

#include "User.h"

User::User() {
    userName = "";
    userID = 0;
}
User::User(string name, int id) {
    userName = name;
    userID = id;
}

User::~User() {}

int User::getId() {
    return userID;
}
string  User::getName() {
    return userName;
}
void User::setName(string name) {
    userName = name;
}
void User::setId(int id) {
    userID = id;
}

LinkedList<Playlist>& User::getPlaylists() {
    return playLists;
}

User& User::operator=(const User& other) {
    if (this != &other) {
        userName = other.userName;
        userID = other.userID;
        playLists = other.playLists;
    }
    return *this;
}
