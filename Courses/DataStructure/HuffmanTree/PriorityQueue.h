//PriorityQueue.h
#ifndef PRIOQUEUE_H
#define PRIOQUEUE_H

#include <iostream>

template<typename T> class PriorityQueue { //优先权队列类
public:
  PriorityQueue(int mSize) :maxSize(mSize), top(0), que(new T[maxSize]) {}
  ~PriorityQueue() { delete[] que; }
  bool isEmpty()const { return top == 0; }
  bool isFull()const { return top == maxSize; }
  bool append(T const &x); //插入元素
  bool serve(T &x); //删除堆顶元素

private:
  void adjustUp(int const i); //向上调整
  void adjustDown(int const r, int const j); //向下调整

  int maxSize;
  int top;
  T *que;
};

template<typename T> bool PriorityQueue<T>::append(T const &x) {
  if (isFull()) {
    cout << "Overflow" << endl;
    return false;
  }
  que[top++] = x;
  adjustUp(top - 1);
  return true;
}

template<typename T> bool PriorityQueue<T>::serve(T &x) {
  if (isEmpty()) {
    cout << "Underflow" << endl;
    return false;
  }
  x = que[0];
  que[0] = que[--top];
  adjustDown(0, top - 1);
  return true;
}

template<typename T> void PriorityQueue<T>::adjustUp(int const i) {
  int j = i;
  T temp = que[j];
  if (typeid(T) == typeid(BTNode<T> *)) { //对二叉树结点指针类型特殊处理
    while (j > 0 && temp->getW() < que[(j - 1) / 2]->getW()) {
      que[j] = que[(j - 1) / 2];
      j = (j - 1) / 2;
    }
  } else {
    while (j > 0 && temp < que[(j - 1) / 2]) {
      que[j] = que[(j - 1) / 2];
      j = (j - 1) / 2;
    }
  }
  que[j] = temp;
}

template<typename T> void PriorityQueue<T>::adjustDown(int const r, int const j) {
  int child = 2 * r + 1;
  T temp = que[r];
  if (typeid(T) == typeid(BTNode<T> *)) { //对二叉树结点指针类型特殊处理
    while (child <= j) {
      if ((child < j) && (que[child]->getW() > que[child + 1]->getW())) { child++; }
      if (temp->getW() <= que[child]->getW()) { break; }
      que[(child - 1) / 2] = que[child];
      child = 2 * child + 1;
    }
  } else {
    while (child <= j) {
      if ((child < j) && (que[child] > que[child + 1])) { child++; }
      if (temp <= que[child]) { break; }
      que[(child - 1) / 2] = que[child];
      child = 2 * child + 1;
    }
  }
  que[(child - 1) / 2] = temp;
}

#endif
