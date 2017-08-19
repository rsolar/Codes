#include <iostream>
#include <cmath>
using namespace std;

int cnt;

bool Place(int k, int i, int *x) {
  for (int j = 0; j < k; j++) {
    if (x[j] == i || abs(x[j] - i) == abs(j - k)) {
      return false;
    }
  }
  return true;
}

void NQueens(int k, int n, int *x) {
  for (int i = 0; i < n; i++) {
    if (Place(k, i, x)) {
      x[k] = i;
      if (k == n - 1) {
        for (i = 0; i < n; i++) { cout << x[i] << " "; }
        cout << endl;
        cnt++;
      } else {
        NQueens(k + 1, n, x);
      }
    }
  }
}

void NQueens(int n, int *x) {
  NQueens(0, n, x);
}

int main() {
  int n;
  cout << "n = ";
  cin >> n;
  int *x = new int[n];
  for (int i = 0; i < n; i++) { x[i] = -1; }
  cnt = 0;
  NQueens(n, x);
  cout << n << "-皇后共" << cnt << "个可行解。" << endl;
  delete[] x;
  return 0;
}
