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

HuffmanTree<int> ht; //��������
int n; //�ַ������ַ�����
vector<char> c; //�ַ���
vector<int> w; //Ȩֵ
vector<BTNode<int> *> leaf; //ָ��ÿ���ַ���ӦҶ�ӽ���ָ��
vector<string> code; //���ַ�����
string text; //�������ַ���
string result; //������

void menu(); //��ʾ�˵�
void B(); //B ���� ����
void T(); //T ���� ����
void E(); //E ���� ���ɱ���
void C(); //C ���� ����
void D(); //D ���� ����
void P(); //P ���� ��ӡ

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
        cout << "�������, ��������ȷ�����" << endl << endl;
        system("pause");
        break;
    }
  }
  return 0;
}

void menu() {
  system("cls");
  cout << "---------- ���������������ϵͳ by Rui ----------" << endl;
  cout << "**********       ��ѡ�����:           **********" << endl;
  cout << "**********       B ���� ����           **********" << endl;
  cout << "**********       T ���� ����           **********" << endl;
  cout << "**********       E ���� ���ɱ���       **********" << endl;
  cout << "**********       C ���� ����           **********" << endl;
  cout << "**********       D ���� ����           **********" << endl;
  cout << "**********       P ���� ��ӡ           **********" << endl;
  cout << "**********       X ���� �˳�           **********" << endl << endl;
  cout << "���������: ";
}

void B() {
  ht.clear();
  for (;;) {
    cout << "�������ַ����е��ַ�����(n >= 2): ";
    cin >> n;
    if (n < 2) {
      cout << endl << "�������, ����������" << endl;
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
  cout << "�����������ַ����е��ַ�: ";
  for (int i = 0; i < n; i++) {
    cin >> c[i];
  }
  cout << "�����������ַ����е��ַ�Ȩֵ: ";
  for (int i = 0; i < n; i++) {
    cin >> w[i];
  }
  leaf = ht.build(c, w);
  cout << endl << "�������" << endl << endl;
  system("pause");
}

void T() {
  cout << "ǰ��������: ";
  ht.preOrder(visit);
  cout << endl << "����������: ";
  ht.inOrder(visit);
  cout << endl;
  system("pause");
}

void E() {
  code = ht.getCode(leaf);
  cout << "�����ַ��Ĺ���������:" << endl;
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
    cout << "���ļ�ʧ��" << endl << endl;;
  } else {
    for (;;) {
      try {
        cout << "���������ַ������ַ���ɵ������ַ���:" << endl;
        cin >> text;
        ftextfile << text;
        result = ht.encode(c, code, text);
        cout << endl << "������:" << endl << result << endl << endl;
        fcodefile << result;
        break;
      } catch (exception e) {
        cout << "������ַ����а��������ַ����е��ַ�, �����������ַ���" << endl << endl;
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
    cout << "���ļ�ʧ��" << endl << endl;;
  } else {
    try {
      fcodefile >> text;
      result = ht.decode(c, code, text);
      cout << "������:" << endl << result << endl << endl;
      fresult << result;
    } catch (exception e) {
      cout << "������ַ����а��������ַ����е��ַ�, �����������ַ���" << endl << endl;
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
    cout << "���ļ�ʧ��" << endl << endl;
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
