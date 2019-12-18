#pragma once

#include <vector>
#include <iostream>
#include <windows.h>
#include <windowsx.h>





class Gameboard {
private:

	//структура клетки, где отображаются её стенки и значение (\0, х, о)
	struct cell {
		bool left = false, right = false, top = false, bottom = false;
		char value = '\0';
	};

	//структура для записи данных хода компьютера
	struct turn_info {
		int x, y; 
		char side; 
	};

	

	//полный список клеток игрового поля
	std::vector<std::vector<cell>> status_;


	//размерность поля (ширина, высота)
	const int m_, n_, marginLeft_, marginTop_;
	int busyX_, busyO_;

	HWND win_;
	HDC hdc_;

	int value(Gameboard G, int i, int j, char side, int number, char player);
	bool cell_status(int i, int j, char side);

public:	
	turn_info computer_turn(int number, char player);
	
	Gameboard(int m, int n, int x, int y);

	char gameTurn(int x, int y, char side, char player);

	void draw();
	turn_info inf;
};






class Point {
private:
	int x_, y_;
	const int r_ = 200, g_ = 200, b_ = 200;
	HDC hdc_;
	HBRUSH brush_;
	HPEN pen_;
public:
	Point(HDC hdc);

	void move(int x, int y);

	void draw();
};






class Line {
private:
	int x_, y_, length_;
	const int r_ = 255, g_ = 50, b_ = 50;
	HDC hdc_;
	HPEN pen_;
public:

	Line(int length, HDC hdc);

	void move(int x, int y);

	void drawToRight();

	void drawToDown();
};





class Mark {
private:
	//координаты центра фигуры
	int x_, y_;
	char type_;
	const int r_ = 255, g_ = 255, b_ = 255;
	HDC hdc_;
	HPEN pen_;
	HBRUSH brush_;
public:
	Mark(char type, HDC hdc);

	void move(int x, int y);

	void draw();
};