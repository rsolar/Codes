//polynomial.h
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "term.h"

class Polynomial {
private:
  Term *first; //ָ���ͷ���
public:
  Polynomial(); //���캯��
  Polynomial(const Polynomial &r); //�������캯��
  ~Polynomial(); //��������
  void addTerms(std::istream &in = std::cin); //�������ʽ
  void output(std::ostream &out = std::cout) const; //�������ʽ
  void polyAdd(const Polynomial &r); //����ʽ�ӷ�
  void polyMul(const Polynomial &r); //����ʽ�˷�
  Polynomial &operator=(const Polynomial &r); //���ض���ʽ��ĸ�ֵ��
  Polynomial operator+(const Polynomial &r)const; //����"+"��
  Polynomial operator*(const Polynomial &r)const; //����"*"��
  friend std::istream &operator>>(std::istream &in, Polynomial &r); //�������������
  friend std::ostream &operator<<(std::ostream &out, const Polynomial &r); //�������������
};

#endif