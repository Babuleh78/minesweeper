#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include<thread>
#include <iostream>

using namespace sf;
using namespace std;
class cell {
public:
	cell() {
		around = 0; condition = 0;
	}
	int get_condition() {
		return condition;
	}
	void set_condition(int _c) {
		condition = _c;
	}
	int get_around() {
		return around;
	}
	void set_around(int _ar) {
		around = _ar;
	}

private:
	int condition; //Мина - 1 пусто - 0 Обезврежена = -1 78 - стена?
	int around; //
};

//----------x w
//|
//|
//|
//y
//h
int min_count(cell(*field)[10], int x, int y, int width, int height) {
	int a = 0;
	if (field[x][y].get_condition() == 1) {
		return 0;
	}
	if (x == 0 && y == 0) {//Левый верхний угол
		return field[1][0].get_condition() + field[1][1].get_condition() + field[0][1].get_condition();
	}
	else if (y == 0 && x != width-1) {//верхняя граница
		return  field[x - 1][0].get_condition() + field[x + 1][0].get_condition() + field[x - 1][1].get_condition() + field[x][1].get_condition() + field[x + 1][1].get_condition();
	}
	else if (y == 0 && x == width-1) {//правый верхний угол
		return field[x - 1][0].get_condition() + field[x - 1][1].get_condition() + field[x][1].get_condition();
	}
	else if (x == 0 && y != height-1) {//левая граница
		return  field[0][y + 1].get_condition() + field[0][y - 1].get_condition() + field[1][y - 1].get_condition() + field[1][y + 1].get_condition() + field[1][y].get_condition();
	}
	else if (y == height-1 && x == 0) {//Левый нижний угол
		return field[0][y - 1].get_condition() + field[1][y].get_condition() + field[1][y - 1].get_condition();
	}
	else if (y == height-1 && x != width-1) {//нижняя граница
		return  field[x - 1][y].get_condition() + field[x + 1][y].get_condition() + field[x + 1][y - 1].get_condition() + field[x - 1][y - 1].get_condition() + field[x][y - 1].get_condition();
	}
	else if (y == height-1 && x == width-1) {//правый нижний угол
		return field[x][y - 1].get_condition() + field[x - 1][y].get_condition() + field[x - 1][y - 1].get_condition();
	}
	else if (x == width-1 && y != 0) {//правая граница
		return  field[x - 1][y].get_condition() + field[x - 1][y+1].get_condition() + field[x - 1][y - 1].get_condition() + field[x][y+1].get_condition() + field[x][y - 1].get_condition();
	}
	else {
		return field[x - 1][y].get_condition() + field[x - 1][y - 1].get_condition() + field[x - 1][y + 1].get_condition() + field[x][y - 1].get_condition() + field[x][y + 1].get_condition() + field[x + 1][y - 1].get_condition() + field[x + 1][y + 1].get_condition() + field[x +1][y].get_condition();
	}
	 cout << "Обосрался";
	return 5678;
}
void show_mas(cell(*field)[10], int width, int height) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			 cout << field[j][i].get_condition() << " ";
		}
		 cout <<  endl;
	}
}
void show_mas_mine(cell(*field)[10], int width, int height){
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			 cout << field[j][i].get_around() << " ";
		}
		 cout <<  endl;
	}
}

int main() {
	RenderWindow window;
	window.create(VideoMode::getDesktopMode(), L"Сапер", Style::Default);

	float wigth_win = VideoMode::getDesktopMode().width;
	float height_win = VideoMode::getDesktopMode().height;
	//Фон меню
	RectangleShape background(Vector2f(wigth_win, height_win));
	Texture texture_window;
	//if (!texture_window.loadFromFile("image/Back.jpg")) cout << 2902024203 << endl; return 1;
	background.setTexture(&texture_window);


	setlocale(LC_ALL, "Russian");


	Font font;
	if (!font.loadFromFile("font/Inky-Thin-Pixels_0.ttf")) return 2;
	Text Titul;
	int width = 10;
	int height = 10;
	int numMines = 10;
	int a = 0;

	int coor_x = 5, coor_y = 3;
	cell field[10][10];
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			a =  rand() % 10; if (a != 1) { a = 0; }
			field[j][i].set_condition(a);
		}
	}
	
	show_mas(field, width, height);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			a = min_count(field, j, i, width, height);
			field[j][i].set_around(a);			
		}
	}
	 cout <<  endl;
	show_mas_mine(field, width, height);

}
