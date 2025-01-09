/*
 *Aral Müftüoğlu
 *22201566
 *Section 3
 */
#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
}

int linearSearch(int *arr, int size, int targetValue) {
    int i = 0;

    while (i < size) {
        if (arr[i] == targetValue) {
            return i; //target found
        } else {
            i++; //increase the index
        }
    }
    return -1; //target not found
}

int linearSearchRecursive(int *arr, int size, int targetValue) {
    if (size == 0) {
        return -1; // target not found
    }
    if (arr[size - 1] == targetValue) {
        return (size - 1); //target found
    }

    return linearSearchRecursive(arr, size - 1, targetValue);
}

int binarySearch(int *arr, int size, int targetValue) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = ((low + high) + 1 )/ 2;

        if (arr[mid] == targetValue) {
            return mid; //value found
        }

        if (arr[mid] < targetValue) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1; //target not found
}

int smallerNumber(int a, int b) {
    if (a > b) {
        return b;
    } else {
        return a;
    }
}

int jumpSearch(int *arr, int size, int targetValue) {
    int resultIndex = 0;
    int difference = sqrt(size);

    while (arr[smallerNumber(size, difference) - 1] < targetValue) {
        resultIndex = difference;

        difference = difference + sqrt(size);

        if (resultIndex >= size) {
            return -1;
        }
    }

    while (arr[resultIndex] < targetValue) {
        resultIndex = resultIndex + 1;

        if (resultIndex == smallerNumber(difference, size)) {
            return -1;
        }
    }

    if (arr[resultIndex] == targetValue) {
        return resultIndex;
    }
    return -1;
}

void shuffleArray(int arr[], int size) {
    int temp = 0;
    for (int i = size - 1; i > 0; --i) {
        int j = rand() % (i + 1);

        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

int randomSearch(int *arr, int size, int targetValue) {
    int indexCheck[size];

    for (int i = 0; i < size; i++) {
        indexCheck[i] = i;
    }

    shuffleArray(indexCheck, size);

    for (int i = 0; i < size; i++) {
        if (arr[indexCheck[i]] == targetValue) {
            return indexCheck[i];
        }
    }

    return -1;
}

void swap(int &x, int &y) {
    int temp = x;
    x = y;
    y = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[j], arr[i]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);

        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

int *createArray(int size) {
    int *arr = new int[size];

    for (int i = 0; i < size; i++) {
        arr[i] = (rand() % (size * 10 + 1));
    }

    quickSort(arr, 0, size - 1);
    return arr;
}

void testLinearIterative(int arr[], int size) {
    chrono::time_point<std::chrono::system_clock> startTime;
    chrono::duration<double, milli> elapsedTime;
    startTime = std::chrono::system_clock::now();
    for (int i = 0; i < 10000; i++) {
        linearSearch(arr, size, arr[size / 6]);
    }
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution took for arr is (the key is close to the beginning) " << (elapsedTime.count()) / 10000 <<
            " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    for (int i = 0; i < 10000; i++) {
        linearSearch(arr, size, arr[size / 2]);
    }
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution took for arr is (the key is around the middle)  " << (elapsedTime.count()) / 10000 <<
            " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    for (int i = 0; i < 10000; i++) {
        linearSearch(arr, size, arr[size - (size / 6)]);
    }
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution took for arr is (the key is close to the end) " << (elapsedTime.count()) / 10000 <<
            " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    for (int i = 0; i < 10000; i++) {
        linearSearch(arr, size, -1);
    }
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution took for arr is (the key does not exist in the collection) " << (elapsedTime.count()) / 10000 <<
            " milliseconds." << endl;
    cout << endl;
}

void testLinearRecursive(int arr[], int size) {
    chrono::time_point<std::chrono::system_clock> startTime;
    chrono::duration<double, milli> elapsedTime;
    startTime = std::chrono::system_clock::now();
    for (int i = 0; i < 10000; i++) {
        linearSearchRecursive(arr, size, arr[size / 6]);
    }
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution took for arr is (the key is close to the beginning) " << (elapsedTime.count()) / 10000 <<
            " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    for (int i = 0; i < 10000; i++) {
        linearSearchRecursive(arr, size, arr[size / 2]);
    }
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution took for arr is (the key is around the middle)  " << (elapsedTime.count()) / 10000 <<
            " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    for (int i = 0; i < 10000; i++) {
        linearSearchRecursive(arr, size, arr[size - (size / 6)]);
    }
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution took for arr is (the key is close to the end) " << (elapsedTime.count()) / 10000 <<
            " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    for (int i = 0; i < 10000; i++) {
        linearSearchRecursive(arr, size, size * 10 + 1);
    }
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution took for arr is (the key does not exist in the collection) " << (elapsedTime.count()) / 10000 <<
            " milliseconds." << endl;
    cout << endl;
}

void testBinarySearch(int arr[], int size) {
    chrono::time_point<std::chrono::system_clock> startTime;
    chrono::duration<double, milli> elapsedTime;
    startTime = std::chrono::system_clock::now();
    for (int i = 0; i < 10000; i++) {
        binarySearch(arr, size, arr[size / 6]);
    }
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution took for arr is (the key is close to the beginning) " << (elapsedTime.count()) / 10000 <<
            " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    for (int i = 0; i < 10000; i++) {
        binarySearch(arr, size, arr[size / 2]);
    }
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution took for arr is (the key is around the middle)  " << (elapsedTime.count()) / 10000 <<
            " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    for (int i = 0; i < 10000; i++) {
        binarySearch(arr, size, arr[size - (size / 6)]);
    }
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution took for arr is (the key is close to the end) " << (elapsedTime.count()) / 10000 <<
            " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    for (int i = 0; i < 10000; i++) {
        binarySearch(arr, size, size * 10 + 1);
    }
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution took for arr is (the key does not exist in the collection) " << (elapsedTime.count()) / 10000 <<
            " milliseconds." << endl;
    cout << endl;
}

void testJumpSearch(int arr[], int size) {
    chrono::time_point<std::chrono::system_clock> startTime;
    chrono::duration<double, milli> elapsedTime;
    startTime = std::chrono::system_clock::now();
    for (int i = 0; i < 10000; i++) {
        jumpSearch(arr, size, arr[size / 6]);
    }
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution took for arr is (the key is close to the beginning) " << (elapsedTime.count()) / 10000 <<
            " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    for (int i = 0; i < 10000; i++) {
        jumpSearch(arr, size, arr[size / 2]);
    }
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution took for arr is (the key is around the middle)  " << (elapsedTime.count()) / 10000 <<
            " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    for (int i = 0; i < 10000; i++) {
        jumpSearch(arr, size, arr[size - (size / 6)]);
    }
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution took for arr is (the key is close to the end) " << (elapsedTime.count()) / 10000 <<
            " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    for (int i = 0; i < 10000; i++) {
        jumpSearch(arr, size, size * 10 + 1);
    }
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution took for arr is (the key does not exist in the collection) " << (elapsedTime.count()) / 10000 <<
            " milliseconds." << endl;
    cout << endl;
}

void testRandomSearch(int arr[], int size) {
    chrono::time_point<std::chrono::system_clock> startTime;
    chrono::duration<double, milli> elapsedTime;
    startTime = std::chrono::system_clock::now();
    for (int i = 0; i < 10000; i++) {
        randomSearch(arr, size, arr[size / 6]);
    }
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution took for arr is (the key is close to the beginning) " << (elapsedTime.count()) / 10000 <<
            " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    for (int i = 0; i < 10000; i++) {
        randomSearch(arr, size, arr[size / 2]);
    }
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution took for arr is (the key is around the middle)  " << (elapsedTime.count()) / 10000 <<
            " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    for (int i = 0; i < 10000; i++) {
        randomSearch(arr, size, arr[size - (size / 6)]);
    }
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution took for arr is (the key is close to the end) " << (elapsedTime.count()) / 10000 <<
            " milliseconds." << endl;
    startTime = std::chrono::system_clock::now();
    for (int i = 0; i < 10000; i++) {
        randomSearch(arr, size, size * 10 + 1);
    }
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Execution took for arr is (the key does not exist in the collection) " << (elapsedTime.count()) / 10000 <<
            " milliseconds." << endl;
    cout << endl;
}


int main() {
    srand(time(0));

    int *arr1 = createArray(100);
    int size1 = 100;
    int *arr2 = createArray(200);
    int size2 = 200;
    int *arr3 = createArray(500);
    int size3 = 500;
    int *arr4 = createArray(1000);
    int size4 = 1000;
    int *arr5 = createArray(2500);
    int size5 = 2500;
    int *arr6 = createArray(5000);
    int size6 = 5000;
    int *arr7 = createArray(7500);
    int size7 = 7500;
    int *arr8 = createArray(10000);
    int size8 = 10000;
    int *arr9 = createArray(15000);
    int size9 = 15000;
    int *arr10 = createArray(20000);
    int size10 = 20000;
    int *arr11 = createArray(30000);
    int size11 = 30000;

    cout << endl;

    cout << "Linear Iterative" << endl;
    testLinearIterative(arr1, size1);
    testLinearIterative(arr2, size2);
    testLinearIterative(arr3, size3);
    testLinearIterative(arr4, size4);
    testLinearIterative(arr5, size5);
    testLinearIterative(arr6, size6);
    testLinearIterative(arr7, size7);
    testLinearIterative(arr8, size8);
    testLinearIterative(arr9, size9);
    testLinearIterative(arr10, size10);
    testLinearIterative(arr11, size11);
    cout << endl;

    cout << "Linear Recursive" << endl;
    testLinearRecursive(arr1, size1);
    testLinearRecursive(arr2, size2);
    testLinearRecursive(arr3, size3);
    testLinearRecursive(arr4, size4);
    testLinearRecursive(arr5, size5);
    testLinearRecursive(arr6, size6);
    testLinearRecursive(arr7, size7);
    testLinearRecursive(arr8, size8);
    testLinearRecursive(arr9, size9);
    testLinearRecursive(arr10, size10);
    testLinearRecursive(arr11, size11);
    cout << endl;

    cout << "Binary" << endl;
    testBinarySearch(arr1, size1);
    testBinarySearch(arr2, size2);
    testBinarySearch(arr3, size3);
    testBinarySearch(arr4, size4);
    testBinarySearch(arr5, size5);
    testBinarySearch(arr6, size6);
    testBinarySearch(arr7, size7);
    testBinarySearch(arr8, size8);
    testBinarySearch(arr9, size9);
    testBinarySearch(arr10, size10);
    testBinarySearch(arr11, size11);
    cout << endl;

    cout << "Jump" << endl;
    testJumpSearch(arr1, size1);
    testJumpSearch(arr2, size2);
    testJumpSearch(arr3, size3);
    testJumpSearch(arr4, size4);
    testJumpSearch(arr5, size5);
    testJumpSearch(arr6, size6);
    testJumpSearch(arr7, size7);
    testJumpSearch(arr8, size8);
    testJumpSearch(arr9, size9);
    testJumpSearch(arr10, size10);
    testJumpSearch(arr11, size11);
    cout << endl;

    cout << "Random" << endl;
    testRandomSearch(arr1, size1);
    testRandomSearch(arr2, size2);
    testRandomSearch(arr3, size3);
    testRandomSearch(arr4, size4);
    testRandomSearch(arr5, size5);
    testRandomSearch(arr6, size6);
    testRandomSearch(arr7, size7);
    testRandomSearch(arr8, size8);
    testRandomSearch(arr9, size9);
    testRandomSearch(arr10, size10);
    testRandomSearch(arr11, size11);
    cout << endl;

    delete [] arr1;
    delete [] arr2;
    delete [] arr3;
    delete [] arr4;
    delete [] arr5;
    delete [] arr6;
    delete [] arr7;
    delete [] arr8;
    delete [] arr9;
    delete [] arr10;
    delete [] arr11;
}
