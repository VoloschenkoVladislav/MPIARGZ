#include <iostream>
#include "gameboard.h"
#include <string>

#define X_POINT 50
#define Y_POINT 50	

using std::cout;
using std::cin;
using std::endl;


struct info {
	int x, y;
	char side;
};

int main() {
	int difficultyLVL;
	int m, n, x, y;
	bool gameCycle = true;
	char player = 'x', side, turn;
	system("mode con cols=130 lines=60");
	cout << "Input m, n: ";
	cin >> m >> n;
	cout << endl << "Difficulty level: " << endl << "1 - Easy" << endl << "2 - Normal" << endl << "3 - Hard" << endl << "4 - Imposible" << endl << "5 - Suicide" << endl << ">> ";
	cin >> difficultyLVL;
	system("cls");



	Gameboard game(m, n, X_POINT, Y_POINT);

	while (gameCycle) {
		system("cls");
		game.draw();
		if (player == 'x') { //Ход игрока
			cout << "Your turn" << endl;
			std::cin >> x >> y >> side;

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
		else { // ход ИИ
			cout << "Enemy's turn" << endl;
			Sleep(1000);
			game.inf = game.computer_turn(difficultyLVL, player);
			turn = game.gameTurn(game.inf.x, game.inf.y, game.inf.side, player);

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
	}

	std::cin >> m;

	return 0;
}