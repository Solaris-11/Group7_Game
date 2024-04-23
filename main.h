#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <cctype>
#include <vector>
#include <iomanip>
#include <termios.h>
#include <unistd.h>
#include "MoveCursor.h"

using namespace std;

#ifndef main_h
#define main_h

struct Board{
    int numRows;  // The number of rows in the table
    int numCols;  // The number of columns in the table
    int numF;   // The number of cards filpped at a time

    // Function: drawTable
    // Nested for loop to draw the table
    // Two loops to print the indicator for the selected row and column
    void drawTable(int numRows, int numCols, int selectedRow, int selectedCol, vector<vector<int> > card, vector<vector<bool> >& table, int numMove, double points) {
        //Clear the screen
        clearScreen();
        for (int row = 1; row <= numRows; row++) {
            // Check if the current row is the selected row
            if (row == selectedRow) {  
                cout << ">  ";      //Print a ">  " is the row is selected  
            } 
            else {
                cout << "   ";      //Otherwise print a "   "
            }
            //Nested for loop to draw the table
            for (int col = 1; col <= numCols; col++) {
            // Check if the card at the current position is face-down
                if (table[row-1][col-1] == false) {
                    cout << "  *";       //Print a "  *" if the card at the current position is face-down
                } 
                else {
                    cout << setw(3) << setfill(' ') << card[row-1][col-1];    //Otherwise print the value of the card
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
        cout << "Move: " << numMove << "    " << "Points: " << points;
        cout << endl;
    }

    //Function: shuffle
    //Initializes the card table and randomly shuffles the card to obtain a randomly arranged value table
    void shuffle(vector<vector<int> > &card, int numRows, int numCols, int numF){
        int numCards = numRows * numCols;   // The size of the table
        int numPairs = numCards / numF;  // Calculate the number of pairs

        // Set the random seed based on the current time
        srand((unsigned int)time(NULL));    
        
        // Card Initialization
        for (int i = 0; i < numRows; i++) {  
            for (int j = 0; j < numCols; j++) {
                card[i][j] = (i * numCols + j) % numPairs + 1;   // Assign a unique value to each card
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
    void checkCards(vector<int> &pairs, vector<vector<int> > &coord, vector<vector<bool> > &table, int &numPaired, double &points, int totalNumPairs, bool &failure){
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
            points += (100 / (double)totalNumPairs) * numPaired;    // Update the points based on the number of pairs matched
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

    // Function: StartNewRound
    // 开启一轮游戏，返回当前轮次获得的分数，若失败则返回-1
    // 挑战模式中设置的两个参数：step: 步数限制，time：翻牌显示的时间
    double StartNewRound(const int numRows, const int numCols, const int numF, int step, int time) {
        setNonCanonicalMode();  // Set the terminal to non-canonical mode to read input 

        int selectedRow = numRows;  
        int selectedCol = 1;

        vector<vector<int> > card(numRows, vector<int>(numCols));
        shuffle(card, numRows, numCols, numF);  // Initialize and shuffle the cards

        int count = 0, numPaired = 0, numMove = 0, totalNumPairs = numRows * numCols / numF;
        double points = 0;
        bool failure = false, flip = false;

        vector<vector<bool> > table(numRows,vector<bool>(numCols,false));    // Create a table to track the state of each card (initial value: false)
        vector<int> pairs(numF);
        vector<vector<int> > coord(numF,vector<int>(numF));

        while (numPaired != totalNumPairs) {  // Keep the process until all the cards are matched
            // Draw the game table
            drawTable(numRows, numCols, selectedRow, selectedCol, card, table, numMove, points);  
            // Check if a pair has been flipped
            if (flip) {
                if(count > 0 && count % numF == 0) {
                    sleep(time);    // Pause for 1 second to display the flipped cards
                    // Check if the flipped pair is a match
                    checkCards(pairs, coord, table, numPaired, points, totalNumPairs, failure);
                    // Show Cards
                    drawTable(numRows, numCols, selectedRow, selectedCol, card, table, numMove, points);
                }
                flip = false;
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
            else if (userInput == '\n') {  // If Enter key is pressed
                flip = true;   // Set the flip flagto true

                // If the selected option is valid
                if (selectedRow <= numRows && selectedCol <= numCols) {
                    if (table[selectedRow-1][selectedCol-1] == false) {
                        table[selectedRow-1][selectedCol-1] = true;   // Flip the selected card face-up
                        pairs[count % numF] = card[selectedRow-1][selectedCol-1];   // Store the card value for comparison
                        coord[count % numF][0] = selectedRow - 1;   // Store the coordinates of the selected card
                        coord[count % numF][1] = selectedCol - 1;
                        count++;  // Increment the number of stored cards
                        numMove++;
                        // 若步数超标，返回-1，表示游戏失败
                        if (step != -1 && numMove >= step) {
                            return -1;
                        }
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
        // 成功通过该轮游戏，返回该轮获得的分数
        return points;
    }
};
#endif
