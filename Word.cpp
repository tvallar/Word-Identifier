//Word.cpp

#include <string>
#include "Word.h"

using namespace std;

int Word::nextAvailableID = 0;

//Constructor for words with no certain type
Word::Word(string s) {
  id_num = nextAvailableID;
  nextAvailableID++;
  word = s;
  typeSum = 0;
  uses = 0;
  typeSet = false;
}

Word::Word(string s, short t) { //Constructor used if the word has only one type
  //Mostly words like determiners which complicated the Network used to identify
  //word types based on location
  id_num = nextAvailableID;
  nextAvailableID++;
  word = s;
  typeSum = t;
  uses = 1;
  typeSet = true;
}

//Add the type to the sum and increment uses
void Word::addTypeUse(int type) {
  typeSum += type;
  uses++;
}

//Returns the sum of all types it has been run as divided by the number of times
// it has been seen in total
double Word::getTypeAverage() {
  if (uses == 0) return 0;
  else{
    double t = typeSum;
    t /= (double) uses;
    return t;
  }
}

//Returns true if the type of this word is known since there is only one type it can be
//Not running this type through the net will make the Net have to identify a smaller ranger of types and therefore more accurate
bool Word::hasSetType() {
  return typeSet;
}

int Word::getID() {
  return id_num;
}

string Word::getWord() {
  return word;
}

void Word::print() {
  cout <<"ID: " << getID() << " Word: " << getWord()  << endl;
}

