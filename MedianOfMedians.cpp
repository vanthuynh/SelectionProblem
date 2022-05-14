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
#include <algorithm>

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

const int TEST_TRIAL = 1;
const int SET_AMOUNT = 1;
const int LARGEST_ARRAY_SIZE = 10000;

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
long double Select_kth_1(vector<int> const& A);
long double  Select_kth_2(vector<int> const& A, int& k);
long double  Select_kth_3(vector<int> const& A, int& k);
long double Select_kth_4(vector<int> const& A, int& k);

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
long double  Select_kth_1(vector<int> const& A)
{
	int N = A.size();						// size of the array
	vector<int> temp(A.begin(), A.end());	// copy an the array to run

	auto start = high_resolution_clock::now();
	mergeSort(temp, 0, temp.size() - 1);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(stop - start);

	/*cout << "Select-kth1 takes " << setw(4) << N << ": " << duration.count() << " nsec" << endl;
	cout << setw(6) << to_string(k1) + "th" << setw(6) << to_string(k2) + "th" << setw(6) << to_string(k3) + "th" << setw(6) << to_string(k4) + "th" << setw(6) << to_string(k5) + "th" << endl;
	cout << setw(6) << temp[k1] << setw(6) << temp[k2] << setw(6) << temp[k3] << setw(6) << temp[k4] << setw(6) << temp[k5] << endl;*/
	return duration.count();
}
long double  Select_kth_2(vector<int> const& A, int& k)
{
	int N = A.size();						// size of the array
	vector<int> temp(A.begin(), A.end());	// copy an the array to run
	long double timePerPartition;
	auto start = high_resolution_clock::now();
	int ans = quickSortIterative(temp, N, k);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(stop - start);
	timePerPartition = duration.count();

	/*cout << setw(10) << to_string(k1) + "th" << setw(10) << to_string(k2) + "th" << setw(10) << to_string(k3) + "th" << setw(10) << to_string(k4) + "th" << setw(10) << to_string(k5) + "th" << endl;
	cout << setw(10) << result[0] << setw(10) << result[1] << setw(10) << result[2] << setw(10) << result[3] << setw(10) << result[4] << endl;
	cout << setw(10) << timePerPartition[0] << setw(10) << timePerPartition[1] << setw(10) << timePerPartition[2] << setw(10) << timePerPartition[3] << setw(10) << timePerPartition[4] << endl;*/
	return timePerPartition;

}
long double  Select_kth_3(vector<int> const& A, int& k)
{
	int N = A.size();						// size of the array
	vector<int> temp(A.begin(), A.end());	// copy an the array to run
	long double timePerPartition;
	auto start = high_resolution_clock::now();
	int ans = quickSortRecursive(temp, 0, N-1, k);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(stop - start);
	timePerPartition = duration.count();

	/*cout << setw(10) << to_string(k1) + "th" << setw(10) << to_string(k2) + "th" << setw(10) << to_string(k3) + "th" << setw(10) << to_string(k4) + "th" << setw(10) << to_string(k5) + "th" << endl;
	cout << setw(10) << result[0] << setw(10) << result[1] << setw(10) << result[2] << setw(10) << result[3] << setw(10) << result[4] << endl;
	cout << setw(10) << timePerPartition[0] << setw(10) << timePerPartition[1] << setw(10) << timePerPartition[2] << setw(10) << timePerPartition[3] << setw(10) << timePerPartition[4] << endl;*/
	return timePerPartition;

}
//long double  Select_kth_4(vector<int> const& A)
//{
//	long double  result;
//
//	return result;
//}

int partition2(vector<int>& arr, int l, int r, int k);
int findMedian(vector<int>& arr, int index, int n)
{
	sort(arr.begin() + index, arr.begin() + index + n); // Sort the array
	return arr[index + (n / 2)];                        // Return middle element
}

int kthSmallest(vector<int>& arr, int l, int r, int k)
{

	if (k > 0 && k <= r - l + 1)
	{
		int n = r - l + 1;
		int i;
		vector<int> median((n + 4) / 5, 0);
		for (i = 0; i < n / 5; i++)
		{
			median[i] = findMedian(arr, l + i * 5, 5);
		}

		if (i * 5 < n)
		{
			median[i] = findMedian(arr, l + i * 5, n % 5);
			i++;
		}
		int medOfMed = (i == 1) ? median[i - 1] : kthSmallest(median, 0, i - 1, i / 2);

		int pos = partition2(arr, l, r, medOfMed);

		if (pos - l == k - 1)
			return arr[pos];
		if (pos - l > k - 1)
			return kthSmallest(arr, l, pos - 1, k);

		return kthSmallest(arr, pos + 1, r, k - pos + l - 1);
	}

	return INT_MAX;
}

int partition2(vector<int>& arr, int l, int r, int x)
{

	int i;
	for (i = l; i < r; i++)
		if (arr[i] == x)
			break;
	swap(arr[i], arr[r]);

	i = l;
	for (int j = l; j <= r - 1; j++)
	{
		if (arr[j] <= x)
		{
			swap(arr[i], arr[j]);
			i++;
		}
	}
	swap(arr[i], arr[r]);
	return i;
}

// MAIN
int main(void)
{
	long double result[5];

	int nList[7] = { 10, 50, 100, 500, 1000, 5000, 10000 };
	long double res1=0;
	long double res2=0;
	long double res3=0;
	long double res4=0;
	for (int i = 0; i < 7; i++)
	{
		int N = nList[i];									// assign the array size N
		int kList[5] = { 0, N / 4, N / 2, 3 * N / 4,N };	// calculate Kth positions after having size N
		long double  averageTime1=0;							// averageTime for array size N
		long double  averageTime2=0;
		long double  averageTime3=0;
		long double  averageTime4=0;
		for (int j = 1; j <= SET_AMOUNT; ++j)				// for every Data Set, we test with 5 different kth values
		{
			vector<int> a = generateList(N);
			long double  totalTime1 = 0;					// totalTime after running with SET_AMOUNT times
			long double  totalTime2 = 0;
			long double  totalTime3 = 0;
			long double  totalTime4 = 0;
			for (int k = 0; k < 5; k++)							// for every pivot position we run 20 test trials
			{
				long double  timePerPivot1 = 0;
				long double  timePerPivot2 = 0;
				long double  timePerPivot3 = 0;
				long double  timePerPivot4 = 0;
				for (int t = 1; t <= TEST_TRIAL; ++t)
				{
					timePerPivot1 += Select_kth_1(a) / 1000000;
					//timePerPivot2 += Select_kth_2(a, kList[k]) / 1000000;
					//timePerPivot3 += Select_kth_3(a, kList[k]) / 1000000;
					//timePerPivot4 += Select_kth_4(a, kList[k]);
				}
				totalTime1 += timePerPivot1 / TEST_TRIAL;
				totalTime2 += timePerPivot2 / TEST_TRIAL;
				totalTime3 += timePerPivot3 / TEST_TRIAL;
				totalTime4 += timePerPivot4 / TEST_TRIAL;
			}
			averageTime1 += totalTime1 / 5;
			averageTime2 += totalTime2 / 5;
			averageTime3 += totalTime3 / 5;
			averageTime4 += totalTime4 / 5;
		}

		//cout << "Total time after 1000 sets = " << totalTime << " nsec" << endl;
		cout << "For size " << N << ", K1 average is: " << averageTime1 / SET_AMOUNT << " msec" << endl;
		cout << "For size " << N << ", K2 average is: " << averageTime2 / SET_AMOUNT << " msec" << endl;
		cout << "For size " << N << ", K3 average is: " << averageTime3 / SET_AMOUNT << " msec" << endl;
		cout << "For size " << N << ", K4 average is: " << averageTime4 / SET_AMOUNT << " msec" << endl;
	}


	/* Below code is to test individually */
	//vector<int> a = generateList(10);
	//vector<int> b = generateList(50);
	//vector<int> c = generateList(100);
	//vector<int> d = generateList(500);
	//vector<int> e = generateList(1000);
	//cout << "Size " << a.size() << ": " << endl;
	//Select_kth_1(a);
	//Select_kth_2(a);
	//Select_kth_3(a);
	//Select_kth_4(a);


	//cout << "Size " << b.size() << ": " << endl;
	//Select_kth_1(b);
	//Select_kth_2(b);
	//Select_kth_3(b);
	//Select_kth_4(b);




	//cout << "Median of Medians: " << kthSmallest(a, 0, 10 - 1, K1+1) << endl;
	//cout << "Median of Medians: " << kthSmallest(a, 0, 10 - 1, K2 * 10 + 1)<< endl;
	//cout << "Median of Medians: " << kthSmallest(a, 0, 10 - 1, K3 * 10 + 1)<< endl;
	//cout << "Median of Medians: " << kthSmallest(a, 0, 10 - 1, K4 * 10 + 1)<< endl;
	//cout << "Median of Medians: " << kthSmallest(a, 0, 10 - 1, K5 * 10) << endl;





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