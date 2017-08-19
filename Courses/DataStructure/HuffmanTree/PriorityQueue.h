//PriorityQueue.h
#ifndef PRIOQUEUE_H
#define PRIOQUEUE_H

#include <iostream>

template<typename T> class PriorityQueue { //����Ȩ������
public:
  PriorityQueue(int mSize) :maxSize(mSize), top(0), que(new T[maxSize]) {}
  ~PriorityQueue() { delete[] que; }
  bool isEmpty()const { return top == 0; }
  bool isFull()const { return top == maxSize; }
  bool append(T const &x); //����Ԫ��
  bool serve(T &x); //ɾ���Ѷ�Ԫ��

private:
  void adjustUp(int const i); //���ϵ���
  void adjustDown(int const r, int const j); //���µ���

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
  if (typeid(T) == typeid(BTNode<T> *)) { //�Զ��������ָ���������⴦��
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
  if (typeid(T) == typeid(BTNode<T> *)) { //�Զ��������ָ���������⴦��
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
