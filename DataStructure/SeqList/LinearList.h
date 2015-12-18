//LinearList.h
#ifndef LINEARLIST_H
#define LINEARLIST_H

#include <iostream>

template<typename T> class LinearList {
protected:
  int n;
public:
  LinearList() :n(0) {}
  virtual bool isEmpty() const = 0;
  virtual int size() const = 0;
  virtual bool find(int i, T &x) const = 0;
  virtual int search(const T &x) const = 0;
  virtual bool insert(int i, const T &x) = 0;
  virtual bool erase(int i) = 0;
  virtual bool update(int i, const T &x) = 0;
  virtual void output(std::ostream &out = std::cout) const = 0;
};

#endif