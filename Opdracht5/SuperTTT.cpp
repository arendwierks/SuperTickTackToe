#include "SuperTTT.h"

using namespace std;

SuperTTT::SuperTTT(Side s) : prow(-1), pcolumn(-1), lastPlayer(s){
	for_each(boards.begin(), boards.end(), [](Board& board){
		fill(board.begin(), board.end(), EMPTY);
	});
}

//SuperTTT::Value SuperTTT::value(int depth, int board) const {
int SuperTTT::value(int depth, int board) const {
	if (depth == MAX_DEPTH){
		if (isAWin(COMPUTER, board)){
			return COMPUTER_WINS;
		}
		else if (isAWin(HUMAN, board)){
			return HUMAN_WINS;
		}
		else if (boardIsFull()){
			return DRAW;
		}
		else{
			int countComputer = 0;
			for_each(boards[board].cbegin(), boards[board].cend(), [&](Side s){
				if (s == COMPUTER){
					countComputer++;
				}
			});
			return countComputer;
		}		
		//return isAWin(COMPUTER, board) ? COMPUTER_WINS : isAWin(HUMAN, board) ? HUMAN_WINS : boardIsFull() ? DRAW : countComputer;
	}
	else if (depth == MAX_DEPTH + 1){
		return isAWin(COMPUTER, board) ? COMPUTER_WINS : isAWin(HUMAN, board) ? HUMAN_WINS : boardIsFull() ? DRAW : UNDECIDED;
	}
	else{
		return UNDECIDED;
	}
	//return isAWin(COMPUTER, 0) ? COMPUTER_WINS : isAWin(HUMAN, 0) ? HUMAN_WINS : boardIsFull() ? DRAW : UNDECIDED;
}


//SuperTTT::Value SuperTTT::chooseComputerMove(int& bestRow, int& bestColumn, int& bestBoard, Value alpha, Value beta, int depth) {
int SuperTTT::chooseComputerMove(int& bestRow, int& bestColumn, int& bestBoard, int alpha, int beta, int depth) {
	//Value bestValue = value(depth, bestBoard);
	int bestValue = value(depth, bestBoard);
	if (depth < MAX_DEPTH){
		++movesConsidered;
		if (bestValue == UNDECIDED) {
			Board pMainboard = boards[0]; // preserve state of big board before function a move is done
			//for (int board = 1; board < 10; ++board){
				//if (!checkFalseBoardMove(board) && !isAWin(HUMAN, board) && !isAWin(COMPUTER, board)){
					for (int row = 0; alpha < beta && row < 3; ++row) {
						for (int column = 0; alpha < beta && column < 3; ++column) {
							if (boards[bestBoard](row, column) == EMPTY) {
								boards[bestBoard](row, column) = COMPUTER;
								checkWins(COMPUTER);
								int dummyRow, dummyColumn, dummyBoard;
								if (bestBoard != 0){									
									dummyBoard = (column + 1) + (row * 3); // calculate on which board next move must be set	
									//giveRandomBoardWhenWon(dummyBoard); // to prevent move on board that is won
									if (dummyBoard < 0 || dummyBoard > 9){
										dummyBoard = 0;
									}
									giveBestBoardWhenWon(dummyBoard, COMPUTER);
								}
								else{
									dummyBoard = 0;
								}
								//Value value = chooseHumanMove(dummyRow, dummyColumn, dummyBoard, alpha, beta, depth + 1);
								int value = chooseHumanMove(dummyRow, dummyColumn, dummyBoard, alpha, beta, depth + 1);
								boards[bestBoard](row, column) = EMPTY;
								boards[0] = pMainboard; // return big board to state before the move was done
								if (value >= alpha) {
									if (row < 0 || row >= 3 || column < 0 || column >= 3){
										cout << "error" << endl;
									}
									alpha = value;
									bestRow = row;
									bestColumn = column;
									//bestBoard = board;
								}
							}
						}
					}
				//}
			//}
			bestValue = alpha;
		}
	}
	//else{
	//	// make value less when move causes next move to be set on a board that is won
	//	int nextBoard = (bestColumn + 1) + (bestRow * 3);
	//	if (isAWin(COMPUTER, nextBoard) || isAWin(HUMAN, nextBoard)){
	//		bestValue = 0;
	//	}
	//	/*	if (boards[0](bestRow, bestColumn) != EMPTY){
	//	bestValue = 0;
	//	}*/
	//}
	return bestValue;
}

//SuperTTT::Value SuperTTT::chooseHumanMove(int& bestRow, int& bestColumn, int& bestBoard, Value alpha, Value beta, int depth) {
int SuperTTT::chooseHumanMove(int& bestRow, int& bestColumn, int& bestBoard, int alpha, int beta, int depth) {
	//Value bestValue = value();
	int bestValue = value(depth, bestBoard);
	if (depth < MAX_DEPTH){
		++movesConsidered;
		if (bestValue == UNDECIDED) {
			Board pMainboard = boards[0]; // preserve state of big board before function a move is done
			//for (int board = 1; board < 10; ++board){
				//if (!checkFalseBoardMove(board) && !isAWin(HUMAN, board) && !isAWin(COMPUTER, board)){
					for (int row = 0; beta > alpha && row < 3; ++row) {
						for (int column = 0; beta > alpha && column < 3; ++column) {
							if (boards[bestBoard](row, column) == EMPTY) {
								boards[bestBoard](row, column) = HUMAN;
								checkWins(HUMAN);
								int dummyRow, dummyColumn, dummyBoard;
								if (bestBoard != 0){
									dummyBoard = (column + 1) + (row * 3); // calculate on which board next move must be set								
									//giveRandomBoardWhenWon(dummyBoard); // to prevent move on board that is won
									if (dummyBoard < 0 || dummyBoard > 9){
										dummyBoard = 0;
									}
									giveBestBoardWhenWon(dummyBoard, HUMAN);
								}
								else{
									dummyBoard = 0;
								}
								//Value value = chooseComputerMove(dummyRow, dummyColumn, dummyBoard, alpha, beta, depth + 1);
								int value = chooseComputerMove(dummyRow, dummyColumn, dummyBoard, alpha, beta, depth + 1);
								boards[bestBoard](row, column) = EMPTY;
								boards[0] = pMainboard; // return big board to state before the move was done
								if (value <= beta) {
									beta = value;
									if (row < 0 || row >= 3 || column < 0 || column >= 3){
										cout << "error" << endl;
									}
									bestRow = row;
									bestColumn = column;
									//bestBoard = board;
								}
							}
						}
					}
				//}
			//}
			bestValue = beta;
		}
		cout << movesConsidered << endl;
	}
	//else{
	//	// make value more when move causes next move to be set on a board that is won
	//	int nextBoard = (bestColumn + 1) + (bestRow * 3);
	//	if (isAWin(COMPUTER, nextBoard) || isAWin(HUMAN, nextBoard)){
	//		bestValue = 5;
	//	}
	//	//if (boards[0](bestRow, bestColumn) != EMPTY){
	//	//	bestValue = 5;
	//	//}
	//}
	return bestValue;
}

SuperTTT::Side SuperTTT::side(int row, int column, int board) const {
	return boards[board](row, column);
}

bool SuperTTT::isUndecided() const {
	return value(MAX_DEPTH+1) == UNDECIDED;
	//return value() == UNDECIDED;
}

bool SuperTTT::playMove(Side s, int board, int row, int column) {
	if (row < 0 || row >= 3 || column < 0 || column >= 3 || board < 1 || board > 9 || boards[board](row, column) != EMPTY || isAWin(HUMAN, board) || isAWin(COMPUTER, board) || checkFalseBoardMove(board))
		return false;
	boards[board](row, column) = s;
	prow = row;
	pcolumn = column;
	//cout << "Next board: " << (column + 1) + (row * 3) << endl;
	return true;
}

bool SuperTTT::boardIsFull() const {
	return none_of(boards[0].cbegin(), boards[0].cend(), [](Side s) {
		return s == EMPTY;
	});
}

bool SuperTTT::checkFalseBoardMove(int board){
	int nextBoard = (pcolumn + 1) + (prow * 3);
	if (prow == -1 && pcolumn == -1){
		return false;
	}
	//else if (isAWin(HUMAN, board) || isAWin(COMPUTER, board)){
	//	return true;
	//}
	else if (isAWin(HUMAN, nextBoard) || isAWin(COMPUTER, nextBoard)){
		return false;
	}
	return (board != nextBoard);
}

int SuperTTT::giveNextBoard(){
	if (prow == -1)
	{
		return 1;
	}
	else{
		return (pcolumn + 1) + (prow * 3);
	}	
}

void SuperTTT::giveRandomBoardWhenWon(int &b){
	if (isAWin(HUMAN, b) || isAWin(COMPUTER, b))
	{
		do{
			b = (rand() % 9) + 1;
		} while (isAWin(HUMAN, b) || isAWin(COMPUTER, b));
	}
}

void SuperTTT::giveBestBoardWhenWon(int &board, Side s){
	if (board < 0 || board > 9){
		board = 0;
	}
	if (isAWin(HUMAN, board) || isAWin(COMPUTER, board))
	{
		int row, column;
		board = 0;
		if (s == COMPUTER)
		{
			chooseComputerMove(row, column, board);
		}
		else
		{
			chooseHumanMove(row, column, board);
		}
		if (row < 0 || row >= 3 || column < 0 || column >= 3){
			cout << "error" << endl;
		}
		board = (column + 1) + (row * 3);
	}
	//return (board);
}

void SuperTTT::checkWins(Side s){
	for (int i = 1; i <= 9; i++){
		if (isAWin(s, i)){
			boards[0]((i - 1) / 3, (i - 1) % 3) = s;
			//cout << "player " << s << " board " << i << endl;
		}
	}
}

bool SuperTTT::isAWin(Side s, int b) const {
	for (int i = 0; i < 3; ++i) {
		if ((boards[b](i, 0) == s && boards[b](i, 1) == s && boards[b](i, 2) == s) ||
			(boards[b](0, i) == s && boards[b](1, i) == s && boards[b](2, i) == s)) {
			return true;
		}
	}
	return (boards[b](0, 0) == s && boards[b](1, 1) == s && boards[b](2, 2) == s) ||
		(boards[b](0, 2) == s && boards[b](1, 1) == s && boards[b](2, 0) == s);
}

SuperTTT::Side SuperTTT::giveLastPlayer() const{
	return lastPlayer;
}

void SuperTTT::setLastPlayer(SuperTTT::Side s){
	lastPlayer = s;
}