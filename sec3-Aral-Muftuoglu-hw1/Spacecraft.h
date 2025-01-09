//
// Created by Aral Müftüoğlu
// 22201566
// Section 3
//

#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#include <string>

#include "Mission.h"


using namespace std;

class Spacecraft {
public:
    Spacecraft(const string name, const string type);
    Spacecraft();
    void setName(string name);
    void setType(string type);
    void alterStatus();
    void setMission(Mission* x);
    void removeMission();
    void showSpacecraftInformation();
    string getName() ;
    string getType();
    string getStatus();
    Mission* getMission();
private:
    string spacecraftName;
    string spacecraftType;
    string spacecraftStatus;
    Mission* mission;
};
#endif //SPACECRAFT_H
