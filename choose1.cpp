#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include <iomanip>
using namespace std;

// Set the terminal to non-canonical mode
void setNonCanonicalMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    // Get the current terminal attributes and save them in the 'term' structure

    term.c_lflag &= ~(ICANON | ECHO);
    // Disable canonical mode and echo in the 'term' structure

    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    // Set the updated terminal attributes as the current terminal attributes
}

// Restore the terminal to canonical mode
void restoreTerminalMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    // Get the current terminal attributes and save them in the 'term' structure

    term.c_lflag |= ICANON | ECHO;
    // Enable canonical mode and echo in the 'term' structure

    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    // Set the updated terminal attributes as the current terminal attributes
}

void clearScreen() {
    cout << "\033[2J";
}

void moveCursorTo(int x, int y) {
    cout << "\033[" << y << ";" << x << "H";
}

void drawTable(int numRows, int numCols, int selectedRow, int selectedCol, vector<vector<int>>& card, vector<vector<bool>>& table) {
    clearScreen();

    for (int row = 1; row <= numRows; row++) {
        if (row == selectedRow) {
            cout << ">  ";
        } 
        else {
            cout << "   ";
        }

        for (int col = 1; col <= numCols; col++) {
            if (table[row-1][col-1] == false) {
                cout << "  *";
            } else {
                cout << setw(3) << setfill(' ') << card[row-1][col-1];
            }
        }
        cout << endl;
    }
    cout << "   ";
    for(int col = 1; col<=numCols; col++){
        if(col == selectedCol){
            cout << "  ^";
        }
        else{
            cout << "   ";
        }
    }
    cout<< endl;
}

void choose(int Rows, int Cols) {
    setNonCanonicalMode();

    int numRows = Rows;
    int numCols = Cols;
    int selectedRow = numRows;
    int selectedCol = 1;

    vector<vector<int>> card(numRows, vector<int>(numCols));
    for(int i = 0;i < numRows;i++){
        for( int j = 0; j<numCols ;j++){
	    card[i][j] = i * numCols +j+1;
	    }
	}
    vector<vector<bool>> table(numRows,vector<bool>(numCols,false));
    while (true) {
        drawTable(numRows, numCols, selectedRow, selectedCol, card, table);

        char input;
        if (read(STDIN_FILENO, &input, 1) == 1) {
            if (input == 'w') {
                if (selectedRow > 1) {
                    selectedRow--;
                }
            } else if (input == 's') {
                if (selectedRow < numRows) {
                    selectedRow++;
                }
            } else if (input == 'a') {
                if (selectedCol > 1) {
                    selectedCol--;
                }
            } else if (input == 'd') {
                if (selectedCol < numCols) {
                    selectedCol++;
                }
            } else if (input == '\n') {
                if (selectedRow <= numRows && selectedCol <= numCols) {
                    if (table[selectedRow-1][selectedCol-1] == false) {
                        table[selectedRow-1][selectedCol-1] = true;
                    	cout << "You choose " << selectedRow << " row and " << selectedCol << " coloum" << endl;
		    }
                }
            }
            else if (input == 'b'){
                break;
            }
        }
    }

    restoreTerminalMode();
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
