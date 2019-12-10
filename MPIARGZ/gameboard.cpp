#include "gameboard.h"




Gameboard::Gameboard(int m, int n, int x, int y) : m_(m), n_(n), marginLeft_(x), marginTop_(y) {
	for (int i = 0; i < m; i++) {
		std::vector<cell> newVector;
		status_.push_back(newVector);
		for (int j = 0; j < n; j++) {
			cell newCell;
			status_[i].push_back(newCell);
		}
	}

	busyX_ = busyO_ = 0;
	win_ = GetConsoleWindow();
	hdc_ = GetDC(win_);
	SetBkColor(hdc_, RGB(0, 0, 0));
}

// 0 - invalid argument, 1 - index out of range, 2 - line is busy
char Gameboard::gameTurn(int x, int y, char side, char player) {
	//добавление линии в заданную и соседнюю с ней клетку (если таковая имеется)
	if (side != 'u' && side != 'd' && side != 'l' && side != 'r' )
		throw 0;
	if (player != 'x' && player != 'o')
		throw 0;
	if (x >= m_ - 1 || y >= n_ - 1)
		throw 1;
	switch (side) {
	case 'u':
		if (!status_[x][y].top) {
			status_[x][y].top = true;
			if (y != 0)
				status_[x][y - 1].bottom = true;
		}
		else
			throw 2;
		break;
	case 'd':
		if (!status_[x][y].bottom) {
			status_[x][y].bottom = true;
			if (y != n_ - 1)
				status_[x][y + 1].top = true;
		}
		else
			throw 2;
		break;
	case 'l':
		if (!status_[x][y].left) {
			status_[x][y].left = true;
			if (x != 0)
				status_[x - 1][y].right = true;
		}
		else
			throw 2;
		break;
	case 'r':
		if (!status_[x][y].right) {
			status_[x][y].right = true;
			if (x != m_ - 1)
				status_[x + 1][y].left = true;
		}
		else
			throw 2;
		break;
	}

	//заполнение ограниченных клеток значениями
	char out = 'n';
	for (int i = 0; i < m_ - 1; i++)
		for (int j = 0; j < n_ - 1; j++)
			if (status_[i][j].bottom && status_[i][j].top && status_[i][j].left && status_[i][j].right)
				if (status_[i][j].value == '\0') {
					status_[i][j].value = player;
					if (player == 'x') {
						busyX_++;
						out = player;
					}
					else {
						busyO_++;
						out = player;
					}
				}

	//проверка на победу
	if (busyX_ + busyO_ == (m_ - 1) * (n_ - 1)) {
		if (busyX_ < busyO_)
			return 'l';
		else if (busyO_ < busyX_)
			return 'w';
		else
			return 'p';
	}

	return out;
}

void Gameboard::draw() {
	//интервал между точками в px
	const int interval = 32;
	Point newPoint(hdc_);
	Line newLine(interval, hdc_);
	Mark markX('x', hdc_), markO('o', hdc_);
	for (int i = 0; i < m_ - 1; i++) {
		for (int j = 0; j < n_ - 1; j++) {
			newLine.move(i*interval + marginLeft_, j*interval + marginTop_);
			if (status_[i][j].top)
				newLine.drawToRight();
			if (status_[i][j].left)
				newLine.drawToDown();
			if (status_[i][j].right) {
				newLine.move((i + 1)*interval + marginLeft_, j*interval + marginTop_);
				newLine.drawToDown();
			}
			if (status_[i][j].bottom) {
				newLine.move(i*interval + marginLeft_, (j + 1)*interval + marginTop_);
				newLine.drawToRight();
			}
		}
	}
	for (int i = 0; i < m_; i++) {
		for (int j = 0; j < n_; j++) {
			newPoint.move(i*interval + marginLeft_, j*interval + marginTop_);
			newPoint.draw();
		}
	}
	for (int i = 0; i < m_ - 1; i++) {
		for (int j = 0; j < n_ - 1; j++) {
			if (status_[i][j].value == 'x') {
				markX.move(i*interval + marginLeft_ + interval / 2, j*interval + marginTop_ + interval / 2);
				markX.draw();
			}
			else if (status_[i][j].value == 'o') {
				markO.move(i*interval + marginLeft_ + interval / 2, j*interval + marginTop_ + interval / 2);
				markO.draw();
			}
		}
	}
}













Point::Point(HDC hdc) {
	brush_ = CreateSolidBrush(RGB(r_, g_, b_));
	pen_ = CreatePen(PS_NULL, 1, RGB(r_, g_, b_));
	hdc_ = hdc;
}

void Point::draw() {
	//радиус точек
	const int radius = 6;
	SelectPen(hdc_, pen_);
	SelectBrush(hdc_, brush_);
	Ellipse(hdc_, x_ - radius, y_ - radius, x_ + radius, y_ + radius);
}

void Point::move(int x, int y) {
	x_ = x;
	y_ = y;
}













Line::Line(int length, HDC hdc) {
	length_ = length;
	hdc_ = hdc;
	pen_ = CreatePen(PS_SOLID, 4, RGB(r_, g_, b_));
}

void Line::move(int x, int y) {
	x_ = x;
	y_ = y;
}

void Line::drawToDown() {
	SelectPen(hdc_, pen_);
	MoveToEx(hdc_, x_, y_, NULL);
	LineTo(hdc_, x_, y_ + length_);
}

void Line::drawToRight() {
	SelectPen(hdc_, pen_);
	MoveToEx(hdc_, x_, y_, NULL);
	LineTo(hdc_, x_ + length_, y_);
}












Mark::Mark(char type, HDC hdc) {
	hdc_ = hdc;
	type_ = type;
	pen_ = CreatePen(PS_SOLID, 3, RGB(r_, g_, b_));
	brush_ = GetStockBrush(NULL_BRUSH);
}

void Mark::move(int x, int y) {
	x_ = x;
	y_ = y;
}

void Mark::draw() {
	SelectPen(hdc_, pen_);
	SelectBrush(hdc_, brush_);
	const int radius = 7;
	if (type_ == 'o')
		Ellipse(hdc_, x_ - radius, y_ - radius, x_ + radius, y_ + radius);
	else if (type_ == 'x') {
		MoveToEx(hdc_, x_ - radius, y_ - radius, NULL);
		LineTo(hdc_, x_ + radius, y_ + radius);
		MoveToEx(hdc_, x_ + radius, y_ - radius, NULL);
		LineTo(hdc_, x_ - radius, y_ + radius);
	}
}