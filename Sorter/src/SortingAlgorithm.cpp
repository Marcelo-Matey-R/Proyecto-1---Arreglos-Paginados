#include "SortingAlgorithm.h"
#include <iostream>

#pragma region QUICK SORT
long long SortingAlgorithms::partition(PagedArray &arr, long long low, long long high) {
    long long pivot = arr[high];
    long long i = (low - 1);

    for (long long j = low; j < high; j++) {
        int32_t valJ = arr[j];
        if (valJ < pivot) {
            i++;
            int32_t temp = arr[i];
            arr[i] = valJ;
            arr[j] = temp;
        }
    }
    int32_t temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void SortingAlgorithms::quickSort(PagedArray &arr, long long low, long long high){
    // Base case: This part will be executed till the starting
    // index low is lesser than the ending index high
    if (low < high) {

        // pi is Partitioning Index, arr[p] is now at
        // right place
        long long pi = partition(arr, low, high);

        // Separately sort elements before and after the
        // Partition Index pi
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
#pragma endregion

#pragma region MERGE SORT
void SortingAlgorithms::merge(PagedArray &arr, long long left, long long mid, long long right){
    long long i, j, k;
    long long n1 = mid - left + 1;
    long long n2 = right - mid;

    // Create temporary vectors
    int32_t* leftArr = new int32_t[n1];
    int32_t* rightArr = new int32_t[n2];

    // Copy data to temporary vectors
    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    // Merge the temporary vectors back long longo arr[left..right]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftVec[], if any
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightVec[], if any
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
    delete[] leftArr;
    delete[] rightArr;
}

void SortingAlgorithms::mergeSort(PagedArray &arr, long long left, long long right){
    if (left < right) {
      
        // Calculate the midpoint
        long long mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}
#pragma endregion

#pragma region 3 WAY MERGE SORT
void SortingAlgorithms::merge2(PagedArray &arr, long long left, long long mid1, long long mid2, long long right){
    // Sizes of three subarrays
    long long size1 = mid1 - left + 1;
    long long size2 = mid2 - mid1;
    long long size3 = right - mid2;

    // Temporary arrays for three parts
    int32_t* leftArr = new int32_t[size1];
    int32_t* midArr = new int32_t[size2];
    int32_t* rightArr = new int32_t[size3];

    // Copy data to temporary arrays
    for (long long i = 0; i < size1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (long long i = 0; i < size2; i++) {
        midArr[i] = arr[mid1 + 1 + i];
    }
    for (long long i = 0; i < size3; i++) {
        rightArr[i] = arr[mid2 + 1 + i];
    }

    // Merge three sorted subarrays
    long long i = 0, j = 0, k = 0, index = left;
    while (i < size1 || j < size2 || k < size3) {
        long long minValue = INT_MAX, minIdx = -1;

        // Find the smallest among the three current elements
        if (i < size1 && leftArr[i] < minValue) {
            minValue = leftArr[i];
            minIdx = 0;
        }
        if (j < size2 && midArr[j] < minValue) {
            minValue = midArr[j];
            minIdx = 1;
        }
        if (k < size3 && rightArr[k] < minValue) {
            minValue = rightArr[k];
            minIdx = 2;
        }

        // Place the smallest element in the merged array
        if (minIdx == 0) {
            arr[index++] = leftArr[i++];
        } else if (minIdx == 1) {
            arr[index++] = midArr[j++];
        } else {
            arr[index++] = rightArr[k++];
        }
    }
    delete[] leftArr;
    delete[] midArr;
    delete[] rightArr;
}
void SortingAlgorithms::threeWayMergeSort(PagedArray &arr, long long left, long long right){
    // Base case: If single element, return
    if (left >= right) {
        return;
    }

    // Finding two midpoints for 3-way split
    long long mid1 = left + (right - left) / 3;
    long long mid2 = left + 2 * (right - left) / 3;

    // Recursively sort first third
    threeWayMergeSort(arr, left, mid1);

    // Recursively sort second third
    threeWayMergeSort(arr, mid1 + 1, mid2);

    // Recursively sort last third
    threeWayMergeSort(arr, mid2 + 1, right);

    // Merge the sorted parts
    merge2(arr, left, mid1, mid2, right);
}
#pragma endregion

#pragma region INSERTION SORT
void SortingAlgorithms::insertionSort(PagedArray &arr, long long n){
    for (long long i = 1; i < n; ++i) {
        long long key = arr[i];
        long long j = i - 1;

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        int32_t val = arr[j];
        while (j >= 0 && val > key) {
            arr[j + 1] = val;
            j = j - 1;
            if(j<0)break;
            val = arr[j];
        }
        arr[j + 1] = key;
    }
}
#pragma endregion

#pragma region SELECTION SORT
void SortingAlgorithms::selectionSort(PagedArray &arr){
    long long n = arr.GetTotalInts();

    for (long long i = 0; i < n - 1; ++i) {

        // Assume the current position holds
        // the minimum element
        long long min_idx = i;
        int32_t min_val = arr[min_idx];

        // Iterate through the unsorted portion
        // to find the actual minimum
        for (long long j = i + 1; j < n; ++j) {
            int32_t val_j = arr[j];
            if (val_j < min_val) {

                // Update min_idx if a smaller
                // element is found
                min_val = val_j;
                min_idx = j; 
            }
        }

        // Move minimum element to its
        // correct position
        if(min_idx != i){
            int32_t temp = arr[i];
            arr[i] = min_val;
            arr[min_idx] = temp;
        }
    }
}
#pragma endregion

void SortingAlgorithms::Sorted(Algo alg, PagedArray &arr){
    if(alg == Algo::INSERTIONSORT){
        insertionSort(arr, arr.GetTotalInts());
    }
    else if(alg == Algo::MERGESORT){
        mergeSort(arr, 0, arr.GetTotalInts()-1);
    }
    else if(alg == Algo::QUICKSORT){
        quickSort(arr, 0, arr.GetTotalInts()-1);
    }
    else if(alg == Algo::SELECTIONSORT){
        selectionSort(arr);
    }
    else{
        threeWayMergeSort(arr, 0, arr.GetTotalInts());
    }
}