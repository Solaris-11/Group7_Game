**Identification of the Team Members:**

 1. Chen Shiyang 3035974432
 2. Hu Yujia 3035980302
 3. Lin Zequn 3036059605
 4. Nie Mingyang 3036086713
 5. Wu Zhikai 3035973804


******************************************

**Game Description and Rules**


Welcome to the Flip Card Game! This is a text_base game based on C++, your objective is to flip cards and match them. Each mode offers its own level of difficulty and challenges.

The operation method of the game is to use the "W,A,S,D, Enter" 5 keys for selection and flipping. 

If you want to pause the game during gameplay, you can press "q" to enter the pause menu. In the pause menu, you can choose to save the game and exit, continue the game, and restart.

You can test your memory and matching skills across different game modes: Endless, Challenge, and Custom, each game mode refers to different rules.
  
  1. **Endless Mode**: including easy mode and hard mode, unlimited numbers of moves and limited 3 types of rounds will be included
      
      1. Easy Mode: Two cards can be flipped at once, larger table will be set in each new round, there are no move limit

      2. Hard Mode: Three cards can be flipped at once, larger table will be set in each new round, there are no move limit
  
  2. **Challenge Mode**: There will be a maximum move limit, there will be a shorter time interval between each flip
  
  3. **Custom Mode**: You can define your own table: its size and the number of cards to be flipped at once, there are no move limit

All of the instructions can be found in the tutorial part, you can check any time if you forget.


******************************************

**Game features and corresponding coding elements**


**Feature 1**: Shuffling mechanism

Every time a player starts a new round, the number positions corresponding to the original cards will be disrupted.
 
We define a `shuffle()` function to initialize and shuffle the cards in the game. Here are the steps for the code:

1. By calculating the value of `numCards`, the total number of cards on the game table is determined. The `numRows` and `numCols` variables are used here, which represent the number of rows and columns of the game desktop respectively.

2. Calculate the logarithm of the cards, divide `numCards` by `numF` (the number of occurrences of each card), and get the value of `numPairs`. This value represents the number of pairs of cards in the game.

3. By calling the `srand()` function, use the current time as the random number seed to ensure that the generated random number sequence is different each time the program is run.

4. Initialize the card. Use a nested `for` loop to iterate through each position on the game table and assign a unique value to the card in each position. The formula `(i * numCols + j) % numPairs + 1` is used here to determine the value of each card. Among them, `i` and `j` represent the row and column index of the current position, and `numPairs` represents the number of pairs of cards. This way, each pair of cards is assigned a unique value from 1 to `numPairs`.

5. Shuffle the cards. Use two nested `for` loops, iterating `numPairs` times. In each iteration, two cards are randomly selected by generating random row and column indices. Then, use the `swap()` function to exchange the values ​​of these two cards to achieve random shuffling of the cards.

We use this function to initialize and shuffle the cards in the game to ensure that each pair of cards has a unique value, and to achieve the shuffling effect by randomly exchanging the positions of the cards.

**Corresponding coding element**: Generation of random game sets or events


******************************************


**Feature 2**: Custom data structure - Structure Board


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

**Corresponding coding element**: Data structures for storing game status


******************************************


**Feature 3**: Using of STL
We mainly use vector as our `STL containers` 

1. Using `vector` for dynamic memory allocation:

   We utilize the `vector` class template for dynamic memory allocation and create multiple two-dimensional vectors and one-dimensional vectors. By using the constructor of `vector`, we can dynamically allocate memory and specify initial values.

3. Dynamic allocation of two-dimensional vectors: 

   In some examples, we create two-dimensional vectors using the `vector<vector<T>>` syntax. By specifying the number of rows and columns in the constructor, we dynamically allocate a two-dimensional vector and allocate memory space for each element.


Examples:
```cpp
vector<vector<int> > (EasySetting[round - 1][0], vector<int>(EasySetting[round - 1][1])),
vector<vector<bool> > (EasySetting[round - 1][0],vector<bool>(EasySetting[round - 1][1],false)),
```


3. Dynamic allocation of one-dimensional vectors:

   We also create one-dimensional vectors using the `vector<T>` syntax. By specifying the size of the vector in the constructor, we dynamically allocate a one-dimensional vector and allocate memory space for each element.



Example:


```cpp
vector<int> (EasySetting[round - 1][2]),
```


By utilizing `vector` for dynamic memory management, we can dynamically allocate and adjust the memory size as needed. This allows for more efficient memory management and eliminates the complexity of manual memory allocation and deallocation. Additionally, the `vector` class provides convenient member functions and operators, making it easier to access and manipulate dynamically allocated memory.


**Corresponding coding element**: Dynamic memory management


******************************************


**Feature 4**: Save and load game

Save game:

During the game, if the you want to save and quit, you can press the key "q" to enter the pause menu, the pause menu will show the save and quit option. We use `saveGame()` function to realize the file saving.





Load game: 

After quit the current round, you can find the load game option in the main menu.
You can choose the option "load game" to return to previous game progress. The function `RunLoadGame()` will help you to access the game progress which you have saved.




**Corresponding coding element**: File input/output


******************************************


**Feature 5**: Faster operation speed and less resource consumption

We spread the program code into multiple files to implement separate compilation.
We scattered the code into the following files:

 1. `MoveCursor.h`: header file, containing declarations of functions or classes related to cursor movement.
 
 2. `README.md`: The project description document, including an overview of the project, how to use it, and other information.
 
 3. `main.cpp`: The main program file, containing the entry point of the program (`main` function) and the implementation of other functions or classes related to the main logic.
 
 4. `main.h`: header file, containing declarations of functions or classes related to the main program file `main.cpp`.
 
 5. `makefile`: Makefile used to build and compile programs, containing rules for compilation and linking.
 
 6. `termios.h`: header file, containing declarations of functions or classes related to terminal input and output.
 
 7. `unistd.h`: header file, containing declarations of functions or classes related to the operating system interface.


Through these files, we can have faster compilation speed, while reducing resource consumption and improving code maintainability.


**Corresponding coding element**: Program codes in multiple files



******************************************


**Compilation and execution instructions**

In order to start playing the game, you can follow the steps below

1. **File Transfer**: Transfer files from the local computer to the virtual machine. 

2. **Log in to the virtual machine**: You can use the SSH client to log in to the Linux system of the virtual machine.

3. **Compile and run the C++ file**: On the Linux system in the virtual machine, use the appropriate compiler and commands to compile and run the C++ file.
You can use the code in makefile to compile:

      ```
      memorymatching: main.cpp main.h MoveCursor.h termios.h unistd.h
	          g++ -pedantic-errors -std=c++11 main.cpp -o memorymatching
      ```

After that, you can start the game.









