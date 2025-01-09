//
// Aral Müftüoğlu
// 22201566
// Section 3
//

#include "PandemicSimulator.h"
#include "LinkedQueue.h"


using namespace std;

// constructor
PandemicSimulator::PandemicSimulator(const string cityGridFile) {
    ifstream file(cityGridFile);

    //reading the sizes of the city grid from txt file
    file >> cityRows >> cityCols;

    int arraySizeForGrid = cityRows * cityCols;

    gridOfTheCity = new int[arraySizeForGrid];

    for (int i = 0; i < cityRows; i++) {
        string line;
        file >> line;

        for (int j = 0; j < cityCols; j++) {
            gridOfTheCity[i * cityCols + j] = line[j] - '0';
        }
    }

    file.close();
}

// destructor
PandemicSimulator::~PandemicSimulator() {
    delete[] gridOfTheCity;
}

// method for printing the grid
void PandemicSimulator::printGrid(int *currentGrind, const int rowNo, const int colNo) {
    for (int i = 0; i < rowNo; i++) {
        for (int j = 0; j < colNo; j++) {
            cout << currentGrind[i * colNo + j];
        }
        cout << endl;
    }
}

//displaying the city state for the wanted numberOfDays
void PandemicSimulator::displayCityState(int numberOfDays) {
    // exit the method if numberOfDays equals to "0"
    if (numberOfDays == 0) {
        cout << "City state at day 0:" << endl;
        printGrid(gridOfTheCity, cityRows, cityCols);
        return;
    }

    // creating a copy of the original city grid
    int *gridToSimulate = new int[cityRows * cityCols];

    // deep copying to original array to gridToSimulate
    for (int i = 0; i < cityRows * cityCols; i++) {
        gridToSimulate[i] = gridOfTheCity[i];
    }

    // creating queues for rows and cols of infected cells separately due to 2D array
    LinkedQueue<int> rowsInfected;
    LinkedQueue<int> colsInfected;

    // enqueue initially infected blocks with value "2"
    for (int i = 0; i < cityRows; i++) {
        for (int j = 0; j < cityCols; j++) {
            // check for infected
            if (gridToSimulate[i * cityCols + j] == 2) {
                rowsInfected.enqueue(i); // row of the infected cell
                colsInfected.enqueue(j); // column of the infected cell
            }
        }
    }

    // initial day "1"
    int day = 1;

    while (day <= numberOfDays) {
        int currentInfectedCount = rowsInfected.getSize();

        // creating a temporary city grid for each day
        int *tempGrid = new int[cityRows * cityCols];
        for (int i = 0; i < cityRows * cityCols; i++) {
            tempGrid[i] = gridToSimulate[i];
        }

        // spread of the infection for each infected block
        for (int i = 0; i < currentInfectedCount; i++) {
            int currentRow = rowsInfected.peekFront(); // row of the infected block
            int currentColumn = colsInfected.peekFront(); // column of the infected block

            // removing the current infected block from infected blocks
            rowsInfected.dequeue();
            colsInfected.dequeue();

            // infect the right block
            if (currentColumn + 1 < cityCols && gridToSimulate[currentRow * cityCols + (currentColumn + 1)] == 1) {
                // enqueue the new infected block
                rowsInfected.enqueue(currentRow);
                colsInfected.enqueue(currentColumn + 1);
                tempGrid[currentRow * cityCols + (currentColumn + 1)] = 2; // update the block in cityGrid
            }

            // infect the left block
            if (currentColumn - 1 >= 0 && gridToSimulate[currentRow * cityCols + (currentColumn - 1)] == 1) {
                // enqueue the new infected block
                rowsInfected.enqueue(currentRow);
                colsInfected.enqueue(currentColumn - 1);
                tempGrid[currentRow * cityCols + (currentColumn - 1)] = 2; // update the block in cityGrid
            }

            // infect the above block
            if (currentRow - 1 >= 0 && gridToSimulate[(currentRow - 1) * cityCols + currentColumn] == 1) {
                // enqueue the new infected block
                rowsInfected.enqueue(currentRow - 1);
                colsInfected.enqueue(currentColumn);
                tempGrid[(currentRow - 1) * cityCols + currentColumn] = 2; // update the block in cityGrid
            }

            // infect the below block
            if (currentRow + 1 < cityRows && gridToSimulate[(currentRow + 1) * cityCols + currentColumn] == 1) {
                // enqueue the new infected block
                rowsInfected.enqueue(currentRow + 1);
                colsInfected.enqueue(currentColumn);
                tempGrid[(currentRow + 1) * cityCols + currentColumn] = 2; // update the block in cityGrid
            }
        }

        // deep copy of tempGrid into gridToSimulate
        for (int i = 0; i < cityRows * cityCols; i++) {
            gridToSimulate[i] = tempGrid[i];
        }

        // deallocating the memory for tempGrid
        delete[] tempGrid;

        // increase the day
        day++;
    }

    //printing the grid of the new city
    cout << "City state at day " << numberOfDays << ":" << endl;
    printGrid(gridToSimulate, cityRows, cityCols);

    //deallocate the duplicated array
    delete[] gridToSimulate;
}

// simulating for a block
void PandemicSimulator::simulateBlock(const int row, const int col) {
    // required day
    int requiredDays = 0;
    // type of the block
    int conditionOfTheBlock = gridOfTheCity[row * cityCols + col];

    // empty block
    if (conditionOfTheBlock == 0) {
        requiredDays = -1;
        cout << "Time for block (" << row << ", " << col << ") to be infected: " << requiredDays << " days." << endl;
    }
    // already infected
    else if (conditionOfTheBlock == 2) {
        requiredDays = 0;
        cout << "Time for block (" << row << ", " << col << ") to be infected: " << requiredDays << " days." << endl;
    }
    // healthy block
    else {
        // creating a copy of the original city grid
        int *gridToSimulate = new int[cityRows * cityCols];

        // deep copying to original array to gridToSimulate
        for (int i = 0; i < cityRows * cityCols; i++) {
            gridToSimulate[i] = gridOfTheCity[i];
        }

        // creating queues for rows and cols of infected cells separately due to 2D array
        LinkedQueue<int> rowsInfected;
        LinkedQueue<int> colsInfected;

        // enqueue initially infected blocks with value "2"
        for (int rowsInGrid = 0; rowsInGrid < cityRows; rowsInGrid++) {
            for (int colsInGrid = 0; colsInGrid < cityCols; colsInGrid++) {
                // check for infected
                if (gridToSimulate[rowsInGrid * cityCols + colsInGrid] == 2) {
                    rowsInfected.enqueue(rowsInGrid); // row of the infected cell
                    colsInfected.enqueue(colsInGrid); // column of the infected cell
                }
            }
        }

        // check for being infected or not
        bool isInfected = false;

        // no more infection
        bool cantInfected = false;

        while (!isInfected && !cantInfected) {
            int currentInfectedCount = rowsInfected.getSize();

            // creating a temporary city grid for each day
            int *tempGrid = new int[cityRows * cityCols];
            for (int i = 0; i < cityRows * cityCols; i++) {
                tempGrid[i] = gridToSimulate[i];
            }

            // spread of the infection for each infected block
            for (int i = 0; i < currentInfectedCount; i++) {
                int currentRow = rowsInfected.peekFront(); // row of the infected block
                int currentColumn = colsInfected.peekFront(); // column of the infected block

                // removing the current infected block from infected blocks
                rowsInfected.dequeue();
                colsInfected.dequeue();

                // infect the right block
                if (currentColumn + 1 < cityCols && gridToSimulate[currentRow * cityCols + (currentColumn + 1)] == 1) {
                    // enqueue the new infected block
                    rowsInfected.enqueue(currentRow);
                    colsInfected.enqueue(currentColumn + 1);
                    tempGrid[currentRow * cityCols + (currentColumn + 1)] = 2; // update the block in cityGrid
                }

                // infect the left block
                if (currentColumn - 1 >= 0 && gridToSimulate[currentRow * cityCols + (currentColumn - 1)] == 1) {
                    // enqueue the new infected block
                    rowsInfected.enqueue(currentRow);
                    colsInfected.enqueue(currentColumn - 1);
                    tempGrid[currentRow * cityCols + (currentColumn - 1)] = 2; // update the block in cityGrid
                }

                // infect the above block
                if (currentRow - 1 >= 0 && gridToSimulate[(currentRow - 1) * cityCols + currentColumn] == 1) {
                    // enqueue the new infected block
                    rowsInfected.enqueue(currentRow - 1);
                    colsInfected.enqueue(currentColumn);
                    tempGrid[(currentRow - 1) * cityCols + currentColumn] = 2; // update the block in cityGrid
                }

                // infect the below block
                if (currentRow + 1 < cityRows && gridToSimulate[(currentRow + 1) * cityCols + currentColumn] == 1) {
                    // enqueue the new infected block
                    rowsInfected.enqueue(currentRow + 1);
                    colsInfected.enqueue(currentColumn);
                    tempGrid[(currentRow + 1) * cityCols + currentColumn] = 2; // update the block in cityGrid
                }
            }

            // check wanted block is infected
            if (tempGrid[row * cityCols + col] == 2) {
                isInfected = true;
            }

            // cant be infected
            if (!isInfected && compareGrids(tempGrid, gridToSimulate)) {
                cantInfected = true;
            }

            // deep copy of tempGrid into gridToSimulate
            for (int i = 0; i < cityRows * cityCols; i++) {
                gridToSimulate[i] = tempGrid[i];
            }

            // deallocating the memory for tempGrid
            delete[] tempGrid;

            // increasing for number of the day
            requiredDays++;
        }

        // condition for not reachable block
        if (cantInfected) {
            cout << "Time for block (" << row << ", " << col << ") to be infected: -1 days." << endl;
        } else {
            cout << "Time for block (" << row << ", " << col << ") to be infected: " << requiredDays << " days." <<
                    endl;
        }

        //deallocate the duplicated array
        delete[] gridToSimulate;
    }
}

// method for comparing the grids
bool PandemicSimulator::compareGrids(int *firstGrid, int *secondGrid) {
    bool result = true;
    int size = cityRows * cityCols;

    for (int i = 0; i < size; i++) {
        if (firstGrid[i] != secondGrid[i]) {
            result = false;
            break;
        }
    }
    return result;
}

// method for checking the infection
bool PandemicSimulator::checkAllInfected(int *cityGrid) {
    bool result = true;

    int size = cityRows * cityCols;

    for (int i = 0; i < size; i++) {
        if (!(cityGrid[i] == 0 || cityGrid[i] == 2)) {
            result = false;
            break;
        }
    }
    return result;
}

// simulate the pandemic method
void PandemicSimulator::simulatePandemic() {
    // required day for all blocks to be infected
    int requiredDays = 0;

    // creating a copy of the original city grid
    int *gridToSimulate = new int[cityRows * cityCols];

    // deep copying to original array to gridToSimulate
    for (int i = 0; i < cityRows * cityCols; i++) {
        gridToSimulate[i] = gridOfTheCity[i];
    }

    // initially all infected
    if (checkAllInfected(gridToSimulate)) {
        cout << "Minimum time for pandemic to spread to all blocks: 0 days." << endl;
    } else {
        // creating queues for rows and cols of infected cells separately due to 2D array
        LinkedQueue<int> rowsInfected;
        LinkedQueue<int> colsInfected;

        // enqueue initially infected blocks with value "2"
        for (int rowsInGrid = 0; rowsInGrid < cityRows; rowsInGrid++) {
            for (int colsInGrid = 0; colsInGrid < cityCols; colsInGrid++) {
                // check for infected
                if (gridToSimulate[rowsInGrid * cityCols + colsInGrid] == 2) {
                    rowsInfected.enqueue(rowsInGrid); // row of the infected cell
                    colsInfected.enqueue(colsInGrid); // column of the infected cell
                }
            }
        }

        // flag for checking completed infection
        bool infectionComplete = false;

        while (!infectionComplete) {
            int currentInfectedCount = rowsInfected.getSize();

            // creating a temporary city grid for each day
            int *tempGrid = new int[cityRows * cityCols];
            for (int i = 0; i < cityRows * cityCols; i++) {
                tempGrid[i] = gridToSimulate[i];
            }

            // spread of the infection for each infected block
            for (int i = 0; i < currentInfectedCount; i++) {
                int currentRow = rowsInfected.peekFront(); // row of the infected block
                int currentColumn = colsInfected.peekFront(); // column of the infected block

                // removing the current infected block from infected blocks
                rowsInfected.dequeue();
                colsInfected.dequeue();

                // infect the right block
                if (currentColumn + 1 < cityCols && gridToSimulate[currentRow * cityCols + (currentColumn + 1)] == 1) {
                    // enqueue the new infected block
                    rowsInfected.enqueue(currentRow);
                    colsInfected.enqueue(currentColumn + 1);
                    tempGrid[currentRow * cityCols + (currentColumn + 1)] = 2; // update the block in cityGrid
                }

                // infect the left block
                if (currentColumn - 1 >= 0 && gridToSimulate[currentRow * cityCols + (currentColumn - 1)] == 1) {
                    // enqueue the new infected block
                    rowsInfected.enqueue(currentRow);
                    colsInfected.enqueue(currentColumn - 1);
                    tempGrid[currentRow * cityCols + (currentColumn - 1)] = 2; // update the block in cityGrid
                }

                // infect the above block
                if (currentRow - 1 >= 0 && gridToSimulate[(currentRow - 1) * cityCols + currentColumn] == 1) {
                    // enqueue the new infected block
                    rowsInfected.enqueue(currentRow - 1);
                    colsInfected.enqueue(currentColumn);
                    tempGrid[(currentRow - 1) * cityCols + currentColumn] = 2; // update the block in cityGrid
                }

                // infect the below block
                if (currentRow + 1 < cityRows && gridToSimulate[(currentRow + 1) * cityCols + currentColumn] == 1) {
                    // enqueue the new infected block
                    rowsInfected.enqueue(currentRow + 1);
                    colsInfected.enqueue(currentColumn);
                    tempGrid[(currentRow + 1) * cityCols + currentColumn] = 2; // update the block in cityGrid
                }
            }

            // no more infection
            if (compareGrids(gridToSimulate, tempGrid)) {
                infectionComplete = true;
            } else {
                // increase the day
                requiredDays++;
            }

            // deep copy of tempGrid into gridToSimulate
            for (int i = 0; i < cityRows * cityCols; i++) {
                gridToSimulate[i] = tempGrid[i];
            }

            // deallocating the memory for tempGrid
            delete[] tempGrid;
        }

        // condition that no more infection
        if (!checkAllInfected(gridToSimulate)) {
            cout << "Pandemic cannot spread to all blocks." << endl;
        } else {
            cout << "Minimum time for pandemic to spread to all blocks: " << requiredDays << " days." << endl;
        }
    }

    // deallocate the memory for duplicated grid
    delete[] gridToSimulate;
}
