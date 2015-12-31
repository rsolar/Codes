#include <iostream>
#include <vector>
using namespace std;

class Matrix {
public:
  Matrix(const size_t &n) :a(n) { for (auto &r : a) { r.resize(n); } }
  friend istream &operator>>(istream &in, Matrix &m) {
    for (size_t i = 0; i < m.a.size(); i++) {
      for (size_t j = 0; j < m.a.size(); j++) {
        int tmp; in >> tmp; m.a[i][j] = tmp != 0;
      }
    }
    return in;
  }
  bool isReflexive() { //自反性
    for (size_t i = 0; i < a.size(); i++) {
      if (!a[i][i]) { return false; }
    }
    return true;
  }
  bool isIrreflexive() { //反自反性
    for (size_t i = 0; i < a.size(); i++) {
      if (a[i][i]) { return false; }
    }
    return true;
  }
  bool isSymmetric() { //对称性
    for (size_t i = 0; i < a.size(); i++) {
      for (size_t j = i + 1; j < a.size(); j++) {
        if (a[i][j] != a[j][i]) { return false; }
      }
    }
    return true;
  }
  bool isAntisymmetric() { //反对称性
    for (size_t i = 0; i < a.size(); i++) {
      for (size_t j = i + 1; j < a.size(); j++) {
        if (a[i][j] && a[j][i]) { return false; }
      }
    }
    return true;
  }
  bool isTransitive() { //传递性
    for (size_t i = 0; i < a.size(); i++) {
      for (size_t j = 0; j < a.size(); j++) {
        if (a[i][j]) {
          for (size_t k = 0; k < a.size(); k++) {
            if (a[j][k] && !a[i][k]) { return false; }
          }
        }
      }
    }
    return true;
  }
private:
  vector<vector<bool> > a;
};

int main() {
  int n;
  while (cout << "请输入集合中的元素数量n, 输入负数退出程序: ", cin >> n) {
    if (n < 0) { break; }
    Matrix m(n);
    if (n > 0) {
      cout << endl << "请输入该集合上的关系矩阵(0代表假, 非0代表真):" << endl;
      cin >> m;
    }
    cout << endl << "该关系是:";
    if (m.isReflexive()) { cout << " 自反的"; }
    if (m.isIrreflexive()) { cout << " 反自反的"; }
    if (m.isSymmetric()) { cout << " 对称的"; }
    if (m.isAntisymmetric()) { cout << " 反对称的"; }
    if (m.isTransitive()) { cout << " 传递的"; }
    cout << endl << endl;
  }
  return 0;
}
