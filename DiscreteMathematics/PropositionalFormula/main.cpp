#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <stack>
#include <hash_map>

using namespace std;
using namespace stdext;

const int maxn = 8;

int n;
hash_map<char, int> var;
stack<char> stk;

bool Not(const bool &a) { return !a; } //��
bool And(const bool &a, const bool &b) { return a && b; } //��ȡ
bool Or(const bool &a, const bool &b) { return a || b; } //��ȡ
bool If(const bool &a, const bool &b) { return !a || b; } //����
bool Iff(const bool &a, const bool &b) { return a == b; } //˫����

bool checkStack(const char &out); //�Ƚ�ջ������������ȼ�
void getValue(int v[], int r); //��ֵָ��
void input(string &s); //������ʽ
void toSuffix(string &s); //ת��Ϊ��׺���ʽ
bool calculate(const string &s, const int v[]); //������ʽ
void print(const string &s); //���

int main() {
  string orgf;
  input(orgf);
  toSuffix(orgf);
  print(orgf);
  return 0;
}

bool checkStack(const char &out) {
  char in = stk.top();
  int i, o;
  switch (in) {
    case '#': i = 0; break;
    case '(': i = 1; break;
    case '=': i = 3; break;
    case '>': i = 5; break;
    case '|': i = 7; break;
    case '&': i = 9; break;
    case '!': i = 11; break;
    case ')': i = 12; break;
  }
  switch (out) {
    case '#': o = 0; break;
    case '(': o = 12; break;
    case '=': o = 2; break;
    case '>': o = 4; break;
    case '|': o = 6; break;
    case '&': o = 8; break;
    case '!': o = 10; break;
    case ')': o = 1; break;
  }
  return i < o;
}

void getValue(int v[], int r) {
  for (int i = n - 1; i >= 0; i--) {
    v[i] = r & 1;
    r >>= 1;
  }
}

void input(string &s) {
  cout << "֧�ַ���: ��: !   ��ȡ:   &    ��ȡ: |" << endl;
  cout << "          ����: ->  ˫����: <->  ����: ( )" << endl << endl;
  size_t i;
  while (true) {
    var.clear();
    cout << "��������ʽ����Ԫ�����ִ�Сд: " << endl;
    getline(cin, s);
    while ((i = s.find(' ')) != -1) {
      s.erase(i, 1);
    }
    for (i = 0; i < s.size(); i++) {
      if (s[i] == '-') {
        if (i + 2 < s.size() && s[i + 1] == '>') {
          s.replace(i, 2, ">");
        } else {
          break;
        }
      } else if (s[i] == '<') {
        if (i + 3 < s.size() && s[i + 1] == '-' && s[i + 2] == '>') {
          s.replace(i, 3, "=");
        } else {
          break;
        }
      } else if (isalpha(s[i])) {
        if (i + 1 == s.size() || !isalpha(s[i + 1])) {
          s[i] = toupper(s[i]);
          if (var.find(s[i]) == var.end()) {
            var[s[i]] = n++;
          }
        } else {
          break;
        }
      } else if (s[i] != '!' && s[i] != '&' && s[i] != '|' && s[i] != '(' && s[i] != ')') {
        break;
      }
    }
    if (s.size() != 0 && i == s.size()) {
      break;
    } else {
      cout << endl << "��������ȷ�ı��ʽ!" << endl << endl;
    }
  }
}

void toSuffix(string &s) {
  string ret;
  stk.push('#');
  for (size_t i = 0; i < s.size(); i++) {
    if (isalpha(s[i])) {
      ret += s[i];
    } else if (checkStack(s[i])) {
      stk.push(s[i]);
    } else if (s[i] == ')') {
      while (stk.top() != '(') {
        ret += stk.top(); stk.pop();
      }
      stk.pop();
    } else {
      do {
        ret += stk.top(); stk.pop();
      } while (!checkStack(s[i]));
      stk.push(s[i]);
    }
  }
  while (stk.top() != '#') {
    ret += stk.top(); stk.pop();
  }
  stk.pop();
  s = ret;
}

bool calculate(const string &s, const int v[]) {
  bool a, b, ret;
  for (size_t i = 0; i < s.size(); i++) {
    if (isalpha(s[i])) {
      stk.push(v[var[s[i]]]);
    } else {
      a = stk.top(); stk.pop();
      if (s[i] != '!') {
        b = stk.top(); stk.pop();
      }
      switch (s[i]) {
        case '!': ret = Not(a); break;
        case '&': ret = And(a, b); break;
        case '|': ret = Or(a, b); break;
        case '>': ret = If(a, b); break;
        case '=': ret = Iff(a, b); break;
      }
      stk.push(ret);
    }
  }
  ret = stk.top(); stk.pop();
  return ret;
}

void print(const string &s) {
  vector<int> pdnf, pcnf;
  int v[maxn];
  bool ret;
  cout << endl;
  for (auto p = var.begin(); p != var.end(); p++) {
    if (p != var.begin()) { cout << '\t'; }
    cout << p->first;
  }
  cout << "\tԭ���ʽ" << endl;
  for (int i = (1 << n) - 1; i >= 0; i--) {
    getValue(v, i);
    ret = calculate(s, v);
    if (ret) {
      pdnf.push_back(i);
    } else {
      pcnf.push_back(i);
    }
    for (auto p = var.begin(); p != var.end(); p++) {
      cout << v[var[p->first]] << '\t';
    }
    cout << ret << endl;
  }
  cout << endl << "����ȡ��ʽΪ: " << endl;
  for (size_t i = pdnf.size() - 1; i >= 0; i--) { //��С���������С��
    if (i != pdnf.size() - 1) { cout << " �� "; }
    cout << 'm' << pdnf[i];
  }
  cout << endl << endl << "����ȡ��ʽΪ: " << endl;
  for (size_t i = pcnf.size() - 1; i >= 0; i--) { //��С�������������
    if (i != pcnf.size() - 1) { cout << " �� "; }
    cout << 'M' << pcnf[i];
  }
  cout << endl << endl;
}
