//main.cpp
#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
  //freopen("input.txt", "r", stdin);
  int n, e, u, v;
  do {
    cout << "�����������(n >= 1): ";
    cin >> n;
  } while (n < 1);
  do {
    cout << "�����뺽����(e >= 0): ";
    cin >> e;
  } while (e < 0);
  MGraph<int> mg(n, INF);
  cout << "����������ÿ�����ߵ���㡢�յ�(0 <= u, v < n, u != v):" << endl;
  for (int i = 0; i < e; i++) {
    cin >> u >> v;
    if (u >= 0 && u < n && v >= 0 && v < n && u != v && !mg.exist(u, v)) {
      mg.insert(u, v, 1);
    } else {
      i--; cout << "��Ч����!" << endl;
    }
  }
  while (cout << endl << "��������Ҫ��ѯ�������յ���(0 <= u, v < n, u != v), ����\"0 0\"��������: ", cin >> u >> v) {
    if (u == 0 && v == 0) { break; }
    if (u < 0 || u >= n || v < 0 || v >= n || u == v) { cout << "��Ч����!" << endl; continue; }
    vector<int> dist(n);
    vector<int> pre(n);
    mg.Dijkstra(u, dist, pre);
    if (dist[v] == INF) { cout << endl << "�����ڴӳ���" << u << "������" << v << "��·��!" << endl; continue; }
    vector<int> path;
    for (int i = v; ~i; i = pre[i]) { path.push_back(i); }
    cout << endl << "�ӳ���" << u << "������" << v << "���ٻ���" << dist[v] - 1 << "��, ��·����Ϊ:" << endl;
    for (int i = path.size() - 1; i >= 0; i--) { cout << path[i] << (i == 0 ? "\n" : "->"); }
  }
  return 0;
}
