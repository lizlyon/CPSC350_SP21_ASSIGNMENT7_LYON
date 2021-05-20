#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include "sort.h"

using namespace std;

Sort::Sort(): size(0){

	arr = quickArr = mergeArr = selectionArr = insertionArr = bubbleArr = radixArr = NULL;
	srand(static_cast<unsigned int>(time(NULL)));
}

Sort::~Sort(){
	clear();
}

void Sort::swap(double* x, double* y){
    double temp = *x;
    *x = *y;
    *y = temp;
}

int Sort::partition(double* arr, int lo, int hi){
	double pivot = arr[hi]; //this is dangerous if the data is sorted

	int smallValue = lo - 1;

	for (int j = lo; j <= hi - 1; j++){
		if (arr[j] <= pivot){
			smallValue++;
			//swap so now the small value < pivot
			swap(&arr[smallValue], &arr[j]);
		}
	}
	//now put the pivot back in place and + 1
	swap(&arr[smallValue + 1], &arr[hi]);
	return (smallValue + 1);
}

void Sort::quickSort(double* arr, int lo, int hi){
	if (lo < hi){
		int partitionIndex = partition(arr, lo, hi);

		quickSort(arr, lo, partitionIndex - 1);
		quickSort(arr, partitionIndex + 1, hi);
	}
}

void Sort::merge(double* arr, int lo, int m, int hi){
	int n1 = m - lo + 1;
	int n2 = hi - m;

	//create temp arrays
	double* low =  new double[n1];
	double* high = new double[n2];

	for (int i = 0; i < n1; i++){
		low[i] = arr[lo + i];
	}

	for (int j = 0; j < n2; j++){
		high[j] = arr[m + 1 + j];
	}

	int i = 0;
	int j = 0;
	int k = lo;

	while (i < n1 && j < n2){
		if (low[i] <= high[j]){
			arr[k] = low[i];
			i++;
		}
		else{
			arr[k] = high[j];
			j++;
		}
		k++;
	}

	while (i < n1){
		arr[k] = low[i];
		i++;
		k++;
	}

	while (j < n2){
		arr[k] = high[j];
		j++;
		k++;
	}

	delete[] high;
	delete[] low;
}

void Sort::mergeSort(double* arr, int lo, int hi){
  if (lo >= hi){
    return;
  }
    //compute the middle
    int m = lo + (hi - lo) / 2;
    mergeSort(arr, lo, m); //recursiveley sort the lo to middle
    mergeSort(arr, m + 1 , hi); //recursiveley sort the middle to high
    merge(arr, lo, m, hi); //recursiveley merge the elements
}

void Sort::selectionSort(double* arr, int n){ //repeadedy pick the next smallest thing and put in order
	//k is to the right of k, so its from that region that we pick the next min
	//then when found, we swap the values
	clock_t s = clock();
	cout << "Start time: " << s << endl;

	int i, j, currMinIdx;

	for (i = 0; i < n-1; i++){

		currMinIdx = i;

		//start w j+1 n everything left of k will be sorted
		for (j = i + 1; j < n; j++){
			if (arr[j] < arr[currMinIdx]){ //then we have to swap
				currMinIdx = j;
			}
		}
		//now swap the currMinIdx at i position
		swap(&arr[currMinIdx], &arr[i]);
	}

	clock_t e = clock();
	cout << "End time: " << e << endl;
	cout << "Duration: " << (float(e - s) / (CLOCKS_PER_SEC)) * 1000 << " seconds" << endl << endl;
}

void Sort::insertionSort(double* arr, int n){
  clock_t s = clock();
  cout << "Start time: " << s << endl;

  for (int j = 1; j < n; ++j){ //0 position is already sorted relative to itself
    double temp = arr[j]; //save value at the marker j
    int k = j;//start shifting at k

    while (k > 0 && arr[k-1] >= temp){ //moves values to the right to make room for values
      arr[k] = arr[k-1]; //then just copy over
      --k;
    }
    arr[k] = temp; //once the loop breaks then we found the correct temp value pos
  }
  clock_t e = clock();
  cout << "End time: " << e << endl;
  cout << "Duration: " << (float(e - s) / (CLOCKS_PER_SEC)) * 1000 << " seconds" << endl << endl;
}

void Sort::bubbleSort(double* arr, int n){ //quadratic in both comparisions and swaps
	clock_t s = clock();
	cout << "Start time: " << s << endl;

	  for(int i = 0; i < n-1; ++i){
			for(int j = 0; j < n-1; ++j){
		  	if(arr[j] > arr[j+1]){
					swap(&arr[j], &arr[j + 1]);
		  	}
			}
	  }

	  clock_t e = clock();
	  cout << "End time: " << e << endl;
	  cout << "Duration: " << (float(e - s) / (CLOCKS_PER_SEC)) * 1000 << " seconds" << endl << endl;
}


double Sort::getMax(double* arr, int n){
  double max = arr[0];

  for (int i = 0; i < n; ++i){
    if (arr[i] > max){
      max = arr[i];
    }
  }
  return max;
}

void Sort::countSort(double* arr, int n, double temp){
	//variable declaration
	const int MAX = 10;

	double* arrNew = new double[n];

	int count[MAX];

	for (int i = 0; i < MAX; ++i){
		count[i] = 0;
	}

	//get element count
	for (int i = 0; i < n; ++i){
		count[static_cast<int>((arr[i] / temp)) % 10]++;
	}

	//get cumulative count
	for (int i = 1; i < MAX; i++){
		count[i] += count[i-1];
	}

	//get elements in sorted order
	for (int i = n - 1; i >= 0; i--){
		arrNew[count[static_cast<int>((arr[i] / temp)) % 10] - 1] = arr[i];
		count[static_cast<int>((arr[i] / temp)) % 10]--;
	}

	//assing the initial array the value of the new array
	for (int i = 0; i < n; i++){
		arr[i] = arrNew[i];
	}

	delete[] arrNew;
}

void Sort::radixSort(double* arr, int n){
	clock_t s = clock();
	cout << "Start time: " << s << endl;

	//get max
	double maxNum = getMax(arr,n);

	//sort the elements on their place value
	for (int temp = 1; maxNum/temp > 0; temp *=10){
		countSort(arr,n,temp);
	}
	clock_t e = clock();
	cout << "End time: " << e << endl;
	cout << "Duration: " << (float(e - s) / (CLOCKS_PER_SEC)) * 1000 << " seconds" << endl << endl;
}

void Sort::printArray(double* arr, int n){
	for (int i = 0; i < n; i++){
		cout << fixed << setprecision(2) << arr[i] << " ";
	}
}

void Sort::randomNumberFileGenerator(int number, const string& filename){
	ofstream outFile(filename, ios::trunc);

	outFile << number << endl;

	for (int i = 0; i < number; i++){
		double ranDbl = (100000.0 - 0.0) * (static_cast<double>(rand()) / static_cast<double>(RAND_MAX)) + 0;
		outFile << fixed << setprecision(2) << ranDbl << endl;
	}

	outFile.close();
}

void Sort::readFile(const string& filename){
	ifstream inFile(filename);

	inFile >> size;

	if (arr){
		clear();
	}

	arr = new double[size];
	quickArr = new double[size];
	mergeArr = new double[size];
	selectionArr = new double[size];
	insertionArr = new double[size];
	bubbleArr = new double[size];
	radixArr = new double[size];

	int index = 0;
	while (inFile >> arr[index++] >> ws) {}

	for (int i = 0; i < size; i++){
		quickArr[i] = mergeArr[i] = selectionArr[i] = insertionArr[i] = bubbleArr[i] = radixArr[i] = arr[i] ;
	}

	inFile.close();
}

void Sort::clear(){
	//delet the arrays
	delete[] arr;
	delete[] quickArr;
	delete[] mergeArr;
	delete[] selectionArr;
	delete[] insertionArr;
	delete[] bubbleArr;
	delete[] radixArr;

	size = 0;
}

void Sort::run(const string& mode, int number, const string& filename){

	if (mode == "create"){
		randomNumberFileGenerator(number, filename);
	}

	else if (mode == "sort"){
		readFile(filename);

		cout << "\nGiven array: " << endl;
		printArray(arr, size);
		cout << endl;

		cout << "\n1) QUICK sorted array:" << endl;
		clock_t start = clock();
		cout << "Start time: " << start << endl;
		quickSort(quickArr, 0, size - 1);
		clock_t end = clock();
		cout << "End time: " << end << endl;
		cout << "Duration: " << (float(end - start) / (CLOCKS_PER_SEC)) * 1000 << " seconds" << endl << endl;
		printArray(quickArr, size);

		cout << "\n\n2) MERGE sorted array:" << endl;
		clock_t s = clock();
		cout << "Start time: " << s << endl;
		mergeSort(mergeArr, 0, size - 1);
		clock_t e = clock();
		cout << "End time: " << e << endl;
		cout << "Duration: " << (float(e - s) / (CLOCKS_PER_SEC)) * 1000 << " seconds" << endl << endl;
		printArray(mergeArr, size);

		cout << "\n\n3) SELECTION sorted array:" << endl;
		selectionSort(selectionArr, size);
		printArray(selectionArr, size);
		cout << endl;

		cout << "\n4) INSERTION sorted array:" << endl;
		insertionSort(insertionArr, size);
		printArray(insertionArr, size);
		cout << endl;

		cout << "\n5) BUBBLE sorted array:" << endl;
		bubbleSort(bubbleArr, size);
		printArray(bubbleArr, size);
		cout << endl;

		cout << "\n6) RADIX sorted array:" << endl;
		radixSort(radixArr, size);
		printArray(radixArr, size);
		cout << endl << "\n";
	}
}
