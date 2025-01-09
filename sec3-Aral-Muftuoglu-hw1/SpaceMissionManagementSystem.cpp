//
// Created by Aral Müftüoğlu
// 22201566
// Section 3
//

#include <string>

#include <iostream>
#include "SpaceMissionManagementSystem.h"

#include <math.h>


//constructor for spaceMissionManagementSystem
SpaceMissionManagementSystem::SpaceMissionManagementSystem() {
    totalNumberOfMissions = 0;
    totalNumberOfSpacecrafts = 0;
    allMissions = nullptr;
    allSpacecrafts = nullptr;
}

SpaceMissionManagementSystem::~SpaceMissionManagementSystem() {
    if (allSpacecrafts) {
        delete [] allSpacecrafts;
    }
    if (allMissions) {
        delete [] allMissions;
    }
}

void SpaceMissionManagementSystem::addMission(const string name, const string launchDate, const string destination) {
    bool canAddMission = true;

    //for null
    if (allMissions) {
        for (int i = 0; i < totalNumberOfMissions; i++) {
            if (name == allMissions[i].getMissionName()) {
                canAddMission = false;
                cout << "Cannot add mission. Mission " << name << " already exists." << endl;
            }
        }
    }

    if (canAddMission) {
        Mission newMission(name, launchDate, destination);

        Mission *newAllMissions = new Mission[totalNumberOfMissions + 1];

        if (allMissions == nullptr) {
            newAllMissions[0] = newMission;
            allMissions = newAllMissions;
        } else {
            for (int i = 0; i < totalNumberOfMissions; i++) {
                newAllMissions[i] = allMissions[i];
            }
            newAllMissions[totalNumberOfMissions] = newMission;

            delete[] allMissions;
            allMissions = newAllMissions;
        }
        totalNumberOfMissions++;

        cout << "Added mission " << name << "." << endl;
    }
}

void SpaceMissionManagementSystem::removeMission(const string name) {
    bool canRemoveMission = false;
    int index = -1;

    for (int i = 0; i < totalNumberOfMissions; i++) {
        if (name == allMissions[i].getMissionName()) {
            canRemoveMission = true;
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Cannot remove mission. Mission " << name << " does not exist." << endl;
    }
    if (canRemoveMission) {
        if (totalNumberOfMissions > 1) {
            Mission *newAllMissions = new Mission[totalNumberOfMissions - 1];

            for (int i = 0; i < index; i++) {
                newAllMissions[i] = allMissions[i];
            }
            for (int i = index + 1; i < totalNumberOfMissions; i++) {
                newAllMissions[i - 1] = allMissions[i];
            }

            //change the status of spacecrafts of mission
            for (int i = 0; i < allMissions[index].getNumberOfSpacecrafts(); i++) {
                (*allMissions[index].getSpacecrafts()[i]).alterStatus();
                (*allMissions[index].getSpacecrafts()[i]).removeMission();
            }


            delete[] allMissions;
            allMissions = newAllMissions;
        } else {
            delete[] allMissions;
            allMissions = nullptr;
        }

        totalNumberOfMissions--;
        cout << "Removed mission " << name << "." << endl;
    }
}

void SpaceMissionManagementSystem::addSpacecraft(const string name, const string type) {
    bool canAddSpacecraft = true;

    //for null
    if (allSpacecrafts) {
        for (int i = 0; i < totalNumberOfSpacecrafts; i++) {
            if (name == allSpacecrafts[i].getName()) {
                canAddSpacecraft = false;
                cout << "Cannot add spacecraft. Spacecraft " << name << " already exists." << endl;
            }
        }
    }

    if (canAddSpacecraft) {
        Spacecraft newSpacecraft(name, type);

        Spacecraft *newAllSpaceCrafts = new Spacecraft[totalNumberOfSpacecrafts + 1];

        if (allSpacecrafts == nullptr) {
            newAllSpaceCrafts[0] = newSpacecraft;
            allSpacecrafts = newAllSpaceCrafts;
        } else {
            for (int i = 0; i < totalNumberOfSpacecrafts; i++) {
                newAllSpaceCrafts[i] = allSpacecrafts[i];
            }
            newAllSpaceCrafts[totalNumberOfSpacecrafts] = newSpacecraft;

            delete[] allSpacecrafts;
            allSpacecrafts = newAllSpaceCrafts;
        }

        totalNumberOfSpacecrafts++;

        cout << "Added spacecraft " << name << "." << endl;
    }
}

void SpaceMissionManagementSystem::removeSpacecraft(const string name) {
    bool canRemoveSpacecraft = false;

    int index = -1;

    for (int i = 0; i < totalNumberOfSpacecrafts; i++) {
        if (name == allSpacecrafts[i].getName()) {
            canRemoveSpacecraft = true;
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Cannot remove spacecraft. Spacecraft " << name << " does not exist." << endl;
    } else {
        if (allSpacecrafts[index].getStatus() == "Assigned") {
            canRemoveSpacecraft = false;
            cout << "Cannot remove spacecraft. Spacecraft " << name << " is assigned to a mission." << endl;
        }
    }

    if (canRemoveSpacecraft) {
        if (totalNumberOfSpacecrafts > 1) {
            Spacecraft *newAllSpaceCrafts = new Spacecraft[totalNumberOfSpacecrafts - 1];

            for (int i = 0; i < index; i++) {
                newAllSpaceCrafts[i] = allSpacecrafts[i];
            }
            for (int i = index + 1; i < totalNumberOfSpacecrafts; i++) {
                newAllSpaceCrafts[i - 1] = allSpacecrafts[i];
            }


            delete[] allSpacecrafts;
            allSpacecrafts = newAllSpaceCrafts;
        } else {
            delete[] allSpacecrafts;
            allSpacecrafts = nullptr;
        }
        totalNumberOfSpacecrafts--;
        cout << "Removed spacecraft " << name << "." << endl;
    }
}

void SpaceMissionManagementSystem::assignSpacecraftToMission(const string spacecraftName, const string missionName) {
    bool canAssignSpacecraft = false;
    int spacecraftIndex = -1;
    bool canAssignMission = false;
    int missionIndex = -1;

    for (int i = 0; i < totalNumberOfSpacecrafts; i++) {
        if (allSpacecrafts[i].getName() == spacecraftName) {
            canAssignSpacecraft = true;
            spacecraftIndex = i;
            break;
        }
    }
    if (!canAssignSpacecraft) {
        cout << "Cannot assign spacecraft. Spacecraft " << spacecraftName << " does not exist." << endl;
    }

    if (canAssignSpacecraft) {
        for (int i = 0; i < totalNumberOfMissions; i++) {
            if (allMissions[i].getMissionName() == missionName) {
                canAssignMission = true;
                missionIndex = i;
                break;
            }
        }
    }
    if (!canAssignMission && canAssignSpacecraft) {
        cout << "Cannot assign spacecraft. Mission " << missionName << " does not exist." << endl;
    }

    if (canAssignMission) {
        if (allSpacecrafts[spacecraftIndex].getStatus() == "Assigned") {
            canAssignMission = false;
            cout << "Cannot assign spacecraft. Spacecraft " << spacecraftName << " is already assigned to mission " << (
                (*allSpacecrafts[spacecraftIndex].getMission()).getMissionName()) << "." << endl;
        }
    }

    if (canAssignMission) {
        allMissions[missionIndex].addSpacecraft(allSpacecrafts[spacecraftIndex]);
        allSpacecrafts[spacecraftIndex].alterStatus();
        allSpacecrafts[spacecraftIndex].setMission(&allMissions[missionIndex]);

        cout << "Assigned spacecraft " << spacecraftName << " to mission " << missionName << "." << endl;
    }
}

void SpaceMissionManagementSystem::dropSpacecraftFromMission(const string spacecraftName) {
    bool canDropSpacecraft = false;
    int spacecraftIndex = -1;

    for (int i = 0; i < totalNumberOfSpacecrafts; i++) {
        if (allSpacecrafts[i].getName() == spacecraftName) {
            spacecraftIndex = i;
            break;
        }
    }

    if (spacecraftIndex == -1) {
        cout << "Cannot drop spacecraft. Spacecraft " << spacecraftName << " does not exist." << endl;
    } else {
        if (allSpacecrafts[spacecraftIndex].getStatus() == "Assigned") {
            canDropSpacecraft = true;
        } else {
            cout << "Cannot drop spacecraft. Spacecraft " << spacecraftName << " is not assigned to any mission." <<
                    endl;
        }
    }

    if (canDropSpacecraft) {
        allSpacecrafts[spacecraftIndex].alterStatus();
        (*allSpacecrafts[spacecraftIndex].getMission()).removeSpacecraft(allSpacecrafts[spacecraftIndex]);
        cout << "Dropped spacecraft " << spacecraftName << " from mission " << (*allSpacecrafts[spacecraftIndex].
            getMission()).getMissionName() << "." << endl;
        allSpacecrafts[spacecraftIndex].removeMission();
    }
}

void SpaceMissionManagementSystem::showAllMissions() const {
    cout << "Missions in the space mission management system:" << endl;

    if (totalNumberOfMissions == 0) {
        cout << "None" << endl;
    } else {
        for (int i = 0; i < totalNumberOfMissions; i++) {
            allMissions[i].showMissionInformationShortForm();
        }
    }
}

void SpaceMissionManagementSystem::showAllSpacecrafts() const {
    cout << "Spacecrafts in the space mission management system:" << endl;

    if (totalNumberOfSpacecrafts == 0) {
        cout << "None" << endl;
    } else {
        for (int i = 0; i < totalNumberOfSpacecrafts; i++) {
            allSpacecrafts[i].showSpacecraftInformation();
        }
    }
}

void SpaceMissionManagementSystem::showMission(const string name) const {
    bool canShowMission = false;
    int missionIndex = -1;

    for (int i = 0; i < totalNumberOfMissions; i++) {
        if (allMissions[i].getMissionName() == name) {
            canShowMission = true;
            missionIndex = i;
            break;
        }
    }

    if (canShowMission) {
        allMissions[missionIndex].showMissionInformation();
    } else {
        cout << "Cannot show mission. Mission " << name << " does not exist." << endl;
    }
}

void SpaceMissionManagementSystem::showSpacecraft(const string name) const {
    bool canShowSpacecraft = false;
    int spacecraftIndex = -1;

    for (int i = 0; i < totalNumberOfSpacecrafts; i++) {
        if (allSpacecrafts[i].getName() == name) {
            canShowSpacecraft = true;
            spacecraftIndex = i;
            break;
        }
    }
    if (canShowSpacecraft) {
        allSpacecrafts[spacecraftIndex].showSpacecraftInformation();
    } else {
        cout << "Cannot show spacecraft. Spacecraft " << name << " does not exist." << endl;
    }
}
