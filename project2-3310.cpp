/*
Name: Tran Nguyen
File: project2-3310.cpp
Description:
*/

#include <iostream>
#include <fstream>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
using namespace std::chrono;

// Swap vector with an empty vector to deallocate it.
void free_vector(vector<int> &list)
{
    vector<int>().swap(list);
}
// Initialize vector to the exact size
void initialize_vector(vector<int> &list, int size)
{
    list.resize(size, 0);
}
// Print the vector for testing purpose
void print(vector<int> &list)
{
    cout << "List[" << list.size() << "]: ";
    for (int i = 0; i < list.size(); i++)
    {
        cout << list[i] << ", ";
    }
    cout << endl;
}

// Generate and populate the list with -max <= x <= max
void randomize(vector<int> &list, int max)
{

    for (int i = 0; i < list.size(); i++)
    {
        list[i] = (rand() % (max * 2 + 1)) - max;
    }
}

// Select_kth_1 :  Merge Sort O(nlogn)--------------------------------------

void merge(vector<int> &A, int low, int mid, int high)
{
    int i = low;
    int j = mid + 1;
    int k = low;
    vector<int> U(A);
    while (i <= mid && j <= high)
    {
        if (A[i] < A[j])
        {
            U[k] = A[i];
            i++;
        }
        else
        {
            U[k] = A[j];
            j++;
        }
        k++;
    }
    if (i > mid)
    {
        for (int index = j; index <= high; index++)
        {
            U[k] = A[index];
            k++;
        }
    }
    else
    {
        for (int index = i; index <= mid; index++)
        {
            U[k] = A[index];
            k++;
        }
    }
    for (int p = low; p <= high; p++)
    {
        A[p] = U[p];
    }
}
void mergeSort(vector<int> &A, int low, int high)
{
    if (low < high)
    {
        int mid = floor((low + high) / 2);

        mergeSort(A, low, mid);
        mergeSort(A, mid + 1, high);
        merge(A, low, mid, high);
    }
}

int Select_kth_1(vector<int> &A, int low, int high, int k)
{
    mergeSort(A, low, high);
    return A[k];
}

// Select_kth_2: Quicksort (Iterative)--------------------------------------------------------
void partition(vector<int> &A, int low, int high, int &pivot)
{

    int v = A[low];
    // pivot = v;
    int j = low;
    for (int i = low + 1; i <= high; i++)
    {
        if (A[i] < v)
        {
            j++;
            swap(A[i], A[j]);
        }
    }
    pivot = j;
    swap(A[low], A[pivot]);
}

int Select_kth_2(vector<int> &A, int n, int k)
{
    int m = 0;
    int j = n;
    int pivot = k;
    while (1)
    {
        partition(A, m, j, pivot);
        if (k == pivot)
        {
            return A[k];
        }
        else if (k < pivot)
        {
            j = pivot - 1;
        }
        else
        {
            m = pivot + 1;
        }
    }
}
// Select_kth_3: Quicksort (Recursive)--------------------------------------------------------

int Select_kth_3(vector<int> &A, int low, int high, int k)
{
    int m = low;
    int j = high;
    int pivot = k;

    partition(A, m, j, pivot);
    if (k == pivot)
    {
        return A[k];
    }
    else if (k < pivot)
    {
        return Select_kth_3(A, low, pivot - 1, k);
    }
    else
    {
        return Select_kth_3(A, pivot + 1, high, k);
    }
}
// Select_kth_4: MM --------------------------------------------------------

int partition2(vector<int> &arr, int l, int r, int k);
int findMedian(vector<int> &arr, int index, int n)
{
    sort(arr.begin() + index, arr.begin() + index + n); // Sort the array
    return arr[index + (n / 2)];                        // Return middle element
}

int kthSmallest(vector<int> &arr, int l, int r, int k)
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

int partition2(vector<int> &arr, int l, int r, int x)
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

int main()
{
    // Output files
    ofstream fp1("select-kth-1.csv");
    ofstream fp2("select-kth-2.csv");
    ofstream fp3("select-kth-3.csv");
    ofstream fp4("select-kth-4.csv");

    int size = 4;                                // total numbers of n
    const int Iteration = 1;                     // Total iteration per set
    const int TOTAL_SETS = 1;                    // Total number of data sets
    int max_rand = 500;                          // Value to generate random number -MAX_RAND <= x <= MAX_RAND
    double k_value[5] = {0, 0.25, 0.5, 0.75, 1}; // K = 1, n/4, 3n/4, n
    int n = 0;
    int k;
    int result1, result2, result3, result4;
    int base_number = 10; // n value;

    long long average_set_1 = 0;
    long long average_set_2 = 0;
    long long average_set_3 = 0;
    long long average_set_4 = 0;

    long long average_time_2 = 0; // Capture avergage time in ms of each data set
    long long average_time_1 = 0;
    long long average_time_3 = 0;
    long long average_time_4 = 0;

    long long average_iteration_1 = 0;
    long long average_iteration_2 = 0;
    long long average_iteration_3 = 0;
    long long average_iteration_4 = 0;

    long long average_k[] = {0, 0, 0, 0, 0};

    srand(time(NULL)); // Seed for random generation

    // auto low = high_resolution_clock::now();
    // auto high = high_resolution_clock::now();
    // auto duration = duration_cast<nanoseconds>(high - low);
    // average_set_1 += duration.count(); // Add this iteration run time to the total

    vector<int> list;
    vector<int> list_copy;

    auto begin = high_resolution_clock::now();
    for (int i = 0; i < size; i++) // n
    {
        n = (i % 2 == 0) ? base_number : base_number * 5;
        if (i % 2 == 0)
        {
            n = base_number;
        }
        else
        {
            n = base_number * 5;
            base_number *= 10;
        }
        initialize_vector(list, n);
        average_time_1 = 0;
        average_time_2 = 0;
        average_time_3 = 0;
        average_time_4 = 0;

        for (int set = 0; set < TOTAL_SETS; set++) // sets
        {
            randomize(list, max_rand);
            // average_set_1 = 0;

            // for(int j = 0; j < 5; j++){
            average_iteration_1 = 0;
            average_iteration_2 = 0;
            average_iteration_3 = 0;
            average_iteration_4 = 0;

            for (int iter = 0; iter < Iteration; iter++) // iteration
            {
                // list_copy = list;
                // QS(list_copy, 0, list_copy.size() - 1, 2);
                k = (int)floor(k_value[0] * (n - 1));

                list_copy = list;
                auto start = high_resolution_clock::now();
                result1 = Select_kth_1(list_copy, 0, list_copy.size() - 1, k);
                // print(list_copy);
                auto end = high_resolution_clock::now();
                auto duration = duration_cast<nanoseconds>(end - start);
                average_iteration_1 += duration.count();

                cout << "Select kth-1[" << k << "]:" << result1 << endl;

                list_copy = list;
                auto start_2 = high_resolution_clock::now();
                result2 = Select_kth_2(list_copy, list_copy.size() - 1, k);
                auto end_2 = high_resolution_clock::now();
                auto duration_2 = duration_cast<nanoseconds>(end_2 - start_2);
                average_iteration_2 += duration_2.count();
                cout << "Select kth-2[" << k << "]:" << result2 << endl;

                list_copy = list;
                auto start_3 = high_resolution_clock::now();
                result3 = Select_kth_3(list_copy, 0, list_copy.size() - 1, k);
                auto end_3 = high_resolution_clock::now();
                auto duration_3 = duration_cast<nanoseconds>(end_3 - start_3);
                average_iteration_3 += duration_3.count();
                cout << "Select kth-3[" << k << "]:" << result3 << endl;

                list_copy = list;
                // print(list_copy);
                auto start_4 = high_resolution_clock::now();
                result4 = kthSmallest(list_copy, 0, list_copy.size() - 1, k + 1);
                auto end_4 = high_resolution_clock::now();
                auto duration_4 = duration_cast<nanoseconds>(end_4 - start_4);
                average_iteration_4 += duration_4.count();
                // print(list_copy);
                cout << "Select kth-4[" << k << "]:" << result4 << endl <<endl;
            }
            average_set_1 += average_iteration_1 / Iteration;
            average_set_2 += average_iteration_2 / Iteration;
            average_set_3 += average_iteration_3 / Iteration; // average of iteration is added to set;
            average_set_4 += average_iteration_4 / Iteration;

            // }
            // average_time_1 += average_set_1 / 5;
        }
        // print(list);
        average_time_1 = average_set_1 / TOTAL_SETS;
        average_time_2 = average_set_2 / TOTAL_SETS;
        average_time_3 = average_set_3 / TOTAL_SETS;
        average_time_4 = average_set_4 / TOTAL_SETS;

        fp1 << n << "," << average_time_1 / (1000000.0) << "\n";
        fp2 << n << "," << average_time_2 / (1000000.0) << "\n";
        fp3 << n << "," << average_time_3 / (1000000.0) << "\n";
        fp4 << n << "," << average_time_4 / (1000000.0) << "\n";
    }

    auto finish = high_resolution_clock::now();
    auto total_time = duration_cast<seconds>(finish - begin);
    cout << "Total time of the program: " << (long)total_time.count() << endl;

    fp1.close();
    fp2.close();
    fp3.close();
    fp4.close();

    return 0;
}