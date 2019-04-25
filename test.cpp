// #include "test.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>


using namespace std;


int rand_int_generator(int N) {
  return rand()%N;
}

string testArray(int op) {
  string path = "test_array_" + to_string(op) + ".txt";
  ofstream file(path);
  if (file.is_open())
  {
    int size = (rand() % 20)+1;
    file << "0 " + to_string(size) + "\n";
    file << "7 0\n";                          //Constructor
    for(int i = 0; i < size; i++) {
      int num = rand_int_generator(200);
      file << "1 " + to_string(num) + "\n";   //Fill array with 0
    }
    int num, arg1, arg2;
    for(int i = 0; i < op-size-2; i++) {
       num = rand_int_generator(8) + 2;
       if(num == 1) {                         //Insert arg2 at index arg1
         arg1 = rand_int_generator(size-1);
         arg2 = rand_int_generator(200);
         file << "1 " + to_string(arg1) + " " + to_string(arg2) + "\n";
       }
       else if(num == 6) {                    //Retrieve element at arg1
         arg1 = rand_int_generator(size-1);
         file << "6 " + to_string(arg1) + "\n";
       }
       else if(num == 7) {                    //Fill array with arg1
         arg1 = rand_int_generator(200);
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

  return path;
}


string testForwardList(int op) {
  string path = "test_forwardlist_" + to_string(op) + ".txt";
  ofstream file(path);

  int num, arg1, arg2, size=0;

  if (file.is_open())
  {
    file << "0\n";                            //Constructor
    for(int i = 0; i < 5; i++) {
      int num = rand_int_generator(200);
      file << "3 " + to_string(num) + "\n";   //Push front 5 random numbers to list
      size++;
    }
    for(int i = 0; i < op-6; i++) {
       num = rand_int_generator(12) + 1;
       if(num == 3) {                        //Push Front element in arg1
         arg1 = rand_int_generator(200);
         file << "3 " + to_string(arg1) + "\n";
         size++;
       }
       // else if(num == 4 || num == 9) {       //Decrease list size on popping or erasing
       //   file << to_string(num) + "\n";
       // }
       else if(num == 5) {                   //Insert at index arg1, element arg2
         arg1 = rand_int_generator(size);
         arg2 = rand_int_generator(200);
         file << "5 " + to_string(arg1) + " " + to_string(arg2) + "\n";
       }
       else if(num == 6) {                   //Get element at index arg1
         arg1 = rand_int_generator(size);
         file << "6 " + to_string(arg1) + "\n";
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

  return path;
}


string testList(int op) {
  string path = "test_forwardlist_" + to_string(op) + ".txt";
  ofstream file(path);

  int num, arg1, arg2, size=0;

  if (file.is_open())
  {
    file << "0\n";                            //Constructor
    for(int i = 0; i < 5; i++) {
      int num = rand_int_generator(200);
      file << "3 " + to_string(num) + "\n";   //Push front 5 random numbers to list
      size++;
    }
    for(int i = 0; i < op-6; i++) {
       num = rand_int_generator(12) + 1;
       if(num == 3) {                        //Push Front element in arg1
         arg1 = rand_int_generator(200);
         file << "3 " + to_string(arg1) + "\n";
         size++;
       }
       // else if(num == 4 || num == 9) {       //Decrease list size on popping or erasing
       //   file << to_string(num) + "\n";
       // }
       else if(num == 5) {                   //Insert at index arg1, element arg2
         arg1 = rand_int_generator(size);
         arg2 = rand_int_generator(200);
         file << "5 " + to_string(arg1) + " " + to_string(arg2) + "\n";
       }
       else if(num == 6) {                   //Get element at index arg1
         arg1 = rand_int_generator(size);
         file << "6 " + to_string(arg1) + "\n";
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

  return path;

}

int main() {
  string path = testForwardList(100);
  cout<<"HI";

  return 0;
}