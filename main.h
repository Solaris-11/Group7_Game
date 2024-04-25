#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <sstream>
#include <cctype>
#include <vector>
#include <iomanip>
#include <cmath>
#include <termios.h>
#include <unistd.h>
#include "MoveCursor.h"

using namespace std;

void RunMainMenu();

#ifndef main_h
#define main_h

struct Board{

    string mode;
    string difficulty;
    int round;

    int numRows;  // The number of rows in the table
    int numCols;  // The number of columns in the table
    int numF;   // The number of cards filpped at a time
    int maxMove;
    double pauseTime;

    int numMove;
    double points;
    int selectedRow;
    int selectedCol;

    vector<vector<int>> card;
    vector<vector<bool>> table;


    int count;
    int numPaired;
    bool failure;
    bool flip; 
    bool challengePass;

    vector<int> pairs;
    vector<vector<int>> coord;

    // Function: drawTable
    // Nested for loop to draw the *table
    // Two loops to print the indicator for the selected row and column
    void drawTable() {
        //Clear the screen
        clearScreen();
        cout << " " << "[ " + mode + "--" + difficulty + "--" << round << " ]" << endl; 
        for (int row = 1; row <= numRows; row++) {
            // Check if the current row is the selected row
            if (row == selectedRow) {  
                cout << ">  ";      //Print a ">  " is the row is selected  
            } 
            else {
                cout << "   ";      //Otherwise print a "   "
            }
            //Nested for loop to draw the *table
            for (int col = 1; col <= numCols; col++) {
            // Check if the card at the current position is face-down
                if (table[row-1][col-1] == false) {
                    cout << "  *";       //Print a "  *" if the *card at the current position is face-down
                } 
                else {
                    cout << setw(3) << setfill(' ') << card[row-1][col-1];    //Otherwise print the value of the *card
                }
            }
            cout << endl;   
        }
        //To escape the first column as it is the place for the row indicator
        cout << "   ";
        //Ierate over each column to check whether the column is selected 
        for(int col = 1; col<=numCols; col++){
        // Check if the current column is the selected column
            if(col == selectedCol){
                cout << "  ^";    //Print a "  ^" is the column is selected
            }
            else {
                cout << "   ";    //Otherwise print a "   "
            }
        }
        // Print the move number and points
        cout<< endl;
        if (mode == "Endless"){
            cout << "Move: " << numMove << "    " << "Points: " << points << endl;
            if (round < 3){
                if (points == 100){
                    cout << endl;
                    cout << "Congratulations! You Pass Round: " << round << endl;
                    cout << "Now Going to the Next Round..." << endl;
                    cout << "(Press any key to continue ...)" << endl;
                }
            }
            else if (round == 3){
                if (points == 100){
                    cout << endl;
                    cout << "Hooray!!! You pass " << "[" + mode + "--" + difficulty +"]"<< "!!!" << endl;
                    cout << "(Press any key to continue ...)" << endl;
                    // move to "choose mode page"
                }
            }   
        }
        else if (mode == "Challenge"){
            cout << "Remaining Move: " << maxMove - numMove << "    " << "Points: " << points << endl;
            if (round < 3){
                if (points == 100){
                    cout << endl;
                    cout << "Congratulations! You Pass Round: " << round << endl;
                    cout << "Now Going to the Next Round..." << endl;
                    cout << "(Press any key to continue ...)" << endl;
                }
            }
            else if (round == 3){
                if (points == 100){
                    cout << endl;
                    cout << "Hooray!!! You pass " << "[" + mode + "--" + difficulty +"]"<< "!!!" << endl;
                    cout << "(Press any key to continue ...)" << endl;
                    // move to "choose mode page"
                }
            }
        }
	else if (mode == "Custom"){
            cout << "Remaining Move: " << maxMove - numMove << "    " << "Points: " << points << endl;
            if (round < 3){
                if (points == 100){
                    cout << endl;
                    cout << "Congratulations! You Pass Round: " << round << endl;
                    cout << "Now Going to the Next Round..." << endl;
                    cout << "(Press any key to continue ...)" << endl;
                }
            }
            else if (round == 3){
                if (points == 100){
                    cout << endl;
                    cout << "Hooray!!! You pass " << "[" + mode + "--" + difficulty +"]"<< "!!!" << endl;
                    cout << "(Press any key to continue ...)" << endl;
                    // move to "choose mode page"
                }
            }
        }
        
        
    }

    //Function: shuffle
    //Initializes the card table and randomly shuffles the card to obtain a randomly arranged value table
    void shuffle(){
        int numCards = numRows * numCols;   // The size of the *table
        int numPairs = numCards / numF;  // Calculate the number of pairs

        // Set the random seed based on the current time
        srand((unsigned int)time(NULL));    
        
        // Card Initialization
        for (int i = 0; i < numRows; i++) {  
            for (int j = 0; j < numCols; j++) {
                card[i][j] = (i * numCols + j) % numPairs + 1;   // Assign a unique value to each *card
            }
        }

        // Card Shuffling
        for (int i = 0; i < numPairs; i++) {
            for (int k = 0; k < numF; k++) {
                int row1 = rand() % numRows;
                int col1 = rand() % numCols;
                int row2 = rand() % numRows;
                int col2 = rand() % numCols;
                
                swap(card[row1][col1], card[row2][col2]);  // Randomly select two cards and swap them
            }
        }
    }

    //Function: swap
    //Swaps the value of two cards
    void swap(int &a, int &b) {
        int tmp;
        tmp = a;
        a = b;
        b = tmp;
    }

    // Function: checkCards
    // Check if the selected cards are matched. If true, keep the cards face-up; otherwise flip the cards back
    void checkCards(vector<int> &pairs, vector<vector<int> > &coord, int &numPaired, int totalNumPairs, bool &failure){
        // Check if the selected cards are matched.
        failure = true;
        int value = pairs[0];
        for (int i = 1; i < pairs.size(); i++) {
            if (pairs[i] != value) {
                failure = false;
            }
        }
        // Cards are a pair
        if (failure) {
            numPaired++;      // Increment the number of successfully paired cards
            points = (100 / (double)totalNumPairs) * numPaired;    // Update the points based on the number of pairs matched
            points = ceil(points);
            failure = false;   // Pairing successful, keep the cards face-up
        }
        // Cards are not a pair
        else {
            // Flip cards face-down
            for (int i = 0; i < coord.size(); i++) {
                table[coord[i][0]][coord[i][1]] = false;
            }
            failure = true;    // Pairing failed, flip the cards back
        }
    }

    // Function: StartNewRoun
    // Start new game, return the points from previous round, if failure occurs, return -1
    // Two paramteters in the Challenge mode: maxMove and time
    double StartNewRound() {
        setNonCanonicalMode();  // Set the terminal to non-canonical mode to read input 

        int totalNumPairs = numRows * numCols / numF;

        while (numPaired != totalNumPairs) {  // Keep the process until all the cards are matched
            // Draw the game table
            drawTable();  
            // Check if a pair has been flipped
            if (flip) {
                if(count > 0 && count % numF == 0) {
                    sleep(pauseTime);    // Pause for 1 second to display the flipped cards
                    // Check if the flipped pair is a match
                    checkCards(pairs, coord, numPaired, totalNumPairs, failure);
                    // Show Cards
                    drawTable();
                }
                flip = false;
            }

            if (mode == "Challenge"){
                if (numMove > maxMove){
                    challengePass = false;
                    break;
                }
            }

            // Process user input and update the position of the indicator of row and column
            char userInput;
            read(STDIN_FILENO, &userInput, 1);
            if (userInput == 'w') {      // If 'w' key is pressed
                if (selectedRow > 1) {   // Move selection up if not already at the top
                    selectedRow--;
                }
            }
            else if (userInput == 's') {  // If 's' key is pressed
                if (selectedRow < numRows) {   // Move selection down if not already at the bottom
                    selectedRow++;
                }
            } 
            else if (userInput == 'a') {  // If 'a' key is pressed
                if (selectedCol > 1) {    // Move selection to the left if not already at the leftmost position
                    selectedCol--;
                }
            } 
            else if (userInput == 'd') {  // If 'd' key is pressed
                if (selectedCol < numCols) {   // Move selection to the right if not already at the rightmost position
                    selectedCol++;
                }
            } 
            else if (userInput == 'q') {
                RunPauseMenu();
            }
            else if (userInput == '\n') {  // If Enter key is pressed
                flip = true;   // Set the flip flagto true

                // If the selected option is valid
                if (selectedRow <= numRows && selectedCol <= numCols) {
                    if (table[selectedRow-1][selectedCol-1] == false) {
                        table[selectedRow-1][selectedCol-1] = true;   // Flip the selected *card face-up
                        pairs[count % numF] = card[selectedRow-1][selectedCol-1];   // Store the *card value for comparison
                        coord[count % numF][0] = selectedRow - 1;   // Store the coordinates of the selected *card
                        coord[count % numF][1] = selectedCol - 1;
                        count++;  // Increment the number of stored cards
                        numMove++;
                    } 
                    else {
                        flip = false;
                    }
                }
            }
            else if (userInput == 'b') {  // If 'b' key is pressed
                break;  // Exit the while loop
            }
        }

        restoreTerminalMode();  // Restore the terminal to the original mode
        // if successfully pass the current round, return the points got from this round
        double result = -1;
        if (challengePass == false){
            return result;
        }
        else{
            return points;
        }
    }

    // Function: RunPauseMenu
    void RunPauseMenu() {
        saveGame();
        // Vector to store the new game options
        vector<string> newgame(5);
        newgame[0] = "Continue";              // Option 1: Continue
        newgame[1] = "Save and Quit";         // Option 2: Save and Quit
        newgame[2] = "Restart";               // Option 3: Restart

        setNonCanonicalMode();   // Set terminal to non-canonical mode
        int numOpts = 3;         // Total number of options
        int currSel = 1;         // Currently selected option

        while (true) {
            clearScreen();       // Clear the terminal screen
            cout << "                         " << "[Pause Menu]" << endl;
            cout << "   " << "--Use 'w' and 's' keys to navigate and select options--" << endl;

            for (int i = 1; i <= 3; i++) {
                if (i == currSel) {
                    cout << ">> " << newgame[i - 1] << endl;   // Print selected option with a cursor (>>)
                } else {
                    cout << "   " << newgame[i - 1] << endl;   // Print non-selected options
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

        if (currSel == 1) {          // Call function for Option 1: Continue
            // No specific action needed for the "Continue" option
        } else if (currSel == 2) {   // Call function for Option 2: Save and Quit
            RunMainMenu();
        } else if (currSel == 3) {   // Call function for Option 3: Restart
            numMove = 0;
            points = 0;
            selectedRow = numRows;
            selectedCol = 1;
            StartNewRound();
        }
    }

    void saveGame() {
        ofstream fout;
        fout.open("savegame.txt");
        if (fout.fail()){
            cout << "Error: cannot open the file" << endl;
            return;
        }
        fout << mode << endl;
        fout << difficulty << endl;
        fout << round << endl;

        fout << numRows << endl;
        fout << numCols << endl;
        fout << numF << endl;
        fout << maxMove << endl;
        fout << time << endl;

        fout << numMove << endl;
        fout << points << endl;
        fout << selectedRow << endl;
        fout << selectedCol << endl;

        for (const auto & row : card) {
            for (const auto & value : row) {
                fout << value << " ";
            }
            fout << '\n';
        }

        for (const auto & row : table) {
            for (const auto & value : row) {
                fout << value << " ";
            }
            fout << '\n';
        }

        fout << count << endl;
        fout << numPaired << endl;
        fout << failure << endl;
        fout << flip << endl;
        fout << challengePass << endl;

        for (const auto & value : pairs) {
            fout << value << " ";
        }
        fout << '\n';

        for (const auto & row : coord) {
            for (const auto & value : row) {
                fout << value << " ";
            }
            fout << '\n';
        }

        fout.close();
    }
};
#endif
