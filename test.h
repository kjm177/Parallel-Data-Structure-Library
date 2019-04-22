#ifndef TEST_H
#define TEST_H

#include<string>
using namespace std;

class Test {
private:
  string path;
public:
  string testArray(int op);
  string testForwardList(int op);
  string testList(int op);
}

#endif
