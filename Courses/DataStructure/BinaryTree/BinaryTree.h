//BinaryTree.h
#ifndef BTREE_H
#define BTREE_H

#include <iostream>

#include "SeqQueue.h"

template<typename T> struct BTNode { //二叉树结点类
  T element;
  BTNode<T> *lChild, *rChild;

  BTNode() :lChild(NULL), rChild(NULL) {}
  BTNode(T const &x) :element(x), lChild(NULL), rChild(NULL) {}
  BTNode(T const &x, BTNode<T> *l, BTNode<T> *r) :element(x), lChild(l), rChild(r) {}
};

template<typename T> class BinaryTree { //二叉树类
public:
  BinaryTree() :root(NULL) {} //构造函数
  BinaryTree(BinaryTree<T> const &r) { this->copyTo(r); } //拷贝构造函数
  ~BinaryTree() { clear(); } //析构函数
  bool isEmpty()const { return root == NULL; } //判断二叉树是否为空
  void clear(); //删除二叉树
  void makeTree(T const &x, BinaryTree<T> &left, BinaryTree<T> &right); //构造二叉树
  void breakTree(T &x, BinaryTree<T> &left, BinaryTree<T> &right); //拆分二叉树
  void preOrder(void (*visit)(BTNode<T> const *const t))const; //前序遍历
  void inOrder(void (*visit)(BTNode<T> const *const t))const; //中序遍历
  void postOrder(void (*visit)(BTNode<T> const *const t))const; //后序遍历
  void levelOrder(void (*visit)(BTNode<T> const *const t))const; //层次遍历
  int height()const; //求二叉树高度
  int leafNum()const; //求二叉树中叶子结点数
  void copyTo(BinaryTree<T> &r)const; //复制二叉树
  void invert(); //翻转二叉树

protected:
  BTNode<T> *root;

private:
  void clear(BTNode<T> *&t);
  void preOrder(void (*visit)(BTNode<T> const *const t), BTNode<T> const *const t)const;
  void inOrder(void (*visit)(BTNode<T> const *const t), BTNode<T> const *const t)const;
  void postOrder(void (*visit)(BTNode<T> const *const t), BTNode<T> const *const t)const;
  int height(BTNode<T> const *const t)const;
  int leafNum(BTNode<T> const *const t)const;
  BTNode<T> *copyTo(BTNode<T> const *const t)const;
  void invert(BTNode<T> *t);
};

template<typename T> void BinaryTree<T>::clear() {
  clear(root);
}

template<typename T> void BinaryTree<T>::clear(BTNode<T> *&t) {
  if (t) {
    clear(t->lChild);
    clear(t->rChild);
    delete t;
    t = NULL;
  }
}

template<typename T> void BinaryTree<T>::makeTree(T const &x, BinaryTree<T> &left, BinaryTree<T> &right) {
  if (root || &left == &right) { return; }
  root = new BTNode<T>(x, left.root, right.root);
  left.root = right.root = NULL;
}

template<typename T> void BinaryTree<T>::breakTree(T &x, BinaryTree<T> &left, BinaryTree<T> &right) {
  if (!root || &left == &right || left.root || right.root) { return; }
  x = root->element;
  left.root = root->lChild;
  right.root = root->rChild;
  delete root;
  root = NULL;
}

template<typename T> void BinaryTree<T>::preOrder(void(*visit)(BTNode<T> const *const t))const {
  preOrder(visit, root);
  cout << endl;
}

template<typename T> void BinaryTree<T>::preOrder(void(*visit)(BTNode<T> const *const t), BTNode<T> const *const t)const {
  if (t) {
    visit(t);
    preOrder(visit, t->lChild);
    preOrder(visit, t->rChild);
  }
}

template<typename T> void BinaryTree<T>::inOrder(void(*visit)(BTNode<T> const *const t))const {
  inOrder(visit, root);
  cout << endl;
}

template<typename T> void BinaryTree<T>::inOrder(void(*visit)(BTNode<T> const *const t), BTNode<T> const *const t)const {
  if (t) {
    inOrder(visit, t->lChild);
    visit(t);
    inOrder(visit, t->rChild);
  }
}

template<typename T> void BinaryTree<T>::postOrder(void(*visit)(BTNode<T> const *const t))const {
  postOrder(visit, root);
  cout << endl;
}

template<typename T> void BinaryTree<T>::postOrder(void(*visit)(BTNode<T> const *const t), BTNode<T> const *const t)const {
  if (t) {
    postOrder(visit, t->lChild);
    postOrder(visit, t->rChild);
    visit(t);
  }
}

template<typename T> void BinaryTree<T>::levelOrder(void(*visit)(BTNode<T> const *const t))const {
  SeqQueue<BTNode<T> *> que((1 << (height() - 1)) + 1); //利用队列作为辅助的数据结构
  BTNode<T> *tmp;
  if (root) { que.push(root); }
  while (!que.isEmpty()) {
    que.front(tmp); que.pop();
    visit(tmp);
    if (tmp->lChild) { que.push(tmp->lChild); }
    if (tmp->rChild) { que.push(tmp->rChild); }
  }
  cout << endl;
}

template<typename T> int BinaryTree<T>::height()const {
  return height(root);
}

template<typename T> int BinaryTree<T>::height(BTNode<T> const *const t)const {
  int l, r;
  return t ? 1 + ((l = height(t->lChild)) > (r = height(t->rChild)) ? l : r) : 0;
}

template<typename T> int BinaryTree<T>::leafNum()const {
  return leafNum(root);
}

template<typename T> int BinaryTree<T>::leafNum(BTNode<T> const *const t)const {
  if (!t) { return 0; }
  if (!t->lChild && !t->rChild) { return 1; }
  return leafNum(t->lChild) + leafNum(t->rChild);
}

template<typename T> void BinaryTree<T>::copyTo(BinaryTree<T> &r)const {
  r.clear();
  r.root = copyTo(root);
}

template<typename T> BTNode<T> *BinaryTree<T>::copyTo(BTNode<T> const *const t)const {
  if (!t) { return NULL; }
  BTNode<T> *r = new BTNode<T>(t->element, copyTo(t->lChild), copyTo(t->rChild));
  return r;
}

template<typename T> void BinaryTree<T>::invert() {
  invert(root);
}

template<typename T> void BinaryTree<T>::invert(BTNode<T> *t) {
  if (t) {
    invert(t->lChild);
    invert(t->rChild);
    swap(t->lChild, t->rChild);
  }
}

template<typename T> void visit(BTNode<T> const *const t) { //
  cout << t->element << ' ';
}

#endif