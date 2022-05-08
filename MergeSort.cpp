//============
// Main.cpp
//============

// Programs: Selection kth
// Programmed by Van Huynh
// Class: CS 3310-03

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

typedef int* IntArrayPtr;

const int RANDOM_MIN_BOUND = -750;
const int RANDOM_MAX_BOUND = 750;
const int RANDOM_TOTAL_BOUND = 1501;
const float SMALLEST = 0;
const float QUARTER = 0.25;
const float HALF = 0.5;
const float THREE_QUARTER = 0.75;
const float LAST_SMALLEST = 1;

const int LARGEST_ARRAY_SIZE = 1000;

/*------------------ Function Prototypes --------------------------*/
void populateList(int N, vector<int> &A, int value);
void displayList(int N, const vector<int> const &A);
vector<int> slice(vector<int> const& v, int m, int n);
vector<int> generateList(int N);
void merge(vector<int> & A, const int low, const int mid, const int high);
void mergeSort(vector<int> &A, int low, int high);
void Selectkth1(int k, vector<int> const& A);
//int Selectkth2(int k);
//int Selectkth3(int k);
//int Selectkth4(int k);

/*------------------ Funtion Implementation ------------------------*/
void populateList(int N, vector<int> &A, int value)
{
	for (int i = 0; i < N; ++i) {
		A[i] = value;
	}
}
void displayList(int N, const vector<int> const &A)
{
	for (int i = 0; i < N; ++i) {
		cout << setw(4) << A[i] << " |";
	}
	cout << "\n-------------------------" << endl;
}
vector<int> slice(vector<int> const& v, int m, int n)
{
	auto first = v.begin() + m;
	auto last = v.begin() + n + 1;
	vector<int> vec(first, last);
	return vec;
}
vector<int> generateList(int N)
{
	srand(time(0));
	// 1. Creating vector
	vector<int> A(N);

	// 2. Initialize the vector
	// https://stackoverflow.com/questions/7887941/random-number-from-9-to-9-in-c
	for (int i = 0; i < N; ++i) {
		A[i] = rand() % RANDOM_TOTAL_BOUND + (RANDOM_MIN_BOUND);
	}
	return A;
}
void merge(vector<int> &A, const int low, const int mid, const int high)
{
	// create 2 half vector
	vector<int> L(mid - low + 1);
	L = slice(A, low, mid);
	vector<int> R(high - mid);
	R = slice(A, mid + 1, high);

	int i = 0, j = 0, k = low;

	// pick larger among until we reach either end of either L or R
	while (i < L.size() && j < R.size()) {
		if (L[i] <= R[j]) {
			A[k] = L[i];
			i++;
		}
		else {
			A[k] = R[j];
			j++;
		}
		k++;
	}

	// when run out of elements in either L or R,
	// pick up the remaining elements and put in A[p..r]
	while (i < L.size()) {
		A[k] = L[i];
		i++;
		k++;
	}

	while (j < R.size()) {
		A[k] = R[j];
		j++;
		k++;
	}
}
void mergeSort(vector<int> &A, int low, int high)
{
	if (low < high) {

		int mid = low + (high - low) / 2;

		mergeSort(A, low, mid);
		mergeSort(A, mid + 1, high);

		// Merge the sorted subarrays
		merge(A, low, mid, high);
	}
}
void Selectkth1(int N, vector<int> const &A)
{
	int k1 = SMALLEST * N;
	int k2 = QUARTER * N;
	int k3 = HALF * N;
	int k4 = THREE_QUARTER * N;
	int k5 = N - 1;
	vector<int> temp(A.begin(), A.end());

	auto start = high_resolution_clock::now();
	mergeSort(temp, 0, temp.size() - 1);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(stop - start);

	//if (N < 100) {
	//	cout << "Sorted: ";
	//	displayList(N, temp);
	//}
	cout << "Size " << setw(4) << N << ": " << duration.count() << " nsec" << endl;
	cout << setw(6) << to_string(k1) + "th" << setw(6) << to_string(k2) + "th" << setw(6) << to_string(k3) + "th" << setw(6) << to_string(k4) + "th" << setw(6) << to_string(k5) + "th" << endl;
	cout << setw(6) << temp[k1] << setw(6) << temp[k2] << setw(6) << temp[k3] << setw(6) << temp[k4] << setw(6) << temp[k5] << endl;
}

// MAIN
int main(void)
{
	int nList[10] = { 10, 50, 100, 500, 1000 };
	vector<int> a = generateList(10);
	vector<int> b = generateList(50);
	vector<int> c = generateList(100);
	vector<int> d = generateList(500);
	vector<int> e = generateList(1000);

	Selectkth1(10, a);
	//Selectkth2(10, a);
	//Selectkth3(10, a);
	//Selectkth4(10, a);

	Selectkth1(50, b);
	//Selectkth2(50, b);
	//Selectkth3(50, b);
	//Selectkth4(50, b);

	Selectkth1(100, c);
	//Selectkth2(100, c);
	//Selectkth3(100, c);
	//Selectkth4(100, c);

	Selectkth1(500, d);
	//Selectkth2(500, d);
	//Selectkth3(500, d);
	//Selectkth4(500, d);

	Selectkth1(1000, e);
	//Selectkth2(1000, e);
	//Selectkth3(1000, e);
	//Selectkth4(1000, e;

	return 0;
}