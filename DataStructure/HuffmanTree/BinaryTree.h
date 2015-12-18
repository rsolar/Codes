//BinaryTree.h
#ifndef BTREE_H
#define BTREE_H

#include <iostream>

template<typename T> struct BTNode { //�����������
  T element;
  BTNode<T> *lChild, *rChild, *parent;

  BTNode() :lChild(NULL), rChild(NULL), parent(NULL) {}
  BTNode(T const &x) :element(x), lChild(NULL), rChild(NULL), parent(NULL) {}
  BTNode(T const &x, BTNode<T> *l, BTNode<T> *r) :element(x), lChild(l), rChild(r), parent(NULL) {
    if (l) { l->parent = this; }
    if (r) { r->parent = this; }
  }
};

template<typename T> class BinaryTree { //��������
public:
  BinaryTree() :root(NULL) {} //���캯��
  BinaryTree(BinaryTree<T> const &r) { this->copyTo(r); } //�������캯��
  ~BinaryTree() { clear(); } //��������
  bool isEmpty()const { return root == NULL; } //�ж϶������Ƿ�Ϊ��
  void clear(); //ɾ��������
  void makeTree(T const &x, BinaryTree<T> &left, BinaryTree<T> &right); //���������
  void breakTree(T &x, BinaryTree<T> &left, BinaryTree<T> &right); //��ֶ�����
  void preOrder(void(*visit)(BTNode<T> const *const t))const; //ǰ�����
  void inOrder(void(*visit)(BTNode<T> const *const t))const; //�������
  void copyTo(BinaryTree<T> &r)const; //���ƶ�����

protected:
  BTNode<T> *root;

private:
  void clear(BTNode<T> *&t);
  void preOrder(void(*visit)(BTNode<T> const *const t), BTNode<T> const *const t)const;
  void inOrder(void(*visit)(BTNode<T> const *const t), BTNode<T> const *const t)const;
  BTNode<T> *copyTo(BTNode<T> const *const t)const;
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

template<typename T> void BinaryTree<T>::copyTo(BinaryTree<T> &r)const {
  r.clear();
  r.root = copyTo(root);
}

template<typename T> BTNode<T> *BinaryTree<T>::copyTo(BTNode<T> const *const t)const {
  if (!t) { return NULL; }
  BTNode<T> *r = new BTNode<T>(t->element, copyTo(t->lChild), copyTo(t->rChild));
  return r;
}

template<typename T> void visit(BTNode<T> const *const t) { //
  cout << t->element << ' ';
}

#endif
