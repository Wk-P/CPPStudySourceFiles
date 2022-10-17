#include <iostream>
using namespace std;
// 八皇后问题，回溯算法
/*
	在每一列寻找皇后位置，
	不能放置就退回
*/

class Board {
private:
	int size;
	int** board;
public:
	Board() { size = 0; board = NULL; }
	Board(int _size) {
		this->size = _size;
		board = new int* [this->size];
		for (int i = 0; i < this->size; i++) {
			board[i] = new int[this->size];
			for (int j = 0; j < this->size; j++) {
				board[i][j] = 0;
			}
		}
	}
	void place(int row, int col) { board[row][col] = 1; }
	void show() {
		for (int row = 0; row < size; row++) {
			cout << "\t{ ";
			for (int col = 0; col < size; col++) {
				cout << board[row][col] << ", ";
			}
			cout << "}" << endl;
		}
		cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
	}
	void showPieces() {
		cout << "\t{ ";
		for (int col = 0; col < size; col++) {
			for (int row = 0; row < size; row++) {
				if (board[row][col] == 1) cout << row << ", ";
			}
		}
		cout << "}" << endl;
	}
	bool isEmpty() {
		for (int i = 0; i < this->size; i++) {
			for (int j = 0; j < this->size; j++) {
				if (board[i][j] == 1) return false;
			}
		}
		return true;
	}
	void pointSetEmpty(int row, int col) { board[row][col] = 0; }
	int get_size() { return size; }
	int** get_board() { return board; }
};


// 判断当前列是否可以放置
int ifPlaced(int row, int column, Board& _board, int size) {
	// 获取棋盘
	int** board = _board.get_board();
	// 判断行
	for (int m = 0; m < size; m++) if (board[row][m] == 1) return 1;
	// 左下 右上
	for (int m = 1; row + m < size && column - m >= 0; m++) if (board[row + m][column - m] == 1) return 2;
	for (int m = 1; row - m >= 0 && column + m < size; m++) if (board[row - m][column + m] == 1) return 2;
	// 左上 右下			 						
	for (int m = 1; row - m >= 0 && column - m >= 0; m++) if (board[row - m][column - m] == 1) return 2;
	for (int m = 1; row + m < size && column + m < size; m++) if (board[row + m][column + m] == 1) return 2;
	// 可放置
	return 0;
}

// 查找上一列棋子位置，更新棋盘信息，返回行下标
int findPrevPiece(Board& _board, int current_col, int size) {
	int** board = _board.get_board();
	for (int i = 0; i < size; i++) {
		if (board[i][current_col - 1] == 1) {
			_board.pointSetEmpty(i, current_col - 1);
			return i;
		}
	}
	return -1;
}

void solution(Board& board, int size) {
	// col 控制列移动 row 控制每列行运动
	int current_row = 0, current_col = 0, count = 0;
	// 列指针小于0则说明所有情况都被找出
	while (current_col < size && current_col >= 0) {
		if (board.isEmpty() && size <= 8) cout << "********---------------------------********\n";
		while (current_row < size) {
			int place = ifPlaced(current_row, current_col, board, size);
			// 当前行能放置
			if (place == 0) {
				board.place(current_row, current_col);
				// 当所有列都被放完，计数器增加
				if (current_col == size - 1) {
					if (size <= 8) board.showPieces();
					//board.show();
					count++;
				}
				// 退出行循环并进行下一列放置
				current_row = 0;
				current_col++;
				break;
			}
			// 当前行不能放置
			else current_row++;
		}
		// 本列均不能被放置，则更新上一列棋子位置
		if (current_row == size) {
			// 获取上一列棋子位置并更新至下一行
			current_row = findPrevPiece(board, current_col, size) + 1;
			// 列指针退回
			current_col--;
		}

		// 当最后一列已经被放置，发生回溯退回上一个棋子位置
   		if (current_col == size) {
			// 获取上一列棋子位置并更新
			current_row = findPrevPiece(board, current_col, size) + 1;
			// 列指针退回上一列
			current_col--;
			// 当指针已退至第一列（第一列棋子位置已被更新）
			// 上一列指针被指向最后一位，即需要向更前一列进行回溯
			while (current_row >= size) {
				current_row = findPrevPiece(board, current_col, size) + 1;
				current_col--;
			}
		}
		
	}
	cout << "\t共有" << count << "种解法！\n";
}

int main() {
	int input = 1; 
	while (input != 0) {
		int n = 0;
		cout << "N皇后问题 N="; cin >> n;
		if (n < 0) { cout << "输入数据错误，请重新输入!" << endl; continue; }
		else if (n >= 13) { cout << "数据量过大无法计算!" << endl; continue; }
		Board* board = new Board(n);
		solution(*board, board->get_size());
		cout << "是否退出\t0.退出, 1.继续\n输入："; cin >> input;
	}
	return 0;
}