#include <algorithm>
#include <ctime>
#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

//////////////////////////////////////////////////////
class myCl {
public:
  myCl() {}
  ~myCl() {}

  void myClFunc1() {
    for (int i = 0; i < 5; i++) {
      printf("no param (%lu)\n", time(NULL));
      usleep(1000000);
    }
  }

  void myClFunc2(int n) {
    for (int i = 0; i < 5; i++) {
      printf("%d (%lu)\n", n, time(NULL));
      usleep(1000000);
    }
  }

  void myClFunc3(int n, int nn) {
    for (int i = 0; i < 5; i++) {
      printf("%d %d (%lu)\n", n, nn, time(NULL));
      usleep(1000000);
    }
  }

  static void myClStaticFunc() {
    int n = 0;
    static int nn = 0;

    for (int i = 0; i < 5; i++) {
      n++;
      nn++;
      printf("%d %d (%lu)\n", n, nn, time(NULL));
      usleep(1000000);
    }
  }

private:
protected:
};
//////////////////////////////////////////////////////

//////////////////////////////////////////////////////
void myFunc1() {
  // while (1) {
  for (int i = 0; i < 5; i++) {
    printf("no param (%lu)\n", time(NULL));
    usleep(1000000);
  }
}

void myFunc2(int n) {
  // while (1) {
  for (int i = 0; i < 5; i++) {
    printf("%d (%lu)\n", n, time(NULL));
    usleep(1000000);
  }
}
//////////////////////////////////////////////////////

//////////////////////////////////////////////////////
void vaFunc(int n, ...) { printf("%d\n", n); }
//////////////////////////////////////////////////////

int main(int argc, char **argv) {
  printf("-----Start-----\n");

#if 1
  std::string str = "PROGRAMMING_TEST";
  cout << "Size : " << str.size() << ", " << str << endl;
  string::iterator it = std::remove(str.begin(), str.end(), 'M');
  cout << "Size : " << str.size() << ", " << str << endl;
  str.erase(it, str.end());
  cout << "Size : " << str.size() << ", " << str << endl;
#endif

#if 0
  myCl::myClStaticFunc();

  myCl mc1;
  mc1.myClStaticFunc();
#endif

#if 0
  myCl mc1;
  thread t1(&myCl::myClFunc1, mc1);
  t1.join();

  myCl mc2;
  thread t2(&myCl::myClFunc2, mc2, 14);
  t2.join();

  myCl mc3;
  thread t3(&myCl::myClFunc3, mc2, 14, 555);
  t3.join();
#endif

#if 0
  thread t1(myFunc1);
  t1.join();

  thread t2(myFunc2, 5);
  t2.join();
#endif

  printf("-----End-----\n");

  return 0;
}