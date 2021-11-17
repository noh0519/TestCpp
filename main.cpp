#include "aria.hpp"
#include "sha1v2.hpp"
#include <algorithm>
#include <ctime>
#include <fmt/format.h>
#include <functional>
#include <ifaddrs.h>
#include <iomanip>
#include <iostream>
#include <net/if.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
#include <filesystem>
#include <fstream>
#include <netdb.h>
#include <nlohmann/json.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/ioctl.h>
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

//////////////////////////////////////////////////////
bool isNumber(const char *str, int length) {
  for (int i = 0; i < length; i++) {
    if (!std::isdigit(str[i])) {
      return false;
    }
  }
  return true;
}
//////////////////////////////////////////////////////

int main(int argc, char **argv) {
  printf("-----Start-----\n");

#if 0
  const char *s = "1s";
  printf("%d\n", atoi(s));
#endif

#if 1
  const char *conf_path = "/var/qcalog/wsd.conf";
  const char *json_path = "/var/qcalog/wsd.json";
  std::ifstream ifs_conf(conf_path);
  std::string line = "";
  char section[64] = {0};
  char key[64] = {0};
  char value[64] = {0};
  nlohmann::json j;

  while (std::getline(ifs_conf, line)) {
    line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
    if (!line.empty()) {
      if (line.find("[") != std::string::npos && line.find("]") != std::string::npos) {
        memset(section, 0x00, 64);
        sscanf(line.c_str(), "[%[a-z]]", section);
        // printf("%s\n", section);
      } else if (line.find("=") != std::string::npos) {
        memset(key, 0x00, 64);
        memset(value, 0x00, 64);
        sscanf(line.c_str(), "%[^'=']=%s", key, value);
        // printf("key : %s, value : %s\n", key, value);
        if (isNumber(value, strlen(value))) {
          j[section][key] = strtol(value, NULL, 10);
        } else {
          j[section][key] = value;
        }
      }
    }
  }

  std::cout << j.dump(4) << std::endl;
#endif

#if 0
  const char *conf_path = "/var/qcalog/wsd.conf";
  const char *json_path = "/var/qcalog/wsd.json";
  std::ifstream ifs_conf(conf_path);
  std::ifstream ifs_json(json_path);
  printf("conf : %s\n", ifs_conf.good() ? "true" : "false");
  printf("json : %s\n", ifs_json.good() ? "true" : "false");
#endif

#if 0
  /// get interface addresses
  struct ifaddrs *interface_addrs = NULL;
  if (getifaddrs(&interface_addrs) == -1) {
    return 1;
  }

  if (!interface_addrs) {
    return 1;
  }

  int32_t sd = socket(PF_INET, SOCK_DGRAM, 0);
  if (sd < 0) {
    /// free memory allocated by getifaddrs
    freeifaddrs(interface_addrs);
    return 1;
  }

  /// get MAC address for each interface
  for (struct ifaddrs *ifa = interface_addrs; ifa != NULL; ifa = ifa->ifa_next) {
    /// print MAC address
    if (ifa->ifa_data != 0) {
      struct ifreq req;
      strcpy(req.ifr_name, ifa->ifa_name);
      if (ioctl(sd, SIOCGIFHWADDR, &req) != -1) {
        uint8_t *mac = (uint8_t *)req.ifr_ifru.ifru_hwaddr.sa_data;
        printf("%s:MAC[%02X:%02X:%02X:%02X:%02X:%02X]\n", ifa->ifa_name, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
      }
    }

    /// print IP address
    if (ifa->ifa_addr != 0) {
      int family = ifa->ifa_addr->sa_family;
      if (family == AF_INET || family == AF_INET6) {
        char host[NI_MAXHOST];
        if (getnameinfo(ifa->ifa_addr, (family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6), host, NI_MAXHOST,
                        NULL, 0, NI_NUMERICHOST) == 0) {
          printf("%s:Address Family:[%d%s]:IP[%s]\n", ifa->ifa_name, family,
                 (family == AF_PACKET)  ? " (AF_PACKET)"
                 : (family == AF_INET)  ? " (AF_INET)"
                 : (family == AF_INET6) ? " (AF_INET6)"
                                        : "",
                 host);
        }
      }
    }
  }

  /// close socket
  close(sd);

  /// free memory allocated by getifaddrs
  freeifaddrs(interface_addrs);
#endif

#if 0
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex << 16;
  printf("%s\n", ss.str().c_str());
#endif

#if 0
  nlohmann::json p;
  nlohmann::json pp1;
  pp1["1"] = 123;
  p.update(pp1);
  nlohmann::json pp2;
  pp2["2"] = 234;
  p.update(pp2);
  nlohmann::json pp3;
  pp3["3"] = 345;
  p.update(pp3);
  std::cout << std::setw(4) << p << std::endl;
#endif

#if 0
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