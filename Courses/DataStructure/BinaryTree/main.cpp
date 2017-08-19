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
  cout << "ԭ��������ǰ��������: ";
  z.preOrder(visit);

  BinaryTree<char> obj;
  z.copyTo(obj);
  cout << endl << "�ѽ�ԭ���������Ƶ��¶�������" << endl;
  cout << endl << "�������ĸ߶�Ϊ: " << obj.height() << endl;
  cout << "��������Ҷ�ӽ����Ϊ: " << obj.leafNum() << endl;
  cout << endl << "ǰ��������: ";
  obj.preOrder(visit);
  cout << "����������: ";
  obj.inOrder(visit);
  cout << "����������: ";
  obj.postOrder(visit);
  cout << "��α������: ";
  obj.levelOrder(visit);
  obj.invert();
  cout << endl << "��ת���������ǰ��������: ";
  obj.preOrder(visit);
  cout << "ɾ�����������ǰ��������: ";
  obj.clear();
  obj.preOrder(visit);
  cout << endl;
  return 0;
}