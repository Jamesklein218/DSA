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

};

#endif SORTING_H
