//Word.h

#ifndef WORD
#define WORD

#include <string>
#include <iostream>
#include "Constants.h"

using namespace std;

class Word
{
 public:
  Word(string s);
  Word(string s, short type);
  int getID(); //id_num getter
  string getWord() ; //word string getter
  double getTypeAverage();
  void addTypeUse(int type);
  bool hasSetType();
  void print();
 private:
  string word;
  //Every Word has a unique ID number
  int id_num;
  int typeSum;
  int uses;
  bool typeSet;
  static int nextAvailableID;
};

#endif
