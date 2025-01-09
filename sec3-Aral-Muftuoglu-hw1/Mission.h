//
// Created by Aral Müftüoğlu
// 22201566
// Section 3
//

#ifndef MISSION_H
#define MISSION_H


#include <string>


class Spacecraft;
using namespace std;

class Mission {
public:
    Mission(const string name, const string launchDate, const string destination);
    Mission();
    ~Mission();
    void setMissionName(  string name );
    void setMissionLaunchDate(  string launchDate );
    void setMissionDestination(  string destination );
    void addSpacecraft(  Spacecraft& newSpacecraft);
    void removeSpacecraft( Spacecraft& spacecraft);
    void showMissionInformation();
    void showMissionInformationShortForm();
    string getMissionName()const;
    string getMissionLaunchDate()const;
    string getMissionDestination()const;
    int getNumberOfSpacecrafts();
    Spacecraft** getSpacecrafts();
    Mission& operator=(const Mission& anotherMission);//overloading assignment operator
    Mission(const Mission& anotherMission);//overloading copy constructor
private:
    string missionName;
    string missionLaunchDate;
    string missionDestination;
    int numberOfSpacecrafts ;
    Spacecraft** spacecrafts ;
};
#endif //MISSION_H
