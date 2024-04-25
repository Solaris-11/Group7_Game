Identification of the team members:
 1. Chen Shiyang 3035974432
 2. Hu Yujia 3035980302
 3. Lin Zequn 3036059605
 4. Nie Mingyang 3036086713
 5. Wu Zhikai 3035973804


Game description and rules


Welcome to the Flip Card Game! This is a text_base game based on C++, your objective is to flip cards and match them. Each mode offers its own level of difficulty and challenges.


The operation method of the game is to use the "wasd" key for selection and flipping. 


If you want to pause the game during gameplay, you can press "q" to enter the pause menu. In the pause menu, you can choose to save the game and exit, continue the game, and restart.


You can test your memory and matching skills across different game modes: Endless, Challenge, and Custom, each game mode refers to different rules.
  1. Endless Mode: including easy mode and hard mode, 3 rounds will be included
      1. Easy Mode: Two cards can be flipped at once, larger table will be set in each new round, there are no move limit
      2. Hard Mode: Three cards can be flipped at once, larger table will be set in each new round, there are no move limit
  2. Challenge Mode: There will be a maximum move limit, there will be a shorter time interval between each flip
  3. Custom Mode: You can define your own table: its size and the number of cards to be flipped at once, there are no move limit
All of the instructions can be found in the tutorial part, you can check any time if you forget.


Game features and corresponding coding element



A list of features that you have implemented and explain how each coding element 1 to 5 listed under the coding requirements aforementioned support your features.



Generation of random game sets or events

Feature 1: Random numbers in each round
 1. The game incorporates random numbers to introduce unpredictability and variability in each round.
 2. The coding element of generating random game sets or events is utilized to achieve this feature.
 3. At the start of each round, the game generates random numbers using the coding element.
 4. These random numbers are used to determine various aspects of the game, such as shuffling the cards, determining the order of turns, or randomizing the positions of game elements.
 5. The randomization ensures that each round is unique and different from the previous ones.

Corresponding coding element: Generation of random game sets or events

Feature 2: Custom data structure - Structure Board

The Struct Board we use is a custom data structure used to represent the board status and properties of the flop game. It combines different data types and containers to provide the necessary information and functionality to support game play and management.

The following is a more detailed description of some important member variables and functions in `struct Board`:

 1. `mode` and `difficulty`: These string variables are used to store the mode and difficulty level of the game and can be set and used according to the design of the game rules.

 2. `round`: This integer variable is used to track the number of rounds of the game, indicating which round of the game is currently.

`numRows` and `numCols`: These two integer variables represent the number of rows and columns of the game board respectively and are used to determine the size of the game board.

`numF`: This integer variable represents the number of cards flipped each time, that is, the number of pairs of cards flipped at the same time.

`maxMove`: This integer variable represents the maximum number of moves in the game, that is, the maximum number of flips allowed by the player.

`pauseTime`: This float variable represents the pause time after flipping the card to control the rhythm and speed of the game.

`numMove`: This integer variable is used to track the player's total number of moves, i.e. the number of pairs of cards that have been flipped.

`points`: This floating point variable is used to record the player's score or game progress.

`selectedRow` and `selectedCol`: These two integer variables represent the currently selected row and column and are used to track the player's selection.

`card`: This two-dimensional integer vector (`vector<vector<int>>`) is used to store the value or identity of the card at each position on the game board.

`table`: This two-dimensional vector of booleans (`vector<vector<bool>>`) is used to track whether the card at each position on the game board has been flipped.

`count`: This integer variable is used to count the number of cards that have been flipped so far.

`numPaired`: This integer variable is used to record the number of matched card pairs.

`failure`: This Boolean variable indicates whether the current game failed and is set based on the game rules.

`flip`: This Boolean variable indicates whether flipping the card is allowed, and is set based on the game state.

`challengePass`: This Boolean variable indicates whether the current challenge is passed or not, and is set based on the game rules.

`pairs`: This integer vector (`vector<int>`) is used to store the value or identity of the matched card pair.

`coord`: This two-dimensional integer vector (`vector<vector<int>>`) is used to store the coordinate information of the card position.

Corresponding coding element: Data structures for storing game status (e.g., arrays, STL containers)


Dynamic memory management (e.g., dynamic arrays, linked lists, STL containers)


File input/output (e.g., for loading/saving game status)


Program codes in multiple files (recall separate compilation)





▪ A list of non-standard C/C++ libraries, if any, that are used in your work and integrated to your code repo. 
Please also indicate what features in your game are supported by these libraries.








▪ Compilation and execution instructions. This serves like a "Quick start" of your game.
The teaching team will follow your instructions to compile and run your game









