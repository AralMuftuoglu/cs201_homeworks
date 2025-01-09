//
// Created by Aral Müftüoğlu
// 22201566
// Section 3
//
#include "Spacecraft.h"
#include "Mission.h"

#include <iostream>
#include <ostream>
//constructor for mission
Mission::Mission(const string name, const string launchDate, const string destination) {
    numberOfSpacecrafts = 0;
    spacecrafts = nullptr;
    setMissionName(name);
    setMissionLaunchDate(launchDate);
    setMissionDestination(destination);
}

//default constructor
Mission::Mission() {
    numberOfSpacecrafts = 0;
    spacecrafts = nullptr;
    setMissionName("");
    setMissionLaunchDate("");
    setMissionDestination("");
}

Mission::~Mission() {
    delete[] spacecrafts;
}

void Mission::setMissionName(string name) {
    missionName = name;
}

void Mission::setMissionLaunchDate(string launchDate) {
    missionLaunchDate = launchDate;
}

void Mission::setMissionDestination(string destination) {
    missionDestination = destination;
}

string Mission::getMissionName() const {
    return missionName;
}

string Mission::getMissionLaunchDate() const {
    return missionLaunchDate;
}

string Mission::getMissionDestination() const {
    return missionDestination;
}

void Mission::addSpacecraft(Spacecraft &newSpacecraft) {
    Spacecraft **newSpacecrafts = new Spacecraft *[numberOfSpacecrafts + 1];

    for (int i = 0; i < numberOfSpacecrafts; i++) {
        newSpacecrafts[i] = spacecrafts[i];
    }

    newSpacecrafts[numberOfSpacecrafts] = &newSpacecraft;

    delete[] spacecrafts;
    spacecrafts = newSpacecrafts;

    numberOfSpacecrafts++;
}

void Mission::removeSpacecraft(Spacecraft &spacecraft) {
    int index = -1;

    if (numberOfSpacecrafts > 1) {
        Spacecraft **newSpacecrafts = new Spacecraft *[numberOfSpacecrafts - 1];

        for (int i = 0; i < numberOfSpacecrafts; i++) {
            if ((*spacecrafts[i]).getName() == spacecraft.getName()) {
                index = i;
            }
        }

        for (int i = 0; i < index; i++) {
            newSpacecrafts[i] = spacecrafts[i];
        }
        for (int i = index + 1; i < numberOfSpacecrafts; i++) {
            newSpacecrafts[i - 1] = spacecrafts[i];
        }

        delete[] spacecrafts;
        spacecrafts = newSpacecrafts;
    } else {
        delete[] spacecrafts;
        spacecrafts = nullptr;
    }
    numberOfSpacecrafts--;
}

int Mission::getNumberOfSpacecrafts() {
    return numberOfSpacecrafts;
}

Spacecraft **Mission::getSpacecrafts() {
    return spacecrafts;
}

void Mission::showMissionInformation() {
    cout << "Mission:" << endl;
    cout << "  Name: " << missionName << endl;
    cout << "  Launch Date: " << missionLaunchDate << endl;
    cout << "  Destination: " << missionDestination << endl;
    cout << "  Assigned Spacecrafts:" << endl;
    for (int i = 0; i < numberOfSpacecrafts; i++) {
        cout << "  - " << (*spacecrafts[i]).getName() << endl;
    }
    if (numberOfSpacecrafts == 0) {
        cout << "    None" << endl;
    }
}

void Mission::showMissionInformationShortForm() {
    cout << "Mission: " << missionName << ", Launch Date: " << missionLaunchDate << ", Destination: " <<
            missionDestination << ", "
            "Assigned Spacecraft Count: " << numberOfSpacecrafts << endl;
}

Mission::Mission(const Mission &anotherMission) {
    //Overloaded copy constructor

    missionName = anotherMission.getMissionName();
    missionLaunchDate = anotherMission.getMissionLaunchDate();
    missionDestination = anotherMission.getMissionDestination();
    numberOfSpacecrafts = anotherMission.numberOfSpacecrafts;

    spacecrafts = new Spacecraft *[numberOfSpacecrafts];

    for (int i = 0; i < numberOfSpacecrafts; i++) {
        spacecrafts[i] = anotherMission.spacecrafts[i];
    }
}

Mission &Mission::operator=(const Mission &anotherMission) {
    //Overloaded assignment operator

    if (this == &anotherMission) {
        return *this;
    }

    delete[] spacecrafts;

    missionName = anotherMission.getMissionName();
    missionLaunchDate = anotherMission.getMissionLaunchDate();
    missionDestination = anotherMission.getMissionDestination();
    numberOfSpacecrafts = anotherMission.numberOfSpacecrafts;

    spacecrafts = new Spacecraft *[numberOfSpacecrafts];

    for (int i = 0; i < numberOfSpacecrafts; i++) {
        spacecrafts[i] = anotherMission.spacecrafts[i];
    }

    return *this;
}
