#include <iostream>
#include <ctime>
#include <cassert>
#include <random> //C11��α��������ɿ�
using namespace std;

//�����������
const long long MAXN = 500LL;
default_random_engine generator((unsigned)time(NULL));
uniform_int_distribution<long long> uniform(2, MAXN);

//ģ��˷���a * b mod m����� O(log(b))
long long mulMod(long long a, long long b, long long m) {
  long long r = 0;
  for (a %= m, b %= m; b; b >>= 1) {
    if (b & 1) { r = (r + a) % m; } a = (a << 1) % m;
  }
  return r;
}

//������ȡģ��a^b mod m O(log(b))
long long powMod(long long a, long long b, long long m) {
  long long r = 1;
  for (a %= m; b; b >>= 1) {
    if (b & 1) { r = mulMod(r, a, m); } a = mulMod(a, a, m);
  }
  return r;
}

//Miller-Rabin���Բ��� nΪ��������true ����(nΪα����)����Ϊ1/4^Times
const int Times = 7;
int WIT[] = { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 }; //7 bases for n < 2^64
bool Miller_Rabin(long long n) {
  if (n == 2) { return true; }
  if (n < 2 || (n & 1) == 0) { return false; }
  long long m = n - 1; int k = 0;
  while ((m & 1) == 0) { k++; m >>= 1; }
  for (int i = 0; i < Times; i++) {
    long long a = WIT[i], x = powMod(a, m, n), y = 0;
    //long long a = rand() % (n - 1) + 1;
    for (int j = 0; j < k; j++, x = y) {
      y = mulMod(x, x, n);
      if (y == 1 && x != 1 && x != n - 1) { return false; }
    }
    if (y != 1) { return false; }
  }
  return true;
}

//����һ��������MAXN������
long long getPrime() {
  long long num;
  do {
    num = uniform(generator);
  } while (!Miller_Rabin(num));
  return num;
}

//ŷ������㷨��gcd(a, b) O(log(min(a, b)))
long long gcd(long long a, long long b) {
  while (b != 0) {
    long long t = a % b;
    a = b;
    b = t;
  }
  return a;
}

//��չŷ������㷨 ����gcd(a, b) xΪa��b�ĳ˷���Ԫ O(log(min(a, b)))
long long exgcd(long long a, long long b, long long &x, long long &y) {
  if (b == 0) { x = 1; y = 0; return a; }
  long long d = exgcd(b, a % b, y, x); return y -= a / b * x, d;
}

int main() {
  long long p, q;
  do {
    p = getPrime();
    q = getPrime();
  } while (p == q);
  cout << "�����������������1e9�Ĳ��������: p = " << p << ", q = " << q << endl << endl;
  assert(Miller_Rabin(p));
  assert(Miller_Rabin(q));

  long long n = p * q;
  cout << "����˻�n = p * q = " << n << endl << endl;
  assert(n == p * q);

  long long mod = (p - 1) * (q - 1);
  cout << "�õ�ŷ��������(n) = (p - 1) * (q - 1) = " << mod << endl << endl;
  assert(mod == (p - 1) * (q - 1));

  long long e;
  do {
    e = uniform(generator);
  } while (gcd(e, mod) != 1 || e <= 0 || e >= mod);
  cout << "ѡ���릵(n)���ʵ��������e = " << e << endl << endl;
  assert(gcd(e, mod) == 1 && e > 0 && e < mod);

  long long x = 0, y = 0;
  exgcd(e, mod, x, y);
  long long d = (x + mod) % mod;
  cout << "����e����ģ��(n)�ĳ˷���Ԫd = " << d << endl << endl;
  assert(mulMod(d, e, mod) == 1);

  cout << "���ɵĹ�����ԿΪ{ e = " << e << ", n = " << n << " }, ˽����ԿΪ{ d = " << d << ", n = " << n << " }" << endl << endl;

  long long M;
  do {
    cout << "����Ҫ���ܵ�С��n�����ķǸ�����M = ";
    cin >> M;
  } while (M < 0 || M >= n);
  long long C = powMod(M, e, n);
  cout << "���ܵõ�����C = " << C << endl;
  long long M_ = powMod(C, d, n);
  cout << "���ܵõ�����M' = " << M_ << endl << endl;

  return 0;
}
