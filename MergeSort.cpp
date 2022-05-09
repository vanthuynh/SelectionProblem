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

/*------------------ Helper Function Prototypes --------------------------*/
vector<int> slice(vector<int> const& v, int m, int n);
void swap(int *a, int *b);

/*------------------ Function Prototypes --------------------------*/
void populateList(int N, vector<int> &A, int value);
void displayList(int N, const vector<int> const &A);
vector<int> generateList(int N);
void merge(vector<int> & A, const int low, const int mid, const int high);
void mergeSort(vector<int> &A, int low, int high);
void partition(vector<int>& A, int low, int high, int &pivotPos);
void quickSortIterative(vector<int>& A, int low, int high, const int& k);
void Selectkth1(vector<int> const& A);
void Selectkth2(vector<int> const& A);
//int Selectkth3(int k);
//int Selectkth4(int k);

/*------------------ Helper Funtion Implementation ------------------------*/
vector<int> slice(vector<int> const& v, int m, int n)
{
	auto first = v.begin() + m;
	auto last = v.begin() + n + 1;
	vector<int> vec(first, last);
	return vec;
}
void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

/*------------------ Funtion Implementation ------------------------*/
void populateList(int N, vector<int>& A, int value)
{
	for (int i = 0; i < N; ++i) {
		A[i] = value;
	}
}
void displayList(int N, const vector<int> const& A)
{
	for (int i = 0; i < N; ++i) {
		cout << setw(4) << A[i] << " |";
	}
	cout << "\n-------------------------" << endl;
}
vector<int> generateList(int N)
{
	//srand(time(0));
	srand(350);
	// 1. Creating vector
	vector<int> A(N);

	// 2. Initialize the vector
	// https://stackoverflow.com/questions/7887941/random-number-from-9-to-9-in-c
	for (int i = 0; i < N; ++i) {
		A[i] = rand() % RANDOM_TOTAL_BOUND + (RANDOM_MIN_BOUND);
	}
	return A;
}
void merge(vector<int>& A, const int low, const int mid, const int high)
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
void mergeSort(vector<int>& A, int low, int high)
{
	if (low < high) {

		int mid = low + (high - low) / 2;

		mergeSort(A, low, mid);
		mergeSort(A, mid + 1, high);

		// Merge the sorted subarrays
		merge(A, low, mid, high);
	}
}
void partition(vector<int>& A, int low, int high, int &pivotPos)
{
	int pivotVal = A[low];
	int j = low;
	for (int i = low+1; i < high; ++i) {
		if (A[i] < pivotVal) {
			j++;
			swap(&A[i], &A[j]);
		}
	}
	pivotPos = j;
	swap(&A[low], &A[pivotPos]);

	///*TextBook version*/
	//int pivotVal = A[high];
	//int i = low - 1;
	//for (int j = 0; j < high-1; j++)
	//{
	//	if (A[j] <= pivotVal) {
	//		i += 1;
	//		swap(&A[i], &A[j]);
	//	}
	//}
	//swap(&A[i+1], &A[high]);
	//return i + 1;
}
void quickSortIterative(vector<int>& A, int low, int high, const int& k)
{
	int m = 1, j = low;
	int pivotPos;
	while (true) {
		partition(A, m, j, pivotPos);
		if (k == pivotPos) {
			return A[k];
		}
		else if (k < pivotPos) {
			j = pivotPos - 1;
		}
		else {
			m = pivotPos + 1;
		}
	}
}
void Selectkth1(vector<int> const& A)
{
	int N = A.size();
	int k1 = 0;
	int k2 = N / 4 ;
	int k3 = N / 2;
	int k4 = 3 * N / 4;
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
	cout << "Select-kth1 takes " << setw(4) << N << ": " << duration.count() << " nsec" << endl;
	cout << setw(6) << to_string(k1) + "th" << setw(6) << to_string(k2) + "th" << setw(6) << to_string(k3) + "th" << setw(6) << to_string(k4) + "th" << setw(6) << to_string(k5) + "th" << endl;
	cout << setw(6) << temp[k1] << setw(6) << temp[k2] << setw(6) << temp[k3] << setw(6) << temp[k4] << setw(6) << temp[k5] << endl;
}
void Selectkth2(vector<int> const& A)
{
	int N = A.size();
	int k1 = 0;
	int k2 = N / 4;
	int k3 = N / 2;
	int k4 = 3 * N / 4;
	int k5 = N - 1;
	vector<int> temp(A.begin(), A.end());

	auto start = high_resolution_clock::now();
	quickSortIterative(temp, 0, N - 1, k1);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(stop - start);

	//if (N < 100) {
	//	cout << "Sorted: ";
	//	displayList(N, temp);
	//}
	cout << "Select-kth1 takes " << setw(4) << N << ": " << duration.count() << " nsec" << endl;
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

	cout << "Size " << a.size() << ": " << endl;
	Selectkth1(a);
	//Selectkth2(a);
	//Selectkth3(a);
	//Selectkth4(a);

	Selectkth1(b);
	//Selectkth2(b);
	//Selectkth3(b);
	//Selectkth4(b);

	Selectkth1(c);
	//Selectkth2(c);
	//Selectkth3(c);
	//Selectkth4(c);

	Selectkth1(d);
	//Selectkth2(d);
	//Selectkth3(d);
	//Selectkth4(d);

	Selectkth1(e);
	//Selectkth2(e);
	//Selectkth3(e);
	//Selectkth4(e;

	return 0;
}