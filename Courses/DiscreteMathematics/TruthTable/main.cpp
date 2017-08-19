#include <iostream>
using namespace std;

const int maxn = 6; //֧������Ԫ����
const int maxrow = 1 << 6; //��ֵ���������
const char varible[] = { 'P', 'Q', 'R', 'S', 'T', 'U' }; //��Ԫ����
int n, row; //��Ԫ����, ��ֵ������
bool table[maxrow][maxn + 1]; //��ֵ��
int pdnf[maxrow], dnfcnt; //����ȡ��ʽ
int pcnf[maxrow], cnfcnt; //����ȡ��ʽ

void input() { //����
  cnfcnt = dnfcnt = 0;
  while (cout << "�������Ԫ����n (2 <= n <= 6): ", cin >> n) {
    if (n >= 2 && n <= maxn) { break; }
    cout << endl << "��������ȷ�ı�Ԫ����!" << endl << endl;
  }
  row = 1 << n;
  cout << endl << "��������ʽ����ֵ��(0Ϊ��, ��0Ϊ��):" << endl;
  for (int i = 0, t; i < row; i++) {
    cin >> t;
    (table[i][n] = t != 0) ? (pdnf[dnfcnt++] = i) : (pcnf[cnfcnt++] = i);
  }
}

void printTable() { //�����ֵ��
  cout << endl << "��ֵ��:" << endl;
  for (int i = 0; i < n; i++) {
    cout << varible[i] << '\t';
  }
  cout << "���ʽ" << endl;
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

void printDNF() { //�������ȡ��ʽ
  cout << "����ȡ��ʽ:" << endl;
  for (int i = 0; i < dnfcnt; i++) {
    cout << (i ? " �� m" : "m") << pdnf[i];
  }
  cout << endl << endl;
}

void printCNF() { //�������ȡ��ʽ
  cout << "����ȡ��ʽ:" << endl;
  for (int i = 0; i < cnfcnt; i++) {
    cout << (i ? " �� M" : "M") << pcnf[i];
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
