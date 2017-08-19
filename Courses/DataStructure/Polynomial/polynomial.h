//polynomial.h
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "term.h"

class Polynomial {
private:
  Term *first; //指向表头结点
public:
  Polynomial(); //构造函数
  Polynomial(const Polynomial &r); //拷贝构造函数
  ~Polynomial(); //析构函数
  void addTerms(std::istream &in = std::cin); //输入多项式
  void output(std::ostream &out = std::cout) const; //输出多项式
  void polyAdd(const Polynomial &r); //多项式加法
  void polyMul(const Polynomial &r); //多项式乘法
  Polynomial &operator=(const Polynomial &r); //重载多项式类的赋值号
  Polynomial operator+(const Polynomial &r)const; //重载"+"号
  Polynomial operator*(const Polynomial &r)const; //重载"*"号
  friend std::istream &operator>>(std::istream &in, Polynomial &r); //重载输入操作符
  friend std::ostream &operator<<(std::ostream &out, const Polynomial &r); //重载输出操作符
};

#endif