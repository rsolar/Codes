#include <iostream>
#include <string>
#include <stack>
#include <hash_map>
using namespace std;
using namespace stdext;

const int maxn = 8;

int n;
hash_map<char, int> var;
stack<char> stk;

bool Not(const bool &a) { return !a; } //否定
bool And(const bool &a, const bool &b) { return a && b; } //合取
bool Or(const bool &a, const bool &b) { return a || b; } //析取
bool If(const bool &a, const bool &b) { return !a || b; } //条件
bool Iff(const bool &a, const bool &b) { return a == b; } //双条件

bool checkStack(const char &out); //比较栈内外操作符优先级
void input(string &s); //输入表达式
void toSuffix(string &s); //转换为后缀表达式
bool calculate(const string &s, const int v[]); //计算表达式
void print(const string &s); //输出

int main() {
  string orgf;
  input(orgf);
  toSuffix(orgf);
  print(orgf);
  return 0;
}

bool checkStack(const char &out) {
  int i, o;
  switch (stk.top()) {
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

void input(string &s) {
  cout << "支持符号: 否定: !   合取:   &    析取: |" << endl;
  cout << "          条件: ->  双条件: <->  括号: ( )" << endl << endl;
  for (size_t i;;) {
    var.clear();
    cout << "请输入表达式，变元不区分大小写: " << endl;
    getline(cin, s);
    while ((i = s.find(' ')) != string::npos) { s.erase(i, 1); }
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
          if (var.find(s[i]) == var.end()) { var[s[i]] = n++; }
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
      cout << endl << "请输入正确的表达式!" << endl << endl;
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
      while (stk.top() != '(') { ret += stk.top(); stk.pop(); }
      stk.pop();
    } else {
      do { ret += stk.top(); stk.pop(); } while (!checkStack(s[i]));
      stk.push(s[i]);
    }
  }
  while (stk.top() != '#') { ret += stk.top(); stk.pop(); }
  stk.pop();
  s = ret;
}

bool calculate(const string &s, const int v[]) {
  bool a, b, ret;
  for (size_t i = 0; i < s.size(); i++) {
    if (isalpha(s[i])) {
      stk.push(v[var[s[i]]]);
    } else {
      a = stk.top() == 1; stk.pop();
      if (s[i] != '!') { b = stk.top() == 1; stk.pop(); }
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
  ret = stk.top() == 1; stk.pop();
  return ret;
}

void print(const string &s) {
  vector<int> pdnf, pcnf;
  int v[maxn]; bool ret;
  cout << endl;
  for (auto p : var) { cout << p.first << '\t'; }
  cout << "原表达式" << endl;
  for (int i = (1 << n) - 1; i >= 0; i--) {
    for (int j = n - 1, t = i; j >= 0; j--) { v[j] = t & 1; t >>= 1; } //真值指派
    ret = calculate(s, v); ret ? pdnf.push_back(i) : pcnf.push_back(i);
    for (auto p : var) { cout << v[var[p.first]] << '\t'; }
    cout << ret << endl;
  }
  cout << endl << "主析取范式为: " << endl;
  for (int i = pdnf.size() - 1; i >= 0; i--) { //从小到大输出各小项
    cout << (i != pdnf.size() - 1 ? " ∨ m" : "m") << pdnf[i];
  }
  cout << endl << endl << "主合取范式为: " << endl;
  for (int i = pcnf.size() - 1; i >= 0; i--) { //从小到大输出各大项
    cout << (i != pcnf.size() - 1 ? " ∧ M" : "M") << pcnf[i];
  }
  cout << endl << endl;
}
