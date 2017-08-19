//HuffmanTree.h
#ifndef HFMTREE_H
#define HFMTREE_H

#include <iostream>
#include <string>
#include <vector>

#include "BinaryTree.h" //����������Ϊ����
#include "PriorityQueue.h" //����Ȩ������Ϊ�������ݽṹ

using std::string;
using std::vector;

template<typename T> class HuffmanTree :public BinaryTree<T> { //����������
public:
  operator T()const { return weight; } //��������ת�������
  T getW()const { return weight; } //��ȡ�����Ȩֵ
  void putW(T const &x) { weight = x; if (root) { root->element = x; } } //�޸ĸ����Ȩֵ
  void clear() { BinaryTree<T>::clear(); weight = 0; } //ɾ����������
  vector<BTNode<T> *> build(vector<char> const &c, vector<T> const &w); //����, ����ָ��ÿ���ַ���ӦҶ�ӽ���ָ������
  vector<string> getCode(vector<BTNode<T> *> &leaf)const; //���ɱ���
  string encode(vector<char> const &c, vector<string> const &code, string const &text)const; //����
  string decode(vector<char> const &c, vector<string> const &code, string const &text)const; //����

private:
  T weight; //�����Ȩֵ
};

template<typename T> vector<BTNode<T> *> HuffmanTree<T>::build(vector<char> const &c, vector<T> const &w) {
  PriorityQueue<HuffmanTree<T> *> pque(w.size());
  HuffmanTree<T> *x = new HuffmanTree<T>(), *y = new HuffmanTree<T>(), *tmp;
  vector<BTNode<T> *> leaf(w.size());
  for (size_t i = 0; i < w.size(); i++) { //����n��Ҷ�ӽ�㲢��������Ȩ����
    tmp = new HuffmanTree<T>();
    tmp->makeTree(w[i], *x, *y);
    tmp->putW(w[i]);
    leaf[i] = tmp->root;
    pque.append(tmp);
  }
  for (size_t i = 1; i < w.size(); i++) { //����n-1�������
    tmp = new HuffmanTree<T>();
    pque.serve(x);
    pque.serve(y);
    tmp->makeTree(x->getW() + y->getW(), *x, *y);
    tmp->putW(x->getW() + y->getW());
    pque.append(tmp);
  }
  pque.serve(tmp);
  this->clear();
  this->root = tmp->root; //��ǰ������Ϊ����
  this->putW(tmp->getW());
  return leaf;
}

template<typename T> vector<string> HuffmanTree<T>::getCode(vector<BTNode<T> *> &leaf)const {
  BTNode<T> *p;
  vector<string> code(leaf.size());
  for (size_t i = 0; i < leaf.size(); i++) {
    string tmp;
    p = leaf[i]; //��Ҷ�ӽ���ߵ������
    while (p != root) {
      tmp += p == p->parent->lChild ? '0' : '1'; //�жϵ�ǰ���Ϊ��������/�Һ���
      p = p->parent; //ָ�򸸽��
    }
    reverse(tmp.begin(), tmp.end()); //����
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
    } else { //�ַ����в����ڸ��ַ����׳��쳣
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
    p = root; //�Ӹ���㿪ʼƥ��
    while (p->lChild || p->rChild) { //ƥ�䵽Ҷ�ӽ��
      if (text[i] == '0' && p->lChild) {
        p = p->lChild;
      } else if (text[i] == '1' && p->rChild) {
        p = p->rChild;
      } else { //ƥ��ʧ�����׳��쳣
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
