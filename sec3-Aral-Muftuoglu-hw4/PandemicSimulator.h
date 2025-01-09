//
// Aral Müftüoğlu
// 22201566
// Section 3
//

#ifndef PANDEMICSIMULATOR_H
#define PANDEMICSIMULATOR_H

#include <iostream>
#include <fstream>

#include <string>
using namespace std;

class PandemicSimulator {
private:
    int *gridOfTheCity; //array for representing the grid
    int cityRows; //first dimension for the grid
    int cityCols; //second dimension fot the grid

public:
    PandemicSimulator(const string cityGridFile); //constructor
    ~ PandemicSimulator(); //destructor

    void displayCityState(const int time); //displaying the city state
    void simulateBlock(const int row, const int col); //infection simulation for the specified block
    void simulatePandemic(); //infection simulation for the entire city

    void printGrid(int *currentGrind, const int rowNo, const int colNo); //printing a grid of the city
    bool compareGrids(int *firstGrid, int *secondGrid); // check for equality of two grids
    bool checkAllInfected(int *cityGrid); // check for all blocks in a city grid
};
#endif //PANDEMICSIMULATOR_H
