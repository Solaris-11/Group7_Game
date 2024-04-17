#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <ios>

using namespace std;

struct Setting {
  int nRows;
  int nCols;
  int numF;
};

//Main Menu Functions
void RunMainMenu();
void RunNewGame();
//void StartEndless();  //undefined
//void StartChallenge();
//void StartCustom(Setting s);
//void PauseMenu();
//void RunLoadGame();
//void RunTutorial();

//Checking Input Functions
void CheckInput(int & Rows, int & Cols, int & numF);

void RunMainMenu() {
  cout << string(50, '\n');
  cout << "Memory Matching Game" << endl;
  cout << "Enter (1) for New game" << endl;
  cout << "Enter (2) for Load game" << endl;
  cout << "Enter (3) for Tutorial" << endl;
  cout << "Enter (4) to quit" << endl;

  string userInput;

  //Use a boolean flag and a while loop to continuously check the validity of the input
  bool validInput = false;
  while (validInput == false) {
    cin >> userInput;
    if (userInput == "1" || userInput == "(1)") {
      validInput = true;
      RunNewGame();
    }

    else if (userInput == "2" || userInput == "(2)") {
      validInput = true;
      //RunLoadGame();
    }

    else if (userInput == "3" || userInput == "(3)") {
      validInput = true;
      //RunTutorial();
    }

    else if (userInput == "4" || userInput == "(4)") {
      validInput = true;
      exit(0);
    }

    else {
      cout << "Invalid user input. Please try again." << endl;
      cout << "Memory Matching Game" << endl;
      cout << "Enter (1) for New game" << endl;
      cout << "Enter (2) for Load game" << endl;
      cout << "Enter (3) for Tutorial" << endl;
      cout << "Enter (4) to quit" << endl;
    } 
  } 
}

void CheckInput(int & nRows, int & nCols, int & numF) {
  string userInput1, userInput2;
  bool validInput1 = false, validInput2 = false;

  // Clear the input buffer
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  //Take user input, stored in nRows and nCols
  cout << "Enter the desired custom board size (2*2 to 6*6): ";
  while (validInput1 == false) {     //Loop until a valid input is received from the user
    validInput1 = true;
    getline(cin, userInput1);
    if (!(isdigit(userInput1[0])) || userInput1[1] != '*' || !(isdigit(userInput1[2]))){    //Check that the input is in the correct format
      cout << "Input format error! Please input \"nRows*nCols\"" << endl;
      validInput1 = false;
    }

    else {
      stringstream ss(userInput1.substr(0, userInput1.find('*')));
      if (!(ss >> nRows)) {    //Verify that the 1st digit of the input is valid
        cout << "Format error! First digit must be a number 2~6" << endl;
        validInput1 = false;
      }

      else if (nRows > 6 || nRows < 2) {  //Verify that the 1st input value falls within the acceptable range
        cout << "Out of Range! First digit must be a number 2~6" << endl;
        validInput1 = false;
      }

      ss.str("");	   //Clear the stringstream
      ss.clear();    //Reset error flags

      ss.str(userInput1.substr(userInput1.find('*') + 1));
      if (!(ss >> nCols)) {     //Verify that the 2nd digit of the input is valid
        cout << "Format error! Second digit must be a number 2~6" << endl;
        validInput1 = false;
      }

      else if (nCols > 6 || nCols < 2) {   //Verify that the 2nd input value falls within the acceptable range
        cout << "Out of Range! Second digit must be a number 2~6" << endl;
        validInput1 = false;
      }
    }
  }

  //Take user input, stored in numF
  cout << "Enter number of cards to flip (2-4): ";
  while (validInput2 == false) {
    validInput2 = true;
    getline(cin, userInput2);
    stringstream ss(userInput2);

    if (!(ss >> numF)) {
      cout << "Format error! It should be a number 2~4" << endl;
      validInput2 = false;
    }

    else if (numF < 2 || numF > 4) {
      cout << "Out of range! It should be a number 2~4" << endl;
      validInput2 = false;
    }
  }
}

void RunNewGame() {
  cout << string(50, '\n');
  cout << "Please choose a mode" << endl;
  cout << "Enter (1) for Endless" << endl;
  cout << "Enter (2) for Challenge" << endl;
  cout << "Enter (3) for Custom" << endl;
  cout << "Enter (4) to quit" << endl;
  cout << "Enter (5) to return to the main menu" << endl;

  string userInput;

  //Use a boolean flag and a while loop to continuously check the validity of the input
  bool validInput = false;
  while (validInput == false) {
      cin >> userInput;
    if (userInput == "1" || userInput == "(1)") {
      validInput = true;
      //StartEndless();
    }

    else if (userInput == "2" || userInput == "(2)") {
      validInput = true;
      //StartChallenge();
    }

    else if (userInput == "3" || userInput == "(3)") {
      validInput = true;

      int nRows, nCols, numF;
      CheckInput(nRows, nCols, numF);
      while ((nRows * nCols) % numF != 0) {
        cout << "Error! Board size must be a multiple of the number of cards flipped" << endl;
        CheckInput(nRows, nCols, numF);
      }
        
      //Store the info in a struct
      Setting c = {nRows, nCols, numF};
      //StartCustom(c);
    }

    else if (userInput == "4" || userInput == "(4)") {
      validInput = true;
      RunMainMenu();
    }

    else if (userInput == "5" || userInput == "(5)") {
      validInput = true;
      exit(0);
    }
      
    else {
      cout << "Invalid user input. Please try again." << endl;
      cout << "Please choose a mode" << endl;
      cout << "Enter (1) for Endless" << endl;
      cout << "Enter (2) for Challenge" << endl;
      cout << "Enter (3) for Custom" << endl;
      cout << "Enter (4) to quit" << endl;
      cout << "Enter (5) to return to the main menu" << endl;
    }  
  }
}

int main() {
  RunMainMenu();
  return 0;
}
