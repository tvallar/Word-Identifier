//Dictionary.h

#ifndef DICTIONARY
#define DICTIONARY

#include <vector>
#include <string>
#include "Word.h"
#include "Constants.h"

using namespace std;

class Dictionary
{
 public:
  Dictionary(string n);
  Dictionary(string n, vector<string> &words);
  ~Dictionary();
  int getSize();
  Word* getWord(int id);
  int getID(string word);
  void addWord(string word);
  void addWord(string word, short type);
  bool contains(string word);
  void print();
 private:
  vector<Word*> dictionary;
  int size;
  string name;
  
};

#endif
  
