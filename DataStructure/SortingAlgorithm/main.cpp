//main.cpp
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <windows.h>
#include "Sort.h"

using namespace std;

const int Times = 8; //每个算法的运行次数

template<typename T> bool check(const T a[], const T b[], const int n) {
  T *c = new T[n];
  memcpy(c, a, sizeof(T) * n);
  sort(c, c + n);
  for (int i = 0; i < n; i++) {
    if (b[i] != c[i]) { delete[] c; return false; }
  }
  delete[] c;
  return true;
}

template<typename T> void runTest(const T *const a[], const int n, void(*Sort)(T *, const int)) {
  T *b = new T[n];
  LARGE_INTEGER start, end, freq, sum;
  sum.QuadPart = 0LL;
  QueryPerformanceFrequency(&freq);
  cout << fixed << setprecision(1);
  for (int i = 0; i < Times; i++) {
    memcpy(b, a[i], sizeof(T) * n);
    QueryPerformanceCounter(&start);
    Sort(b, n);
    QueryPerformanceCounter(&end);
    sum.QuadPart += end.QuadPart - start.QuadPart;
    cout << setw(7) << (end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart << "ms";
    if (!check(a[i], b, n)) { cout << endl << "错误!" << endl; return; }
  }
  cout << endl << "平均时间: " << sum.QuadPart * 1000.0 / freq.QuadPart / Times << "ms" << endl;
  //fstream out("out.txt", fstream::out | fstream::app);
  //out << fixed << setprecision(2) << sum.QuadPart * 1000.0 / freq.QuadPart / Times << endl;
  delete[] b;
}

int main() {
  int n;
  while (cout << endl << "请输入元素个数, 输入负数退出程序: ", cin >> n) {
    if (n < 0) { break; }
    default_random_engine random((unsigned)time(NULL));
    uniform_int_distribution<int> dis(0, 100000000); //C11提供的均匀分布随机数生成器 范围[0, 10^8]
    //cout << endl << "待排序序列为: ";
    int **a = new int *[Times];
    for (int i = 0; i < Times; i++) {
      a[i] = new int[n];
      for (int j = 0; j < n; j++) {
        a[i][j] = dis(random);
        //cout << a[i][j] << (j != n - 1 ? ' ' : '\n');
      }
    }
    cout << "简单选择排序 O(n^2):" << endl;
    runTest(a, n, selectionSort);
    cout << "直接插入排序 O(n^2):" << endl;
    runTest(a, n, insertionSort);
    cout << "冒泡排序 O(n^2):" << endl;
    runTest(a, n, bubbleSort);
    cout << "递归版快速排序 O(nlogn):" << endl;
    runTest(a, n, quickSortRecursive);
    cout << "改进的递归版快速排序 O(nlogn):" << endl;
    runTest(a, n, GQuickSortRecursive);
    cout << "非递归版快速排序 O(nlogn):" << endl;
    runTest(a, n, quickSortIterative);
    cout << "递归版两路归并排序 O(nlogn):" << endl;
    runTest(a, n, mergeSortRecursive);
    cout << "改进的递归版两路归并排序 O(nlogn):" << endl;
    runTest(a, n, GMergeSortRecursive);
    cout << "非递归版两路归并排序 O(nlogn):" << endl;
    runTest(a, n, mergeSortIterative);
    cout << "原地两路归并排序 O(nlogn):" << endl;
    runTest(a, n, mergeSortInplace);
    cout << "堆排序 O(nlogn):" << endl;
    runTest(a, n, heapSort);
    cout << "鸡尾酒排序 O(n^2):" << endl;
    runTest(a, n, cocktailSort);
    cout << "基数排序 O(kn):" << endl;
    runTest(a, n, radixSort);
    cout << "希尔排序 O(nlogn^2):" << endl;
    runTest(a, n, shellSort);
    cout << "C qsort O(nlogn):" << endl;
    runTest(a, n, qsort);
    cout << "STL sort O(nlogn):" << endl;
    runTest(a, n, STLsort);
    cout << "STL stable_sort O(nlogn):" << endl;
    runTest(a, n, STLstable_sort);
    cout << "STL partial_sort O(nlogn):" << endl;
    runTest(a, n, STLpartial_sort);
    for (int i = 0; i < Times; i++) { delete[] a[i]; }
    delete[] a;
  }
  return 0;
}
