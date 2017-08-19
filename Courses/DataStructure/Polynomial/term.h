//term.h
#ifndef TERM_H
#define TERM_H

#include <iostream>

class Term {
private:
  int coef; //ϵ��
  int exp;  //ָ��
  Term *link; //ָ����һ��ڵ�
public:
  Term(int c, int e);
  Term(int c, int e, Term *nxt);
  Term(const Term &r);
  Term *insertAfter(int c, int e); //�ڴ���󷽲����µ���ڵ�
  friend std::ostream &operator<<(std::ostream &, const Term &); //�������������
  friend class Polynomial; //������Ԫ��
};

#endif