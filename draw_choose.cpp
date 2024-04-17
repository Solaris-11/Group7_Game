#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include <iomanip>
using namespace std;

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

// 绘制表格
void drawTable(int numRows, int numCols, int selectedRow, int selectedCol, const int card[4][4], const bool table[4][4]) {
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

void shuffles(int (*card)[4]) {
	srand((unsigned int)time(NULL)); //讓亂數隨著時間改變
	for (int i = 0; i < 4; i++) {  //進行卡片初始化
		for (int j = 0; j < 4; j++) {
			card[i][j] = i * 4 +j + 1;
		}
	}
	//for (int i = 0; i < 16; i++) {  //隨機挑兩張牌交換
		//swap(card[rand() % 4][rand() % 4], card[rand() % 4][rand() % 4]);
	//}
}
//實作交換函式
void swap(int &a, int &b) {
	int tmp;
	tmp = a;
	a = b;
	b = tmp;
}

int main() {
    setNonCanonicalMode();

    int numRows = 4;
    int numCols = 4;
    int selectedRow = numRows;
    int selectedCol = 1;

    int card[4][4];
    for(int i = 0;i < 4;i++){
        for( int j = 0; j<4 ;j++){
	    card[i][j] = i * 4 +j+1;
	    }
	}
    bool table[4][4] = {false};
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
        }
    }

    restoreTerminalMode();
    return 0;
}
