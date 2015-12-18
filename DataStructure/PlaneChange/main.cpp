//main.cpp
#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
  //freopen("input.txt", "r", stdin);
  int n, e, u, v;
  do {
    cout << "请输入城市数(n >= 1): ";
    cin >> n;
  } while (n < 1);
  do {
    cout << "请输入航线数(e >= 0): ";
    cin >> e;
  } while (e < 0);
  MGraph<int> mg(n, INF);
  cout << "请依次输入每条航线的起点、终点(0 <= u, v < n, u != v):" << endl;
  for (int i = 0; i < e; i++) {
    cin >> u >> v;
    if (u >= 0 && u < n && v >= 0 && v < n && u != v && !mg.exist(u, v)) {
      mg.insert(u, v, 1);
    } else {
      i--; cout << "无效输入!" << endl;
    }
  }
  while (cout << endl << "请输入想要查询的起点和终点编号(0 <= u, v < n, u != v), 输入\"0 0\"结束程序: ", cin >> u >> v) {
    if (u == 0 && v == 0) { break; }
    if (u < 0 || u >= n || v < 0 || v >= n || u == v) { cout << "无效输入!" << endl; continue; }
    vector<int> dist(n);
    vector<int> pre(n);
    mg.Dijkstra(u, dist, pre);
    if (dist[v] == INF) { cout << endl << "不存在从城市" << u << "到城市" << v << "的路线!" << endl; continue; }
    vector<int> path;
    for (int i = v; ~i; i = pre[i]) { path.push_back(i); }
    cout << endl << "从城市" << u << "到城市" << v << "最少换乘" << dist[v] - 1 << "次, 线路方案为:" << endl;
    for (int i = path.size() - 1; i >= 0; i--) { cout << path[i] << (i == 0 ? "\n" : "->"); }
  }
  return 0;
}
