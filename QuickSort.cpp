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
const float K1 = 0;
const float K2 = 0.25;
const float K3 = 0.5;
const float K4 = 0.75;
const float K5 = 1;

const int TEST_TRIAL = 20;
const int SET_AMOUNT = 500;
const int LARGEST_ARRAY_SIZE = 1000;

/*------------------ Helper Function Prototypes --------------------------*/
vector<int> slice(vector<int> const& v, int m, int n);

/*------------------ Function Prototypes --------------------------*/
void populateList(int N, vector<int> &A, int value);
void displayList(int N, vector<int> const &A);
vector<int> generateList(int N);
void merge(vector<int> & A, const int low, const int mid, const int high);
void mergeSort(vector<int> &A, int low, int high);
void partition(vector<int>& A, int low, int high, int &pivotPos);
int quickSortIterative(vector<int>& A, int N, const int k);
void Select_kth_1(vector<int> const& A);
void Select_kth_2(vector<int> const& A);
void Select_kth_3(vector<int> const& A);
//int Select_kth_4(int k);

/*------------------ Helper Funtion Implementation ------------------------*/
vector<int> slice(vector<int> const& v, int m, int n)
{
	auto first = v.begin() + m;
	auto last = v.begin() + n + 1;
	vector<int> vec(first, last);
	return vec;
}

/*------------------ Funtion Implementation ------------------------*/
void populateList(int N, vector<int>& A, int value)
{
	for (int i = 0; i < N; ++i) {
		A[i] = value;
	}
}
void displayList(int N, vector<int> const& A)
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
	int pivotVal = A[low]; // value of pivot is at index 0
	int j = low;		// any values on the left of j is < pivotVal
	for (int i = low+1; i <= high; ++i) {
		if (A[i] < pivotVal) {
			j++;
			swap(A[i], A[j]);
		}
	}
	pivotPos = j;
	swap(A[low], A[pivotPos]);
}
int quickSortIterative(vector<int> &A, int N, const int k)
{
	int m = 0, j = N-1;	// partition with A[m...j]
	int pivotPos = 0;
	while (true) {
		partition(A, m, j, pivotPos);
		if (k == pivotPos) {
			//displayList(N, temp);
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
int quickSortRecursive(vector<int> &A, int low, int high, const int k)
{
	int m = low, j = high;
	int pivotPos;
	partition(A, m, j, pivotPos);
	int ans;
	if (k == pivotPos) {
		//displayList(N, temp);
		return A[k];
	}
	else if (k < pivotPos) {
		ans = quickSortRecursive(A, low, pivotPos - 1, k);
	}
	else {
		ans = quickSortRecursive(A, pivotPos + 1, high, k);
	}
	return ans;
}
void Select_kth_1(vector<int> const& A)
{
	int N = A.size();
	int k1 = 0, k2 = N / 4, k3 = N / 2, k4 = 3 * N / 4, k5 = N - 1;

	vector<int> temp(A.begin(), A.end());

	auto start = high_resolution_clock::now();
	mergeSort(temp, 0, temp.size() - 1);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(stop - start);

	cout << "Select-kth1 takes " << setw(4) << N << ": " << duration.count() << " nsec" << endl;
	cout << setw(6) << to_string(k1) + "th" << setw(6) << to_string(k2) + "th" << setw(6) << to_string(k3) + "th" << setw(6) << to_string(k4) + "th" << setw(6) << to_string(k5) + "th" << endl;
	cout << setw(6) << temp[k1] << setw(6) << temp[k2] << setw(6) << temp[k3] << setw(6) << temp[k4] << setw(6) << temp[k5] << endl;
}
void Select_kth_2(vector<int> const& A)
{
	int N = A.size();
	int k1 = 0, k2 = N / 4, k3 = N / 2, k4 = 3 * N / 4, k5 = N - 1;
	int kList[5] = { k1,k2,k3,k4,k5 };
	int result[5];
	int timePerPartition[5];
	vector<int> temp(A.begin(), A.end());
	cout << "\nSelect_kth_2 Result: " << endl;
	// repeat the partition 5 times for 5 Kth posiion
	for (int i = 0; i < 5; i++) {
		auto start = high_resolution_clock::now();
		result[i] = quickSortIterative(temp, N, kList[i]);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<nanoseconds>(stop - start);
		timePerPartition[i] = duration.count();
	}

	//printf("%-25s%-20s%-10s%-10s%-10s\n", "Name", "Title", "Gross", "Tax", "Net");
	cout << setw(10) << to_string(k1) + "th" << setw(10) << to_string(k2) + "th" << setw(10) << to_string(k3) + "th" << setw(10) << to_string(k4) + "th" << setw(10) << to_string(k5) + "th" << endl;
	cout << setw(10) << result[0] << setw(10) << result[1] << setw(10) << result[2] << setw(10) << result[3] << setw(10) << result[4] << endl;
	cout << setw(10) << timePerPartition[0] << setw(10) << timePerPartition[1] << setw(10) << timePerPartition[2] << setw(10) << timePerPartition[3] << setw(10) << timePerPartition[4] << endl;
}
void Select_kth_3(vector<int> const& A)
{
	int N = A.size();
	int k1 = 0, k2 = N / 4, k3 = N / 2, k4 = 3 * N / 4, k5 = N - 1;
	int kList[5] = { k1,k2,k3,k4,k5 };
	int result[5];
	int timePerPartition[5];
	vector<int> temp(A.begin(), A.end());
	cout << "\nSelect_kth_3 Result: " << endl;
	// repeat the partition 5 times for 5 Kth posiion
	for (int i = 0; i < 5; i++) {
		auto start = high_resolution_clock::now();
		result[i] = quickSortRecursive(temp, 0, N-1, kList[i]);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<nanoseconds>(stop - start);
		timePerPartition[i] = duration.count();
	}

	//printf("%-25s%-20s%-10s%-10s%-10s\n", "Name", "Title", "Gross", "Tax", "Net");
	cout << setw(10) << to_string(k1) + "th" << setw(10) << to_string(k2) + "th" << setw(10) << to_string(k3) + "th" << setw(10) << to_string(k4) + "th" << setw(10) << to_string(k5) + "th" << endl;
	cout << setw(10) << result[0] << setw(10) << result[1] << setw(10) << result[2] << setw(10) << result[3] << setw(10) << result[4] << endl;
	cout << setw(10) << timePerPartition[0] << setw(10) << timePerPartition[1] << setw(10) << timePerPartition[2] << setw(10) << timePerPartition[3] << setw(10) << timePerPartition[4] << endl;
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
	//for (int i = 0; i < 5; i++)
	//{
	//	int N = nList[i]; // assign the array size
	//	long long totalTime = 0; // totalTime after running with SET_AMOUNT times
	//	for (int i = 1; i <= SET_AMOUNT; ++i)
	//	{
	//		vector<int> a = generateList(N);
	//		totalTime += Select_kth_1(a);
	//	}
	//	long long averageTime = totalTime / SET_AMOUNT;
	//	//cout << "Total time after 1000 sets = " << totalTime << " nsec" << endl;
	//	cout << "For size " << N << ", average is: " << averageTime << " nsec" << endl;
	//}

	cout << "Size " << a.size() << ": " << endl;
	Select_kth_1(a);
	Select_kth_2(a);
	Select_kth_3(a);
	//Select_kth_4(a);

	cout << "Size " << b.size() << ": " << endl;
	Select_kth_1(b);
	Select_kth_2(b);
	Select_kth_3(b);
	//Select_kth_4(b);

	//cout << "Size " << c.size() << ": " << endl;
	//Select_kth_1(c);
	//Select_kth_2(c);
	//Select_kth_3(c);
	//Select_kth_4(c);

	//cout << "Size " << d.size() << ": " << endl;
	//Select_kth_1(d);
	//Select_kth_2(d);
	//Select_kth_3(d);
	//Select_kth_4(d);

	//cout << "Size " << e.size() << ": " << endl;
	//Select_kth_1(e);
	//Select_kth_2(e);
	//Select_kth_3(e);
	//Select_kth_4(e;

	return 0;
}