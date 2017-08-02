#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

template<class T> void Swap(T &a, T &b) {
  T t(a); a = b; b = t;
}

template <class T> class SortableList {
public:
  SortableList(int m) { n = m; }
  void MergeSort();
  void Merge(int left, int mid, int right);
  void QuickSort();
  void Generate();
  void Init();
  void Output();
private:
  int RPartition(int left, int right);
  int Partition(int left, int right);
  void MergeSort(int left, int right);
  void QuickSort(int left, int right);
  T l[1000]; //���������ֵ
  T a[1000]; //ʵ���������
  int n;
};

template<class T> void SortableList<T>::Generate() {
  for (int i = 0; i < n; i++) { l[i] = rand() % n; cout << l[i] << ' '; }
  cout << endl << endl;
}

//Init()����������������·�ϲ�������������лָ�����ʼ����
//�ٽ��п�������
template<class T> void SortableList<T>::Init() {
  for (int i = 0; i < n; i++) { a[i] = l[i]; }
}

template<class T> void SortableList<T>::Output() {
  for (int i = 0; i < n; i++) { cout << a[i] << " "; }
  cout << endl << endl;
}

//��·�ϲ�����
template<class T> void SortableList<T>::MergeSort() {
  MergeSort(0, n - 1);
}

template<class T> void SortableList<T>::MergeSort(int left, int right) {
  if (left < right) {
    int mid = (left + right) / 2;
    MergeSort(left, mid);
    MergeSort(mid + 1, right);
    Merge(left, mid, right);
  }
}

template <class T> void SortableList<T>::Merge(int left, int mid, int right) {
  T* temp = new T[right - left + 1];
  int i = left, j = mid + 1, k = 0;
  while (i <= mid && j <= right) {
    if (a[i] <= a[j]) {
      temp[k++] = a[i++];
    } else {
      temp[k++] = a[j++];
    }
  }
  while (i <= mid) { temp[k++] = a[i++]; }
  while (j <= right) { temp[k++] = a[j++]; }
  for (i = 0, k = left; k <= right;) { a[k++] = temp[i++]; }
}

//��������
template <class T> int SortableList<T>::RPartition(int left, int right) {
  int i = rand() % (right - left) + left;
  Swap(a[i], a[left]);
  return Partition(left, right);
}

template <class T> int SortableList<T>::Partition(int left, int right) {
  int i = left, j = right + 1;
  do {
    do { i++; } while (a[i] < a[left]);
    do { j--; } while (a[j] > a[left]);
    if (i < j) { Swap(a[i], a[j]); }
  } while (i < j);
  Swap(a[left], a[j]);
  return j;
}

template <class T> void SortableList<T>::QuickSort(int left, int right) {
  if (left < right) {
    int j = RPartition(left, right);
    QuickSort(left, j - 1);
    QuickSort(j + 1, right);
  }
}

template<class T>
void SortableList<T>::QuickSort() {
  QuickSort(0, n - 1);
}

int main() {
  srand((unsigned)time(NULL));
  int n;
  cout << "���鳤��n: ";
  cin >> n;
  SortableList<int> List(n);
  cout << "������ɵ�" << n << "������:" << endl;
  List.Generate();
  List.Init();//�õ���ʼ״̬
  List.MergeSort();
  cout << "��·�ϲ������" << endl;
  List.Output();
  List.Init();//�ָ���ʼ״̬
  cout << "���������" << endl;
  List.QuickSort();
  List.Output();
  return 0;
}
