Identification of the team members:

 1. Chen Shiyang 3035974432
 2. Hu Yujia 3035980302
 3. Lin Zequn 3036059605
 4. Nie Mingyang 3036086713
 5. Wu Zhikai 3035973804


******************************************

Game description and rules

******************************************

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


******************************************

Game features and corresponding coding element

******************************************


Feature 1: Random numbers in each round

 1. The game incorporates random numbers to introduce unpredictability and variability in each round.
 
 2. The coding element of generating random game sets or events is utilized to achieve this feature.
 
 3. At the start of each round, the game generates random numbers using the coding element.
 
 4. These random numbers are used to determine various aspects of the game, such as shuffling the cards, determining the order of turns, or randomizing the positions of game elements.
 
 5. The randomization ensures that each round is unique and different from the previous ones.

Corresponding coding element: Generation of random game sets or events


******************************************


Feature 2: Custom data structure - Structure Board

The Struct Board we use is a custom data structure used to represent the board status and properties of the flop game. It combines different data types and containers to provide the necessary information and functionality to support game play and management.

The following is a more detailed description of some important member variables and functions in `struct Board`:

 1. `mode` and `difficulty`: These string variables are used to store the mode and difficulty level of the game and can be set and used according to the design of the game rules.

 2. `round`: This integer variable is used to track the number of rounds of the game, indicating which round of the game is currently.

 3. `numRows` and `numCols`: These two integer variables represent the number of rows and columns of the game board respectively and are used to determine the size of the game board.

 4. `numF`: This integer variable represents the number of cards flipped each time, that is, the number of pairs of cards flipped at the same time.

 5. `maxMove`: This integer variable represents the maximum number of moves in the game, that is, the maximum number of flips allowed by the player.

 6. `pauseTime`: This float variable represents the pause time after flipping the card to control the rhythm and speed of the game.

 7. `numMove`: This integer variable is used to track the player's total number of moves, i.e. the number of pairs of cards that have been flipped.

 8. `points`: This floating point variable is used to record the player's score or game progress.

 9. `selectedRow` and `selectedCol`: These two integer variables represent the currently selected row and column and are used to track the player's selection.

 10. `card`: This two-dimensional integer vector (`vector<vector<int>>`) is used to store the value or identity of the card at each position on the game board.

 11. `table`: This two-dimensional vector of booleans (`vector<vector<bool>>`) is used to track whether the card at each position on the game board has been flipped.

 12. `count`: This integer variable is used to count the number of cards that have been flipped so far.

 13. `numPaired`: This integer variable is used to record the number of matched card pairs.

 14. `failure`: This Boolean variable indicates whether the current game failed and is set based on the game rules.

 15. `flip`: This Boolean variable indicates whether flipping the card is allowed, and is set based on the game state.

 16. `challengePass`: This Boolean variable indicates whether the current challenge is passed or not, and is set based on the game rules.

 17. `pairs`: This integer vector (`vector<int>`) is used to store the value or identity of the matched card pair.

 18. `coord`: This two-dimensional integer vector (`vector<vector<int>>`) is used to store the coordinate information of the card position.

Corresponding coding element: Data structures for storing game status (e.g., arrays, STL containers)


******************************************


Feature 3: Using of STL
We mainly use vector as our `STL containers` 

1. Using `vector` for dynamic memory allocation:

   We utilize the `vector` class template for dynamic memory allocation and create multiple two-dimensional vectors and one-dimensional vectors. By using the constructor of `vector`, we can dynamically allocate memory and specify initial values.

3. Dynamic allocation of two-dimensional vectors: 

   In some examples, we create two-dimensional vectors using the `vector<vector<T>>` syntax. By specifying the number of rows and columns in the constructor, we dynamically allocate a two-dimensional vector and allocate memory space for each element.


Examples:
```cpp
vector<vector<int>> matrix(numRows, vector<int>(numCols));
vector<vector<bool>> booleanMatrix(numRows, vector<bool>(numCols, false));
vector<vector<int>> nestedMatrix(numF, vector<int>(numF));
```


3. Dynamic allocation of one-dimensional vectors:

   We also create one-dimensional vectors using the `vector<T>` syntax. By specifying the size of the vector in the constructor, we dynamically allocate a one-dimensional vector and allocate memory space for each element.


Example:
```cpp
vector<int> singleVector(numF);
```


By utilizing `vector` for dynamic memory management, we can dynamically allocate and adjust the memory size as needed. This allows for more efficient memory management and eliminates the complexity of manual memory allocation and deallocation. Additionally, the `vector` class provides convenient member functions and operators, making it easier to access and manipulate dynamically allocated memory.


Corresponding coding element: Dynamic memory management (e.g., dynamic arrays, linked lists, STL containers)


******************************************


Feature 4:
During the game, if the player want to 

File input/output (e.g., for loading/saving game status)


******************************************


Feature 5:

Program codes in multiple files (recall separate compilation)


******************************************











▪ Compilation and execution instructions. This serves like a "Quick start" of your game.
The teaching team will follow your instructions to compile and run your game










