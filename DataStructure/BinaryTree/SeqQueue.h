//SeqQueue.h
#ifndef SEQQUEUE_H
#define SEQQUEUE_H

#include <iostream>

template<typename T> class SeqQueue {
private:
  int _front, _rear;
  int maxSize;
  T *q;
public:
  SeqQueue(int mSize) :_front(0), _rear(0), maxSize(mSize + 1), q(new T[maxSize]) {}
  ~SeqQueue() { delete[] q; }
  bool isEmpty()const { return _front == _rear; }
  bool isFull()const { return (_rear + 1) % maxSize == _front; }
  bool front(T &x)const;
  bool push(T const &x);
  bool pop();
  void clear() { _front = _rear = 0; }
};

template<typename T> bool SeqQueue<T>::front(T &x)const {
  if (isEmpty()) {
    cout << "Queue's empty" << endl;
    return false;
  }
  x = q[(_front + 1) % maxSize];
  return true;
}

template<typename T> bool SeqQueue<T>::push(T const &x) {
  if (isFull()) {
    cout << "Queue's full" << endl;
    return false;
  }
  q[_rear = (_rear + 1) % maxSize] = x;
  return true;
}

template<typename T> bool SeqQueue<T>::pop() {
  if (isEmpty()) {
    cout << "Underflow" << endl;
    return false;
  }
  _front = (_front + 1) % maxSize;
  return true;
}

#endif