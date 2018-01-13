//InputHandler.h

//InputHandler is where the input is sent. It breaks down sentences into the key parts such as subject, verb, target noun (ie 'kitchen' in 'Tommy is in the kitchen'), and input type (request, question, opinion, statement).
//Additionally, will contain the neural network that all the information is plugged into that generates responses.
//This is the brain of the program.
#ifndef INPUT_HANDLER
#define INPUT_HANDLER

#include "Dictionary.h"
#include <string>
#include <vector>
#include "Net.h"
#include <fstream>



class InputHandler {
 public:
  InputHandler(Dictionary * dict, vector<unsigned> &typeTop, vector<unsigned> &functionTop);
  void trainTypeNet(string filename); //Trains the typeNet
  void trainFunctionNet(string filename); //trains the functionNet
  void evaluateInput(string sentence, vector<double> &fullResult); //Run a specific sentence, does not train the net but places all values into fullResult
 private:
  string* getWordsInSentence(string line, int &count); // takes in the line and a reference to an int. returns a string array of the words and sets the int equal to the number of words in the sentence;
  void getTypeNetVectors(string * &words, int index, int count, vector<double> &input); // Method for getting the values to be passed into the net
  void runTypeNet(vector<double> &input, vector<double> &result); // Method for running the typeNet
  Net typeNet; // For determining type of words based on location in sentence
  Net functionNet; // For determining function of words based on location and type, is fed by the typeNet
  Dictionary  *dictionary;
  void printVectorVals(vector<double> &vec);
  vector<unsigned>& typeTopology;
  vector<unsigned>& functionTopology;
};

#endif
  
  
  
  
  
