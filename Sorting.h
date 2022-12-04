//
// Created by Khoa on 08/11/2022.
//
#ifndef SORTING_H
#define SORTING_H
#include <iostream>

using namespace std;
template <class T>
class Sorting {
public:
    /* Function to print an array */
    static void printArray(T *start, T *end)
    {
        long size = end - start; // or can be end - start + 1
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }

    static void merge(T* left, T* middle, T* right){
        T *tmp = new T[right - left], *pTmp = tmp;
        T *pL = left, *pR = middle;
        while (pL < middle && pR <= right) {
            *(pTmp++) = *pL < *pR ? *(pL++) : *(pR++);
        }

        while (pL < middle) *(pTmp++) = *(pL++);
        while (pR <= right) *(pTmp++) = *(pR++);

        pL = left, pR = right;
        for (;pL <= pR; pL++, tmp++) {
            *pL = *tmp;
        }

        Sorting::printArray(left, right);
    }
    static void mergeSort(T* start, T* end) {
        if (start == end) return;
        long N = end - start;

        mergeSort(start, start + N / 2);
        mergeSort(start + N / 2 + 1, end);
        merge(start, start + N / 2 + 1 ,end);
    }

    static void oddEvenSort(T *start, T *end);
    static void selectionSort(T *start, T *end);

    static void heapDown(T* arr, int N, int index) {
        int leftIdx = (index << 1) + 1;
        while (leftIdx >= 0 && leftIdx < N) {
            if (leftIdx + 1 < N && arr[leftIdx + 1] > arr[leftIdx])
                leftIdx++;
            if (arr[leftIdx] < arr[index]) return;

            swap(arr[index], arr[leftIdx]);

            index = leftIdx;
            leftIdx = (index << 1) + 1;
        }
    }

    static void heapSort(T* start, T* end){
        int N = end - start;
        T* arr = start;

        // Build the heap
        for (int i = N/2 - 1; i >= 0; i--)
            heapDown(arr, N, i);

        // Swap and rebuild heap
        for (N--; N; N--) {
            swap(arr[0], arr[N]);
            heapDown(arr, N, 0);
        }

        Sorting<T>::printArray(start,end);
    }
};

#endif SORTING_H
