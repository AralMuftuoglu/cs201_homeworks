//
// Created by Aral Müftüoğlu
// 22201566
// Section 3
//

#include "Spacecraft.h"

#include <iostream>
#include <ostream>

#include "Mission.h"

//constructor for spacecraft
Spacecraft::Spacecraft(const string name, const string type) {
    setName(name);
    setType(type);
    spacecraftStatus = "Available";
    mission = nullptr;
}

//default constructor
Spacecraft::Spacecraft() {
    setName("");
    setType("");
    spacecraftStatus = "Available";
    mission = nullptr;
}

void Spacecraft::setName(string name) {
    spacecraftName = name;
}

string Spacecraft::getName() {
    return spacecraftName;
}

void Spacecraft::setType(string type) {
    spacecraftType = type;
}

string Spacecraft::getType() {
    return spacecraftType;
}

void Spacecraft::alterStatus() {
    if (spacecraftStatus == "Available") {
        spacecraftStatus = "Assigned";
    } else {
        spacecraftStatus = "Available";
    }
}

string Spacecraft::getStatus() {
    return spacecraftStatus;
}

void Spacecraft::setMission(Mission *x) {
    mission = x;
}

Mission *Spacecraft::getMission() {
    return mission;
}

void Spacecraft::showSpacecraftInformation() {
    cout << "Spacecraft: " << spacecraftName << ", Type: " << spacecraftType << ", Status: " << spacecraftStatus <<
        endl;
}

void Spacecraft::removeMission() {
    mission = nullptr;
}
