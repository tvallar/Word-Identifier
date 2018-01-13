//Main.cpp

#include "Dictionary.h"
#include "Word.h"
#include "Neuron.h"
#include "Net.h"
#include "InputHandler.h"
#include "Constants.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <tgmath.h>

using namespace std;

//Reads words from a basic dictionary filled with the most common words
void buildDictionary(Dictionary& dictionary);
//Function for making a string all lower case
void toLowerCase(string &in);
//Converts net results to form that can be understood easily
void printResults(vector<double> &results);
//Runs menu to remove clutter from main() function
void runMenu(InputHandler &inHandler, Dictionary &dictionary);

int main() {
  Dictionary dictionary("Dictionary");
  buildDictionary(dictionary);
  vector<unsigned> typeTop; // Net Topology for the Type Net
  typeTop.push_back(4);
  typeTop.push_back(6);
  typeTop.push_back(1);
  vector<unsigned> functionTop; // Net topology for the function net
  //The function net is not implemented yet
  functionTop.push_back(1);
  functionTop.push_back(1);
  InputHandler inHandler(&dictionary, typeTop, functionTop);
  inHandler.trainTypeNet("typetraining2.txt");
  runMenu(inHandler, dictionary);
  return 0;
}

void runMenu(InputHandler &inHandler, Dictionary &dictionary) {
  cout << "-------Word Identifier-------" << endl;
  cout << "The dictionary is quite limited at the moment and entering \na word not in the dictionary will most likely return incorrect results." << endl << endl;
  cout << "Additionally, the training data is not complete and some words in \nthe dictionary have not been trained for. Results may not always be accurate." << endl;
  while (true) {
    cout << "----------------------------------" << endl;
    cout << "To run a sentence through the identifier, enter 0. \nTo check the dictionary for a specific word or words, enter 1. \nTo quit, enter 2." << endl;
    string choice;
    cin >> choice;
    if (choice == "0") {
      cout << "----------------------------------" << endl;
      string sentence;
      string firstWord;
      cout << "Enter the sentence:" << endl;
      cin >> firstWord;
      getline(cin, sentence);
      sentence = firstWord + sentence;;
      toLowerCase(sentence);
      vector<double> result;
      inHandler.evaluateInput(sentence, result);
      printResults(result);
    } else if (choice =="1") {
      cout << "----------------------------------" << endl;
      string word;
      while (true) {
	cout << "Enter the word." << endl;
	cin>>word;
	toLowerCase(word);
	if (dictionary.getID(word) != -1)
	  cout << "The word is in the dictionary" << endl;
	else cout << "The word is not in the dictionary" << endl;
	cout << endl;
	cout << "Check for another word? \nEnter y to check another word, n to return to main menu" << endl;
	string response;
	cin >> response;
	if (response == "Y" || response == "y") {}
	else break;
      }
    } else if (choice == "2") {
      break;
    }else {
      cout << "Please enter a valid response." << endl;
    }
  }


}

void toLowerCase(string &in) {
  for (int i = 0; i < in.length(); i++) {
    if(in[i]<='Z' && in[i]>='A' && in[i] != ' ')
     in[i]-=('Z'-'z');
  }
}

void buildDictionary(Dictionary& dictionary) {
  ifstream file("words_minimal.txt", ifstream::binary);
  // report any problems opening the file and then exit
  if ( !file.is_open() ) {
      cout << "Unable to open file '" << "words.txt" << "'." << endl;
      exit(2);
  }
  // read in two strings
  string s1, s2, s3;
  file >> s1;
  // output those strings
  cout << s1 << endl;
  bool knownWords=false;
  int type;
  while(true) {
    file >> s1;
    cout << s1 << endl;
    if (s1 == "----") break;
    if (s1 == "**") {
      knownWords = true;
      getline(file, s2);
    }
    else if (s1 == "*") {
      knownWords = false;
      getline(file, s2);
    }
    else if (s1 == "##") {
      getline(file, s2);
    }
    else {
      if (knownWords) {
	type = s1[0] - '0';
	file >> s2;
	dictionary.addWord(s2, type);
      } else {
	dictionary.addWord(s1);
      }
    }
    
  }
  cout << "Test";
  dictionary.print();
  // close the file before exiting
  file.close();
  //Dictionary Filled, Next create the neural Net
 
}

void printResults(vector<double> &results) {
  int type;
  string word;
  for (int i = 0; i < results.size(); i++) {
    if (results.at(i) < 1.0) type = 1;
    else type = round(results.at(i));
    switch(type){
    case NOUN: {
      word = "noun";
      break;
    }
    case PRONOUN: {
      word = "pronoun";
      break;
    }
    case VERB: {
      word = "verb";
      break;
    }
    case ADJECTIVE: {
      word = "adjective";
      break;
    }
    case QUESTION: {
      word = "question word";
      break;
    }
    case ADVERB: {
      word = "adverb";
      break;
    }
    case CONJUNCTION: {
      word = "conjunction";
      break;
    }
    case PREPOSITION: {
      word = "preposition";
      break;
    }
    case DETERMINER: {
      word = "determiner";
      break;
    }
    default: {
      word = "unknown";
      break;
    }
    }
    cout << "Word " << i << ": " << word << endl;
  }
}
  
