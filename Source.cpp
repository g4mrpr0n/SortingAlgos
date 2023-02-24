#include <iostream>
#include <chrono>
#include <fstream>
using namespace std;
using namespace std::chrono;

ofstream outfile("in.txt", std::fstream::in | std::fstream::out | std::fstream::app);

void bubblesort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

void heapify(int arr[], int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}
void heapsort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) 
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int partition(int array[], int start, int end)
{
    int pivot = array[end];
    int i = start - 1;
    for (int j = start; j <= end; j++)
    {
        if (array[j] < pivot)
        {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    i++;
    int temp = array[i];
    array[i] = array[end];
    array[end] = temp;
    return i;
}
void quicksort(int array[], int start, int end)
{
    if (end <= start) return;
    int pivot = partition(array, start, end);
    quicksort(array, start, pivot - 1);
    quicksort(array, pivot + 1, end);
}

void merge(int leftArr[], int rightArr[], int arr[], int left, int right)
{
    int i = 0, j = 0, k = 0;
    int length = left + right;
    while (i < left && j < right)
    {
        if (leftArr[i] < rightArr[j])
        {
            arr[k] = leftArr[i];
            i++;
        }
        else
        {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    while (i < left)
    {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    while (j < right)
    {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}
void mergesort(int array[], int n)
{
    if (n <= 1)
    {
        return;
    }
    int middle = n / 2;
    int* leftarr = new int[middle];
    int* rightarr = new int[n - middle];
    int j = 0, k = 0;

    for (int i = 0; i < n; i++)
    {
        if (i < middle)
        {
            leftarr[j] = array[i];
            j++;
        }
        else
        {
            rightarr[k] = array[i];
            k++;
        }
    }
    mergesort(leftarr, middle);
    mergesort(rightarr, n - middle);
    merge(leftarr, rightarr, array, middle, n - middle);
    delete[] leftarr;
    delete[] rightarr;
}

void generateRandomArray(int n, int arr[], bool a)
{
    for (int i = 0; i < n; i++)
    {
        if (a)
        {
            int rng = rand() % 11;
            if (rng < 8 && i > 0)
            {
                arr[i] = rand() % INT_MAX;
                arr[i - 1] = arr[i];
            }
        }
        else {
            arr[i] = rand() % INT_MAX;
        }
    }
}
void generateSortedArray(int n, int arr[])
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = i;
    }
}
void generateReverseSortedArray(int n, int arr[])
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = n - 1 - i;
    }
}
void generatePartiallySortedArray(int n, int arr[])
{
    for (int i = 0; i < n; i++)
    {
        if (i < n / 2)
        {
            arr[i] = i;
        }
        else {
            arr[i] = rand() % INT_MAX;
        }
    }
}
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << "\n\n\n";
}

void outputMetrics(char f, int arr[], int n)
{
    string s;
    auto sort_start = high_resolution_clock::now();
    switch (f) 
    {
    case 'b':
        bubblesort(arr, n);
        s = "Bubble sort";
        break;
    case 'm':
        mergesort(arr, n);
        s = "Merge sort";
        break;
    case 'h':
        heapsort(arr, n);
        s = "Heap sort";
        break;
    case 'q':
        quicksort(arr, 0, n - 1);
        s = "Quick sort";
        break;
    }
    auto sort_stop = high_resolution_clock::now();
    auto duration_sort = duration_cast<milliseconds>(sort_stop - sort_start);
    outfile << "\t" << duration_sort.count() / 1e3f;
}

int main()
{
    srand(time(NULL));
    //int n = 3577; //fucking quicksort
    int n = 40000;

    int* arr = (int*)malloc(sizeof(int) * n); 
    int* arr1 = (int*)malloc(sizeof(int) * n);
    //int* arr2 = (int*)malloc(sizeof(int) * n);
    //int* arr3 = (int*)malloc(sizeof(int) * n);
    int* arr4 = (int*)malloc(sizeof(int) * n);
    outfile << n;

    //outfile << "Random Array\n";
    generateRandomArray(n, arr, 0);
    //generateRandomArray(n, arr1, 0);
    //generateRandomArray(n, arr2, 0);
    //generateRandomArray(n, arr3, 0);
    //generateRandomArray(n, arr4, 0);

    //outfile << "\nRandom Array with Duplicates\n";
    //generateRandomArray(n, arr, 1);
    generateRandomArray(n, arr1, 1);
    //generateRandomArray(n, arr2, 1);
    //generateRandomArray(n, arr3, 1);
    //generateRandomArray(n, arr4, 1);
    
    //outfile << "\nSorted Array\n";
    //generateSortedArray(n, arr);
    //generateSortedArray(n, arr1);
    //generateSortedArray(n, arr2);
    //generateSortedArray(n, arr3);
    //generateSortedArray(n, arr4);
    
    //outfile << "\nReverse Array\n";
    //generateReverseSortedArray(n, arr);
    //generateReverseSortedArray(n, arr1);
    //generateReverseSortedArray(n, arr2);
    //generateReverseSortedArray(n, arr3);
    //generateReverseSortedArray(n, arr4);
    
    //outfile << "\nPartially Sorted Array\n";
    //generatePartiallySortedArray(n, arr);
    //generatePartiallySortedArray(n, arr1);
    //generatePartiallySortedArray(n, arr2);
    //generatePartiallySortedArray(n, arr3);
    generatePartiallySortedArray(n, arr4);
    

    //mergesort(arr, n);
    //quicksort(arr1, 0, n-1);
    //heapsort(arr2, n);
    //bubblesort(arr3, n);
    //printArray(arr, n);
    //printArray(arr1, n);
    //printArray(arr2, n);
    //printArray(arr3, n);    
    //outputMetrics('b', arr, n);
    //outputMetrics('m', arr, n);
    //outputMetrics('h', arr, n);
    outputMetrics('q', arr, n);
    outputMetrics('q', arr1, n);
    //outputMetrics('q', arr2, n);
    //outputMetrics('q', arr3, n);
    outputMetrics('q', arr4, n);
    outfile << "\n";
    delete[]arr;
    delete[]arr1;
    //delete[]arr2;
    //delete[]arr3;
    delete[]arr4;
}