//main.cpp
#include "BinaryTree.h"

using namespace std;

int main() {
  BinaryTree<char> a, b, x, y, z;
  y.makeTree('E', a, b);
  z.makeTree('F', a, b);
  x.makeTree('C', y, z);
  y.makeTree('D', a, b);
  z.makeTree('B', y, x);
  cout << "原二叉树的前序遍历结果: ";
  z.preOrder(visit);

  BinaryTree<char> obj;
  z.copyTo(obj);
  cout << endl << "已将原二叉树复制到新二叉树中" << endl;
  cout << endl << "二叉树的高度为: " << obj.height() << endl;
  cout << "二叉树中叶子结点数为: " << obj.leafNum() << endl;
  cout << endl << "前序遍历结果: ";
  obj.preOrder(visit);
  cout << "中序遍历结果: ";
  obj.inOrder(visit);
  cout << "后序遍历结果: ";
  obj.postOrder(visit);
  cout << "层次遍历结果: ";
  obj.levelOrder(visit);
  obj.invert();
  cout << endl << "翻转二叉树后的前序遍历结果: ";
  obj.preOrder(visit);
  cout << "删除二叉树后的前序遍历结果: ";
  obj.clear();
  obj.preOrder(visit);
  cout << endl;
  return 0;
}