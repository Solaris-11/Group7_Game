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


void shuffle(vector<vector<int>> &card, int numRows, int numCols);
void swap(int &a, int &b);


// 将终端设置为非规范模式
void setNonCanonicalMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// 恢复终端的规范模式
void restoreTerminalMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// 清空终端屏幕
void clearScreen() {
    cout << "\033[2J";
}

// 移动终端光标到指定位置
void moveCursorTo(int x, int y) {
    cout << "\033[" << y << ";" << x << "H";
}


void drawTable(int numRows, int numCols, int selectedRow, int selectedCol, vector<vector<int>> card, vector<vector<bool>>& table, int numMove, double points) {
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
    cout << "Move: " << numMove << "    " << "Points: " << points;
    cout << endl;

}


void shuffle(vector<vector<int>> &card, int numRows, int numCols){
    int numCards = numRows * numCols;
    int numPairs = numCards / 2;    // Assume each pair has 2 cards
    srand((unsigned int)time(NULL));    //讓亂數隨著時間改變
	for (int i = 0; i < numRows; i++) {  //進行卡片初始化
		for (int j = 0; j < numCols; j++) {
			card[i][j] = (i * numCols + j) % numPairs + 1;
		}
	}
	for (int i = 0; i < numCards; i++) {  //隨機挑兩張牌交換
		swap(card[rand() % numRows][rand() % numCols], card[rand() % numRows][rand() % numCols]);
	}
}

void swap(int &a, int &b) {
	int tmp;
	tmp = a;
	a = b;
	b = tmp;
}

void checkpair(vector<int> &pairs, vector<vector<int>> &coord, vector<vector<bool>> &table, int &numPaired, double &points, int totalNumPairs, bool &failure){
    if(pairs[0] == pairs[1]){
        numPaired++;
        points = (100/(double)totalNumPairs)*numPaired;
        failure = false;   // 配對成功 保持翻牌
    }else{
        int row1 = coord[0][0], row2 = coord[1][0], col1 = coord[0][1], col2 = coord[1][1];
        table[row1][col1]=false;
        table[row2][col2]=false;
        failure = true;    // 配對失敗 重新drawtable（蓋回去）
    }
}

void choose(const int Rows, const int Cols) {
    setNonCanonicalMode();

    const int numRows = Rows;
    const int numCols = Cols;
    int selectedRow = numRows;
    int selectedCol = 1;

    vector<vector<int>> card(numRows, vector<int>(numCols));
    shuffle(card, numRows, numCols);  // 卡牌初始化 + 洗牌

    //for (int i = 0; i < Rows; i++){
    //    for (int j = 0; j < Cols; j++){
    //        cout << card[i][j] << " ";
    //    }
    //}
    int count = 0, numPaired = 0, numMove = 0, totalNumPairs = Rows*Cols/2;
    double points = 0;
    bool failure = false, flip = false;

    vector<vector<bool>> table(numRows,vector<bool>(numCols,false));    // create a table that consist the condition of each card (initial value: false)
    vector<int> pairs(Rows*Cols);
    vector<vector<int>> coord(2,vector<int>(2));
    while (numPaired != totalNumPairs) {
        drawTable(numRows, numCols, selectedRow, selectedCol, card, table, numMove, points);
        if (flip){
            if(count>0 && count%2 ==0){
                sleep(1);
                checkpair(pairs, coord, table, numPaired, points, totalNumPairs, failure);
                if(failure == true){    // 配對失敗 重新drawtable（蓋回去）
                    drawTable(numRows, numCols, selectedRow, selectedCol, card, table, numMove, points);
                }
                else if (failure == false){
                    drawTable(numRows, numCols, selectedRow, selectedCol, card, table, numMove, points);
                }
            }
            flip = false;
        }

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
                flip = true;
                if (selectedRow <= numRows && selectedCol <= numCols) {
                    numMove++;
                    if (table[selectedRow-1][selectedCol-1] == false) {
                        table[selectedRow-1][selectedCol-1] = true;
                        pairs[count%2]=card[selectedRow-1][selectedCol-1];
                        coord[count%2][0]=selectedRow-1;
                        coord[count%2][1]=selectedCol-1;
                        count++;
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


