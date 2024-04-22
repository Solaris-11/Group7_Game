#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <ios>
#include <vector>
#include <iomanip>
#include <termios.h>
#include <unistd.h>
#include "main.h"

using namespace std;

//Move Cursor Functions
void setNonCanonicalMode();
void restoreTerminalMode();
void clearScreen();
void moveCursorTo(int x, int y);

//Main Menu Functions
void RunMainMenu();
void RunNewGame();
void StartEndless();  
void StartNewGame(int numRows, int numCols, int numF);
//void StartChallenge();  //undefined
//void StartCustom(Setting s);
//void PauseMenu();
//void RunLoadGame();
//void RunTutorial();


//Checking Input Functions
void CheckInput(int & Rows, int & Cols, int & numF);

void StartNewGame(int numRows, int numCols, int numF) {
	Board b = {
		numRows,
		numCols,
		numF,
	};
	b.choose(numRows, numCols);
}

// 将终端设置为非规范模式
void setNonCanonicalMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// 恢复终端的规范模式
void restoreTerminalMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// 清空终端屏幕
void clearScreen() {
    cout << "\033[2J";
}

// 移动终端光标到指定位置
void moveCursorTo(int x, int y) {
    cout << "\033[" << y << ";" << x << "H";
}

void CheckInput(int & nRows, int & nCols, int & numF) {
  string userInput1, userInput2;
  bool validInput1 = false, validInput2 = false;

  // Take user input for board size, stored in nRows and nCols
  while (validInput1 == false) {     //Loop until a valid input is received from the user
    cout << "Enter the desired custom board size (2*2 to 6*6): ";
    validInput1 = true;
    getline(cin, userInput1);

    // Check input format
    if (!(isdigit(userInput1[0])) || userInput1[1] != '*' || !(isdigit(userInput1[2]))){    
      cout << "Input format error! Please input \"nRows*nCols\"" << endl;
      validInput1 = false;
    }

    else {
      stringstream ss(userInput1.substr(0, userInput1.find('*')));
      if (!(ss >> nRows)) {    //Verify that the 1st digit of the input is a number
        cout << "Format error! First digit must be a number 2~6" << endl;
        validInput1 = false;
      }

      else if (nRows > 6 || nRows < 2) {  //Verify that the 1st input value falls within the acceptable range
        cout << "Out of Range! First digit must be a number 2~6" << endl;
        validInput1 = false;
      }

      ss.str("");    //Clear the stringstream
      ss.clear();    //Reset error flags

      ss.str(userInput1.substr(userInput1.find('*') + 1));
      if (!(ss >> nCols)) {     //Verify that the 2nd digit of the input is a number
        cout << "Format error! Second digit must be a number 2~6" << endl;
        validInput1 = false;
      }

      else if (nCols > 6 || nCols < 2) {   //Verify that the 2nd input value falls within the acceptable range
        cout << "Out of Range! Second digit must be a number 2~6" << endl;
        validInput1 = false;
      }
    }
  }

  //Take user input for the number of cards to flip, stored in numF
  while (validInput2 == false) {
    cout << "Enter number of cards to flip (2-4): ";
    validInput2 = true;
    getline(cin, userInput2);
    stringstream ss(userInput2);

    if (!(ss >> numF)) {      // Verify the input is a number
      cout << "Format error! It should be a number 2~4" << endl;
      validInput2 = false;
    }

    else if (numF < 2 || numF > 4) {
      cout << "Out of range! It should be a number 2~4" << endl;
      validInput2 = false;
    }
  }
}

void RunNewGame(){
  //Vector to store the new game options
  vector<string> newgame(5);
  newgame[0]= "Endless Mode";               //Option 1: Endless Mode
  newgame[1]= "Challenge Mode";             //Option 2: Challenge Mode
  newgame[2]= "Custom Mode" ;               //Option 3: Custom Mode
  newgame[3]= "Return to Main Menu";        //Option 4: Return to Main Menu
  newgame[4]= "Quit";                       //Option 5: Quit
	
  setNonCanonicalMode();   // Set terminal to non-canonical mode
  int numOpts = 5;         // Total number of options
  int currSel = 1;         // Currently selected option

  while (true) {
    clearScreen();         // Clear the terminal screen
	  
    cout << "   "<< "Choose a mode" << endl;
    cout << endl;
	  
    for(int i = 1; i <=5 ;i++){
      if(i == currSel){
        cout << ">> " << newgame[i-1] <<endl;    // Print selected option with a cursor (>>)
      }
	      
      else{
        cout << "   " << newgame[i-1] <<endl;    // Print non-selected options
      }
    }

    char userInput;
    if (read(STDIN_FILENO, &userInput, 1) == 1) {
      if (userInput == 'w') {     // If 'w' key is pressed
        if (currSel > 1) {    // Move selection up if not already at the top
          currSel--;
        }
      } 
    
      else if (userInput == 's') {       // If 's' key is pressed
        if (currSel < numOpts) {     // Move selection down if not already at the bottom
          currSel++;
         }
      } 
    
      else if (userInput == '\n') {
        if (currSel <= numOpts) {    // If Enter key is pressed and a valid option is selected
          break;                     // Exit the while loop
        }
      }
    }
  }
	
  restoreTerminalMode();          // Restore terminal to canonical mode

  if (currSel == 1) {
    cout << "Start Endless Mode"<< endl;
    StartEndless();             // Call function for Option 1: Endless Mode
  }

  else if (currSel == 2) {
    cout << "Start Challenge Mode"<< endl;
    //StartChallenge();           // Call function for Option 2: Challenge Mode
  }

  else if (currSel == 3) {        // Call function for Option 3: Custom Mode
    int nRows, nCols, numF;
    CheckInput(nRows, nCols, numF);
    while ((nRows * nCols) % numF != 0) {
      cout << "Error! Board size must be a multiple of the number of cards flipped" << endl;
      CheckInput(nRows, nCols, numF);
    }
  }

  else if (currSel == 4) {       // Call function for Option 4: Return to Main Menu
    RunMainMenu();
    }
	  
  else if (currSel == 5) {       // Exit the program for Option 5: Quit
    exit(0);
  }
}

void RunMainMenu(){
  //Vector to store the main menu options
  vector<string> mainmap(4);
  mainmap[0]= "New game";   //Option 1: New game
  mainmap[1]= "Load game";  //Option 2: Load game
  mainmap[2]= "Tutorial" ;  //Option 3: Tutorial
  mainmap[3]= "Quit";       //Option 4: Quit

  setNonCanonicalMode();    // Set terminal to non-canonical mode
  int numOpts = 4;          // Total number of options
  int currSel = 1;          // Currently selected option

  while (true) {
    clearScreen();     // Clear the terminal screen
	  
    cout << "   " << "[Memory Matching Game]" << endl;
    cout << endl;
	  
    for(int i = 1; i <=4 ;i++){
      if(i == currSel){
        cout << ">> " << mainmap[i-1] <<endl;    // Print selected option with a cursor (>>)
      }
	      
       else{
        cout << "   " << mainmap[i-1] <<endl;    // Print non-selected options
       }
    }
	    
    char userInput;
    if (read(STDIN_FILENO, &userInput, 1) == 1) {
      if (userInput == 'w') {      // If 'w' key is pressed
        if (currSel > 1) {     // Move selection up if not already at the top
          currSel--;
        }
      }
	    
      else if (userInput == 's') {     // If 's' key is pressed
        if (currSel < numOpts) {   // Move selection down if not already at the bottom
          currSel++;
        }
      } 
	    
      else if (userInput == '\n') {    
        if (currSel <= numOpts) {  // If Enter key is pressed and a valid option is selected
          break;                   // Exit the while loop
        }
      }
    }
  }
	
  restoreTerminalMode();       // Restore terminal to canonical mode
	
  if (currSel == 1) {          // Call function for Option 1: New game
    RunNewGame();
  }

  else if (currSel == 2) {     // Call function for Option 2: Load game
    //RunLoadGame();
  }

  else if (currSel == 3) {     // Call function for Option 3: Tutorial
    //RunTutorial();
  }

  else if (currSel == 4) {     // Exit the program for Option 4: Quit
    exit(0);
  }
} 

void StartEndless(){
  vector<string> difficulties (5);
  difficulties[0] = "Easy Mode";
  difficulties[1] = "Hard Mode";
  difficulties[2] = "Return to Previous menu";
  difficulties[3] = "Return to Main menu";
  difficulties[4] = "Quit";
	
  setNonCanonicalMode();
	
  int allInputDiff = 5;
  int userInputDiff = 1;
  while (true) {
    clearScreen();
    cout << "   " << "[Choose Difficulty]" << endl;
    cout << endl;
	  
    for (int j = 1; j <= difficulties.size(); j++) {
      if (j == userInputDiff) {
        cout << ">> " << difficulties[j-1] << endl;
      }
      else {
        cout << "   " << difficulties[j-1] << endl;
      }
    }

    char input;
    if (read(STDIN_FILENO, &input, 1) == 1) {
      if (input == 'w') {
        if (userInputDiff > 1) {
          userInputDiff--;
        }
      } else if (input == 's') {
          if (userInputDiff < allInputDiff) {
              userInputDiff++;
          }
      } else if (input == '\n') {
          if (userInputDiff <= allInputDiff) {
              break;
	        }
      }
    }
  }
	
  restoreTerminalMode();
  if (userInputDiff == 1){
    cout << "Start Easy Mode" << endl;
    StartNewGame(4,2,2);
  }
  else if (userInputDiff == 2){
    cout << "Start Hard Mode" << endl;
    StartNewGame(3,3,3);
  }
  else if (userInputDiff == 3){
    RunNewGame();
  }
  else if (userInputDiff == 4){
    RunMainMenu();
  }
  else if (userInputDiff == 5){
    exit(0);
  }
}

int main(){
  RunMainMenu();
  return 0;
}
