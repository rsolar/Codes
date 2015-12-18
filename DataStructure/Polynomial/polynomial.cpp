//polynomial.cpp
#include "polynomial.h"

using namespace std;

Polynomial::Polynomial() :first(new Term(0, -1)) {} //创建带表头结点的非循环列表

Polynomial::Polynomial(const Polynomial &r) : first(new Term(*r.first)) {
  Term *q = first;
  Term *p = r.first->link;
  while (p != NULL) { //依次复制链表的每一结点
    q = q->insertAfter(p->coef, p->exp);
    p = p->link;
  }
}

Polynomial::~Polynomial() {
  Term *p = first->link;
  while (p != NULL) { //依次删除链表的每一结点
    first->link = p->link;
    delete p;
    p = first->link;
  }
  delete first; //释放表头结点
}

void Polynomial::addTerms(istream &in) {
  this->~Polynomial(); //调用析构函数释放原链表的空间
  first = new Term(0, -1);
  Term *p = first;
  int c, e;
  cout << "请以\"系数 指数\"的格式按指数递减顺序输入多项式的各项，指数小于0时输入结束。" << endl;
  for (;;) {
    in >> c >> e;
    if (e < 0) { //指数小于0时输入结束
      break;
    }
    if (c != 0) { //系数为零时忽略该项
      p = p->insertAfter(c, e);
    }
  }
}

void Polynomial::output(ostream &out) const {
  Term *p = first->link;
  bool f = true; //记录是否首项
  for (; p != NULL; p = p->link) {
    if (!f && p->coef > 0) { //首项前无须输出"+"号
      out << '+';
    }
    f = false;
    out << *p; //调用项结点的输出函数
  }
  if (f) { //若多项式为空则输出0
    out << "0";
  }
  out << endl;
}

void Polynomial::polyAdd(const Polynomial &r) {
  Term *q = first->link; //指向第一个要处理的结点
  Term *q1 = first; //q1为q的前驱
  Term *p = r.first->link; //指向第一个要处理的结点
  while (p != NULL) {
    while (q != NULL && p->exp < q->exp) { //q未到链表末端时 找到q->exp >= p->exp的第一个结点
      q1 = q;
      q = q->link;
    }
    if (q != NULL && p->exp == q->exp) { //p->exp == q->exp的情况 则系数相加
      q->coef += p->coef;
      if (q->coef == 0) { //系数为0则删除当前结点
        q1->link = q->link;
        delete q;
        q = q1->link;
      } else {
        q1 = q;
        q = q->link;
      }
    } else { //q已到链表末端或p->exp > q->exp的情况 则插入新节点
      q1 = q1->insertAfter(p->coef, p->exp); //在q的前驱结点后插入新结点
      q = q1->link; //q指向q1的后续
    }
    p = p->link; //指向下一个要处理的结点
  }
}

void Polynomial::polyMul(const Polynomial &r) {
  Polynomial ret; //临时变量用于储存结果
  Term *q = first->link; //指向第一个要处理的结点
  while (q != NULL) {
    Polynomial tmp; //临时变量用于储存结果
    Term *p = r.first->link;
    Term *t = tmp.first;
    while (p != NULL) { //将当前多项式的当前项与待乘多项式的每一项相乘
      t = t->insertAfter(q->coef * p->coef, q->exp + p->exp);
      p = p->link;
    }
    ret.polyAdd(tmp); //调用多项式加法函数将当前项的结果加到总体结果中
    q = q->link;
  }
  *this = ret; //将结果赋值给当前多项式
}

Polynomial &Polynomial::operator=(const Polynomial &r) {
  if (this == &r) { //自赋值检查
    return *this;
  }
  this->~Polynomial(); //调用析构函数释放原链表的空间
  first = new Term(*r.first); //同拷贝构造函数
  Term *q = first;
  Term *p = r.first->link;
  while (p != NULL) {
    q = q->insertAfter(p->coef, p->exp);
    p = p->link;
  }
  return *this;
}

Polynomial Polynomial::operator+(const Polynomial &r)const {
  Polynomial ret(*this); //临时变量用于返回结果
  ret.polyAdd(r);
  return ret;
}

Polynomial Polynomial::operator*(const Polynomial &r)const {
  Polynomial ret(*this); //临时变量用于返回结果
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
