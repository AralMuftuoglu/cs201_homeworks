//
// Aral Müftüoğlu
// 22201566
// Section 3
//

#ifndef USER_H
#define USER_H
#include <string>

#include "LinkedList.h"
#include "Playlist.h"

using namespace std;

class User {

public:
    User();
    User(string name, int id);
    ~User();
    string getName() ;
    int getId () ;
    void setName(string name);
    void setId(int id);
    LinkedList<Playlist>& getPlaylists();
    User& operator=(const User& other);

private:
    int userID;
    string userName;
    LinkedList<Playlist> playLists;
};

#endif //USER_H
