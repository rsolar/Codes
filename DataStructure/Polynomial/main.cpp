//main.cpp
#include "polynomial.h"

using namespace std;

void printMenu() {
  cout << "-----多项式的算术运算-----" << endl;
  cout << "(1) 多项式加法" << endl;
  cout << "(2) 多项式乘法" << endl;
  cout << "(0) 退出" << endl;
  cout << "请选择一项操作: ";
}

int main() {
  Polynomial a, b, ret;
  int choice;
  while (true) {
    printMenu(); //输出菜单
    cin >> choice;
    switch (choice) {
      case 1:
        cout << endl << "输入多项式A:" << endl;
        cin >> a;
        cout << endl << "A: " << a;
        cout << endl << "输入多项式B:" << endl;
        cin >> b;
        cout << endl << "B: " << b;
        ret = a + b;
        cout << endl << "A + B: " << ret;
        break;
      case 2:
        cout << endl << "输入多项式A:" << endl;
        cin >> a;
        cout << endl << "A: " << a;
        cout << endl << "输入多项式B:" << endl;
        cin >> b;
        cout << endl << "B: " << b;
        ret = a * b;
        cout << endl << "A * B: " << ret;
        break;
      case 0:
        return 0;
      default:
        cout << "请输入正确的操作序号！" << endl;
        break;
    }
    cout << endl;
  }
  return 0;
}
