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
#include "MoveCursor.h"

using namespace std;

// Main Menu Functions
void RunMainMenu();
void RunNewGame();
void StartEndless();  
void StartEasyEndless();
void StartHardEndless();
void StartChallenge();
//void PauseMenu();
//void RunLoadGame();
//void RunTutorial();

// Checking Input Functions
void CheckInput(int & numRows, int & numCols, int & numF);

// Function: CheckInput
// Effect: Check the userinputs for validity; Stored them in numRows, numCols and numF respectively
void CheckInput(int &numRows, int &numCols, int &numF) {
    string userInput1, userInput2;
    bool validInput1 = false, validInput2 = false;

    // Take user userInput for board size, stored in numRows and numCols
    while (validInput1 == false) {  // Loop until a valid userInput is received from the user
        cout << "Enter the desired custom board size (2*2 to 6*6): ";
        validInput1 = true;
        getline(cin, userInput1);

        // Check userInput format
        if (!(isdigit(userInput1[0])) || userInput1[1] != '*' || !(isdigit(userInput1[2]))) {
            cout << "Input format error! Please userInput \"numRows*numCols\"" << endl;
            validInput1 = false;
        } else {
            stringstream ss(userInput1.substr(0, userInput1.find('*')));
            if (!(ss >> numRows)) {  // Verify that the 1st digit of the userInput is a number
                cout << "Format error! First digit must be a number 2~6" << endl;
                validInput1 = false;
            } else if (numRows > 6 || numRows < 2) {  // Verify that the 1st userInput value falls within the acceptable range
                cout << "Out of Range! First digit must be a number 2~6" << endl;
                validInput1 = false;
            }

            ss.str("");  // Clear the stringstream
            ss.clear();  // Reset error flags

            ss.str(userInput1.substr(userInput1.find('*') + 1));
            if (!(ss >> numCols)) {  // Verify that the 2nd digit of the userInput is a number
                cout << "Format error! Second digit must be a number 2~6" << endl;
                validInput1 = false;
            } else if (numCols > 6 || numCols < 2) {  // Verify that the 2nd userInput value falls within the acceptable range
                cout << "Out of Range! Second digit must be a number 2~6" << endl;
                validInput1 = false;
            }
        }
    }

    // Take user userInput for the number of cards to flip, stored in numF
    while (validInput2 == false) {
        cout << "Enter number of cards to flip (2-4): ";
        validInput2 = true;
        getline(cin, userInput2);
        stringstream ss(userInput2);

        if (!(ss >> numF)) {  // Verify the userInput is a number
            cout << "Format error! It should be a number 2~4" << endl;
            validInput2 = false;
        } else if (numF < 2 || numF > 4) {    // Verify that the value falls within the acceptable range
            cout << "Out of range! It should be a number 2~4" << endl;
            validInput2 = false;
        }
    }
}

// Function: StartEasyEndless
// This function starts the endless mode in easy difficulty
// It consists of three rounds, and the settings for each round are stored in the EasySetting 2D array
// The function uses a while loop to proceed to the next round after completing each round
// The settings for the current round are read from EasySetting and passed to the Board object
// The StartNewRound function of the Board is called to start the game
void StartEasyEndless() {
	// Difficulty Initialization
    int EasySetting[3][3] ={{2, 4, 2}, {3, 4, 2}, {4, 4, 2}};
	int round = 1;

	// Endless mode: infinite loop
    while (round <= 3) {
        // Start a new round of game
        cout << "Current Round: " << round << endl;

        // Read the settings from EasySetting and store them in Board
		int numRows = EasySetting[round - 1][0];   
		int numCols = EasySetting[round - 1][1];
		int numF = EasySetting[round - 1][2];
		Board b = {numRows, numCols, numF};

        // Start the new round
		b.StartNewRound(numRows, numCols, numF, -1, 1);

		// Game over
        cout << "Congratulations! You Pass Round:" << round << endl;
		cout << "Now Going to the Next Round..." <<  endl;
		sleep(1);    // Pause for 1 second and continue with the next game
        round++;
    }
}

// Function: StartHardEndless
// This function starts the endless mode in hard difficulty
// It consists of three rounds, and the settings for each round are stored in the HardSetting 2D array
// The function uses a while loop to proceed to the next round after completing each round
// The settings for the current round are read from HardSetting and passed to the Board object
// The StartNewRound function of the Board is called to start the game
void StartHardEndless() {
    // Difficulty Initialization
    int HardSetting[3][3] = {{3, 3, 3},{3, 4, 3}, {3, 5, 3}};
    int round = 1;

    // Endless mode: infinite loop
    while (round <= 3) {
        // Start a new round of game
        cout << "Current Round: " << round << endl;

        // Read the settings from EasySetting and store them in Board
		int numRows = HardSetting[round - 1][0];
		int numCols = HardSetting[round - 1][1];
		int numF = HardSetting[round - 1][2];
		Board b = {numRows, numCols, numF};

        // Start the new round
		b.StartNewRound(numRows, numCols, numF, -1, 1);
		// Game over
        cout << "Congratulations! You Pass Round:" << round << endl;
		cout << "Now Going to the Next Round..." <<  endl;
		// Pause for 1 second and continue with the next game
		sleep(1);
        round++;
    }
}

// Function: StartEndless
// Prompt the user to choose a difficulty
// Direct them to different pages based on their selection
void StartEndless() {
    // Vector to store the new game options
    vector<string> difficulties(5); 
    difficulties[0] = "Easy Mode";                   // Option 1: Easy Mode
    difficulties[1] = "Hard Mode";                   // Option 2: Hard Mode
    difficulties[2] = "Return to Previous menu";     // Option 3: Return to Previous menu
    difficulties[3] = "Return to Main menu";         // Option 4: Return to Main menu
    difficulties[4] = "Quit";                        // Option 5: Quit

    setNonCanonicalMode();     // Set terminal to non-canonical mode
    int numOpts = 5;           // Total number of options
    int currSel = 1;           // Currently selected option

    while (true) {
        clearScreen();      // Clear the terminal screen
        cout << "   " << "[Choose Difficulty]" << endl;
        cout << endl;

        for (int j = 1; j <= difficulties.size(); j++) {
            if (j == currSel ) {
                cout << ">> " << difficulties[j - 1] << endl;     // Print selected option with a cursor (>>)
            } else {
                cout << "   " << difficulties[j - 1] << endl;     // Print non-selected options
            }
        }

        char userInput;
		read(STDIN_FILENO, &userInput, 1);
        if (userInput == 'w') {               // If 'w' key is pressed
			if (currSel  > 1) {               // Move selection up if not already at the top
				currSel --;
			}
		} else if (userInput == 's') {        // If 's' key is pressed
			if (currSel  < numOpts) {         // Move selection down if not already at the bottom
				currSel ++;
			}
		} else if (userInput == '\n') {       // If '\n' key is pressed
			if (currSel  <= numOpts) {        // Exit the while loop
				break;
			}
		}
    }

    restoreTerminalMode();        // Restore terminal to canonical mode

    if (currSel  == 1) {
        StartEasyEndless();            // Call function for Option 1: Easy Mode
    } else if (currSel  == 2) {
        StartHardEndless();            // Call function for Option 2: Hard Mode
    } else if (currSel  == 3) {        
        RunNewGame();                  // Call function for Option 3: Return to Previous menu
    } else if (currSel  == 4) {
        RunMainMenu();                 // Call function for Option 3: Return to Main menu
    } else if (currSel  == 5) {
        exit(0);                       // Exit the program for Option 5: Quit
    }
}

// Function: StartChallenge
// This function starts the challenge mode
// The difficulty settings include the number of rows, columns, and hidden cards (numRows, numCols, numF)
// The maximum number of moves allowed is specified by maxMove
// The time limit for each move is set to time (in seconds)
void StartChallenge() {
	// Difficulty settings
	int numRows = 3, numCols = 5, numF = 3;
	int maxMove = 30;
	int time = 0.5;

	// Display welcome message and instructions
	cout << "Welcome to Challenge Mode!" << endl;
	cout << "Note: You Need to Find All Cards in " << maxMove << " Move" << endl;
	
    // Start the game
	Board b = {numRows, numCols, numF};
    double points = b.StartNewRound(numRows, numCols, numF, maxMove, 0.5);
	
    // If the challenge is passed
	if (points != -1) {
		cout << "Congratulations! You Pass the Challenge Mode!" << endl;
	}
	
    // If the challenge is not passed
	else {
		cout << "Unfortunately! You Didn't Pass the Challenge Mode!" << endl;
	}
}

// Function: RunNewGame
// Prompt the user to choose a mode
// Direct them to different pages based on their selection
void RunNewGame() {
    // Vector to store the new game options
    vector<string> newgame(5);
    newgame[0] = "Endless Mode";          // Option 1: Endless Mode
    newgame[1] = "Challenge Mode";        // Option 2: Challenge Mode
    newgame[2] = "Custom Mode";           // Option 3: Custom Mode
    newgame[3] = "Return to Main Menu";   // Option 4: Return to Main Menu
    newgame[4] = "Quit";                  // Option 5: Quit

    setNonCanonicalMode();   // Set terminal to non-canonical mode
    int numOpts = 5;         // Total number of options
    int currSel = 1;         // Currently selected option

    while (true) {
        clearScreen();       // Clear the terminal screen
        cout << "   " << "[Choose a mode]" << endl;
        cout << endl;

        for (int i = 1; i <= 5; i++) {
            if (i == currSel) {
                cout << ">> " << newgame[i - 1] << endl;   // Print selected option with a cursor (>>)
            } else {
                cout << "   " << newgame[i - 1] << endl;   // Print non-selected options
            }
        }

        char userInput;
		read(STDIN_FILENO, &userInput, 1);
		if (userInput == 'w') {     // If 'w' key is pressed
			if (currSel > 1) {      // Move selection up if not already at the top
				currSel--;
			}
		} else if (userInput == 's') {  // If 's' key is pressed
			if (currSel < numOpts) {   // Move selection down if not already at the bottom
				currSel++;
			}
		} else if (userInput == '\n') {
			if (currSel <= numOpts) {  // If Enter key is pressed and a valid option is selected
				break;                 // Exit the while loop
			}
		}
    }

    restoreTerminalMode();   // Restore terminal to canonical mode

    if (currSel == 1) {
        cout << "Start Endless Mode" << endl;
        StartEndless();        // Call function for Option 1: Endless Mode
    } else if (currSel == 2) {
        cout << "Start Challenge Mode" << endl;
        StartChallenge();      // Call function for Option 2: Challenge Mode
    } else if (currSel == 3) {   // Call function for Option 3: Custom Mode
        int numRows, numCols, numF;
        CheckInput(numRows, numCols, numF);
        while ((numRows * numCols) % numF != 0) {
            cout << "Error! Board size must be a multiple of the number of cards flipped" << endl;
            CheckInput(numRows, numCols, numF);
        }
        // 开启一轮游戏
		Board b = {numRows, numCols, numF};
		b.StartNewRound(numRows, numCols, numF, -1, 1);
    } else if (currSel == 4) {   // Call function for Option 4: Return to Main Menu
        RunMainMenu();
    } else if (currSel == 5) {   // Exit the program for Option 5: Quit
        exit(0);
    }
}

// Function: RunMainMenu
// Prompt the user to choose an option
// Direct them to different pages based on their selection
void RunMainMenu() {
    // Vector to store the main menu options
    vector<string> mainmap(4);
    mainmap[0] = "New game";   // Option 1: New game
    mainmap[1] = "Load game";  // Option 2: Load game
    mainmap[2] = "Tutorial";   // Option 3: Tutorial
    mainmap[3] = "Quit";       // Option 4: Quit

    setNonCanonicalMode();    // Set terminal to non-canonical mode
    int numOpts = 4;          // Total number of options
    int currSel = 1;          // Currently selected option

    while (true) {
        clearScreen();        // Clear the terminal screen

        cout << "   " << "[Memory Matching Game]" << endl;
        cout << endl;

        for (int i = 1; i <= 4; i++) {
            if (i == currSel) {
                cout << ">> " << mainmap[i - 1] << endl;   // Print selected option with a cursor (>>)
            } else {
                cout << "   " << mainmap[i - 1] << endl;   // Print non-selected options
            }
        }

        char userInput;
		read(STDIN_FILENO, &userInput, 1);
		if (userInput == 'w') {      // If 'w' key is pressed
			if (currSel > 1) {     // Move selection up if not already at the top
				currSel--;
			}
		} else if (userInput == 's') {  // If 's' key is pressed
			if (currSel < numOpts) {   // Move selection down if not already at the bottom
				currSel++;
			}
		} else if (userInput == '\n') {
			if (currSel <= numOpts) {  // If Enter key is pressed and a valid option is selected
				break;                   // Exit the while loop
			}
		}
    }

    restoreTerminalMode();       // Restore terminal to canonical mode

    if (currSel == 1) {          // Call function for Option 1: New game
        RunNewGame();
    } else if (currSel == 2) {   // Call function for Option 2: Load game
        //RunLoadGame();
    } else if (currSel == 3) {   // Call function for Option 3: Tutorial
        //RunTutorial();
    } else if (currSel == 4) {   // Exit the program for Option 4: Quit
        exit(0);
    }
}

int main() {
    RunMainMenu();
    return 0;
}
