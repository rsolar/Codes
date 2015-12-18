//HuffmanTree.h
#ifndef HFMTREE_H
#define HFMTREE_H

#include <iostream>
#include <string>
#include <vector>

#include "BinaryTree.h" //二叉树类作为基类
#include "PriorityQueue.h" //优先权队列作为辅助数据结构

using std::string;
using std::vector;

template<typename T> class HuffmanTree :public BinaryTree<T> { //哈夫曼树类
public:
  operator T()const { return weight; } //重载类型转换运算符
  T getW()const { return weight; } //获取根结点权值
  void putW(T const &x) { weight = x; if (root) { root->element = x; } } //修改根结点权值
  void clear() { BinaryTree<T>::clear(); weight = 0; } //删除哈夫曼树
  vector<BTNode<T> *> build(vector<char> const &c, vector<T> const &w); //建树, 返回指向每个字符对应叶子结点的指针数组
  vector<string> getCode(vector<BTNode<T> *> &leaf)const; //生成编码
  string encode(vector<char> const &c, vector<string> const &code, string const &text)const; //编码
  string decode(vector<char> const &c, vector<string> const &code, string const &text)const; //译码

private:
  T weight; //根结点权值
};

template<typename T> vector<BTNode<T> *> HuffmanTree<T>::build(vector<char> const &c, vector<T> const &w) {
  PriorityQueue<HuffmanTree<T> *> pque(w.size());
  HuffmanTree<T> *x = new HuffmanTree<T>(), *y = new HuffmanTree<T>(), *tmp;
  vector<BTNode<T> *> leaf(w.size());
  for (size_t i = 0; i < w.size(); i++) { //建立n个叶子结点并加入优先权队列
    tmp = new HuffmanTree<T>();
    tmp->makeTree(w[i], *x, *y);
    tmp->putW(w[i]);
    leaf[i] = tmp->root;
    pque.append(tmp);
  }
  for (size_t i = 1; i < w.size(); i++) { //建立n-1个父结点
    tmp = new HuffmanTree<T>();
    pque.serve(x);
    pque.serve(y);
    tmp->makeTree(x->getW() + y->getW(), *x, *y);
    tmp->putW(x->getW() + y->getW());
    pque.append(tmp);
  }
  pque.serve(tmp);
  this->clear();
  this->root = tmp->root; //当前对象作为树根
  this->putW(tmp->getW());
  return leaf;
}

template<typename T> vector<string> HuffmanTree<T>::getCode(vector<BTNode<T> *> &leaf)const {
  BTNode<T> *p;
  vector<string> code(leaf.size());
  for (size_t i = 0; i < leaf.size(); i++) {
    string tmp;
    p = leaf[i]; //从叶子结点走到根结点
    while (p != root) {
      tmp += p == p->parent->lChild ? '0' : '1'; //判断当前结点为父结点的左/右孩子
      p = p->parent; //指向父结点
    }
    reverse(tmp.begin(), tmp.end()); //逆序
    code[i] = tmp;
  }
  return code;
}

template<typename T> string HuffmanTree<T>::encode(vector<char> const &c, vector<string> const &code, string const &text)const {
  string result;
  for (size_t i = 0, j; i < text.size(); i++) {
    for (j = 0; j < c.size() && c[j] != text[i]; j++);
    if (j < c.size()) {
      result += code[j];
    } else { //字符集中不存在该字符则抛出异常
      throw new exception;
      return result;
    }
  }
  return result;
}

template<typename T> string HuffmanTree<T>::decode(vector<char> const &c, vector<string> const &code, string const &text)const {
  BTNode<T> *p;
  string result;
  for (size_t i = 0, id; i < text.size();) {
    string tmp;
    p = root; //从根结点开始匹配
    while (p->lChild || p->rChild) { //匹配到叶子结点
      if (text[i] == '0' && p->lChild) {
        p = p->lChild;
      } else if (text[i] == '1' && p->rChild) {
        p = p->rChild;
      } else { //匹配失败则抛出异常
        throw new exception;
        return result;
      }
      tmp += text[i++];
    }
    for (id = 0; code[id] != tmp; id++);
    result += c[id];
  }
  return result;
}

#endif
