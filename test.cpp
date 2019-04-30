// #include "test.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "test.h"


using namespace std;

#define elementRange 1000

int rand_int_generator(int N) {
  return rand()%N;
}

void Test::Array(int op) {
  string path = "test_array_" + to_string(op) + ".txt";
  ofstream file(path);
  if (file.is_open())
  {
    file << "1\n";
    file << op <<"\n";
    int size = (rand() % 20)+1;
    file << "0 " + to_string(size) + "\n";
    file << "7 0\n";                          //Constructor
    for(int i = 0; i < size; i++) {
      int num = rand_int_generator(elementRange);
      file << "1 " + to_string(num) + "\n";   //Fill array with 0
    }
    int num, arg1, arg2;
    for(int i = 0; i < op-size-2; i++) {
       num = rand_int_generator(8) + 2;
       if(num == 1) {                         //Insert arg2 at index arg1
         arg1 = rand_int_generator(size-1);
         arg2 = rand_int_generator(elementRange);
         file << "1 " + to_string(arg1) + " " + to_string(arg2) + "\n";
       }
       else if(num == 6) {                    //Retrieve element at arg1
         arg1 = rand_int_generator(size-1);
         file << "6 " + to_string(arg1) + "\n";
       }
       else if(num == 7) {                    //Fill array with arg1
         arg1 = rand_int_generator(elementRange);
         file << "7 " + to_string(arg1) + "\n";
       }
       else if(num == 8) {                    //Sort asc if arg1=1 else desc
         arg1 = rand_int_generator(2);
         file << "8 " + to_string(arg1) + "\n";
       }
       else {
         file << to_string(num) + "\n";
       }
    }
  }

  else cout << "Unable to open file";
  file.close();

}


void Test::ForwardList(int op) {
  string path = "test_forwardlist_" + to_string(op) + ".txt";
  ofstream file(path);

  int num, arg1, arg2, size=0;

  if (file.is_open())
  {
    int count = 0;
    file << "2\n";
    file << op <<"\n";
    file << "0\n";                            //Constructor
    for(int i = 0; i < 5; i++) {
      int num = rand_int_generator(elementRange);
      file << "3 " + to_string(num) + "\n";   //Push front 5 random numbers to list
      size++;
      count++;
    }
    for(int i = 0; i < op-count-1; i++) {
       num = rand_int_generator(11) + 1;
       if(num == 3) {                        //Push Front element in arg1
         arg1 = rand_int_generator(elementRange);
         file << "3 " + to_string(arg1) + "\n";
         size++;
       }
       else if(num == 5) {                   //Insert element arg1 ar index arg2
         arg1 = rand_int_generator(elementRange);
         arg2 = rand_int_generator(size);
         size++;
         file << "5 " + to_string(arg1) + " " + to_string(arg2) + "\n";
       }
       else if(num == 6) {                   //Get element at index arg1
         arg1 = rand_int_generator(size);
         file << "6 " + to_string(arg1) + "\n";
       }
       else if(num == 9) {                   //Erase element at index arg1
         arg1 = rand_int_generator(size);
         size--;
         file << "9 " + to_string(arg1) + "\n";
       }
       else if(num == 11) {                   //Sort asc if arg1=1 else desc
         arg1 = rand_int_generator(2);
         file << "11 " + to_string(arg1) + "\n";
       }
       else {
         file << to_string(num) + "\n";
       }
    }
  }

  else cout << "Unable to open file";
  file.close();

}


void Test::List(int op) {
  string path = "test_list_" + to_string(op) + ".txt";
  ofstream file(path);

  int num, arg1, arg2, size=0;

  if (file.is_open())
  {
    int count = 0;
    file << "3\n";
    file << op <<"\n";
    file << "0\n";                            //Constructor
    for(int i = 0; i < op/40; i++) {
      int num = rand_int_generator(elementRange);
      file << "3 " + to_string(num) + "\n";   //Push front 5 random numbers to list
      size++;
      count++;
    }
    for(int i = 0; i < op-count-1; i++) {
       num = rand_int_generator(15) + 1;
       if(num == 3 || num == 4) {                        //Push Front or back element in arg1
         arg1 = rand_int_generator(elementRange);
         file << to_string(num) + " " + to_string(arg1) + "\n";
         size++;
       }
       else if(num == 7) {                   //Insert at index arg1, element arg2
         arg1 = rand_int_generator(elementRange);
         arg2 = rand_int_generator(size);
         size++;
         file << to_string(num) + " " + to_string(arg1) + " " + to_string(arg2) + "\n";
       }
       else if(num == 8) {                   //Get element at index arg1
         arg1 = rand_int_generator(size);
         file << "8 " + to_string(arg1) + "\n";
       }
       else if(num == 12) {                   //Sort asc if arg1=1 else desc
         arg1 = rand_int_generator(size);
         size--;
         file << "12 " + to_string(arg1) + "\n";
       }
       else if(num == 14) {                   //Sort asc if arg1=1 else desc
         arg1 = rand_int_generator(2);
         file << "14 " + to_string(arg1) + "\n";
       }
       else if(num == 15)                  // search arg1 in list
       {
            arg1 = rand_int_generator(elementRange);
            file << "15 " + to_string(arg1) + "\n";
       }
       else {
         file << to_string(num) + "\n";
       }
    }
  }

  else cout << "Unable to open file";
  file.close();
}

int main(int argc, char* argv[]) {
  srand(time(NULL));
  if(argc != 3) {
    cout<<"Run as ./test <a/s/d> <# of ops>";
    exit(0);
  }
  else {
    Test t;
    switch(argv[1][0]) {
      case 'a':
        t.Array(atoi(argv[2]));
        break;
      case 's':
        t.ForwardList(atoi(argv[2]));
        break;
      case 'd':
        t.List(atoi(argv[2]));
        break;
      default:
        cout<<"default";
    }
  }
  return 0;
}
