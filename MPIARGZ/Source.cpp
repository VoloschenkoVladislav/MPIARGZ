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
	if (difficultyLVL > 5) difficultyLVL = 5;
	if (m > 30) m = 30;
	if (n > 20) n = 20;


	Gameboard game(m + 1, n + 1, X_POINT, Y_POINT);

	while (gameCycle) {
		system("cls");
		game.draw();
		if (player == 'x') { //Ход игрока
			cout << "Your turn:" << endl;
			std::cin >> x >> y >> side;

			try {
				turn = game.gameTurn(x - 1, y - 1, side, player);
			}
			catch (int error) {
				system("cls");
				cout << "Error, try again." << endl << "Press any key to continue...";
				getchar();
				getchar();

				system("cls");
				turn = 'e';
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
				game.draw();
				gameCycle = false;
				break;
			case 'l':
				std::cout << "You lose!" << std::endl;
				game.draw();
				gameCycle = false;
				break;
			case 'p':
				std::cout << "Tie!" << std::endl;
				game.draw();
				gameCycle = false;
				break;
			case 'e':
				break;
			}
		}
		else { // ход ИИ
			cout << "Enemy's turn:" << endl;
			if (difficultyLVL == 1 || difficultyLVL == 2) Sleep(1000);
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
				game.draw();
				gameCycle = false;
				break;
			case 'l':
				std::cout << "You lose!" << std::endl;
				game.draw();
				gameCycle = false;
				break;
			case 'p':
				std::cout << "Tie!" << std::endl;
				game.draw();
				gameCycle = false;
				break;
			}

		}
	}

	std::cin >> m;

	return 0;
}