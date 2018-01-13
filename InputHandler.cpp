//InputHandler.cpp

#include "InputHandler.h"

#include <iostream>
#include <cstdlib>

using namespace std;

InputHandler::InputHandler(Dictionary *dict, vector<unsigned> &typeTop, vector<unsigned> &functionTop) : dictionary(dict), typeNet(typeTop), typeTopology(typeTop), functionTopology(functionTop), functionNet(functionTop) {
}

void InputHandler::trainTypeNet(string filename) {
  ifstream file(filename.c_str(), ifstream::binary);
  // report any problems opening the file and then exit
  if ( !file.is_open() ) {
      cout << "Unable to open file '" << filename << "'." << endl;
      exit(2);
  }
  int trainingPasses = 0;
  while (true){
    string line;
    getline(file, line);
    if (line=="----") break;
    int count = 0;
    string * words = getWordsInSentence(line, count);
    vector<double> input, target, result;
    for (int i = 0; i < count; i++) {
      double expected;
      file >> expected;
      //Checking to see if the word is already known
      int id = dictionary->getID(words[i]);
      //cout << id << endl;
      //Check to see if the word has a set type, if so no need to run net
      if (dictionary->getWord(id)->hasSetType()) {
	cout << words[i] << " has known type " << dictionary->getWord(id)->getTypeAverage() << endl;
	cout << endl;
      }
      //Otherwise run the net
      else {
	//Initially add the type use to the word before running
	//Set up for net
	dictionary->getWord(id)->addTypeUse(expected);
	trainingPasses++;
	input.clear();
	target.clear();
	
	//Set up input vector
	getTypeNetVectors(words, i, count, input);
	
	//Set up target vector
	expected/=10.0;
	target.push_back(expected);

	//Run the net and get results
	cout << "------ Pass: " << trainingPasses << " ------" << endl;
	runTypeNet(input, result);

	//Print inputs and targets and results
	cout << "Inputs: ";
	printVectorVals(input);
	cout << " | ";
	cout << "Targets: ";
	printVectorVals(target);
	cout <<  endl;
	cout << "Results: ";
	printVectorVals(result);
	cout << endl;

	//Back prop and train net
	typeNet.backProp(target);

	// Report how well the training is working, average over recnet
	cout << "Net recent average error: "
	 << typeNet.getRecentAverageError() << endl;
	cout << endl;
      }
    }
	
      
    string rest;
    getline(file, rest);
    cout << rest << endl;
    

    

    //Cleanup from run (deleting dynamic allocation)
    delete [] words;
  }

  cout << endl << "Training Done" << endl << endl;
}

void InputHandler::evaluateInput(string sentence, vector<double> &fullResult)
{
  int count = 0;
  string * words = getWordsInSentence(sentence, count);
  vector<double> input, result;
  for (int i = 0; i < count; i++) {
      //Checking to see if the word is already known
      int id = dictionary->getID(words[i]);
      //Check to see if the word has a set type, if so no need to run net
      if (dictionary->getWord(id)->hasSetType()) {
	fullResult.push_back(dictionary->getWord(id)->getTypeAverage());
      }
      //Otherwise run the net
      else {
	//Set up for net
	input.clear();
	result.clear();
	//Set up input vector
	getTypeNetVectors(words, i, count, input);

	//Run the net and get results
	runTypeNet(input, result);
	fullResult.push_back(result.at(0) * 10);
      }
  }
  delete [] words;
  cout << endl;

}

void InputHandler::runTypeNet(vector<double> &input, vector<double> &result)
{
  typeNet.feedForward(input);
  typeNet.getResults(result);

}
  

void InputHandler::getTypeNetVectors(string * &words, int index, int count, vector<double> &input) {
  //Adding the word before in the sentence, the word being identified, and the following two words
  //The number added is the average of all uses and types it has been
  //cout << "Words: ";
  int id;
  for (int j = 0; j < typeTopology[0]; j++) {
     if (index-1+j >= 0 && index-1+j < count) {
	id = dictionary->getID(words[index-1+j]);
	double num = dictionary->getWord(id)->getTypeAverage()/10.0;
	input.push_back(num);
	//cout << j << " = " << words[index-1+j] << " ";
     } else input.push_back(0.0);

   }
  //cout << endl;
}
  

string* InputHandler::getWordsInSentence(string line, int& count) {
  string* temp = new string[line.length()]; //Much larger than it needs to be but will be removed soon.
  count = 0;
  for (short i = 0; i < line.length(); i++) {
    if (line[i] == ' ') {
      count++;
    } else {
      temp[count]+=line[i];
    }
  }
  count++;
  string* ret = new string[count]; // Resize string array for more effecient memory use
  for (short i = 0; i < count; i++) {
    ret[i] = temp[i];
    //Adding all words that aren't in the dictionary
    int id = dictionary->getID(temp[i]);
    if (id == -1) {
       dictionary->addWord(temp[i]);
    }
  }
  delete [] temp;
  return ret;
}

void InputHandler::printVectorVals(vector<double> &vec) {
  for (int i = 0; i < vec.size(); i++) {
    cout << " " << vec.at(i);
  }
}

