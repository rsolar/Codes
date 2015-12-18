#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
using namespace std;

vector<vector<bool> > generateMap(const int n) { //随机生成无向图
  vector<vector<bool> > mp(n, vector<bool>(n));
  srand((unsigned)time(NULL));
  for (size_t i = 0; i < mp.size(); i++) {
    for (size_t j = i + 1; j < mp[i].size(); j++) {
      mp[i][j] = mp[j][i] = rand() & 1;
    }
  }
  return mp;
}

void dfs1(int u, const vector<vector<bool> > &mp, vector<bool> &vis) { //DFS
  vis[u] = true;
  for (size_t v = 0; v < mp.size(); v++) {
    if (mp[u][v] && !vis[v]) { dfs1(v, mp, vis); }
  }
}

bool isConnected(const vector<vector<bool> > &mp) { //判断无向图连通性
  vector<bool> vis(mp.size());
  dfs1(0, mp, vis);
  return all_of(vis.begin(), vis.end(), [](bool x) { return x; });
}

vector<int> calcDegree(const vector<vector<bool> > &mp) { //计算各结点的度
  vector<int> degree(mp.size());
  for (size_t i = 0; i < mp.size(); i++) {
    for (size_t j = 0; j < mp[i].size(); j++) { degree[i] += mp[i][j]; }
  }
  return degree;
}

bool isEulerianGraph(const vector<int> &degree) { //判断是否(半)欧拉图
  int count = 0;
  for (size_t i = 0; i < degree.size(); i++) { count += degree[i] & 1; }
  return count == 0 || count == 2;
}

void dfs2(int u, vector<vector<bool> > &mp, vector<int> &path) { //DFS
  for (int v; (v = find(mp[u].begin(), mp[u].end(), true) - mp[u].begin()) != mp.size(); mp[u][v] = mp[v][u] = false, dfs2(v, mp, path));
  path.push_back(u + 1);
}

vector<int> getEulerianPath(vector<vector<bool> > mp, const vector<int> &degree) { //Hierholzer算法求欧拉路径/回路
  vector<int> path;
  auto ptr = find_if(degree.begin(), degree.end(), [](int x) { return x & 1; });
  dfs2(ptr == degree.end() ? 0 : *ptr, mp, path);
  return path;
}

int main() {
  int n;
  while (cout << "请输入结点数, 输入非正数退出程序: ", cin >> n) {
    if (n <= 0) { break; }
    vector<vector<bool> > mp = generateMap(n);
    cout << endl << "生成的无向图的邻接矩阵为:" << endl;
    for (size_t i = 0; i < mp.size(); i++) {
      for (size_t j = 0; j < mp[i].size(); j++) {
        cout << mp[i][j] << (j == mp[i].size() - 1 ? '\n' : ' ');
      }
    }
    if (isConnected(mp)) {
      cout << endl << "该图是连通图." << endl;
      vector<int> degree = calcDegree(mp);
      if (isEulerianGraph(degree)) {
        vector<int> path = getEulerianPath(mp, degree);
        cout << (path.front() == path.back() ? "该图是欧拉图, 一条欧拉回路为:" : "该图是半欧拉图, 一条欧拉路径为:") << endl;
        for (size_t i = 0; i < path.size(); i++) {
          cout << path[i] << (i == path.size() - 1 ? "\n\n" : " ");
        }
      } else {
        cout << "该图不是(半)欧拉图." << endl << endl;
      }
    } else {
      cout << endl << "该图不是连通图." << endl << endl;
    }
  }
  return 0;
}
