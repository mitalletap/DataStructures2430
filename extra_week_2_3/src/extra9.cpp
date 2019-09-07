//============================================================================
// Name        : extra9.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <ctime>
using namespace std;

void swap(int *x, int *y){
	int temp = *x;
	*x = *y;
	*y = temp;
}


void randomizeArray(int arr[], int s){
	for(int i = 0; i < s; i++){
		arr[i] = rand() % 1000;
	}
}

// BUBBLE

void bubbleSort(int arr[], int s){
	for(int i = 0; i < s - 1; i++){
		for(int j = 0; j < s - i - 1; j++){
			if(arr[j] > arr[j+1]){
				swap(&arr[j], &arr[j+1]);
			}
		}
	}
}

void printArray(int arr[], int s){
	for(int i = 0; i < s; i++){
		cout << arr[i] << " ";
	}
	cout << endl;
}


// INSERTION

void insertionSort(int arr[], int s){
	for(int i = 1; i < s; i++){
		int key = arr[i];
		int j = i-1;
		while(j >= 0 && arr[j] > key){
			arr[j+1] = arr[j];
			j = j-1;
		}
		arr[j+1] = key;
	}
}


// SELECTION SORT

void selectionSort(int arr[], int s){
	for(int i = 0; i < s-1; i++){
		int min = i;
		for(int j = i+1; j < s; j++){
			if(arr[j] < arr[min]){
				min = j;
			}
		}
		swap(&arr[min], &arr[i]);

	}
}


int main() {
	clock_t program, bubble, insertion, selection;
	program = clock();
	cout << "Welcome to the program!" << endl;
	cout << "Input a size for the array!" << endl;
	int s;
	cin >> s;
	cout << "Please wait while the program runs!" << endl;
	srand(time(NULL));
	// Initialize Array
	//int s = 100000;
	int *a = new int[s];

	//cout << "RANDOMIZING ARRAY" << endl;
	randomizeArray(a,s);
	//printArray(a,s);


	//cout << "BUBBLE SORTING" << endl;
	bubble = clock();
	bubbleSort(a, s);
	bubble = clock() - bubble;
	//printArray(a,s);

	//cout << endl;

	//cout << "RANDOMIZING ARRAY" << endl;
	randomizeArray(a,s);
	//printArray(a,s);


	//cout << "INSERTION SORTING" << endl;
	insertion = clock();
	insertionSort(a, s);
	insertion = clock() - insertion;
	//printArray(a,s);

	//cout << endl;

	//cout << "RANDOMIZING ARRAY" << endl;
	randomizeArray(a,s);
	//printArray(a,s);

	//cout << "SELECTION SORTING" << endl;
	selection = clock();
	selectionSort(a, s);
	selection = clock() - selection;
	//printArray(a,s);


	delete [] a;
	cout << "Computation Complete!" << endl;
	cout << "Array Deleted!" << endl;
	cout << endl;

//	int arrayTimes[3] = {bubble, insertion, selection};
//	bubbleSort(arrayTimes, 3);
//	cout << arrayTimes[0] << " had the fastest time!" << endl;
//	cout << arrayTimes[1] << " had the second fastest time!" << endl;
//	cout << arrayTimes[2] << " had the slowest time!" << endl;



	program = clock() - program;


	cout << "===================================" << endl;
	cout << "It took BUBBLE SORT " << bubble << " ticks or " << bubble/CLOCKS_PER_SEC << " seconds to run" << endl;
	cout << "===================================" << endl;
	cout << "==========================================" << endl;
	cout << "It took the INSERTION SORT " << insertion << " ticks or " << insertion/CLOCKS_PER_SEC << " seconds to run" << endl;
	cout << "==========================================" << endl;
	cout << "==========================================" << endl;
	cout << "It took the SELECTION SORT " << selection << " ticks or " << selection/CLOCKS_PER_SEC << " seconds to run" << endl;
	cout << "==========================================" << endl;
	cout << "=====================================" << endl;
	cout << "It took the program " << program << " ticks or " << program/CLOCKS_PER_SEC << " seconds to run" << endl;
	cout << "=====================================" << endl;






	return 0;
}
