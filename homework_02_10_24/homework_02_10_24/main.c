#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

void swap(int* left, int* right) {
    if (left != right) {
        *left ^= *right;
        *right ^= *left;
        *left ^= *right;
    }
}

void printArray(int array[], int lengh) {
    for (int i = 0; i < lengh; ++i) {
        printf("%d ", array[i]);
    }
}

// Half QSort
void fillArray(int array[], int lengh) {
    for (int i = 0; i < lengh; ++i) {
        array[i] = rand();
    }
}
void halfQSort(int array[], int lengh) {
    int supportingElement = array[0], i = 0, j = lengh - 1;
    while (i <= j) {
        while ((array[i] < supportingElement) && (i <= j)) {
            ++i;
        }
        while ((supportingElement <= array[j]) && (i <= j)) {
            --j;
        }
        if (i <= j) {
            swap(&array[i], &array[j]);
            ++i;
            --j;
        }
    }
}
void wrapperHalfQSort() {
    int array[10] = { 0 };
    fillArray(array, 10);
    int supportingElement = array[0];
    halfQSort(array, 10);
    printf("----------\nHalfQSort\n Supporting element: %d\n", supportingElement);
    printArray(array, 10);
    printf("\n----------");
}



// Bubble and counting
float bubbleSort(int array[], int lengh) {
    clock_t timeCounter = clock();
    for (int i = 0; i + 1 < lengh; ++i) {
        for (int j = 0; j + 1 < lengh; ++j) {
            if (array[j + 1] < array[j]) {
                swap(&array[j + 1], &array[j]);
            }
        }
    }
    timeCounter = clock() - timeCounter;
    return (float)timeCounter / CLOCKS_PER_SEC;
}
float countingSort(int array[], int lengh) {
    clock_t timeCounter = clock();
    int min = array[0], max = array[0], j = 0;
    for (int i = 0; i < lengh; ++i) {
        if (min > array[i]) {
            min = array[i];
        }
        if (max < array[i]) {
            max = array[i];
        }
    }
    int* auxiliaryArray = (int*)calloc(max - min + 1, sizeof(int));
    for (int i = 0; i < lengh; ++i) {
        ++auxiliaryArray[array[i] - min];
    }
    for (int i = 0; i < max - min + 1; ++i) {
        while (auxiliaryArray[i] > 0) {
            array[j] = i + min;
            ++j;
            --auxiliaryArray[i];
        }
    }
    timeCounter = clock() - timeCounter;
    free(auxiliaryArray);
    return (float)timeCounter / CLOCKS_PER_SEC;
}
void bubbleAndCouting() {
    int lengh = 100000;
    int array[100000] = { 0 };
    fillArray(array, lengh);
    printf("\nBubble And Couting\n Bubble sort time: %fsec.\n Counting sort time: %fsec.\n----------",
        bubbleSort(array, lengh), countingSort(array, lengh));
}

// Raising to a power
float raisingToAPower(int number, int degree) {
    float result = 1;
    for (int i = 0; i < abs(degree); ++i) {
        result *= number;
    }
    if (degree >= 0) {
        return result;
    }
    else {
        return (1 / result);
    }
}
float fastRaisingToAPower(int number, int degree) {
    float result = 1;
    int degreeAbs = abs(degree);
    while (degreeAbs) {
        if (degreeAbs % 2 == 0) {
            degreeAbs /= 2;
            number *= number;
        }
        else {
            degreeAbs--;
            result *= number;
        }
    }
    if (degree >= 0) {
        return result;
    }
    else {
        return 1 / result;
    }

}

// Numbers Fibonacci
int recursivelyFibonacci(int number) {
    if (number == 0) {
        return 0;
    }
    else if (number <= 2) {
        return 1;
    }
    return (recursivelyFibonacci(number - 1) + recursivelyFibonacci(number - 2));
}
int iterativelyFibonacci(int number) {
    if (number == 0) {
        return 0;
    }
    else if (number <= 2) {
        return 1;
    }
    int fib1 = 1, fib2 = 1, c = 0;
    for (int i = 3; i <= number; ++i) {
        c = fib1 + fib2;
        fib1 = fib2;
        fib2 = c;
    }
    return fib2;
}
void fibonacci() {
    int number = 45;
    clock_t timeCounter1 = clock();
    recursivelyFibonacci(number);
    timeCounter1 = clock() - timeCounter1;
    clock_t timeCounter2 = clock();
    iterativelyFibonacci(number);
    timeCounter2 = clock() - timeCounter2;
    printf("\nFibonacci\n Recursively, number 45: %fsec.\n Iteratively, number 45: %fsec.\n----------",
        (float)timeCounter1 / CLOCKS_PER_SEC,
        (float)timeCounter2 / CLOCKS_PER_SEC);
}

// Tests
bool arrayComparison(int array1[], int array2[], int lenghs) {
    for (int i = 0; i < lenghs; ++i) {
        if (array1[i] != array2[i]) {
            return false;
        }
    }
    return true;
}
bool testHalfQSort() {
    int array[] = { 3, 5, 2, 1, 4 };
    int supportingElement = array[0];
    halfQSort(array, 5);
    return (array[0] < supportingElement) && (array[1] < supportingElement) && (array[2] >= supportingElement)
        && (array[3] >= supportingElement) && (array[4] >= supportingElement);
}
bool testBubbleSort() {
    int array[] = { -1, 4, 5, -3, 2 }, sortedArray[] = { -3, -1, 2, 4, 5 };
    bubbleSort(array, 5);
    return arrayComparison(array, sortedArray, 5);
}
bool testCoutingSort() {
    int array[] = { -1, 4, 5, -3, 2 }, sortedArray[] = { -3, -1, 2, 4, 5 };
    countingSort(array, 5);
    return arrayComparison(array, sortedArray, 5);
}
bool testRaisingToAPower() {
    return ((raisingToAPower(10, 2) == 100) && (raisingToAPower(10, 0) == 1) && (raisingToAPower(-10, 1) == -10)
        && (raisingToAPower(10, -1) == 0, 1) && (raisingToAPower(10, 1) == 10) && (raisingToAPower(-10, 2) == 100)
        && (raisingToAPower(-10, -1) == -0, 1) && (raisingToAPower(-10, -2) == -0, 01));
}
bool testFastRaisingToAPower() {
    return ((fastRaisingToAPower(10, 2) == 100) && (fastRaisingToAPower(10, 0) == 1) && (fastRaisingToAPower(-10, 2) == 100)
        && (fastRaisingToAPower(10, -1) == 0, 1) && (fastRaisingToAPower(10, 1) == 10) && (fastRaisingToAPower(-10, 1) == -10)
        && (fastRaisingToAPower(-10, -1) == -0, 1) && (fastRaisingToAPower(-10, -2) == -0, 01));
}
bool testRecursivelyFibonacci() {
    int array[10] = { 0 }, arrayFibonacciNumbers[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };
    for (int i = 0; i < 10; ++i) {
        array[i] = recursivelyFibonacci(i);
    }
    return arrayComparison(array, arrayFibonacciNumbers, 10);
}
bool testIterativelyFibonacci() {
    int array[10] = { 0 }, arrayFibonacciNumbers[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };
    for (int i = 0; i < 10; ++i) {
        array[i] = iterativelyFibonacci(i);
    }
    return arrayComparison(array, arrayFibonacciNumbers, 10);
}
bool testProgram() {
    return testBubbleSort() && testCoutingSort() && testRaisingToAPower() && testFastRaisingToAPower()
        && testRecursivelyFibonacci() && testIterativelyFibonacci() && testHalfQSort();
}

int main(void) {
    if (!testProgram()) {
        printf("\nTest failed");
        return 0;
    }
    printf("\nPlease wait\n");
    wrapperHalfQSort();
    bubbleAndCouting();
    printf("\nRaising to a power\n Ordinary: %f\n Fast: %f\n----------",
        raisingToAPower(-10, -1),
        fastRaisingToAPower(-10, -1));
    fibonacci();
}