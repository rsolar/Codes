//term.h
#ifndef TERM_H
#define TERM_H

#include <iostream>

class Term {
private:
  int coef; //系数
  int exp;  //指数
  Term *link; //指向下一项节点
public:
  Term(int c, int e);
  Term(int c, int e, Term *nxt);
  Term(const Term &r);
  Term *insertAfter(int c, int e); //在此项后方插入新的项节点
  friend std::ostream &operator<<(std::ostream &, const Term &); //重载输出操作符
  friend class Polynomial; //声明友元类
};

#endif