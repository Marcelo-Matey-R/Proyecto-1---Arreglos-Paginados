#include "PagedArray.h"
#include "common\EnumSorts.h"

#ifndef SORTING_ALGORITHMS_H
#define SORTIN_ALGORITHMS_H

class SortingAlgorithms{
    private:
    static long long partition(PagedArray &arr, long long low, long long high);
    static void merge(PagedArray &arr, long long left, long long mid, long long right);
    static void merge2(PagedArray &arr, long long left, long long mid1, long long mid2, long long right);
    static void quickSort(PagedArray &arr, long long low, long long high);
    static void mergeSort(PagedArray &arr, long long left, long long right);
    static void insertionSort(PagedArray &arr, long long n);
    static void selectionSort(PagedArray &arr);
    static void threeWayMergeSort(PagedArray &arr, long long left, long long right);
    public:
    static void Sorted(Algo alg, PagedArray &arr);
};

#endif