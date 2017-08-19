#include <iostream>
using namespace std;

const int maxn = 6; //支持最大变元数量
const int maxrow = 1 << 6; //真值表最大行数
const char varible[] = { 'P', 'Q', 'R', 'S', 'T', 'U' }; //变元符号
int n, row; //变元数量, 真值表行数
bool table[maxrow][maxn + 1]; //真值表
int pdnf[maxrow], dnfcnt; //主合取范式
int pcnf[maxrow], cnfcnt; //主析取范式

void input() { //输入
  cnfcnt = dnfcnt = 0;
  while (cout << "请输入变元个数n (2 <= n <= 6): ", cin >> n) {
    if (n >= 2 && n <= maxn) { break; }
    cout << endl << "请输入正确的变元个数!" << endl << endl;
  }
  row = 1 << n;
  cout << endl << "请输入表达式的真值表(0为假, 非0为真):" << endl;
  for (int i = 0, t; i < row; i++) {
    cin >> t;
    (table[i][n] = t != 0) ? (pdnf[dnfcnt++] = i) : (pcnf[cnfcnt++] = i);
  }
}

void printTable() { //输出真值表
  cout << endl << "真值表:" << endl;
  for (int i = 0; i < n; i++) {
    cout << varible[i] << '\t';
  }
  cout << "表达式" << endl;
  for (int i = 0; i < row; i++) {
    for (int j = n - 1, tmp = row - 1 - i; j >= 0; j--) {
      table[i][j] = tmp & 1; tmp >>= 1;
    }
  }
  for (int i = 0; i < row; i++) {
    for (int j = 0; j <= n; j++) {
      cout << table[i][j] << (j == n ? '\n' : '\t');
    }
  }
  cout << endl;
}

void printDNF() { //输出主析取范式
  cout << "主析取范式:" << endl;
  for (int i = 0; i < dnfcnt; i++) {
    cout << (i ? " ∨ m" : "m") << pdnf[i];
  }
  cout << endl << endl;
}

void printCNF() { //输出主合取范式
  cout << "主合取范式:" << endl;
  for (int i = 0; i < cnfcnt; i++) {
    cout << (i ? " ∧ M" : "M") << pcnf[i];
  }
  cout << endl << endl;
}

int main() {
  input();
  printTable();
  printDNF();
  printCNF();
  return 0;
}
