/**
 * 不同游戏模式设计
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

// 显示牌桌
void ShowCards(vector<vector<int>> table, vector<vector<bool>> flipped) {
  int row = table.size(), col = table[0].size();
  // 第一行
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
  // 后续几行，翻牌则显示数字，未翻牌显示*
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

// 洗牌
void shuffles(vector<vector<int>>& table){
  int rows = table.size();
  int cols = table[0].size();
  // 创建随机数生成器
  srand((unsigned int)time(NULL));
  // 随机交换多次
  for (int i = 0; i < rows*cols; i++) {
    // 生成两个随机索引
    int row1 = rand() % rows, col1 = rand() % cols;
    int row2 = rand() % rows, col2 = rand() % cols;
    // 交换两个随机索引对应的元素
    swap(table[row1][col1], table[row2][col2]);
  }
}

// 读取玩家输入并判断是否合法
void GameInput(vector<Position>& coordinates, Setting s) {
  // 接收玩家输入
  for (int i = 1; i < coordinates.size(); i++) {
    // 直到输入合法
    string input;
    while (true) {
      cout << "Please enter the coordinate" << i << " : ";
      cin >> input;
      // 检查输入是否合法
      // 重复检测
      // 已翻牌检测
    }
  }
  
}

// 根据设置开启一轮游戏
void StartNewRound(Setting s) {
  // 牌型 table[0]
  vector<vector<int>> table(s.nRows, vector<int>(s.nCols, 0));
  // 初始化:3*3,2   table[0][0] = 1 table[0][1]=2 table[0][2]=3 table[1][0]=2
  for (int i = 0; i < table.size(); ++i) {
    for (int j = 0; j < table[i].size(); ++j) {
      int seq = i * table.size() + j;
      int sum = table.size() * table[i].size() / s.numF;
      table[i][j] = seq % sum + 1;
    }
  }
  // 洗牌
  shuffles(table);
  // 是否翻牌
  vector<vector<bool>> flipped(s.nRows, vector<bool>(s.nCols, true));
  // 当前进度和目标
  int isFound = 0, target = s.nRows * s.nCols / s.numF;
  // 是否匹配
  bool isMatch = true;
  // 显示牌桌
  ShowCards(table, flipped);
  // 游戏循环
  while (isFound < target) {
    // 玩家输入
    vector<Position> inputs(s.numF);
    GameInput(inputs, s);
    // 翻牌处理
    for (int i = 0; i < inputs.size(); i++) {
      flipped[inputs[i].row - 1][inputs[i].col - 1] = true;
    }
    // 判断是否匹配
    int cur = table[inputs[0].row - 1][inputs[0].col - 1];
    for (int i = 1; i < inputs.size(); i++) {
      if (table[inputs[i].row - 1][inputs[i].col - 1] != cur) {
        isMatch = false;
        break;
      }
    }
    // 匹配成功
    if (isMatch) {
      // 进度+1
      isFound++;
      // 显示info
    }
    // 匹配失败
    else {
      // 重置翻牌
      for (int i = 0; i < inputs.size(); i++) {
        flipped[inputs[i].row - 1][inputs[i].col - 1] = false;
      }
      // 显示info
    }
    // 显示牌桌
    ShowCards(table, flipped);
    // 重置匹配位
    bool isMatch = true;
  }
}

// 简单无尽模式
void StartEasyEndless() {
    // 不同轮次的难度设置
    vector<Setting> settings{
        {2, 4, 2},
        {3, 4, 2},
        {4, 4, 2}
    };
    // 轮次
    int round = 1;
    // 无尽模式
    while (true) {
        // 提示
        cout << "Current Round: " << round << endl;
        // 根据当前轮次的难度开启游戏回合
        StartNewRound(settings[round - 1]);
        // 恭喜信息
        cout << "Congratulations! You Pass Round:" << round << endl;
        round++;
    }
}

// 困难无尽模式 
void StartHardEndless() {

}

// 挑战模式
void StartChallenge(){

}

// 自定义模式
void StartCustom(Setting s) {

}