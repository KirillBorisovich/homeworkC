#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void printArray(int array[], int lengh) {
	for (int i = 0; i < lengh; ++i) {
		printf("%d ", array[i]);
	}
}
void fillArray(int array[], int lengh) {
	for (int i = 0; i < lengh; ++i) {
		array[i] = rand();
	}
}

// The most common element
int theMostCommonElement(int array[], int lengh) {
	int min = array[0], max = array[0];
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
	int counterMax = 0, frequentEment = 0;
	for (int i = 0; i <= max - min + 1; ++i) {
		if (counterMax < auxiliaryArray[i]) {
			frequentEment = i + min;
			counterMax = auxiliaryArray[i];
		}
	}
	free(auxiliaryArray);
	return frequentEment;
}
void wrapperTheMostCommonElement() {
	int array[] = { 1, 2, 3, 3, 4, 5, 1, 2, 3, 7 };
	printf("\n----------\nThe most common element: %d\nArray: ", theMostCommonElement(array, 10));
	printArray(array, 10);
	printf("\n----------");
}

// Search
bool presenceInArray(int arrayToSearch[], int lengh, int searchNumber) {
	int left = 0, right = lengh - 1;
	while (left <= right) {
		int middle = (left + right) / 2;
		if (arrayToSearch[middle] == searchNumber) {
			return true;
		}
		else if (arrayToSearch[middle] > searchNumber) {
			right -= (lengh - 1) / 2;
		}
		else if (arrayToSearch[middle] < searchNumber) {
			left += (lengh - 1) / 2;
		}
	}
	return false;
}

void wrapperSearch() {
	int n = 0, k = 0;
	printf("\nSearch\n");
	printf(" Enter number n: ");
	scanf_s("%d", &n);
	printf(" Enter number k: ");
	scanf_s("%d", &k);

	int* arrayToSearch = (int*)calloc(n, sizeof(int));
	int* arrayOfRandomNumbers = (int*)calloc(k, sizeof(int));
	int maxKN = n > k ? n : k;
	for (int i = 0; i < maxKN; ++i) {
		if (n >= i) {
			arrayToSearch[i] = rand();
		}
		if (k >= i) {
			arrayOfRandomNumbers[i] = rand();
		}
	}
	printf(" Array: ");
	printArray(arrayToSearch, n);
	for (int i = 0; i < k; ++i) {
		if (presenceInArray(arrayToSearch, n, arrayOfRandomNumbers[i])) {
			printf("\n The %d is in the array", arrayOfRandomNumbers[i]);
		}
		else {
			printf("\n The %d is not in the array", arrayOfRandomNumbers[i]);
		}
	}
	printf("\n----------");
}

// Tests
bool testTheMostCommonElement() {
	int array[] = { 1, 2, -3, 4, 5, -3 };
	return theMostCommonElement(array, 5) == -3;
}
bool testPresenceInArray() {
	int array[] = { 1, 2, 3 };
	return presenceInArray(array, 5, 1) && presenceInArray(array, 5, 2) && presenceInArray(array, 5, 3)
		&& !presenceInArray(array, 5, 0) && !presenceInArray(array, 5, 4);
}
bool testProgram() {
	return testTheMostCommonElement() && testPresenceInArray();
}

int main(void) {
	if (!testProgram()) {
		printf("\nTest failed");
		return 1;
	}
	wrapperTheMostCommonElement();
	wrapperSearch();
}