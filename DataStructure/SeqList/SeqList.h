//SeqList.h
#ifndef SEQLIST_H
#define SEQLIST_H

#include "LinearList.h"

template<typename T> class SeqList :public LinearList < T > {
private:
  int max_size; //顺序表最大长度
  T *element; //动态一位数组指针
public:
  SeqList(int mSize) :max_size(mSize), element(new T[max_size]) {} //构造函数
  ~SeqList() { delete[] element; } //析构函数
  bool isEmpty() const { return n == 0; } //判断顺序表是否为空
  int size() const { return n; } //返回顺序表元素个数
  bool find(int i, T &x) const; //通过引用x返回下标为i的元素
  int search(const T &x) const; //返回第一个值等于x的元素的下标,若未找到则返回-1
  bool insert(int i, const T &x); //在下标为i的元素前插入值为x的元素
  bool erase(int i); //删除下标为i的元素
  bool update(int i, const T &x); //将下标为i的元素的值修改为x
  void output(std::ostream &out = std::cout) const; //输出顺序表

  void reverse(); //逆置顺序表
  bool eraseX(const T &x); //删除表中所有值等于x的元素
};

template<typename T> bool SeqList<T>::find(int i, T &x) const {
  if (i < 0 || i >= n) { //越界检查
    cout << "Out of Bounds" << endl;
    return false;
  }
  x = element[i];
  return true;
}

template<typename T> int SeqList<T>::search(const T &x) const {
  for (int j = 0; j < n; j++) {
    if (element[j] == x) {
      return j; //找到则返回下标
    }
  }
  return -1; //未找到则返回-1
}

template<typename T> bool SeqList<T>::insert(int i, const T &x) {
  if (i < 0 || i > n) { //越界检查
    cout << "Out of Bounds" << endl;
    return false;
  }
  if (n == max_size) { //溢出检查
    cout << "Overflow" << endl;
    return false;
  }
  for (int j = n; j > i; j--) { //将后方元素从后往前依次后移
    element[j] = element[j - 1];
  }
  element[i] = x; //插入元素
  n++;
  return true;
}

template<typename T> bool SeqList<T>::erase(int i) {
  if (isEmpty()) { //空顺序表检查
    cout << "Underflow" << endl;
    return false;
  }
  if (i < 0 || i >= n) { //越界检查
    cout << "Out of Bounds" << endl;
    return false;
  }
  for (int j = i + 1; j < n; j++) { //将后方元素从前往后依次前移
    element[j - 1] = element[j];
  }
  n--;
  return true;
}

template<typename T> bool SeqList<T>::update(int i, const T &x) {
  if (i < 0 || i >= n) { //越界检查
    cout << "Out of Bounds" << endl;
    return false;
  }
  element[i] = x;
  return true;
}

template<typename T> void SeqList<T>::output(std::ostream &out) const {
  if (isEmpty()) { //空顺序表检查
    out << "Empty" << endl;
    return;
  }
  for (int i = 0; i < n; i++) {
    out << element[i] << ' ';
  }
  out << endl;
}

template<typename T> void SeqList<T>::reverse() {
  for (int i = 0; i < n / 2; i++) { //将顺序表中下标i在[0,n/2)范围内的元素与下标为n-i-1的元素交换
    T t = element[i];
    element[i] = element[n - i - 1];
    element[n - i - 1] = t;
  }
}

template<typename T> bool SeqList<T>::eraseX(const T &x) {
  bool found = false; //记录是否有元素被删除
  for (int i = 0; i < n; i++) {
    if (element[i] == x) {
      erase(i--); //调用erase函数删除元素
      found = true;
    }
  }
  return found;
}

#endif