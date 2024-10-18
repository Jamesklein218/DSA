//
// Created by Khoa on 08/11/2022.
//
#ifndef SORTING_H
#define SORTING_H
#include <iostream>

using namespace std;
template <class T> class Sorting {
public:
  /* Function to print an array */
  static void printArray(T *start, T *end) {
    long size = end - start; // or can be end - start + 1
    for (int i = 0; i < size - 1; i++)
      cout << start[i] << ", ";
    cout << start[size - 1];
    cout << endl;
  }

  /*
   * Merging Two Array
   *
   * Time Complexity: O(N)
   * Algorithm: Using two pointers on two array, add the larger pointer's
   * value and append its pointer
   */
  static void merge(T *left, T *middle, T *right) {
    T *tmp = new T[right - left], *pTmp = tmp;
    T *pL = left, *pR = middle;
    while (pL < middle && pR <= right) {
      *(pTmp++) = *pL < *pR ? *(pL++) : *(pR++);
    }

    while (pL < middle)
      *(pTmp++) = *(pL++);
    while (pR <= right)
      *(pTmp++) = *(pR++);

    pL = left, pR = right;
    for (; pL <= pR; pL++, tmp++) {
      *pL = *tmp;
    }

    Sorting::printArray(left, right);
  }

  /*
   * Merge Sort
   *
   * Time Complexity: O(N logN) worst case, O(N logN) average, O(N logN) best
   * Algorithm: Merge sort uses the programming paradigm called Divide and
   * Conquer. The algorithm consist of two steps:
   *      1.  Splitting O(1): Split the array into two halves.
   *          And recursively call sorting on them
   *      2.  Merging O(N): Assume that the two halves has been sorted, merge
   *          together to have a sorted array.
   */
  static void mergeSort(T *start, T *end) {
    if (start == end)
      return;
    long N = end - start;

    mergeSort(start, start + N / 2);
    mergeSort(start + N / 2 + 1, end);
    merge(start, start + N / 2 + 1, end);
  }

  static void oddEvenSort(T *start, T *end);

  /*
   * Selection Sort
   *
   * Time Complexity: O(N^2), faster than Bubble Sort
   * Algorithm: Sort by selecting the smallest value among the right list
   * swap that value with the current index.
   */
  static void selectionSort(T *start, T *end);

  /*
   * Insertion Sort
   *
   * Time Complexity: O(N^2), faster than Selection Sort
   * Algorithm: Sort by assumming the left array (0 elements) has been sorted.
   * Inserting the left-most elements from the right array to the left array.
   */
  static void insertionSort(T *arr, T *end);

  /*
   * Heapify down
   *
   * Time complexity: O(logN)
   * Algorithm: Explained in Heap data structure
   */
  static void heapDown(T *arr, int N, int index) {
    int leftIdx = (index << 1) + 1;
    while (leftIdx >= 0 && leftIdx < N) {
      if (leftIdx + 1 < N && arr[leftIdx + 1] > arr[leftIdx])
        leftIdx++;
      if (arr[leftIdx] < arr[index])
        return;

      swap(arr[index], arr[leftIdx]);

      index = leftIdx;
      leftIdx = (index << 1) + 1;
    }
  }

  /*
   * Heap Sort
   *
   * Time Complexity: O(N logN) -> unstable
   * Algorithm: Put it all in the heap take back one-by-one
   */
  static void heapSort(T *start, T *end) {
    int N = end - start;
    T *arr = start;

    // Build the heap
    for (int i = N / 2 - 1; i >= 0; i--)
      heapDown(arr, N, i);

    // Swap and rebuild heap
    for (N--; N; N--) {
      swap(arr[0], arr[N]);
      heapDown(arr, N, 0);
    }

    Sorting<T>::printArray(start, end);
  }

  /*
   * Quick Sort
   *
   * Time Complexity: O(N logN), O(N^2) worst -> Depending on the pivot choice
   * Algorithm: The steps are similar to Merge Sort, however the idea
   * and time complexity is different. The steps are:
   *      1.  Splitting O(N): Choose a pivot and put it in the right position.
   *          This position will be the final position of that element. We
   * achieve that by making sure every element on the right is smaller than that
   * element, and every element on the left is larger than that element. Then
   * the array is splited into two parts, recursively call quick sort on those
   * two array.
   *      2.  Merging O(1): Do Nothing
   */
  static void quickSort(T *start, T *end) {
    int N = end - start;
    if (N < 2)
      return;
    T *pivot = start + N / 2;
    T *left = start, *right = start + N - 1;
    while (left < right) {
      while (*left < *pivot)
        left++;
      while (*right >= *pivot)
        right--;
      if (left < right) {
        swap(*left, *right);
        left++, right--;
      }
    }
    if (left != pivot)
      swap(*left, *pivot);
    quickSort(start, left);
    quickSort(left + 1, end);
  }
};

#endif SORTING_H
