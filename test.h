#ifndef TEST_H
#define TEST_H

#include<string>
using namespace std;

class Test {
private:
  string path;
public:
  void testArray(int op);
  void testForwardList(int op);
  void testList(int op);
};

#endif
