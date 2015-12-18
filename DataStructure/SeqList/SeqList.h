//SeqList.h
#ifndef SEQLIST_H
#define SEQLIST_H

#include "LinearList.h"

template<typename T> class SeqList :public LinearList < T > {
private:
  int max_size; //˳�����󳤶�
  T *element; //��̬һλ����ָ��
public:
  SeqList(int mSize) :max_size(mSize), element(new T[max_size]) {} //���캯��
  ~SeqList() { delete[] element; } //��������
  bool isEmpty() const { return n == 0; } //�ж�˳����Ƿ�Ϊ��
  int size() const { return n; } //����˳���Ԫ�ظ���
  bool find(int i, T &x) const; //ͨ������x�����±�Ϊi��Ԫ��
  int search(const T &x) const; //���ص�һ��ֵ����x��Ԫ�ص��±�,��δ�ҵ��򷵻�-1
  bool insert(int i, const T &x); //���±�Ϊi��Ԫ��ǰ����ֵΪx��Ԫ��
  bool erase(int i); //ɾ���±�Ϊi��Ԫ��
  bool update(int i, const T &x); //���±�Ϊi��Ԫ�ص�ֵ�޸�Ϊx
  void output(std::ostream &out = std::cout) const; //���˳���

  void reverse(); //����˳���
  bool eraseX(const T &x); //ɾ����������ֵ����x��Ԫ��
};

template<typename T> bool SeqList<T>::find(int i, T &x) const {
  if (i < 0 || i >= n) { //Խ����
    cout << "Out of Bounds" << endl;
    return false;
  }
  x = element[i];
  return true;
}

template<typename T> int SeqList<T>::search(const T &x) const {
  for (int j = 0; j < n; j++) {
    if (element[j] == x) {
      return j; //�ҵ��򷵻��±�
    }
  }
  return -1; //δ�ҵ��򷵻�-1
}

template<typename T> bool SeqList<T>::insert(int i, const T &x) {
  if (i < 0 || i > n) { //Խ����
    cout << "Out of Bounds" << endl;
    return false;
  }
  if (n == max_size) { //������
    cout << "Overflow" << endl;
    return false;
  }
  for (int j = n; j > i; j--) { //����Ԫ�شӺ���ǰ���κ���
    element[j] = element[j - 1];
  }
  element[i] = x; //����Ԫ��
  n++;
  return true;
}

template<typename T> bool SeqList<T>::erase(int i) {
  if (isEmpty()) { //��˳�����
    cout << "Underflow" << endl;
    return false;
  }
  if (i < 0 || i >= n) { //Խ����
    cout << "Out of Bounds" << endl;
    return false;
  }
  for (int j = i + 1; j < n; j++) { //����Ԫ�ش�ǰ��������ǰ��
    element[j - 1] = element[j];
  }
  n--;
  return true;
}

template<typename T> bool SeqList<T>::update(int i, const T &x) {
  if (i < 0 || i >= n) { //Խ����
    cout << "Out of Bounds" << endl;
    return false;
  }
  element[i] = x;
  return true;
}

template<typename T> void SeqList<T>::output(std::ostream &out) const {
  if (isEmpty()) { //��˳�����
    out << "Empty" << endl;
    return;
  }
  for (int i = 0; i < n; i++) {
    out << element[i] << ' ';
  }
  out << endl;
}

template<typename T> void SeqList<T>::reverse() {
  for (int i = 0; i < n / 2; i++) { //��˳������±�i��[0,n/2)��Χ�ڵ�Ԫ�����±�Ϊn-i-1��Ԫ�ؽ���
    T t = element[i];
    element[i] = element[n - i - 1];
    element[n - i - 1] = t;
  }
}

template<typename T> bool SeqList<T>::eraseX(const T &x) {
  bool found = false; //��¼�Ƿ���Ԫ�ر�ɾ��
  for (int i = 0; i < n; i++) {
    if (element[i] == x) {
      erase(i--); //����erase����ɾ��Ԫ��
      found = true;
    }
  }
  return found;
}

#endif