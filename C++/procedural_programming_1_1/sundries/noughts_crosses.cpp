// крестики нолики

#include<iostream>
#include<vector>

using namespace std;

void display_board(const vector<vector<char>>& board) {
	cout << "  1 2 3" << endl;
	for (int i = 0; i < 3; ++i) {
		cout << i + 1 << " ";
		for (int j = 0; j < 3; ++j) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

bool check_win(const vector<vector<char>>& board, char symbol) {
	for (int i = 0; i < 3; ++i) {
		if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) {
			return true;
		}
		if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) {
			return true;
		}
	}

	if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) {
		return true;
	}
	if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) {
		return true;
	}

	return false;
}

bool check_tie(const vector<vector<char>>& board) {
	for (const auto& row : board) {
		for (char cell : row) {
			if (cell == ' ') {
				return false; // если пустая ячейка найдена - игра окончена
			}
		}
	}
	return true; // все ячейки заняты - ничья
}


// player move

void computer_move(vector<vector<char>>& board) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (board[i][j] = ' ') {

				vector<vector<char>> temp_board = board;
				temp_board[i][j] = 'X';

				if (check_win(temp_board, 'X')) {
					board[i][j] = 'O';
					return;
				}
			}
		}
	}

	int row, col;

	try {
		do {
			row = rand() % 3;
			col = rand() % 3;
		} while (board[row][col] != ' ');
		board[row][col] = '0';
	}
	catch (const exception& err) {
		cerr << err.what();
	}
	// если не заработает перемещение - убрать исключения
}

void play_game() {
	vector<vector<char>> board(3, vector<char>(3, ' '));

	while (true) {
		display_board(board);

		// player_move(board);

		if (check_win(board, 'X')) {
			display_board(board);
			cout << "\n Win \n";
			break;
		}

		if (check_tie(board)) {
			display_board(board);
			cout << "\n no \n";
			break;
		}

		computer_move(board);
		if (check_win(board, 'O')) {
			display_board(board);
			cout << "pc win\n";
			break;
		}

	}


}
