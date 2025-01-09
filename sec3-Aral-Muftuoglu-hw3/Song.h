//
// Aral Müftüoğlu
// 22201566
// Section 3
//

#ifndef SONG_H
#define SONG_H
#include <string>
using namespace std;


class Song {
public:
    Song();
    Song(int id, string name, string artists);
    ~Song();
    int getId();
    string getName();
    string getArtists();
    void setId(int id);
    void setName(string name);
    void setArtists(string artists);

private:
    string songName;
    string artistName;
    int songID;
};



#endif //SONG_H
