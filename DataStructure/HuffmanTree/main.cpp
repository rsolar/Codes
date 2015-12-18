//main.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "HuffmanTree.h"

using namespace std;

fstream ftextfile; //textfile.txt
fstream fcodefile; //codefile.txt
fstream fresult; //result.txt

HuffmanTree<int> ht; //哈夫曼树
int n; //字符集中字符个数
vector<char> c; //字符集
vector<int> w; //权值
vector<BTNode<int> *> leaf; //指向每个字符对应叶子结点的指针
vector<string> code; //各字符编码
string text; //待处理字符串
string result; //处理结果

void menu(); //显示菜单
void B(); //B —— 建树
void T(); //T —— 遍历
void E(); //E —— 生成编码
void C(); //C —— 编码
void D(); //D —— 译码
void P(); //P —— 打印

int main() {
  char choice = 0;
  while (choice != 'X') {
    menu();
    cin >> choice;
    choice = toupper(choice);
    system("cls");
    switch (choice) {
      case 'B': B(); break;
      case 'T': T(); break;
      case 'E': E(); break;
      case 'C': C(); break;
      case 'D': D(); break;
      case 'P': P(); break;
      case 'X': break;
      default:
        cout << "输出错误, 请输入正确的序号" << endl << endl;
        system("pause");
        break;
    }
  }
  return 0;
}

void menu() {
  system("cls");
  cout << "---------- 哈夫曼编码和译码系统 by Rui ----------" << endl;
  cout << "**********       请选择操作:           **********" << endl;
  cout << "**********       B —— 建树           **********" << endl;
  cout << "**********       T —— 遍历           **********" << endl;
  cout << "**********       E —— 生成编码       **********" << endl;
  cout << "**********       C —— 编码           **********" << endl;
  cout << "**********       D —— 译码           **********" << endl;
  cout << "**********       P —— 打印           **********" << endl;
  cout << "**********       X —— 退出           **********" << endl << endl;
  cout << "请输入序号: ";
}

void B() {
  ht.clear();
  for (;;) {
    cout << "请输入字符集中的字符个数(n >= 2): ";
    cin >> n;
    if (n < 2) {
      cout << endl << "输入错误, 请重新输入" << endl;
      system("pause");
      system("cls");
    } else {
      break;
    }
  }
  c.resize(n);
  w.resize(n);
  leaf.resize(n);
  code.resize(n);
  cout << "请依次输入字符集中的字符: ";
  for (int i = 0; i < n; i++) {
    cin >> c[i];
  }
  cout << "请依次输入字符集中的字符权值: ";
  for (int i = 0; i < n; i++) {
    cin >> w[i];
  }
  leaf = ht.build(c, w);
  cout << endl << "建树完毕" << endl << endl;
  system("pause");
}

void T() {
  cout << "前序遍历结果: ";
  ht.preOrder(visit);
  cout << endl << "中序遍历结果: ";
  ht.inOrder(visit);
  cout << endl;
  system("pause");
}

void E() {
  code = ht.getCode(leaf);
  cout << "各个字符的哈夫曼编码:" << endl;
  for (int i = 0; i < n; i++) {
    cout << c[i] << ": " << code[i] << endl;
  }
  cout << endl;
  system("pause");
}

void C() {
  ftextfile.open("textfile.txt", ios::out);
  fcodefile.open("codefile.txt", ios::out);
  if (!ftextfile || !fcodefile) {
    cout << "打开文件失败" << endl << endl;;
  } else {
    for (;;) {
      try {
        cout << "请输入由字符集中字符组成的任意字符串:" << endl;
        cin >> text;
        ftextfile << text;
        result = ht.encode(c, code, text);
        cout << endl << "编码结果:" << endl << result << endl << endl;
        fcodefile << result;
        break;
      } catch (exception e) {
        cout << "输入的字符串中包含不在字符集中的字符, 请重新输入字符串" << endl << endl;
        system("pause");
        system("cls");
      }
    }
  }
  ftextfile.close();
  fcodefile.close();
  system("pause");
}

void D() {
  fcodefile.open("codefile.txt", ios::in);
  fresult.open("result.txt", ios::out);
  if (!fcodefile || !fresult) {
    cout << "打开文件失败" << endl << endl;;
  } else {
    try {
      fcodefile >> text;
      result = ht.decode(c, code, text);
      cout << "解码结果:" << endl << result << endl << endl;
      fresult << result;
    } catch (exception e) {
      cout << "输入的字符串中包含不在字符集中的字符, 请重新输入字符串" << endl << endl;
    }
  }
  fcodefile.close();
  fresult.close();
  system("pause");
}

void P() {
  ftextfile.open("textfile.txt", ios::in);
  fcodefile.open("codefile.txt", ios::in);
  fresult.open("result.txt", ios::in);
  if (!ftextfile || !fcodefile || !fresult) {
    cout << "打开文件失败" << endl << endl;
  } else {
    ftextfile >> text;
    cout << "textfile.txt:" << endl << text << endl;
    fcodefile >> text;
    cout << endl << "fcodefile.txt:" << endl << text << endl;
    fresult >> text;
    cout << endl << "fresult.txt:" << endl << text << endl << endl;
  }
  ftextfile.close();
  fcodefile.close();
  fresult.close();
  system("pause");
}
