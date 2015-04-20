#pragma once

#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <array>
#include "Matrix.h"

const int MAX_DEPTH = 9;

class SuperTTT{
public:
	enum Side { EMPTY, HUMAN, COMPUTER };
	enum Value { HUMAN_WINS = -2, DRAW = -1, COMPUTER_WINS = 10, UNDECIDED = 11};

	SuperTTT(Side s = SuperTTT::COMPUTER);

	//Value chooseComputerMove(int& bestRow, int& bestColumn, int& bestBoard, Value alpha = HUMAN_WINS, Value beta = COMPUTER_WINS, int depth = 1);
	int chooseComputerMove(int& bestRow, int& bestColumn, int& bestBoard, int alpha = HUMAN_WINS, int beta = COMPUTER_WINS, int depth = 1);
	//Value chooseHumanMove(int& bestRow, int& bestColumn, int& bestBoard, Value alpha = HUMAN_WINS, Value beta = COMPUTER_WINS, int depth = 1);
	int chooseHumanMove(int& bestRow, int& bestColumn, int& bestBoard, int alpha = HUMAN_WINS, int = COMPUTER_WINS, int depth = 1);

	Side side(int row, int column, int board) const;
	bool isUndecided() const;
	bool playMove(Side s, int board, int row, int column);
	bool boardIsFull() const;
	bool checkFalseBoardMove(int board);
	void giveRandomBoardWhenWon(int &b);
	void giveBestBoardWhenWon(int &board, Side s);
	int giveNextBoard() const;
	void checkWins(Side s);
	bool isAWin(Side s, int b) const;
	Side giveLastPlayer() const;
	void setLastPlayer(Side s);
private:
	int movesConsidered = 0;
	int prow, pcolumn;
	typedef matrix<Side, 3, 3> Board;
	//Board board;
	std::array<Board, 10> boards;
	//Value value(int depth, int board) const;
	int value(int depth = 0, int board = 0) const;
	Side lastPlayer;
};