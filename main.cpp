#include <iostream>
#include <fstream>
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
void RunPauseMenu();
void RunLoadGame();
void RunTutorial();

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
void StartEasyEndless(int round, Board b1, bool new1) {
	// Difficulty Initialization
    int EasySetting[3][3] ={{2, 4, 2}, {3, 4, 2}, {4, 4, 2}};
    Board b;
	// Endless mode: infinite loop
    while (round <= 3) {
        // Start a new round of game
        // Read the settings from EasySetting and store them in Board
        if(new1==true){
	    b = {
            "Endless",
            "Easy",
            round,

            EasySetting[round - 1][0],
            EasySetting[round - 1][1],
            EasySetting[round - 1][2],
            -1,
            1,

            0,
            0,
            EasySetting[round - 1][0],
            1,

            vector<vector<int> > (EasySetting[round - 1][0], vector<int>(EasySetting[round - 1][1])),
            vector<vector<bool> > (EasySetting[round - 1][0],vector<bool>(EasySetting[round - 1][1],false)),

            0,
            0,
            false,
            false,
            true,

            vector<int> (EasySetting[round - 1][2]),
            vector<vector<int> > (EasySetting[round - 1][2],vector<int>(EasySetting[round - 1][2])),
            };

            // Start the new round
            b.shuffle();  // Initialize and shuffle the cards
        }
        else{
            b = b1;
        }
		b.StartNewRound();

		// Game over
		sleep(1);    // Pause for 1 second and continue with the next game
        round++;
        new1 = true;
    }

    // Pass 3 rounds in Easy Endless mode
    // Go back to "Choose Difficulty" of "Endless Mode" page
    StartEndless();
}

// Function: StartHardEndless
// This function starts the endless mode in hard difficulty
// It consists of three rounds, and the settings for each round are stored in the HardSetting 2D array
// The function uses a while loop to proceed to the next round after completing each round
// The settings for the current round are read from HardSetting and passed to the Board object
// The StartNewRound function of the Board is called to start the game
void StartHardEndless(int round, Board b1, bool new1) {
    // Difficulty Initialization
    int HardSetting[3][3] = {{3, 3, 3},{3, 4, 3}, {3, 5, 3}};
    Board b;
    // Endless mode: infinite loop
    while (round <= 3) {
        // Start a new round of game
        // Read the settings from EasySetting and store them in Board
	    if(new1 == true){
            b = {
            "Endless",
            "Hard",
            round,

            HardSetting[round - 1][0],
            HardSetting[round - 1][1],
            HardSetting[round - 1][2],
            -1,
            1,

            0,
            0,
            HardSetting[round - 1][0],
            1,

            vector<vector<int> > (HardSetting[round - 1][0], vector<int>(HardSetting[round - 1][1])),
            vector<vector<bool> > (HardSetting[round - 1][0],vector<bool>(HardSetting[round - 1][1],false)),

            0,
            0,
            false,
            false,
            true,

            vector<int> (HardSetting[round - 1][2]),
            vector<vector<int> > (HardSetting[round - 1][2],vector<int>(HardSetting[round - 1][2])),
            };
            // Start the new round
            b.shuffle();  // Initialize and shuffle the cards
        }else{
            b =b1;
        }
	    b.StartNewRound();

	    // Game over
	    sleep(1);    // Pause for 1 second and continue with the next game
        round++;
        new1 = true;
    }

    // Pass 3 rounds in Hard Endless mode
    // Go back to "Choose Difficulty" of "Endless Mode" page
    StartEndless();
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
        cout << "                         " << "[Endless]" << endl;
        cout << "                    " << "[Choose Difficulty]" << endl;
        cout << "   " << "--Use 'w' and 's' keys to navigate and select options--" << endl;

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
    int round = 1;
    Board b;
    bool new1 = true;
    if (currSel  == 1) {
        StartEasyEndless(round, b, new1);            // Call function for Option 1: Easy Mode
    } else if (currSel  == 2) {
        StartHardEndless(round, b, new1);            // Call function for Option 2: Hard Mode
    } else if (currSel  == 3) {        
        RunNewGame();                  // Call function for Option 3: Return to Previous menu
    } else if (currSel  == 4) {
        RunMainMenu();                 // Call function for Option 3: Return to Main menu
    } else if (currSel  == 5) {
        exit(0);                       // Exit the program for Option 5: Quit
    }
}

// Function: StartEasyChallenge
// This function starts the Challenge mode in easy difficulty
// It consists of three rounds, and the settings for each round are stored in the EasySetting 2D array
// The function uses a while loop to proceed to the next round after completing each round
// The settings for the current round are read from EasySetting and passed to the Board object
// The StartNewRound function of the Board is called to start the game
// There is a maximum moves for each round in Challenge mode
// When player has reached the maximum moves and has not flipped all cards, then return -1 as result
void StartEasyChallenge(int round, Board b1, bool new1) {
	// Difficulty Initialization
    int EasySetting[3][4] ={{2, 4, 2, 12}, {3, 4, 2, 18}, {4, 4, 2, 24}};
    Board b;
	// Challenge mode: limited move
    while (round <= 3) {
        // Start a new round of game
        // Read the settings from EasySetting and store them in Board
        if(new1==true){
            b = {
            "Challenge",
            "Easy",
            round,

            EasySetting[round - 1][0],
            EasySetting[round - 1][1],
            EasySetting[round - 1][2],
            EasySetting[round - 1][3],
            1,

            0,
            0,
            EasySetting[round - 1][0],
            1,

            vector<vector<int> > (EasySetting[round - 1][0], vector<int>(EasySetting[round - 1][1])),
            vector<vector<bool> > (EasySetting[round - 1][0],vector<bool>(EasySetting[round - 1][1],false)),

            0,
            0,
            false,
            false,
            true,

            vector<int> (EasySetting[round - 1][2]),
            vector<vector<int> > (EasySetting[round - 1][2],vector<int>(EasySetting[round - 1][2])),
            };

            // Start the new round
            b.shuffle();  // Initialize and shuffle the cards  
        }else{
            b=b1;
        }

        double result = b.StartNewRound();
        if (result == -1){  // lose
            cout << "Unfortunately! You Didn't Pass [Challenge--Easy] Mode!" << endl;
            sleep(4);
            break;
        }

		// Game over
		sleep(1);    // Pause for 1 second and continue with the next game
        round++;
        new1 = true;
    }

    // Pass 3 rounds in Easy Challenge mode
    // Go back to "Choose Difficulty" of "Challenge Mode" page
    StartChallenge();
}

// Function: StartHardChallenge
// This function starts the challenge mode in hard difficulty
// It consists of three rounds, and the settings for each round are stored in the HardSetting 2D array
// The function uses a while loop to proceed to the next round after completing each round
// The settings for the current round are read from HardSetting and passed to the Board object
// The StartNewRound function of the Board is called to start the game
// There is a maximum moves for each round in Challenge mode
// When player has reached the maximum moves and has not flipped all cards, then return -1 as result
void StartHardChallenge(int round, Board b1, bool new1) {
    // Difficulty Initialization
    int HardSetting[3][4] = {{3, 3, 3, 15},{3, 4, 3, 21}, {3, 5, 3, 27}};
    Board b;
    // Endless mode: infinite loop
    while (round <= 3) {
        // Start a new round of game
        // Read the settings from EasySetting and store them in Board
        if(new1 ==true){
	    b = {
            "Challenge",
            "Hard",
            round,

            HardSetting[round - 1][0],
            HardSetting[round - 1][1],
            HardSetting[round - 1][2],
            HardSetting[round - 1][3],
            1,

            0,
            0,
            HardSetting[round - 1][0],
            1,

            vector<vector<int> > (HardSetting[round - 1][0], vector<int>(HardSetting[round - 1][1])),
            vector<vector<bool> > (HardSetting[round - 1][0],vector<bool>(HardSetting[round - 1][1],false)),

            0,
            0,
            false,
            false,
            true,

            vector<int> (HardSetting[round - 1][2]),
            vector<vector<int> > (HardSetting[round - 1][2],vector<int>(HardSetting[round - 1][2])),
            };

            // Start the new round
            b.shuffle();  // Initialize and shuffle the cards
        }else{
            b= b1;
        }
        double result = b.StartNewRound();
        if (result == -1){  // lose
            cout << "Unfortunately! You Didn't Pass [Challenge--Hard] Mode!" << endl;
            sleep(4);
            break;
        }

	    // Game over
	    sleep(1);    // Pause for 1 second and continue with the next game
        round++;
        new1 = true;
    }

    // Pass 3 rounds in Hard Endless mode
    // Go back to "Choose Difficulty" of "Endless Mode" page
    StartChallenge();
}


// Function: StartChallenge
// This function starts the challenge mode
// The difficulty settings include the number of rows, columns, and hidden cards (numRows, numCols, numF)
// The maximum number of moves allowed is specified by maxMove
void StartChallenge() {
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
        cout << "                        " << "[Challenge]" << endl;
        cout << "                    " << "[Choose Difficulty]" << endl;
        cout << "   " << "--Use 'w' and 's' keys to navigate and select options--" << endl;

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
    int round = 1;
    Board b;
    bool new1 = true;
    if (currSel  == 1) {
        StartEasyChallenge(round, b, new1);            // Call function for Option 1: Easy Mode
    } else if (currSel  == 2) {
        StartHardChallenge(round, b, new1);            // Call function for Option 2: Hard Mode
    } else if (currSel  == 3) {        
        RunNewGame();                  // Call function for Option 3: Return to Previous menu
    } else if (currSel  == 4) {
        RunMainMenu();                 // Call function for Option 3: Return to Main menu
    } else if (currSel  == 5) {
        exit(0);                       // Exit the program for Option 5: Quit
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
        cout << "                          " << "[NewGame]" << endl;
        cout << "                       " << "[Choose a mode]" << endl;
        cout << "   " << "--Use 'w' and 's' keys to navigate and select options--" << endl;

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

    if (currSel == 1) {        // Call function for Option 1: Endless Mode
        StartEndless();        
    } else if (currSel == 2) { // Call function for Option 2: Challenge Mode
        StartChallenge();      
    } else if (currSel == 3) {   // Call function for Option 3: Custom Mode
        int numRows, numCols, numF;
        CheckInput(numRows, numCols, numF);
        while ((numRows * numCols) % numF != 0) {
            cout << "Error! Board size must be a multiple of the number of cards flipped" << endl;
            CheckInput(numRows, numCols, numF);
        }

        cout << "Start Custom Mode Game" << endl;
        sleep(2);               // Pause 2 seconds and enter 

        Board b = {
            "CUS",
            "TOM",
            1,

            numRows,
            numCols,
            numF,
            -1,
            1,

            0,
            0,
            numRows,
            1,

            vector<vector<int> > (numRows, vector<int>(numCols)),
	    vector<vector<bool> > (numRows,vector<bool>(numCols,false)),

            0,
	    0,
	    false,
	    false,
	    true,
   
	    vector<int> (numF),
	    vector<vector<int> > (numF,vector<int>(numF)),
        };
 	b.shuffle();
	b.StartNewRound();
        RunNewGame();
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

        cout << "                   " << "[Memory Matching Game]" << endl;
        cout << "                         " << "[Main Menu]" << endl;
        cout << "   " << "--Use 'w' and 's' keys to navigate and select options--" << endl;

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
        RunLoadGame();
    } else if (currSel == 3) {   // Call function for Option 3: Tutorial
        RunTutorial();
    } else if (currSel == 4) {   // Exit the program for Option 4: Quit
        exit(0);
    }
}

// Function: RunTutorial
// 
void RunTutorial() {
    string userInput;
    //page1
    clearScreen();
    cout << "                 " << "--Welcome to the Game Tutorial--" << endl;
    cout << "In this tutorial, we will guide you step by step on how to play the game" << endl;
    cout << "(Enter any word to continue...)"<< endl;
    cin >> userInput;

    //page2
    clearScreen();
    cout << "Here's how you can play" << endl;
    cout << "1. Use the 'w', 's', 'a', 'd' keys to move the indicator on the table" << endl;
    cout << "2. Press the Enter key to select a card and flip it over" << endl;
    cout << "3. Try to uncover two cards that have the same symbol" << endl;
    cout << "   " << "If the cards match, they will remain flipped, and you will earn points" << endl;
    cout << "   " << "If the cards don't match, they will be flipped back over within 1 sec" << endl;
    cout << "   " << "and your move count will increase by 1. The points will not change." << endl;
    cout << "4. Continue flipping cards and matching pairs until all the cards are uncovered" << endl;
    cout << "(Enter any word to continue...)"<< endl;
    cin >> userInput;

    //page3
    clearScreen();
    cout << "Let's start with a simple 2x2 game" << endl;
    cout << "The objective is to uncover the entire table using as few steps as possible" << endl;
    cout << "(Enter any word to start...)"<< endl;
    cin >> userInput;

	Board b1 = {
        "TUT",
        "Easy",
        1,

        2,
        2,
        2,
        -1,
        1,

        0,
        0,
        2,
        1,

        vector<vector<int> > (2, vector<int>(2)),
        vector<vector<bool> > (2,vector<bool>(2,false)),

        0,
        0,
        false,
        false,
        true,

        vector<int> (2),
        vector<vector<int> > (2,vector<int>(2)),
        };
        
    b1.shuffle();  // Initialize and shuffle the cards
    b1.StartNewRound();
    //cout << "Congrats! You win!" << endl;
    //cout << "(Press any key to continue...)"<< endl;
    cin >> userInput;


    //page4
    clearScreen();
    cout << "Now, let's move on to a slightly more challenging game with a 3x3 table" << endl;
    cout << "This time, you can flip three cards at a time" << endl;
    cout << "The goal remains the same—uncover all the cards with the fewest moves possible" << endl;
    cout << "(Press any key to start...)"<< endl;
    cin >> userInput;

    Board b2 = {
        "TUT",
        "Hard",
        2,

        3,
        3,
        3,
        -1,
        1,

        0,
        0,
        3,
        1,

        vector<vector<int> > (3, vector<int>(3)),
        vector<vector<bool> > (3,vector<bool>(3,false)),

        0,
        0,
        false,
        false,
        true,

        vector<int> (3),
        vector<vector<int> > (3,vector<int>(3)),
        };   
    b2.shuffle();  // Initialize and shuffle the cards
    b2.StartNewRound();
    //cout << "Congrats! You win!" << endl;
    //cout << "(Enter any word to continue...)"<< endl;
    cin >> userInput;
    
    //page5
    clearScreen();
    cout << "There are different modes you can try" << endl;
    cout << "Let's introduce them one by one: " << endl;
    cout << "(Enter any word to continue...)"<< endl;
    cin >> userInput;

    //page6
    clearScreen();
    cout << "1. Endless Mode" << endl;
    cout << "There are two difficulties you can choose from: " << endl;
    cout << "Easy Mode: Two cards can be flipped at once" << endl;
    cout << "Hard Mode: Three cards can be flipped at once" << endl;
    cout << "In each difficulty, you will have a larger table in each new round" << endl;
    cout << "(Enter any word to continue...)"<< endl;
    cin >> userInput;

    //page7
    clearScreen();
    cout << "2. Challenge Mode" << endl;
    cout << "There will be a maximum move limit and a short time interval between each flip" << endl;
    cout << "You will lose if you don't complete the matching within the maximum move limit" << endl;
    cout << "(Enter any word to continue...)"<< endl;
    cin >> userInput;

    //page8
    clearScreen();
    cout << "3. Custom Mode" << endl;
    cout << "You can define your own table: its size and the number of cards to be flipped at once" << endl;
    cout << "(Enter any word to continue...)"<< endl;
    cin >> userInput;

    //page9
    clearScreen();
    cout << "Let's have a look at the main menu" << endl;
    cout << "The main menu allows you choose: " << endl;
    cout << "\"New Game\": Start a new game" << endl;
    cout << "\"Load Game\": Play the last unfinished game" << endl; 
    cout << "\"Tutorial\": You're looking at it now!" << endl;
    cout << "\"Quit\": Exit the game" << endl;
    cout << "(Enter any word to continue...)" << endl;
    cin >> userInput;

    //page10
    clearScreen();
    cout << "Congrats! You've finished the tutorial!" << endl;
    cout << "Have fun playing the game!" << endl;
    cout << "(Enter any word to return to the main menu)"<< endl;
    cin >> userInput;
    RunMainMenu();
} 

void RunLoadGame() {
    ifstream fin;
    fin.open("savegame.txt");

    if (fin.fail()){
    cout << "Game not found!" << endl;
    }

    else {
        string mode, difficulty;
        int round, numRows, numCols, numF, maxMove, numMove, selectedRow, selectedCol, count, numPaired;
        double pauseTime, points;
        bool failure, flip, challengePass;

        fin >> mode >> difficulty >> round >> numRows >> numCols >> numF >> maxMove >> pauseTime >> numMove >> points >> selectedRow >> selectedCol;
       
        vector<vector<int>> card(numRows, vector<int>(numCols));
        vector<vector<bool>> table(numRows, vector<bool>(numCols));
        vector<int> pairs(numF);
        vector<vector<int> > coord(numF,vector<int>(numF));

        // Read the card vector from the file
        int value;
        for (int row = 0; row < numRows; ++row) {
            for (int col = 0; col < numCols; ++col) {
                if (fin >> value) {
                    card[row][col] = value;
                } 
            }
        }

        // Read the table vector from the file
        bool boolean;
        for (int row = 0; row < numRows; ++row) {
            for (int col = 0; col < numCols; ++col) {
                if (fin >> boolean) {
                    table[row][col] = boolean;
                } 
            }
        }

        fin >> count >> numPaired >> failure >> flip >> challengePass;

        // Read the pairs vector from the file
        int value1;
        for (int num = 0; num < numF; ++num) {
            if (fin >> value1) {
                pairs[num] = value1;
            }
        }

        // Read the coord vector from the file
        bool boolean1;
        for (int row = 0; row < numF; ++row) {
            for (int col = 0; col < numF; ++col) {
                if (fin >> boolean1) {
                    coord[row][col] = boolean1;
                } 
            }
        }

        fin.close();

        Board b {
            mode,
            difficulty,
            round,

            numRows,  
            numCols,  
            numF,   
            maxMove,
            pauseTime,

            numMove,
            points,
            selectedRow,
            selectedCol,

            card,
            table,

            count,
            numPaired,
            failure,
            flip,
            challengePass,

            pairs,
            coord,
        };
        bool new1 = false;
        if(mode == "Endless" && difficulty == "Easy"){
            StartEasyEndless(round, b, new1);
        }
        else if(mode == "Endless" && difficulty == "Hard"){
            StartHardEndless(round, b, new1);
        }
        else if(mode == "Challenge" && difficulty == "Easy"){
            StartEasyChallenge(round, b, new1);
        }
        else if(mode == "Challenge" && difficulty == "Hard"){
            StartHardChallenge(round, b, new1);
        }
    }
}

int main() {
    RunMainMenu();
    return 0;
}
