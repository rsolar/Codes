//main.cpp
#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
  //freopen("input1.txt", "r", stdin);
  //freopen("input2.txt", "r", stdin);
  bool dir;
  int n, e, u, v;
  for (char c;;) {
    cout << "�Ƿ�����ͼ(Y / N)? ";
    cin >> c; c = toupper(c);
    if (c == 'Y' || c == 'N') { dir = c == 'Y'; break; }
  }
  do {
    cout << "�����붥����(n >= 1): ";
    cin >> n;
  } while (n < 1);
  do {
    cout << "���������(e >= 0): ";
    cin >> e;
  } while (e < 0);
  MGraph<int> mg(n, INF);
  LGraph<int> lg(n);
  cout << "����������ߵ���㡢�յ�(0 <= u, v < n, u != v):" << endl;
  for (int i = 0; i < e; i++) {
    cin >> u >> v;
    if (u >= 0 && u < n && v >= 0 && v < n && u != v && !mg.exist(u, v) && !lg.exist(u, v)) {
      mg.insert(u, v, 1); lg.insert(u, v, 1);
      if (!dir) { mg.insert(v, u, 1); lg.insert(v, u, 1); }
    } else {
      i--; cout << "������Ч!" << endl;
    }
  }
  cout << endl << "��ͼ���ڽӾ�������:" << endl;
  mg.print();
  cout << endl << "��ͼ���ڽӾ���ʵ�ֵ�������ȱ������:" << endl;
  mg.DFS();
  cout << endl << "��ͼ���ڽӱ�ʵ�ֵ�������ȱ������:" << endl;
  lg.DFS();
  cout << endl << "��ͼ���ڽӾ���ʵ�ֵĹ�����ȱ������:" << endl;
  mg.BFS();
  cout << endl << "��ͼ���ڽӱ�ʵ�ֵĹ�����ȱ������:" << endl;
  lg.BFS();
  cout << endl;
  return 0;
}
