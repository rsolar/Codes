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
  bool isReflexive() { //�Է���
    for (size_t i = 0; i < a.size(); i++) {
      if (!a[i][i]) { return false; }
    }
    return true;
  }
  bool isIrreflexive() { //���Է���
    for (size_t i = 0; i < a.size(); i++) {
      if (a[i][i]) { return false; }
    }
    return true;
  }
  bool isSymmetric() { //�Գ���
    for (size_t i = 0; i < a.size(); i++) {
      for (size_t j = i + 1; j < a.size(); j++) {
        if (a[i][j] != a[j][i]) { return false; }
      }
    }
    return true;
  }
  bool isAntisymmetric() { //���Գ���
    for (size_t i = 0; i < a.size(); i++) {
      for (size_t j = i + 1; j < a.size(); j++) {
        if (a[i][j] && a[j][i]) { return false; }
      }
    }
    return true;
  }
  bool isTransitive() { //������
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
  while (cout << "�����뼯���е�Ԫ������n, ���븺���˳�����: ", cin >> n) {
    if (n < 0) { break; }
    Matrix m(n);
    if (n > 0) {
      cout << endl << "������ü����ϵĹ�ϵ����(0�����, ��0������):" << endl;
      cin >> m;
    }
    cout << endl << "�ù�ϵ��:";
    if (m.isReflexive()) { cout << " �Է���"; }
    if (m.isIrreflexive()) { cout << " ���Է���"; }
    if (m.isSymmetric()) { cout << " �ԳƵ�"; }
    if (m.isAntisymmetric()) { cout << " ���ԳƵ�"; }
    if (m.isTransitive()) { cout << " ���ݵ�"; }
    cout << endl << endl;
  }
  return 0;
}
