#include "aria.hpp"
#include "sha1v2.hpp"
#include <algorithm>
#include <ctime>
#include <fmt/format.h>
#include <functional>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <unistd.h>
#include <unordered_map>

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
  while (1) {
    // for (int i = 0; i < 5; i++) {
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
  testEncryptAria();
  // ARIA_test();
#endif

#if 0
  Byte intext[10 + 1] = "0123456789";
  Byte outtext[128] = {0};
  Byte mk[16 + 1] = "a5c59d200b9ae44a";
  Byte rk[16 * 17] = {0};
  int rk_len = EncKeySetup(mk, rk, 128);
  printf("rk : ");
  for (int i = 0; i < 16 * 17; i++) {
    printf("%02x", rk[i]);
  }
  printf("\n");
  printf("rk_len : %d\n", rk_len);
  Crypt(intext, rk_len, rk, outtext);
  printf("encrypt value : ");
  for (int i = 0; i < 17; i++) {
    printf("%02x", outtext[i]);
  }
  printf("\n");
  printf("intext : ");
  for (int i = 0; i < 10; i++) {
    printf("%02x", intext[i]);
  }
  printf("\n");
  printf("mk : ");
  for (int i = 0; i < 16; i++) {
    printf("%02x", mk[i]);
  }
  printf("\n");
#endif

#if 0
  nlohmann::json j;
  fmt::print("hello {}\n", 1);
#endif

#if 0
  uint16_t nonce = 41419;
  std::string shared_key = "Secui00@!";
  uint8_t secret_key[128] = {0}; // 암호화 key
  memcpy(secret_key, shared_key.data(), shared_key.size());
  memcpy(secret_key + shared_key.size(), &nonce, 2);
  int32_t secret_key_len = shared_key.size() + 2;
  uint8_t text_out[20] = {0};
  printf("plain text : %s\n", secret_key);
  int err;
  SHA1Context sha1;
  err = SHA1Reset(&sha1);
  err = SHA1Input(&sha1, (const unsigned char *)secret_key, secret_key_len);
  err = SHA1Result(&sha1, text_out);
  printf("descrypt text : ");
  for (int i = 0; i < 20; i++) {
    printf("%02x", text_out[i]);
  }
  printf("\n");
#endif

#if 0
  // SHA1
  uint16_t nonce = 41419;
  std::string shared_key = "Secui00@!";
  uint8_t secret_key[128] = {0}; // 암호화 key
  memcpy(secret_key, shared_key.data(), shared_key.size());
  memcpy(secret_key + shared_key.size(), &nonce, 2);
  int32_t secret_key_len = shared_key.size() + 2;
  uint8_t text_out[20] = {0};
  printf("plain text : %s\n", secret_key);
  SHA1Context sha_1;
  int err;
  err = SHA1Reset(&sha_1);
  if (err != shaSuccess)
    return err;
  err = SHA1Input(&sha_1, (const unsigned char *)secret_key, secret_key_len);
  if (err != shaSuccess)
    return err;
  err = SHA1Result(&sha_1, text_out);
  if (err != shaSuccess)
    return err;
  //////////////////
  for (int i = 0; i < 20; i++) {
    printf("%02x", text_out[i]);
  }
  printf("\n");
  printf("~!!!NBH!!!\n");
  exit(0);
#endif

#if 0
  std::string s1 = "aabbccddeeff";
  unsigned char i = (unsigned char)strtoul(s1.substr(0, 2).c_str(), NULL, 16);
  printf("%x\n", i);
  int ii = 0;
  int jj = ii / 2;
  printf("%d\n", jj);
#endif

#if 0
  std::string s1 = "1234567890";
  std::string s2 = s1.substr(0, 4);
  printf("%s\n", s2.c_str());
#endif

#if 0
  time_t tt = time(NULL);
  struct tm tst = *localtime(&tt);
#endif

#if 0
  std::thread t1;

  while (1) {
    // printf("thread status : %d\n", t1.);
    usleep(1000000);
  }
#endif

#if 0
  std::thread t1;
  for (int i = 0; i < 10; i++) {
    t1 = std::thread(myFunc2, i);
    t1.detach();
  }

  while (1) {
    usleep(1000000);
  }
#endif

#if 0
  std::unordered_map<int, std::string> m;
  m.insert(std::make_pair(1, "1socket"));
  printf("%s\n", m[1].c_str());
#endif

#if 0
  std::function<void(char *)> f;
  if (!f) {
    printf("function is NULL\n");
  }
  f = [](char *str) -> void { printf("%s\n", str); };
  f("123");
  if (f) {
    printf("function is not NULL\n");
  }
#endif

#if 0
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