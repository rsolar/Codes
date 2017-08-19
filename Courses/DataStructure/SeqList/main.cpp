//main.cpp:
#include "SeqList.h"

using namespace std;

int main() {
  SeqList<int> lst(20);
  for (int i = 0; i < 20; i++) {
    lst.insert(i, (i + 4) / 4);
  }

  cout << "lst: ";
  lst.output();

  lst.reverse();
  cout << "���ú�: ";
  lst.output();

  lst.eraseX(3);
  cout << "ɾ��ֵ����3��Ԫ�غ�: ";
  lst.output();

  return 0;
}
