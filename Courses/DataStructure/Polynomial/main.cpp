//main.cpp
#include "polynomial.h"

using namespace std;

void printMenu() {
  cout << "-----����ʽ����������-----" << endl;
  cout << "(1) ����ʽ�ӷ�" << endl;
  cout << "(2) ����ʽ�˷�" << endl;
  cout << "(0) �˳�" << endl;
  cout << "��ѡ��һ�����: ";
}

int main() {
  Polynomial a, b, ret;
  int choice;
  while (true) {
    printMenu(); //����˵�
    cin >> choice;
    switch (choice) {
      case 1:
        cout << endl << "�������ʽA:" << endl;
        cin >> a;
        cout << endl << "A: " << a;
        cout << endl << "�������ʽB:" << endl;
        cin >> b;
        cout << endl << "B: " << b;
        ret = a + b;
        cout << endl << "A + B: " << ret;
        break;
      case 2:
        cout << endl << "�������ʽA:" << endl;
        cin >> a;
        cout << endl << "A: " << a;
        cout << endl << "�������ʽB:" << endl;
        cin >> b;
        cout << endl << "B: " << b;
        ret = a * b;
        cout << endl << "A * B: " << ret;
        break;
      case 0:
        return 0;
      default:
        cout << "��������ȷ�Ĳ�����ţ�" << endl;
        break;
    }
    cout << endl;
  }
  return 0;
}
