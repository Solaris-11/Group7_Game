/**
 * Different game mode designs
*/
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <ios>
#include <vector>
#include <iomanip>
#include <unistd.h>

using namespace std;

struct Setting {
  int nRows;
  int nCols;
  int numF;
};
struct Position {
  int row;
  int col;
};

// Show card table
void ShowCards(vector<vector<int>> table, vector<vector<bool>> flipped) {
  int row = table.size(), col = table[0].size();
  // First row
  cout << "\t";
  for (int i = 1; i <= col; i++) {
    cout << "[" << i << "]";
		if (i == col){
			cout << endl;
		}
		else {
			cout << "\t";
		}
  }
  // In the following lines, numbers are displayed when the cards are turned over, and * is displayed when the cards are not turned over.
  for (int i = 0; i < row; i++) {
    cout << "[" << (i + 1) << "]\t";
    for (int j = 0; j < col; j++) {
      if (flipped[i][j]){
				cout << " " << table[i][j];
			}
			else{
				cout << "*";
			}
			if (j == col - 1) {
				cout << endl;
			}
			else {
				cout << "\t";
			}
    }
  }
}

// shuffle
void shuffles(vector<vector<int>>& table){
  int rows = table.size();
  int cols = table[0].size();
  // create random number generator
  srand((unsigned int)time(NULL));
  // Swap randomly multiple times
  for (int i = 0; i < rows*cols; i++) {
    // Generate two random indexes
    int row1 = rand() % rows, col1 = rand() % cols;
    int row2 = rand() % rows, col2 = rand() % cols;
    // Swap elements corresponding to two random indices
    swap(table[row1][col1], table[row2][col2]);
  }
}

// Read player input and determine whether it is legal
void GameInput(vector<Position>& coordinates, Setting s) {
  // Receive the input from player
  for (int i = 1; i < coordinates.size(); i++) {
    // until the input is legal
    string input;
    while (true) {
      cout << "Please enter the coordinate" << i << " : ";
      cin >> input;
      // Check whether the input is legal
      // Check repeatedly
      // Flipped card testing
    }
  }
  
}

// Starting game according to the setting
void StartNewRound(Setting s) {
  // Card type table[0]
  vector<vector<int>> table(s.nRows, vector<int>(s.nCols, 0));
  // Initialize:3*3,2   table[0][0] = 1 table[0][1]=2 table[0][2]=3 table[1][0]=2
  for (int i = 0; i < table.size(); ++i) {
    for (int j = 0; j < table[i].size(); ++j) {
      int seq = i * table.size() + j;
      int sum = table.size() * table[i].size() / s.numF;
      table[i][j] = seq % sum + 1;
    }
  }
  // shuffle
  shuffles(table);
  // Check whether shuffled or not
  vector<vector<bool>> flipped(s.nRows, vector<bool>(s.nCols, true));
  // current progress and goal
  int isFound = 0, target = s.nRows * s.nCols / s.numF;
  // check whether it can be matched
  bool isMatch = true;
  // Display cards
  ShowCards(table, flipped);
  // Looping the game
  while (isFound < target) {
    // Input from player
    vector<Position> inputs(s.numF);
    GameInput(inputs, s);
    // Flipping the cards
    for (int i = 0; i < inputs.size(); i++) {
      flipped[inputs[i].row - 1][inputs[i].col - 1] = true;
    }
    // Determine whether it matches
    int cur = table[inputs[0].row - 1][inputs[0].col - 1];
    for (int i = 1; i < inputs.size(); i++) {
      if (table[inputs[i].row - 1][inputs[i].col - 1] != cur) {
        isMatch = false;
        break;
      }
    }
    // Successfully matches
    if (isMatch) {
      // Progress +1
      isFound++;
      // Display information
    }
    // Failure to match
    else {
      // Reset flop
      for (int i = 0; i < inputs.size(); i++) {
        flipped[inputs[i].row - 1][inputs[i].col - 1] = false;
      }
      // Display information
    }
    // show the crads
    ShowCards(table, flipped);
    // Reset matching bit
    bool isMatch = true;
  }
}

// Simple unlimited mode
void StartEasyEndless() {
    // Difficulty settings for different rounds
    vector<Setting> settings{
        {2, 4, 2},
        {3, 4, 2},
        {4, 4, 2}
    };
    // Number of rounds
    int round = 1;
    // unlimited mode
    while (true) {
        // Hint
        cout << "Current Round: " << round << endl;
        // Start a game round based on the difficulty of the current round
        StartNewRound(settings[round - 1]);
        // Congratulations message
        cout << "Congratulations! You Pass Round:" << round << endl;
        round++;
    }
}

// Diffuclt unlimited mode
void StartHardEndless() {

}

// Challenge mode
void StartChallenge(){

}

// Custom mode
void StartCustom(Setting s) {

}
