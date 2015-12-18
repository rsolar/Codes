//Graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <iomanip>
#include <vector>
#include "SeqQueue.h"

using std::vector;

const int INF = 0x3f3f3f3f;
enum ResultCode { Success, Failure, Duplicate, NotPresent };

template<typename T> class Graph { //图抽象类
public:
  Graph(int mSize) :n(mSize) {};
  virtual ResultCode insert(int u, int v, T const &w) = 0;
  virtual ResultCode remove(int u, int v) = 0;
  virtual bool exist(int u, int v)const = 0;
  virtual int verticeNum()const { return n; }
  virtual int edgeNum()const { return e; }
protected:
  int n, e; //n是图中顶点数, e是边数, 顶点编号范围为[0, n - 1]
};

template<typename T> class MGraph : public Graph<T> { //图的邻接矩阵类
public:
  MGraph(int mSize, T const &noedge) : Graph(mSize), noEdge(noedge), a(n) {
    for (int i = 0; i < n; i++) {
      a[i].resize(n, noEdge); a[i][i] = 0;
    }
  }
  ~MGraph() {}
  ResultCode insert(int u, int v, T const &w); //边的插入
  ResultCode remove(int u, int v); //边的删除
  bool exist(int u, int v)const; //判边是否存在
  void print()const; //打印邻接矩阵
  void DFS()const; //深度优先遍历图
  void BFS()const; //宽度优先遍历图
protected:
  vector<vector<T> > a; //动态二维数组
  T noEdge; //两结点间无边时的值(0 或 INF)
private:
  void DFS(int u, vector<bool> &visited)const;
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

template<typename T> void MGraph<T>::print()const {
  using std::cout;
  using std::setw;
  cout << "u\\v";
  for (int u = 0; u < n; u++) { cout << setw(3) << u; }
  cout << endl;
  for (int u = 0; u < n; u++) {
    cout << setw(3) << u;
    for (int v = 0; v < n; v++) {
      if (a[u][v] == INF) { cout << " ∞"; }
      else { cout << setw(3) << a[u][v]; }
    }
    cout << endl;
  }
}

template<typename T> void MGraph<T>::DFS()const {
  vector<bool> visited(n, false);
  for (int u = 0; u < n; u++) {
    if (!visited[u]) { DFS(u, visited); }
  }
  cout << endl;
}

template<typename T> void MGraph<T>::DFS(int u, vector<bool> &visited)const {
  visited[u] = true;
  cout << u << ' ';
  for (int v = 0; v < n; v++) {
    if (exist(u, v) && !visited[v]) { DFS(v, visited); }
  }
}

template<typename T> void MGraph<T>::BFS()const {
  vector<bool> visited(n, false);
  SeqQueue<int> que(n);
  for (int u = 0, t; u < n; u++) {
    if (!visited[u]) {
      visited[u] = true;
      que.push(u);
      while (!que.isEmpty()) {
        que.front(t); que.pop();
        cout << t << ' ';
        for (int v = 0; v < n; v++) {
          if (exist(t, v) && !visited[v]) {
            visited[v] = true; que.push(v);
          }
        }
      }
    }
  }
  cout << endl;
}

template<typename T> struct ENode { //边结点类
  ENode() :nextArc(NULL) {}
  ENode(int vertex, T const &weight, ENode *next) :adjVex(vertex), w(weight), nextArc(next) {}
  int adjVex;
  T w;
  ENode *nextArc;
};

template<typename T> class LGraph :public Graph<T> { //图的邻接表类
public:
  LGraph(int mSize) :Graph(mSize) { a.resize(n, NULL); }
  ~LGraph() {
    for (int i = 0; i < n; i++) {
      for (ENode<T> *p = a[i], *q = p; p; p = p->nextArc, delete q, q = p);
    }
  }
  ResultCode insert(int u, int v, T const &w); //边的插入
  ResultCode remove(int u, int v); //边的删除
  bool exist(int u, int v)const; //判边是否存在
  void DFS()const; //深度优先遍历图
  void BFS()const; //宽度优先遍历图
protected:
  vector<ENode<T> *> a; //动态一维指针数组
private:
  void DFS(int u, vector<bool> &visited)const;
};

template<typename T> ResultCode LGraph<T>::insert(int u, int v, T const &w) {
  if (u < 0 || v < 0 || u >= n || v >= n || u == v) { return Failure; }
  if (exist(u, v)) { return Duplicate; }
  a[u] = new ENode<T>(v, w, a[u]); e++;
  return Success;
}

template<typename T> ResultCode LGraph<T>::remove(int u, int v) {
  if (u < 0 || v < 0 || u >= n || v >= n || u == v) { return Failure; }
  ENode<T> *p = a[u], *q = NULL;
  while (p && p->adjVex != v) { q = p; p = p->nextArc; }
  if (!p) { return NotPresent; }
  if (q) {
    q->nextArc = p->nextArc;
  } else {
    a[u] = p->nextArc;
  }
  delete p; e--;
  return Success;
}

template<typename T> bool LGraph<T>::exist(int u, int v)const {
  if (u < 0 || v < 0 || u >= n || v >= n || u == v) { return false; }
  ENode<T> *p = a[u];
  while (p && p->adjVex != v) { p = p->nextArc; }
  return p != NULL;
}

template<typename T> void LGraph<T>::DFS()const {
  vector<bool> visited(n, false);
  for (int u = 0; u < n; u++) {
    if (!visited[u]) { DFS(u, visited); }
  }
  cout << endl;
}

template<typename T> void LGraph<T>::DFS(int u, vector<bool> &visited)const {
  visited[u] = true;
  cout << u << ' ';
  for (ENode<T> *v = a[u]; v; v = v->nextArc) {
    if (!visited[v->adjVex]) { DFS(v->adjVex, visited); }
  }
}

template <typename T> void LGraph<T>::BFS()const {
  vector<bool> visited(n, false);
  SeqQueue<int> que(n);
  for (int u = 0, t; u < n; u++) {
    if (!visited[u]) {
      visited[u] = true;
      que.push(u);
      while (!que.isEmpty()) {
        que.front(t); que.pop();
        cout << t << ' ';
        for (ENode<T> *v = a[t]; v; v = v->nextArc) {
          if (!visited[v->adjVex]) {
            visited[v->adjVex] = true; que.push(v->adjVex);
          }
        }
      }
    }
  }
  cout << endl;
}

#endif
