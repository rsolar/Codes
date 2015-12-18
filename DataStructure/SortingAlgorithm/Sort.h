//Sort.h
#ifndef SORT_H
#define SORT_H

#include <cstdlib>
#include <algorithm>

const int INSERTION_BOUND = 10; //ʹ��ֱ�Ӳ�������ı߽�

//������������
template<typename T> inline void Swap(T &a, T &b) {
  T t = a; a = b; b = t;
}

//��ѡ������ O(n^2)
template<typename T> void selectionSort(T a[], const int n) {
  for (int i = 0; i < n - 1; i++) { //n - 1��
    int mn = i; //iָ�������������ʼԪ�ص�λ��
    for (int j = i + 1; j < n; j++) {
      if (a[j] < a[mn]) { mn = j; } //ѡ��СԪ
    }
    Swap(a[i], a[mn]); //��������Ԫ��
  }
}

//ֱ�Ӳ������� O(n^2)
template<typename T> void insertionSort(T a[], const int n) {
  for (int i = 1, j; i < n; i++) { //i���ڿ��ƴ�����������ʼԪ�ص�λ��
    T tmp = a[i];
    for (j = i - 1; j >= 0 && a[j] > tmp; j--) { a[j + 1] = a[j]; } //��Ԫ�غ���
    a[j + 1] = tmp;
  }
}

//ð������ O(n^2)
template<typename T> void bubbleSort(T a[], const int n) {
  for (int i = n - 1, j, last; i > 0; i = last) {
    for (j = last = 0; j < i; j++) {
      if (a[j] > a[j + 1]) { Swap(a[j], a[j + 1]); last = j; }
    }
  }
}

//�ݹ��������� O(nlogn)
template<typename T> void quickSortRecursive(T a[], const int n) {
  quickSortRecursive(a, 0, n - 1);
}

template<typename T> void quickSortRecursive(T a[], const int left, const int right) {
  if (left >= right) { return; }
  int l = left, r = right; T key = a[left];
  while (l < r) {
    while (l < r && a[r] >= key) { r--; }
    a[l] = a[r];
    while (l < r && a[l] <= key) { l++; }
    a[r] = a[l];
  }
  a[l] = key;
  quickSortRecursive(a, left, l - 1); //��������п������
  quickSortRecursive(a, l + 1, right); //���Ҳ����п������
}

//�Ľ��ĵݹ��������� O(nlogn)
template<typename T> void GQuickSortRecursive(T a[], const int n) {
  GQuickSortRecursive(a, 0, n - 1);
}

template<typename T> void GQuickSortRecursive(T a[], const int left, const int right) {
  if (left >= right) { return; }
  if (right - left + 1 >= INSERTION_BOUND) { //�Ӽ���Ԫ����С��ĳ��ֵʱ����ֱ�Ӳ�������
    int l = left, r = right; T key = a[left];
    while (l < r) {
      while (l < r && a[r] >= key) { r--; }
      a[l] = a[r];
      while (l < r && a[l] <= key) { l++; }
      a[r] = a[l];
    }
    a[l] = key;
    GQuickSortRecursive(a, left, l - 1); //��������п������
    GQuickSortRecursive(a, l + 1, right); //���Ҳ����п������
  } else {
    insertionSort(a + left, right - left + 1);
  }
}

//�ǵݹ��������� O(nlogn)
struct Range {
  int left, right;
  Range(int l = 0, int r = 0) :left(l), right(r) {}
};

template<typename T> void quickSortIterative(T a[], const int n) {
  if (n <= 1) { return; }
  Range *S = new Range[n];
  int top = 0;
  S[top++] = Range(0, n - 1);
  while (top > 0) {
    Range cur = S[--top];
    if (cur.left >= cur.right) { continue; }
    int l = cur.left, r = cur.right; T key = a[cur.left];
    while (l < r) {
      while (l < r && a[r] >= key) { r--; }
      a[l] = a[r];
      while (l < r && a[l] <= key) { l++; }
      a[r] = a[l];
    }
    a[l] = key;
    S[top++] = Range(cur.left, l - 1);
    S[top++] = Range(l + 1, cur.right);
  }
  delete[] S;
}

//�ݹ����·�鲢���� O(nlogn)
template<typename T> void mergeSortRecursive(T a[], const int n) {
  T *tmp = new T[n];
  mergeSortRecursive(a, tmp, 0, n - 1);
  delete[] tmp;
}

template<typename T> void mergeSortRecursive(T a[], T tmp[], const int left, const int right) {
  if (left >= right) { return; }
  int mid = (left + right) >> 1;
  mergeSortRecursive(a, tmp, left, mid);
  mergeSortRecursive(a, tmp, mid + 1, right);
  int i = left, j = mid + 1, k = left;
  while (i <= mid && j <= right) { tmp[k++] = (a[i] < a[j] ? a[i++] : a[j++]); }
  while (i <= mid) { tmp[k++] = a[i++]; }
  while (j <= right) { tmp[k++] = a[j++]; }
  for (k = left; k <= right; k++) { a[k] = tmp[k]; }
}

//�Ľ��ĵݹ����·�鲢���� O(nlogn)
template<typename T> void GMergeSortRecursive(T a[], const int n) {
  T *tmp = new T[n];
  GMergeSortRecursive(a, tmp, 0, n - 1);
  delete[] tmp;
}

template<typename T> void GMergeSortRecursive(T a[], T tmp[], const int left, const int right) {
  if (left >= right) { return; }
  if (right - left + 1 >= INSERTION_BOUND) { //�Ӽ���Ԫ����С��ĳ��ֵʱ����ֱ�Ӳ�������
    int mid = (left + right) >> 1;
    GMergeSortRecursive(a, tmp, left, mid);
    GMergeSortRecursive(a, tmp, mid + 1, right);
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) { tmp[k++] = (a[i] < a[j] ? a[i++] : a[j++]); }
    while (i <= mid) { tmp[k++] = a[i++]; }
    while (j <= right) { tmp[k++] = a[j++]; }
    for (k = left; k <= right; k++) { a[k] = tmp[k]; }
  } else {
    insertionSort(a + left, right - left + 1);
  }
}

//�ǵݹ����·�鲢���� O(nlogn)
template<typename T> void mergeSortIterative(T a[], const int n) {
  T *arr = a, *tmp = new T[n];
  for (int size = 1; size < n; size <<= 1) {
    for (int left = 0; left < n; left += size + size) {
      int mid = left + size < n ? left + size : n, right = left + size + size < n ? left + size + size : n;
      int i = left, j = mid, k = left;
      while (i < mid && j < right) { tmp[k++] = (arr[i] < arr[j] ? arr[i++] : arr[j++]); }
      while (i < mid) { tmp[k++] = arr[i++]; }
      while (j < right) { tmp[k++] = arr[j++]; }
    }
    Swap(arr, tmp);
  }
  if (arr != a) {
    for (int i = 0; i < n; i++) { tmp[i] = arr[i]; }
    tmp = arr;
  }
  delete[] tmp;
}

//ԭ����·�鲢���� O(nlogn)
template<typename T> void mergeSortInplace(T a[], const int n) {
  mergeSortInplace(a, 0, n - 1);
}

template<typename T> void mergeSortInplace(T a[], const int left, const int right) {
  if (left >= right) { return; }
  if (right - left + 1 >= INSERTION_BOUND) { //�Ӽ���Ԫ����С��ĳ��ֵʱ����ֱ�Ӳ�������
    int mid = (left + right) >> 1;
    mergeSortInplace(a, left, mid);
    mergeSortInplace(a, mid + 1, right);
    int i = left, j = mid + 1, k;
    while (i < j && j <= right) {
      while (i < j && a[i] <= a[j]) { i++; }
      k = 0;
      while (j <= right && a[i] > a[j]) { j++; k++; }
      SwapBlocks(a + i, j - i, j - k - i);
      i += k;
    }
  } else {
    insertionSort(a + left, right - left + 1);
  }
}

template<typename T> void Reverse(T a[], const int n) { //��ת����
  for (int left = 0, right = n - 1; left < right; Swap(a[left++], a[right--]));
}

template<typename T> void SwapBlocks(T a[], const int n, const int k) { //����������ѭ����λk��λ��
  Reverse(a, k);
  Reverse(a + k, n - k);
  Reverse(a, n);
}

//������ O(nlogn)
template<typename T> void heapSort(T a[], const int n) {
  for (int i = (n >> 1) - 1; i >= 0; i--) {
    adjustDown(a, i, n - 1);
  }
  for (int i = n - 1; i > 0; i--) {
    Swap(a[0], a[i]);
    adjustDown(a, 0, i - 1);
  }
}

template<typename T> void adjustDown(T a[], const int start, const int end) {
  int child = start + start + 1; T tmp = a[start];
  while (child <= end) {
    if (child < end && a[child] < a[child + 1]) { child++; }
    if (tmp >= a[child]) { break; }
    a[(child - 1) >> 1] = a[child];
    child += child + 1;
  }
  a[(child - 1) >> 1] = tmp;
}

//��β������ O(n^2)
template<typename T> void cocktailSort(T a[], const int n) {
  for (int left = 0, right = n - 1, j; left < right; left++) {
    for (j = left; j < right; j++) {
      if (a[j] > a[j + 1]) { Swap(a[j], a[j + 1]); }
    }
    for (j = --right; j > left; j--) {
      if (a[j - 1] > a[j]) { Swap(a[j - 1], a[j]); }
    }
  }
}

//�������� O(kn)
template<typename T> void radixSort(T a[], const int n) {
  int digit = 1, count[10]; T *tmp = new T[n], radix = 1, mx = a[0];
  for (int i = 1; i < n; i++) { if (mx < a[i]) { mx = a[i]; } }
  for (T p = 10; mx >= p; p *= 10, digit++);
  for (int i = 0; i < digit; radix *= 10, i++) {
    for (int j = 0; j < 10; j++) { count[j] = 0; }
    for (int j = 0; j < n; j++) { count[a[j] / radix % 10]++; }
    for (int j = 1; j < 10; j++) { count[j] += count[j - 1]; }
    for (int j = n - 1; j >= 0; j--) { tmp[count[a[j] / radix % 10]-- - 1] = a[j]; }
    for (int j = 0; j < n; j++) { a[j] = tmp[j]; }
  }
  delete[] tmp;
}

//ϣ������ O(nlogn^2)
template<typename T> void shellSort(T a[], const int n) {
  for (int gap = n >> 1; gap > 0; gap >>= 1) {
    for (int i = gap, j; i < n; i++) {
      T tmp = a[i];
      for (j = i - gap; j >= 0 && a[j] > tmp; j -= gap) { a[j + gap] = a[j]; }
      a[j + gap] = tmp;
    }
  }
}

//C qsort O(nlogn)
template<typename T> void qsort(T a[], const int n) {
  qsort(a, n, sizeof(T), cmp<T>);
}

template<typename T> int cmp(const void *a, const void *b) {
  return *(T *)a - *(T *)b;
}

//STL sort O(nlogn)
template<typename T> void STLsort(T a[], const int n) {
  std::sort(a, a + n);
}

//STL stable_sort O(nlogn)
template<typename T> void STLstable_sort(T a[], const int n) {
  std::stable_sort(a, a + n);
}

//STL partial_sort O(nlogn)
template<typename T> void STLpartial_sort(T a[], const int n) {
  std::partial_sort(a, a + n, a + n);
}

#endif
