#include <iostream>
#include "gameboard.h"

int main() {
	int m, n, x, y;
	bool gameCycle = true;
	char player = 'x', side, turn;

	std::cout << "Input m, n: ";
	std::cin >> m >> n;

	Gameboard game(m, n, 50, 50);

	while (gameCycle) {
		game.draw();
		std::cin >> x >> y >> side;
		system("cls");
		try {
			turn = game.gameTurn(x, y, side, player);
		}
		catch (int error) {
			std::cout << error;
			system("pause");
			return 1;
		}
		switch (turn) {
		case 'n':
			if (player == 'x')
				player = 'o';
			else
				player = 'x';
			break;

		case 'x':
			break;
		case 'o':
			break;
		case 'w':
			std::cout << "You win!" << std::endl;
			gameCycle = false;
			break;
		case 'l':
			std::cout << "You lose!" << std::endl;
			gameCycle = false;
			break;
		}
	}

	std::cin >> m;

	return 0;
}