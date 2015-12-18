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
    cout << "是否有向图(Y / N)? ";
    cin >> c; c = toupper(c);
    if (c == 'Y' || c == 'N') { dir = c == 'Y'; break; }
  }
  do {
    cout << "请输入顶点数(n >= 1): ";
    cin >> n;
  } while (n < 1);
  do {
    cout << "请输入边数(e >= 0): ";
    cin >> e;
  } while (e < 0);
  MGraph<int> mg(n, INF);
  LGraph<int> lg(n);
  cout << "请依次输入边的起点、终点(0 <= u, v < n, u != v):" << endl;
  for (int i = 0; i < e; i++) {
    cin >> u >> v;
    if (u >= 0 && u < n && v >= 0 && v < n && u != v && !mg.exist(u, v) && !lg.exist(u, v)) {
      mg.insert(u, v, 1); lg.insert(u, v, 1);
      if (!dir) { mg.insert(v, u, 1); lg.insert(v, u, 1); }
    } else {
      i--; cout << "输入无效!" << endl;
    }
  }
  cout << endl << "该图的邻接矩阵如下:" << endl;
  mg.print();
  cout << endl << "该图的邻接矩阵实现的深度优先遍历结果:" << endl;
  mg.DFS();
  cout << endl << "该图的邻接表实现的深度优先遍历结果:" << endl;
  lg.DFS();
  cout << endl << "该图的邻接矩阵实现的广度优先遍历结果:" << endl;
  mg.BFS();
  cout << endl << "该图的邻接表实现的广度优先遍历结果:" << endl;
  lg.BFS();
  cout << endl;
  return 0;
}
