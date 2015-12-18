#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template<typename T> T getGCD(T a, T b) { //�����Լ��
  return a == 0 ? b : getGCD(b % a, a);
}

template<typename T> vector<T> getFactor(const T &n) { //��n���������� O(sqrt(n))
  vector<T> fac;
  for (T i = 1; i * i <= n; i++) {
    if (n % i == 0) {
      fac.push_back(i);
      if (i * i != n) { fac.push_back(n / i); }
    }
  }
  sort(fac.begin(), fac.end());
  return fac;
}

template<typename T> void printCoveringRelation(const vector<T> &fac) { //��ӡ���и�ס��ϵ
  cout << "{";
  bool first = true;
  for (size_t i = 0; i < fac.size(); i++) {
    for (size_t j = i + 1; j < fac.size(); j++) {
      if (fac[j] % fac[i] == 0) {
        bool flag = true;
        for (size_t k = i + 1; k < j; k++) {
          if (fac[j] % fac[k] == 0 && fac[k] % fac[i] == 0) { flag = false; }
        }
        if (flag) {
          cout << (first ? "<" : ", <") << fac[i] << ", " << fac[j] << ">";
          first = false;
        }
      }
    }
  }
  cout << "}" << endl;
}

template<typename T> bool isComplementedLattice(const vector<T> &fac) {
  if (fac.size() < 2) { return false; }
  for (size_t i = 0; i < fac.size(); i++) {
    for (size_t j = i + 1; j < fac.size(); j++) {
      T gcd = getGCD(fac[i], fac[j]);
      T lcm = fac[i] / gcd * fac[j];
      if (gcd != fac.front() || lcm != fac.back()) { return false; }
    }
  }
  return true;
}

int main() {
  long long n;
  while (cout << endl << "������һ��������(n < 2^63): ", cin >> n) {
    if (n <= 0) { continue; }
    vector<long long> fac = getFactor(n);
    cout << endl << "�����������ӹ��ɵļ���Ϊ:" << endl;
    for (size_t i = 0; i < fac.size(); i++) {
      cout << fac[i] << (i != fac.size() - 1 ? ' ' : '\n');
    }
    cout << endl << "��ƫ���ϵĸ�ס��ϵΪ:" << endl;
    printCoveringRelation(fac);
    cout << endl << (isComplementedLattice(fac) ? "�ø����в���" : "�ø����в���") << endl;
  }
  return 0;
}
