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

      int nRows, nCols, numF;
      string userinput1, userinput2;
      bool validInput1 = false;

      //Take user input, stored in nRows and nCols
      cout << "Enter the desired custom board size (2*2 to 6*6): ";
      while (validInput1 == false) {     //Loop until a valid input is received from the user
        validInput1 = true;
        getline(cin, userinput1);
        if (!(isdigit(userinput1[0])) || userinput1[1] != '*' || !(isdigit(userinput1[2]))){    //Check that the input is in the correct format
          cout << "Input format error! Please input \"nRows*nCols\"" << endl;
          validInput1 = false;
        }

        else {
          stringstream ss(userInput1.substr(0, userInput.find('*')));
          if (!(ss >> nRows)) {    //Verify that the 1st digit of the input is valid
            cout << "Error format! First digit must be a number 2~6" << endl;
            validInput1 = false;
          }

          else if (x > 6 || x < 2) {  //Verify that the 1st input value falls within the acceptable range
            cout << "Out of Range! First digit must be a number 2~6" << endl;
            validInput1 = false;
          }

          ss.str("");	   //Clear the stringstream
          ss.clear();    //Reset error flags

          ss.str(userInput1.substr(userInput1.find('*') + 1));
          if (!(ss >> nCols)) {     //Verify that the 2nd digit of the input is valid
            cout << "Error format! Second digit must be a number 2~6" << endl;
            validInput1 = false;
          }

          else if (x > 6 || x < 2) {   //Verify that the 2nd input value falls within the acceptable range
            cout << "Out of Range! Second digit must be a number 2~6" << endl;
            validInput1 = false;
          }
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

void input(int nRows, int nCols, int numF) {
  string userinput1, userinput2;
  while (true) {
    cout << "Enter the desired custom board size (2*2 to 6*6): ";
    getline(cin, userinput1);
    if (checkInput1(userinput, nRows, nCols)) {
      break;
    }
  }

  while (true) {
    cout << "Enter the desired number of cards to flip at once (2-4): ":
    getline(cin, userinput2);
    stringstream ss(userinput2);
    if (!(ss >> numF)) {
      cout << "Format error! It should be a number 2~4" << endl;
    }
    
  }
  
}
