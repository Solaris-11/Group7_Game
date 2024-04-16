#include <iostream>
#include <string>

using namespace std;

struct Setting {
  int sizeX;
  int sizeY;
  int numF;
};

//Main Menu Functions
void RunMainMenu();
void RunNewGame();
void StartEndless(Setting s);
void StartChallenge(Setting s);
void StartCustom();
void PauseMenu();
void RunLoadGame();
void RunTutorial();

//Input Checking Functions
void input1();
bool checkInput1();

void RunMainMenu() {
  //print out the content of the main menu
  cout << string(50, '\n');
  cout << "Memory Matching Game" << endl;
  cout << "Enter (1) for New game" << endl;
  cout << "Enter (2) for Load game" << endl;
  cout << "Enter (3) for Tutorial" << endl;
  cout << "Enter (4) to quit" << endl;

  string userInput;

  //use flag validInput and while loop to check whether the input is valid
  bool validInput = false;
  while (validInput == false) {
    cin >> userInput;
    if (userInput == "1" || userInput == "(1)") {
      validInput1 = true;
      RunNewGame();
    }

    else if (userInput == "2" || userInput == "(2)") {
      validInput1 = true;
      RunLoadGame();
    }

    else if (userInput == "3" || userInput == "(3)") {
      validInput1 = true;
      RunTutorial();
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

void RunNewGame() {
  cout << string(50, '\n');
  cout << "Please choose a mode" << endl;
  cout << "Enter (1) for Endless" << endl;
  cout << "Enter (2) for Challenge" << endl;
  cout << "Enter (3) for Custom" << endl;
  cout << "Enter (4) to quit" << endl;
  cout << "Enter (5) to return to the main menu" << endl;

  string userInput;

  bool validInput = false;
  while (validInput == false) {
      cin >> userInput;
    if (userInput == "1" || userInput == "(1)") {
      validInput = true;
      StartEndless();
    }

    else if (userInput == "2" || userInput == "(2)") {
      validInput = true;
      StartChallenge();
    }

    else if (userInput == "3" || userInput == "(3)") {
      validInput = true;
      Setting s;
      input(s.nRows, s.nCols, s.numF);
      StartCustom(s);
    }

    else if (userInput == "4" || userInput == "(4)") {
      validInput = true;
      RunMainMenu()
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
