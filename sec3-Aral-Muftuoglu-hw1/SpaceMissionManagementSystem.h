//
// Created by Aral Müftüoğlu
// 22201566
// Section 3
//

#ifndef SPACEMISSIONMANAGEMENTSYSTEM_H
#define SPACEMISSIONMANAGEMENTSYSTEM_H

#include <string>
#include "Spacecraft.h"
#include "Mission.h"

using namespace std;

class SpaceMissionManagementSystem {
public:
    SpaceMissionManagementSystem();
    ~SpaceMissionManagementSystem();
    void addMission( const string name, const string launchDate, const string destination );
    void removeMission( const string name );
    void addSpacecraft( const string name, const string type );
    void removeSpacecraft( const string name );
    void assignSpacecraftToMission( const string spacecraftName, const string missionName );
    void dropSpacecraftFromMission( const string spacecraftName );
    void showAllMissions()const;
    void showAllSpacecrafts()const;
    void showMission(const string name)const;
    void showSpacecraft(const string name)const;
private:
    Spacecraft* allSpacecrafts;
    Mission* allMissions;
    int totalNumberOfSpacecrafts;
    int totalNumberOfMissions;
};
#endif //SPACEMISSIONMANAGEMENTSYSTEM_H
