#include <iostream>
#include <cstring>
using namespace std;

const int MAXLEN = 10005;

class LCS {
public:
  LCS(int nx, int ny, char *x, char *y); //������ά����c��s��һά����a��b�������г�ʼ��
  ~LCS();
  int LCSLength();                       //�����Ž�ֵ������������г��ȣ�
  void CLCS();                           //�������Ž⣨����������У�

private:
  void CLCS(int i, int j);
  int **c, **s, m, n;
  char *a, *b;
};

LCS::LCS(int nx, int ny, char *x, char *y) :c(new int*[nx + 1]), s(new int*[nx + 1]), m(nx), n(ny), a(new char[m + 2]), b(new char[n + 2]) {
  for (int i = 0; i <= m; i++) { c[i] = new int[ny + 1]; s[i] = new int[ny + 1]; }
  for (int i = 1; i <= m; i++) { a[i] = x[i - 1]; }
  for (int i = 1; i <= n; i++) { b[i] = y[i - 1]; }
}

LCS::~LCS() {
  for (int i = 0; i <= m; i++) { delete[] c[i]; delete[] s[i]; }
  delete[] c; delete[] s; delete[] a; delete[] b;
}

int LCS::LCSLength() {
  for (int i = 1; i <= m; i++) { c[i][0] = 0; }
  for (int i = 1; i <= n; i++) { c[0][i] = 0; }
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (a[i] == b[j]) {
        c[i][j] = c[i - 1][j - 1] + 1; s[i][j] = 1; //��c[i-1][j-1]����c[i][j]
      } else if (c[i - 1][j] >= c[i][j - 1]) {
        c[i][j] = c[i - 1][j]; s[i][j] = 2;         //��c[i-1][j]�õ�c[i][j]
      } else {
        c[i][j] = c[i][j - 1]; s[i][j] = 3;         //��c[i][j-1]�õ�c[i][j]
      }
    }
  }
  return c[m][n];                                   //�������Ž�ֵ
}

void LCS::CLCS() {
  CLCS(m, n);
}

void LCS::CLCS(int i, int j) {
  if (i == 0 || j == 0) { return; }
  if (s[i][j] == 1) {
    CLCS(i - 1, j - 1);
    cout << a[i];
  } else if (s[i][j] == 2) {
    CLCS(i - 1, j);
  } else {
    CLCS(i, j - 1);
  }
}

int main() {
  int nx, ny;
  char *x = new char[MAXLEN], *y = new char[MAXLEN];
  cout << "������X�������ո񣩣�";
  cin >> x;
  nx = strlen(x);
  cout << "������Y�������ո񣩣�";
  cin >> y;
  ny = strlen(y);
  cout << endl;
  LCS lcs(nx, ny, x, y);
  cout << "X��Y������������г���Ϊ" << lcs.LCSLength() << endl;
  cout << "�����������Ϊ";
  lcs.CLCS();
  cout << endl;
  delete[] x; delete[] y;
  return 0;
}
