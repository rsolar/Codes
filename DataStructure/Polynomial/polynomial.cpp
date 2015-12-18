//polynomial.cpp
#include "polynomial.h"

using namespace std;

Polynomial::Polynomial() :first(new Term(0, -1)) {} //��������ͷ���ķ�ѭ���б�

Polynomial::Polynomial(const Polynomial &r) : first(new Term(*r.first)) {
  Term *q = first;
  Term *p = r.first->link;
  while (p != NULL) { //���θ��������ÿһ���
    q = q->insertAfter(p->coef, p->exp);
    p = p->link;
  }
}

Polynomial::~Polynomial() {
  Term *p = first->link;
  while (p != NULL) { //����ɾ�������ÿһ���
    first->link = p->link;
    delete p;
    p = first->link;
  }
  delete first; //�ͷű�ͷ���
}

void Polynomial::addTerms(istream &in) {
  this->~Polynomial(); //�������������ͷ�ԭ����Ŀռ�
  first = new Term(0, -1);
  Term *p = first;
  int c, e;
  cout << "����\"ϵ�� ָ��\"�ĸ�ʽ��ָ���ݼ�˳���������ʽ�ĸ��ָ��С��0ʱ���������" << endl;
  for (;;) {
    in >> c >> e;
    if (e < 0) { //ָ��С��0ʱ�������
      break;
    }
    if (c != 0) { //ϵ��Ϊ��ʱ���Ը���
      p = p->insertAfter(c, e);
    }
  }
}

void Polynomial::output(ostream &out) const {
  Term *p = first->link;
  bool f = true; //��¼�Ƿ�����
  for (; p != NULL; p = p->link) {
    if (!f && p->coef > 0) { //����ǰ�������"+"��
      out << '+';
    }
    f = false;
    out << *p; //����������������
  }
  if (f) { //������ʽΪ�������0
    out << "0";
  }
  out << endl;
}

void Polynomial::polyAdd(const Polynomial &r) {
  Term *q = first->link; //ָ���һ��Ҫ����Ľ��
  Term *q1 = first; //q1Ϊq��ǰ��
  Term *p = r.first->link; //ָ���һ��Ҫ����Ľ��
  while (p != NULL) {
    while (q != NULL && p->exp < q->exp) { //qδ������ĩ��ʱ �ҵ�q->exp >= p->exp�ĵ�һ�����
      q1 = q;
      q = q->link;
    }
    if (q != NULL && p->exp == q->exp) { //p->exp == q->exp����� ��ϵ�����
      q->coef += p->coef;
      if (q->coef == 0) { //ϵ��Ϊ0��ɾ����ǰ���
        q1->link = q->link;
        delete q;
        q = q1->link;
      } else {
        q1 = q;
        q = q->link;
      }
    } else { //q�ѵ�����ĩ�˻�p->exp > q->exp����� ������½ڵ�
      q1 = q1->insertAfter(p->coef, p->exp); //��q��ǰ����������½��
      q = q1->link; //qָ��q1�ĺ���
    }
    p = p->link; //ָ����һ��Ҫ����Ľ��
  }
}

void Polynomial::polyMul(const Polynomial &r) {
  Polynomial ret; //��ʱ�������ڴ�����
  Term *q = first->link; //ָ���һ��Ҫ����Ľ��
  while (q != NULL) {
    Polynomial tmp; //��ʱ�������ڴ�����
    Term *p = r.first->link;
    Term *t = tmp.first;
    while (p != NULL) { //����ǰ����ʽ�ĵ�ǰ������˶���ʽ��ÿһ�����
      t = t->insertAfter(q->coef * p->coef, q->exp + p->exp);
      p = p->link;
    }
    ret.polyAdd(tmp); //���ö���ʽ�ӷ���������ǰ��Ľ���ӵ���������
    q = q->link;
  }
  *this = ret; //�������ֵ����ǰ����ʽ
}

Polynomial &Polynomial::operator=(const Polynomial &r) {
  if (this == &r) { //�Ը�ֵ���
    return *this;
  }
  this->~Polynomial(); //�������������ͷ�ԭ����Ŀռ�
  first = new Term(*r.first); //ͬ�������캯��
  Term *q = first;
  Term *p = r.first->link;
  while (p != NULL) {
    q = q->insertAfter(p->coef, p->exp);
    p = p->link;
  }
  return *this;
}

Polynomial Polynomial::operator+(const Polynomial &r)const {
  Polynomial ret(*this); //��ʱ�������ڷ��ؽ��
  ret.polyAdd(r);
  return ret;
}

Polynomial Polynomial::operator*(const Polynomial &r)const {
  Polynomial ret(*this); //��ʱ�������ڷ��ؽ��
  ret.polyMul(r);
  return ret;
}

istream &operator>>(istream &in, Polynomial &r) {
  r.addTerms(in);
  return in;
}

ostream &operator<<(ostream &out, const Polynomial &r) {
  r.output(out);
  return out;
}
