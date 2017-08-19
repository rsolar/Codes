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
  cout << "逆置后: ";
  lst.output();

  lst.eraseX(3);
  cout << "删除值等于3的元素后: ";
  lst.output();

  return 0;
}
