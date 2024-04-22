#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <cctype>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include <iomanip>

using namespace std;

#ifndef main_h
#define main_h

struct Board{
  int numRows;  // The number of rows in the table
  int numCols;  // The number of columns in the table
  int numF;   // The number of cards filpped at a time
  int numCards = numRows * numCols;   // The size of the table
  int numPairs = numCards / 2;  // Calculate the number of pairs
  int totalNumPairs;
  bool failure;

  int selectedRow;  // The currently selected row
  int selectedCol;  // The currently selected column

  vector<vector<int>> card;    // 2D vector representing the cards on the table
  vector<vector<bool>> table;  // 2D vector representing the cards on the table
  vector<int> pairs;
  vector<vector<int>> coord;

  int numPaired;
  int numMove;       // The number of moves made by the player
  double points;     // The current points earned by the player

  // Function: setNonCanonicalMode
  // Set the terminal to non-canonical mode
  void setNonCanonicalMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
  }

  // Function: restoreTerminalMode
  // Restore the terminal to canonical mode
  void restoreTerminalMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
  }

  // Function: clearScreen
  // Clear the terminal screen
  void clearScreen() {
    cout << "\033[2J";
  }

  // Funtion: moveCursorTo
  // Move the terminal cursor to the specified position
  void moveCursorTo(int x, int y) {
    cout << "\033[" << y << ";" << x << "H";
  }

  // Function: drawTable
  // Nested for loop to draw the table
  // Two loops to print the indicator for the selected row and column
  void drawTable() {
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
        else{
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
  void shuffle(){
    // Set the random seed based on the current time
    srand((unsigned int)time(NULL));    
	
    // Card Initialization
    for (int i = 0; i < numRows; i++) {  
	for (int j = 0; j < numCols; j++) {
		card[i][j] = (i * numCols + j) % numPairs + 1;   // Assign a unique value to each card
	}
    }

    // Card Shuffling
    for (int i = 0; i < numCards; i++) {  
	swap(card[rand() % numRows][rand() % numCols], card[rand() % numRows][rand() % numCols]);  // Randomly select two cards and swap them
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

  //Funtion: checkpair
  //Check if the selected pair is matched. If true, keep the cards face-up; otherwise flip the cards back
  void checkpair(){
    //Cards are a pair
    if(pairs[0] == pairs[1]){
        numPaired++;      // Increment the number of successfully paired cards
        points = (100/(double)totalNumPairs)*numPaired;    // Update the points based on the number of pairs matched
        failure = false;   // Pairing successful, keep the cards face-up
    }
	    
    //Cards are not a pair
    else{
        int row1 = coord[0][0], row2 = coord[1][0], col1 = coord[0][1], col2 = coord[1][1];
        table[row1][col1]=false;   // Flip the first card face-down
        table[row2][col2]=false;   // Flip the second card face-down
        failure = true;    // Pairing failed, flip the cards back
    }
  }

//Function: choose
//
void choose() {
    setNonCanonicalMode();  //Set the terminal to non-canonical mode to read input 

    int selectedRow = numRows;  
    int selectedCol = 1;

    vector<vector<int>> card(numRows, vector<int>(numCols));
    shuffle(card, numRows, numCols);  // Initialize and shuffle the cards

    int count = 0, numPaired = 0, numMove = 0, totalNumPairs = Rows*Cols/2;
    double points = 0;
    bool failure = false, flip = false;

    vector<vector<bool>> table(numRows,vector<bool>(numCols,false));    //Create a table to track the state of each card (initial value: false)
    vector<int> pairs(Rows*Cols);
    vector<vector<int>> coord(2,vector<int>(2));

    while (numPaired != totalNumPairs) {  //Keep the process until all the cards are matched
        //Draw the game table
	drawTable(numRows, numCols, selectedRow, selectedCol, card, table, numMove, points);  

	// Check if a pair has been flipped
	if (flip){
            if(count>0 && count%2 ==0){
                sleep(1);    // Pause for 1 second to display the flipped cards
                checkpair(pairs, coord, table, numPaired, points, totalNumPairs, failure);   // Check if the flipped pair is a match
                if(failure == true){    // Pairing failed, flip the cards back
                    drawTable(numRows, numCols, selectedRow, selectedCol, card, table, numMove, points);
                }
                else if (failure == false){   // Pairing successful, keep the cards face-up
                    drawTable(numRows, numCols, selectedRow, selectedCol, card, table, numMove, points);
                }
            }
            flip = false;
        }

	// Process user input and update the position of the indicator of row and column
        char userInput;
        if (read(STDIN_FILENO, &userInput, 1) == 1) {
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
                flip = true;   //Set the flip flag to true

		//If the selected option is valid
                if (selectedRow <= numRows && selectedCol <= numCols) {    
                    numMove++;   // Increment the number of moves
		    
		    //If the selected card is not flipped
                    if (table[selectedRow-1][selectedCol-1] == false) {    
                        table[selectedRow-1][selectedCol-1] = true;   // Flip the selected card face-up
                        pairs[count%2]=card[selectedRow-1][selectedCol-1];   // Store the card value for comparison
                        coord[count%2][0]=selectedRow-1;   // Store the coordinates of the selected card
                        coord[count%2][1]=selectedCol-1;
                        count++;   // Increment the number of stored cards
		     }
                }
            }
	
            else if (input == 'b'){  // If 'b' key is pressed
                break;  // Exit the while loop
            }
        }  
    }
    restoreTerminalMode();  // Restore the terminal to the original mode
}


int main(){
    int Rows, Cols;
    cout << "Row:";
    cin >> Rows;
    cout << "Col:";
    cin >> Cols;
    choose(Rows,Cols);
    return 0;
}		    
};
#endif
