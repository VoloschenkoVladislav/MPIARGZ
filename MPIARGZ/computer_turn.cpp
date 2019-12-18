#include "gameboard.h"

char computer;

Gameboard::turn_info Gameboard::computer_turn(int number, char player) {
	computer = player;
	Gameboard G(m_, n_, marginLeft_, marginTop_);
	turn_info result;
	char side;
	int v = -10000, temp, i, j;
	G.status_ = Gameboard::status_;
	for (i = 0; i < m_ - 1; i++)
		for (j = 0; j < n_ - 1; j++) {
			if (!status_[i][j].top) {
				side = 'u';
				temp = G.value(G, i, j, side, number - 1, player);
				if (temp > v) {
					v = temp;
					result.x = i;
					result.y = j;
					result.side = side;
				}
			}
			if (!status_[i][j].left) {
				side = 'l';
				temp = G.value(G, i, j, side, number - 1, player);
				if (temp > v) {
					v = temp;
					result.x = i;
					result.y = j;
					result.side = side;
				}
			};
		}
	j = n_ - 2;
	for (i = 0; i < m_ - 1; i++)
		if (!status_[i][j].bottom) {
			side = 'd';
			temp = G.value(G, i, j, side, number - 1, player);
			if (temp > v) {
				v = temp;
				result.x = i;
				result.y = j;
				result.side = side;
			}
		}
	i = m_ - 2;
	for (j = 0; j < n_ - 1; j++)
		if (!status_[i][j].right) {
			side = 'r';
			temp = G.value(G, i, j, side, number - 1, player);
			if (temp > v) {
				v = temp;
				result.x = i;
				result.y = j;
				result.side = side;
			}
		}
	return result;
}

int Gameboard::value(Gameboard G, int i, int j, char side, int number, char player) {
	int result = 0, v = -10000, temp, mn=1;
	char c = G.gameTurn(i, j, side, player);
	if (c == 'n') {
		result = 0;
		if (player == 'x') player = 'o';
		else player = 'x';
		mn = -1;
	}
	else if (c == player) result = 1;
	else if (c == 'r' || c == 'l') {
		result = 100;
		number = 0;
	}
	if (number > 0) {
		for (i = 0; i < m_ - 1; i++)
			for (j = 0; j < n_ - 1; j++) {
				if (!G.cell_status(i, j, 'u')) {
					side = 'u';
					temp = value(G, i, j, side, number - 1, player);
					if (temp > v) {
						v = temp;
					}
				}
				if (!G.cell_status(i, j, 'l')) {
					side = 'l';
					temp = value(G, i, j, side, number - 1, player);
					if (temp > v) {
						v = temp;
					}
				}
			}
	
			j = n_ - 2;
			for (i = 0; i < m_ - 1; i++)
				if (!G.cell_status(i, j, 'd')) {
					side = 'd';
					temp = value(G, i, j, side, number - 1, player);
					if (temp > v) {
						v = temp;
					}
				}
			i = m_ - 2;
			for (j = 0; j < n_ - 1; j++)
				if (!G.cell_status(i, j, 'r')) {
					side = 'r';
					temp = value(G, i, j, side, number - 1, player);
					if (temp > v) {
						v = temp;
					}
				}
			v = v * mn;
			result += v;
	}
	return result;
}

bool Gameboard::cell_status(int i, int j, char side) {
	switch (side) {
	case 'u':
		return status_[i][j].top;
		break;
	case 'd':
		return status_[i][j].bottom;
		break;
	case 'l':
		return status_[i][j].left;
		break;
	case 'r':
		return status_[i][j].right;
		break;
	}
}