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