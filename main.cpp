#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <ios>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include <iomanip>
using namespace std;
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

struct Setting {
  int nRows;
  int nCols;
  int numF;
};

//Main Menu Functions
void RunMainMenu(int selected, vector<string> mainmap);
void RunNewGame(int selected, vector<string> newgame);
void MainChoose();
void ChooseNewGame();
//void StartEndless();  //undefined
//void StartChallenge();
//void StartCustom(Setting s);
//void PauseMenu();
//void RunLoadGame();
//void RunTutorial();

//Checking Input Functions
void CheckInput(int & Rows, int & Cols, int & numF);

void RunMainMenu(int selected, vector<string> mainmap) {
  clearScreen();
  for(int i = 1; i <=4 ;i++){
    if(i == selected){
      cout << ">> " << mainmap[i-1] <<endl;
    }
    else{
      cout << "   " << mainmap[i-1] <<endl;
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

void RunNewGame(int selected, vector<string> newgame) {
  clearScreen();
  for(int i = 1; i <=5 ;i++){
    if(i == selected){
      cout << ">> " << newgame[i-1] <<endl;
    }
    else{
      cout << "   " << newgame[i-1] <<endl;
    }
  }
}
void ChooseNewGame(){
    vector<string> newgame(5);
    newgame[0]= "Endless Mode";
    newgame[1]= "Challenge Mode";
    newgame[2]= "Custom Mode" ;
    newgame[3]= "return to the main menu";
    newgame[4]= "quit";
    setNonCanonicalMode();
    int allInput = 5;
    int userInput = 1;
    while (true) {
        RunNewGame(userInput, newgame);
        char input;
        if (read(STDIN_FILENO, &input, 1) == 1) {
            if (input == 'w') {
                if (userInput > 1) {
                    userInput--;
                }
            } else if (input == 's') {
                if (userInput < allInput) {
                    userInput++;
                }
            } else if (input == '\n') {
                if (userInput <= allInput) {
                    break;
		            }
            }
        }
    }
    restoreTerminalMode();
    if (userInput == 1) {
      cout << "Start Endless Mode"<< endl;
      //StartEndless();
    }

    else if (userInput == 2) {
      cout << "Start Challenge Mode"<< endl;
      //StartChallenge();
    }

    else if (userInput == 3) {
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

    else if (userInput == 4) {
      MainChoose();
    }
    else if (userInput == 5) {
      exit(0);
    }
}

void MainChoose(){
    vector<string> mainmap(4);
    mainmap[0]= "New game";
    mainmap[1]= "Load game";
    mainmap[2]= "Tutorial" ;
    mainmap[3]= "quit";
    setNonCanonicalMode();
    int allselected = 4;
    int selected = 1;
    while (true) {
        RunMainMenu(selected,mainmap);
        char input;
        if (read(STDIN_FILENO, &input, 1) == 1) {
            if (input == 'w') {
                if (selected > 1) {
                    selected--;
                }
            } else if (input == 's') {
                if (selected < allselected) {
                    selected++;
                }
            } else if (input == '\n') {
                if (selected <= allselected) {
                    break;
		            }
            }
        }
    }
    restoreTerminalMode();
  //Use a boolean flag and a while loop to continuously check the validity of the input
    if (selected == 1) {
      ChooseNewGame();
    }

    else if (selected == 2) {
      //RunLoadGame();
    }

    else if (selected == 3) {
      //RunTutorial();
    }

    else if (selected == 4) {
      exit(0);
    }
  } 

int main(){
  MainChoose();
  return 0;
}
