//Dictionary.cpp

#include "Dictionary.h"
#include "Word.h"
#include <iostream>
#include <vector>


using namespace std;

Dictionary::Dictionary(string n) {
  name = n;
  size = 0;
}

Dictionary::Dictionary(string n, vector<string> &words) {
  name = n;
  for (int i =0; i < words.size(); i++) {
    addWord(words.at(i));
  }
  size = words.size();
}

Dictionary::~Dictionary() {
  for (int i = 0; i < size; i++) {
    Word* temp = dictionary.at(i);
    delete temp;
  }
}

int Dictionary::getSize() {
  return size;
}

Word* Dictionary::getWord(int id) {
  if (id < size) return dictionary[id];
  else return NULL;
}

int Dictionary::getID(string word) {
   for (int i =0; i < size; i++) {
    if (dictionary.at(i)->getWord() == word) return i;
  }
  return -1;
}

//Add word method for adding words that have no known type
void Dictionary::addWord(string word) {
  if (!contains(word)){
    dictionary.push_back(new Word(word));
    size++;
  }
}

//Add word method for adding words that have a known type
void Dictionary::addWord(string word, short type) {
  if (!contains(word)) {
    dictionary.push_back(new Word(word, type));
    size++;
  }
}

bool Dictionary::contains(string word) {
  for (int i =0; i < size; i++) {
    if (dictionary.at(i)->getWord() == word) return true;
  }
  return false;
}
  
    
  

void Dictionary::print() {
  for (int i = 0; i < size; i++) {
    Word* temp = dictionary.at(i);
    cout << i << ": ";
    temp ->print();
    //cout << "ID: " << temp->getID() << "\t" << temp->getWord() << endl;
  }
}
					    
