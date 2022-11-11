

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <queue>
#include <set>
using namespace std;
// a function that will help us to read the word entered by the user
void getWords(string &fword, string &lword) {
  while (true) {
    cout << "Please enter first word: ";
    cin>>fword;
    
    cout << "Please enter second word: ";
    cin>>lword;
    // we compare the length of the two words and if they are equal we continue
    if (fword.length() == lword.length()) {
      break;
    }
    // when the length of the two words are different we request the user
    // to reenter the words of the same length
    cout << "Please enter two words with the same length." << endl;
  }
}



// the function which  help to print the word ladder
void printWordLadder(string fword, string lword){
    
    // creates an empty queue of stacks
    queue<stack<string> > myQueue;
    
    //stack which  holds final word ladder
    stack<string> wordladder;
    
    // creates and adds a stack containing word1 to the queue
    stack<string> myStack;
    myStack.push(fword);
    myQueue.push(myStack);
    
    // creates two sets: one for the dictionary and one for the tested words
    string token;
    ifstream dictionary("EnglishWords.dat");
    set<string> myDictionary;
    set<string> testedWords;
    
    if(dictionary.is_open()) {
      
	      while (dictionary >> token) {
	    	myDictionary.insert(token);
	      }
	      
	      // while the queue is not empty:
	      while (!(myQueue.empty())) {
	        
	        // dequeue the partial-ladder stack from the front of the queue.
			stack<string> ladder = myQueue.front();
			myQueue.pop();
			string word = ladder.top();
		        
			// if the word on top of the stack is the destination word:
			if (word == lword) {
			
			  // Yeey! output the elements of the stack as the solution.
			  cout << "The wordsladder from " << fword << " to " << lword << " is \n";
			 
			  //Copy the ladder stack to worldladder to take it in the order.
			  while(!ladder.empty()){
			  	wordladder.push(ladder.top());
			  	ladder.pop();
			  }
			  while(!wordladder.empty()){
			  	cout<<wordladder.top()<<" > ";
			  	wordladder.pop();
			  }
		} 
		else {
			 
			  string test;
			  for (int i = 0; i < word.size(); i++) {
			    for (char k = 'a'; k <= 'z'; k++) {
			    test = word.substr(0, i) + k + word.substr(i + 1);
		            
			    // if that word is an english word
			    if (myDictionary.count(test)) {
			      
			     
			      if (!testedWords.count(test)) {
				
						// create a copy of the current ladder stack.
						stack<string> copy = ladder;
				                
						// put the neighbor word on top of the copy stack.
						copy.push(test);
				                
						// add the copy stack to the end of the queue.
						myQueue.push(copy);
			      }
			    }
		            
			    // Add test to tested words because it is already used.
			    testedWords.insert(test);
			}
		}
	      }
	    }
    } else {
      cerr << "ERROR: the dictionary can not be opened" << endl;
    }
    
    
}

/* Constants */
const int ALPHA_LENGTH = 26;

/* Prototypes */
void getWords(string &fword, string &lword);
void printWordLadder(string fword, string lword);

/* Main function */
int main() {
    
  string fword, lword;
  getWords(fword, lword); 
  printWordLadder(fword, lword);
    
  return 0;
}



