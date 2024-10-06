#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

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
void fillArray(int array[], int lengh) {
	for (int i = 0; i < lengh; ++i) {
		array[i] = rand();
	}
}
bool arrayComparison(int array1[], int array2[], int lenghs) {
	for (int i = 0; i < lenghs; ++i) {
		if (array1[i] != array2[i]) {
			return false;
		}
	}
	return true;
}

// Smart QSort
void insertSort(int array[], int first, int last) {
	int newElement = 0, location = 0;
	for (int i = first; i <= last; ++i) {
		newElement = array[i]; 
		location = i - 1;
		while (location >= 0 && array[location] > newElement) {
			array[location + 1] = array[location];
			--location;
		}
		array[location + 1] = newElement;
	}
}
void smartQSort(int array[], int first, int last) {
	if (last - first + 1 < 10) {
		insertSort(array, first, last);
	}
	else {
		if (first < last) {
			int supportingElement = array[first];
			int left = first;
			int right = last;
			while (left <= right) {
				while ((array[left] < supportingElement) && (left <= right)) {
					++left;
				}
				while ((supportingElement < array[right]) && (left <= right)) {
					--right;
				}
				if (left <= right) {
					swap(&array[left], &array[right]);
					++left;
					--right;
				}
			}
			smartQSort(array, first, right);
			smartQSort(array, left, last);
		}
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
	if (auxiliaryArray == NULL) {
		return -1;
	}
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
			right = middle - 1;
		}
		else if (arrayToSearch[middle] < searchNumber) {
			left = middle + 1;
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
	smartQSort(arrayToSearch, 0, n - 1);
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
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	for (int i = 0; i < 10; ++i) {
		if (!presenceInArray(array, 10, array[i])) {
			return false;
		}
	}
	if (presenceInArray(array, 10, array[0] - 1) || presenceInArray(array, 10, array[9] + 1)) {
		return false;
	}
	return true;
}
bool testSmartQsort() {
	int array[] = { 6, 2, 5, 3, 1, 8, 2, 3, 5, 7 };
	int referenceArray[] = { 1, 2, 2, 3, 3, 5, 5, 6, 7 ,8 };
	smartQSort(array, 0, 9);
	return arrayComparison(array, referenceArray, 10);
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