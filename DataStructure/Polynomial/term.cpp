//term.cpp
#include "term.h"

using namespace std;

Term::Term(int c, int e) :coef(c), exp(e), link(NULL) {}

Term::Term(int c, int e, Term *nxt) : coef(c), exp(e), link(nxt) {}

Term::Term(const Term &r) : coef(r.coef), exp(r.exp), link(NULL) {}

Term *Term::insertAfter(int c, int e) {
  link = new Term(c, e, link);
  return link;
}

ostream &operator<<(ostream &out, const Term &val) {
  if (val.coef == 0) { return out; } //����ϵ��Ϊ0����
  if (val.exp != 0 && val.coef == -1) { //�ǳ�������ϵ��Ϊ-1ʱֻ���'-'
      out << '-';
  } else if (val.exp == 0 || val.coef != 1) { //�ǳ�������ϵ��Ϊ1ʱ�����ϵ��
    out << val.coef;
  }
  switch (val.exp) {
    case 0:
      break;
    case 1:
      out << "X";
      break;
    default:
      out << "X^" << val.exp;
      break;
  }
  return out;
}