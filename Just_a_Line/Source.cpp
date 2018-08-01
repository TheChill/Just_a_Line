#include <iostream>
#include <windows.h>
#include <ctime>
#include <vector>

HWND myconsole = GetConsoleWindow();
HDC mydc = GetDC(myconsole);

class Tail {
	class Pixel {
		int x;
		int y;
		COLORREF color;
	public:
		Pixel(int x, int y, COLORREF color) : x(x), y(y), color(color) {
		}

		void set_position(int x, int y) {
			this->x = x;
			this->y = y;
		}

		int get_x() {
			return x;
		}

		int get_y() {
			return y;
		}

		COLORREF get_color() {
			return color;
		}
	};

	std::vector<Pixel> tail;
	std::pair<int, int> to_remove;
public:
	Tail() {
		//red
		//for (int i = 0; i < 201; i++) {
		//	tail.push_back(Pixel(10, 10, RGB(255, i, 0)));
		//}

		//green
		for (int i = 255; i > 0; i --) {
			tail.push_back(Pixel(10, 10, RGB(0, i, 0)));
		}

		//blue
		//for (int i = 255; i > 0; i -= 3) {
		//	tail.push_back(Pixel(10, 10, RGB(i, 255, 255)));
		//}
		//for (int i = 255; i > 0; i -= 3) {
		//	tail.push_back(Pixel(10, 10, RGB(0, i, 255)));
		//}
		//for (int i = 255; i > 0; i -= 3) {
		//	tail.push_back(Pixel(10, 10, RGB(0, 0, i)));
		//}


	}

	void move() {
		to_remove.first = tail[tail.size() - 1].get_x();
		to_remove.second = tail[tail.size() - 1].get_y();

		for (int i = tail.size() - 1; i > 0; i--) {
			tail[i].set_position(tail[i - 1].get_x(), tail[i - 1].get_y());
		}

		if ((GetKeyState(VK_UP) & 0x8000) && (tail[0].get_y() > 0)) {
			tail[0].set_position(tail[0].get_x(), tail[0].get_y() - 1);
		}
		if ((GetKeyState(VK_DOWN) & 0x8000) && (tail[0].get_y() < 750)) {
			tail[0].set_position(tail[0].get_x(), tail[0].get_y() + 1);
		}
		if ((GetKeyState(VK_LEFT) & 0x8000) && (tail[0].get_x() > 0)) {
			tail[0].set_position(tail[0].get_x() - 1, tail[0].get_y());
		}
		if ((GetKeyState(VK_RIGHT) & 0x8000) && (tail[0].get_x() < 1300)) {
			tail[0].set_position(tail[0].get_x() + 1, tail[0].get_y());
		}
	}

	void print() {


		SetPixel(mydc, to_remove.first, to_remove.second, RGB(0, 0, 0));
		//system("cls");

		for (int i = tail.size() - 1; i >= 0; i--) {
			SetPixel(mydc, tail[i].get_x(), tail[i].get_y(), tail[i].get_color());
		}
	}
};

int main() {
	Tail tail;
	int count = 0;

	while (true) {
		tail.move();
		tail.print();
		count++;

		//if (count == 100) {
		//	system("cls");
		//	count = 0;
		//}
	}

	std::cin.ignore();
	return 0;
}