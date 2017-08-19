//Graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

using std::vector;

const int INF = 0x3f3f3f3f;
enum ResultCode { Success, Failure, Duplicate, NotPresent, OutOfBounds };

template<typename T> class Graph { //ͼ������
public:
  Graph(int mSize) :n(mSize) {};
  virtual ResultCode insert(int u, int v, T const &w) = 0;
  virtual ResultCode remove(int u, int v) = 0;
  virtual bool exist(int u, int v)const = 0;
  virtual int verticeNum()const { return n; }
  virtual int edgeNum()const { return e; }
protected:
  int n, e; //n��ͼ�ж�����, e�Ǳ���, �����ŷ�ΧΪ[0, n - 1]
};

template<typename T> class MGraph : public Graph<T> { //ͼ���ڽӾ�����
public:
  MGraph(int mSize, T const &noedge) : Graph(mSize), noEdge(noedge), a(n) {
    for (int i = 0; i < n; i++) {
      a[i].resize(n, noEdge); a[i][i] = 0;
    }
  }
  ~MGraph() {}
  ResultCode insert(int u, int v, T const &w); //�ߵĲ���
  ResultCode remove(int u, int v); //�ߵ�ɾ��
  bool exist(int u, int v)const; //�б��Ƿ����
  void Dijkstra(int src, vector<T> &dist, vector<int> &pre)const; //Dijkstra�㷨��Դ���·
protected:
  vector<vector<T> > a; //��̬��ά����
  T noEdge; //�������ޱ�ʱ��ֵ(0��INF)
};

template<typename T> ResultCode MGraph<T>::insert(int u, int v, T const &w) {
  if (u < 0 || v < 0 || u >= n || v >= n || u == v) { return Failure; }
  if (a[u][v] != noEdge) { return Duplicate; }
  a[u][v] = w; e++;
  return Success;
}

template<typename T> ResultCode MGraph<T>::remove(int u, int v) {
  if (u < 0 || v < 0 || u >= n || v >= n || u == v) { return Failure; }
  if (a[u][v] == noEdge) { return NotPresent; }
  a[u][v] = noEdge; e--;
  return Success;
}

template<typename T> bool MGraph<T>::exist(int u, int v)const {
  if (u < 0 || v < 0 || u >= n || v >= n || u == v || a[u][v] == noEdge) { return false; }
  return true;
}

template<typename T> void MGraph<T>::Dijkstra(int src, vector<T> &dist, vector<int> &pre)const {
  if (src < 0 || src >= n) { throw OutOfBounds; }
  vector<bool> visited(n, false);
  std::fill(dist.begin(), dist.end(), INF);
  std::fill(pre.begin(), pre.end(), -1);
  dist[src] = 0;
  for (int i = 0; i < n; i++) {
    int k = -1, mn = INF;
    for (int u = 0; u < n; u++) {
      if (!visited[u] && dist[u] < mn) { mn = dist[u]; k = u; }
    }
    if (k == -1) { break; }
    visited[k] = true;
    for (int v = 0; v < n; v++) {
      if (!visited[v] && dist[k] + a[k][v] < dist[v]) {
        dist[v] = dist[k] + a[k][v]; pre[v] = k;
      }
    }
  }
}

#endif
