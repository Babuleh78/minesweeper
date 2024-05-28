#include "raylib.h"
#include<thread>
#include <iostream>
#include <string>
#include "raymath.h"
#include "rlgl.h"

using namespace std;
class cell {
public:
	
	cell() {
		around = 0; condition = 0;
		image = LoadImage("image/default.png");
		texture = LoadTextureFromImage(image);
		UnloadImage(image);
		open = false;
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
	Image get_image() {
		return image;
	}
	void set_image(Image _image) {
		image = _image;
		texture = LoadTextureFromImage(image);	
	}
	bool is_open() {
		return open;
	}
	void set_open(bool _e) {
		open = _e;
	}
	Texture2D get_texture() {
		return texture;
	}
	void set_texture(Image _image) {
		image = _image;
		texture = LoadTextureFromImage(_image);
	}

private:
	int condition; //Мина - 1 пусто - 0 Обезврежена = -1 78 - стена?
	int around; //сколько вокруг
	bool open;
	Image image; //Изображение
	Texture2D texture; //Его текстура
	
	
};
#define MAX_TEXTURES 100 // Количество загружаемых текстур

int min_count(cell(*field)[30], int x, int y, int width, int height) {
	int a = 0;
	if (field[x][y].get_condition() == 1) {
		return 0;
	}
	if (x == 0 && y == 0) {//Левый верхний угол
		return field[1][0].get_condition() + field[1][1].get_condition() + field[0][1].get_condition();
	}
	else if (y == 0 && x != width - 1) {//верхняя граница
		return  field[x - 1][0].get_condition() + field[x + 1][0].get_condition() + field[x - 1][1].get_condition() + field[x][1].get_condition() + field[x + 1][1].get_condition();
	}
	else if (y == 0 && x == width - 1) {//правый верхний угол
		return field[x - 1][0].get_condition() + field[x - 1][1].get_condition() + field[x][1].get_condition();
	}
	else if (x == 0 && y != height - 1) {//левая граница
		return  field[0][y + 1].get_condition() + field[0][y - 1].get_condition() + field[1][y - 1].get_condition() + field[1][y + 1].get_condition() + field[1][y].get_condition();
	}
	else if (y == height - 1 && x == 0) {//Левый нижний угол
		return field[0][y - 1].get_condition() + field[1][y].get_condition() + field[1][y - 1].get_condition();
	}
	else if (y == height - 1 && x != width - 1) {//нижняя граница
		return  field[x - 1][y].get_condition() + field[x + 1][y].get_condition() + field[x + 1][y - 1].get_condition() + field[x - 1][y - 1].get_condition() + field[x][y - 1].get_condition();
	}
	else if (y == height - 1 && x == width - 1) {//правый нижний угол
		return field[x][y - 1].get_condition() + field[x - 1][y].get_condition() + field[x - 1][y - 1].get_condition();
	}
	else if (x == width - 1 && y != 0) {//правая граница
		return  field[x - 1][y].get_condition() + field[x - 1][y + 1].get_condition() + field[x - 1][y - 1].get_condition() + field[x][y + 1].get_condition() + field[x][y - 1].get_condition();
	}
	else {
		return field[x - 1][y].get_condition() + field[x - 1][y - 1].get_condition() + field[x - 1][y + 1].get_condition() + field[x][y - 1].get_condition() + field[x][y + 1].get_condition() + field[x + 1][y - 1].get_condition() + field[x + 1][y + 1].get_condition() + field[x + 1][y].get_condition();
	}
	cout << "Обосрался";
	return 5678;
}
void show_mas(cell(*field)[30], int width, int height) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << field[j][i].get_condition() << " ";
		}
		cout << endl;
	}
}
void show_mas_mine(cell(*field)[30], int width, int height) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << field[j][i].get_around() << " ";

		}
		cout << endl;
	}
}
void draw_field(cell(*field)[30], int width, int height, int screenWidth, int screenHeight)  {
	return;	
}
Image image_number_set(int i);
void empty_check(cell(*field)[30], int x, int y, int width, int height) {
	cout << x << " " << y << endl;
	if (x > 0 && x < width - 1 && y>0 && y < height - 1) {
		if(!field[x][y-1].is_open())field[x][y - 1].set_image(image_number_set(field[x][y - 1].get_around())); field[x][y - 1].set_open(true);
		if (!field[x][y + 1].is_open())field[x][y + 1].set_image(image_number_set(field[x][y + 1].get_around())); field[x][y + 1].set_open(true);
		if (!field[x-1][y -1].is_open())field[x-1][y + 1].set_image(image_number_set(field[x-1][y - 1].get_around())); field[x-1][y - 1].set_open(true);
		if (!field[x+1][y - 1].is_open())field[x+1][y - 1].set_image(image_number_set(field[x+1][y - 1].get_around())); field[x+1][y - 1].set_open(true);
		if (!field[x+1][y +1].is_open())field[x+1][y +1].set_image(image_number_set(field[1+x][y +1].get_around())); field[x+1][y +1].set_open(true);
		if (!field[x - 1][y + 1].is_open())field[x -1][y + 1].set_image(image_number_set(field[ x-1][y + 1].get_around())); field[x - 1][y + 1].set_open(true);
		if (!field[x-1][y].is_open())field[x-1][y].set_image(image_number_set(field[x-1][y].get_around())); field[x-1][y].set_open(true);
		if (!field[x +1][y].is_open())field[x + 1][y].set_image(image_number_set(field[x + 1][y].get_around())); field[x + 1][y].set_open(true);
	} else if (x == 0 && y == 0) {//Левый верхний угол
		if (!field[x][y + 1].is_open())field[x][y + 1].set_image(image_number_set(field[x][y + 1].get_around())); field[x][y + 1].set_open(true);
		if (!field[x + 1][y].is_open())field[x + 1][y].set_image(image_number_set(field[x + 1][y].get_around())); field[x + 1][y].set_open(true);
		if (!field[x + 1][y + 1].is_open())field[x + 1][y + 1].set_image(image_number_set(field[1 + x][y + 1].get_around())); field[x + 1][y + 1].set_open(true);
	}
	else if (y == 0 && x != width - 1) {//верхняя граница
		if (!field[x][y + 1].is_open())field[x][y + 1].set_image(image_number_set(field[x][y + 1].get_around())); field[x][y + 1].set_open(true);
		if (!field[x + 1][y].is_open())field[x + 1][y].set_image(image_number_set(field[x + 1][y].get_around())); field[x + 1][y].set_open(true);
		if (!field[x + 1][y + 1].is_open())field[x + 1][y + 1].set_image(image_number_set(field[1 + x][y + 1].get_around())); field[x + 1][y + 1].set_open(true);
		if (!field[x - 1][y].is_open())field[x - 1][y].set_image(image_number_set(field[x - 1][y].get_around())); field[x - 1][y].set_open(true);
		if (!field[x - 1][y +1].is_open())field[x - 1][y + 1].set_image(image_number_set(field[x - 1][y + 1].get_around())); field[x - 1][y + 1].set_open(true);

	}
	else if (y == 0 && x == width - 1) {//правый верхний угол
		if (!field[x - 1][y].is_open())field[x - 1][y].set_image(image_number_set(field[x - 1][y].get_around())); field[x - 1][y].set_open(true);
		if (!field[x - 1][y + 1].is_open())field[x - 1][y + 1].set_image(image_number_set(field[x - 1][y + 1].get_around())); field[x - 1][y + 1].set_open(true);
		if (!field[x][y + 1].is_open())field[x][y + 1].set_image(image_number_set(field[x][y + 1].get_around())); field[x][y + 1].set_open(true);
	}
	else if (x == 0 && y != height - 1) {//левая граница
		if (!field[x][y - 1].is_open())field[x][y - 1].set_image(image_number_set(field[x][y - 1].get_around())); field[x][y - 1].set_open(true);
		if (!field[x + 1][y - 1].is_open())field[x + 1][y - 1].set_image(image_number_set(field[x + 1][y - 1].get_around())); field[x + 1][y - 1].set_open(true);
		if (!field[x][y + 1].is_open())field[x][y + 1].set_image(image_number_set(field[x][y + 1].get_around())); field[x][y + 1].set_open(true);
		if (!field[x + 1][y].is_open())field[x + 1][y].set_image(image_number_set(field[x + 1][y].get_around())); field[x + 1][y].set_open(true);
		if (!field[x + 1][y + 1].is_open())field[x + 1][y + 1].set_image(image_number_set(field[1 + x][y + 1].get_around())); field[x + 1][y + 1].set_open(true);
	}
	else if (y == height - 1 && x == 0) {//Левый нижний угол
		if (!field[x][y - 1].is_open())field[x][y - 1].set_image(image_number_set(field[x][y - 1].get_around())); field[x][y - 1].set_open(true);
		if (!field[x + 1][y -1].is_open())field[x + 1][y - 1].set_image(image_number_set(field[x + 1][y - 1].get_around())); field[x + 1][y - 1].set_open(true);
		if (!field[x+1][y].is_open())field[x][y].set_image(image_number_set(field[x][y].get_around())); field[x][y].set_open(true);
	}
	else if (y == height - 1 && x != width - 1) {//нижняя граница
		if (!field[x][y - 1].is_open())field[x][y - 1].set_image(image_number_set(field[x][y - 1].get_around())); field[x][y - 1].set_open(true);
		if (!field[x + 1][y].is_open())field[x][y].set_image(image_number_set(field[x][y].get_around())); field[x][y].set_open(true);
		if (!field[x - 1][y].is_open())field[x - 1][y].set_image(image_number_set(field[x - 1][y].get_around())); field[x - 1][y].set_open(true);
		if (!field[x + 1][y - 1].is_open())field[x + 1][y - 1].set_image(image_number_set(field[x + 1][y - 1].get_around())); field[x + 1][y - 1].set_open(true);
		if (!field[x - 1][y - 1].is_open())field[x - 1][y + 1].set_image(image_number_set(field[x - 1][y + 1].get_around())); field[x - 1][y - 1].set_open(true);
	}
	else if (y == height - 1 && x == width - 1) {//правый нижний угол
		if (!field[x - 1][y].is_open())field[x - 1][y].set_image(image_number_set(field[x - 1][y].get_around())); field[x - 1][y].set_open(true);
		if (!field[x - 1][y - 1].is_open())field[x - 1][y + 1].set_image(image_number_set(field[x - 1][y + 1].get_around())); field[x - 1][y - 1].set_open(true);
		if (!field[x][y - 1].is_open())field[x][y - 1].set_image(image_number_set(field[x][y - 1].get_around())); field[x][y - 1].set_open(true);
	}
	else if (x == width - 1 && y != 0) {//правая граница
		if (!field[x - 1][y - 1].is_open())field[x - 1][y + 1].set_image(image_number_set(field[x - 1][y + 1].get_around())); field[x - 1][y - 1].set_open(true);
		if (!field[x - 1][y].is_open())field[x - 1][y].set_image(image_number_set(field[x - 1][y].get_around())); field[x - 1][y].set_open(true);
		if (!field[x - 1][y + 1].is_open())field[x - 1][y + 1].set_image(image_number_set(field[x - 1][y + 1].get_around())); field[x - 1][y + 1].set_open(true);
		if (!field[x][y + 1].is_open())field[x][y + 1].set_image(image_number_set(field[x][y + 1].get_around())); field[x][y + 1].set_open(true);
		if (!field[x][y - 1].is_open())field[x][y - 1].set_image(image_number_set(field[x][y - 1].get_around())); field[x][y - 1].set_open(true);


	}





	if (field[x][y - 1].get_around() == 0)empty_check(field, x, y - 1, width, height);
	if (field[x][y + 1].get_around() == 0)empty_check(field, x, y + 1, width, height);
	if (field[x-1][y + 1].get_around() == 0)empty_check(field, x-1, y + 1, width, height);
	if (field[x+1][y - 1].get_around() == 0)empty_check(field, x+1, y - 1, width, height);
	if (field[x+1][y + 1].get_around() == 0)empty_check(field, x+1, y + 1, width, height);
	if (field[x-1][y +1].get_around() == 0)empty_check(field, x-1, y + 1, width, height);
	if (field[x-1][y].get_around() == 0)empty_check(field, x-1, y, width, height);
	if (field[x+1][y].get_around() == 0)empty_check(field, x+1, y, width, height);


	
	
}
Image image_number_set(int i) {
	Image open_image = LoadImage("Image/empty.png"); ImageResize(&open_image, 50, 50);
	Image image1 = LoadImage("Image/1.png"); ImageResize(&image1, 50, 50);
	Image image2 = LoadImage("Image/2.png");ImageResize(&image2, 50, 50);
	Image image3 = LoadImage("Image/3.png");ImageResize(&image3, 50, 50);
	Image image4 = LoadImage("Image/4.png");ImageResize(&image4, 50, 50);
	Image image5 = LoadImage("Image/5.png");ImageResize(&image5, 50, 50);
	Image image6 = LoadImage("Image/6.png");ImageResize(&image6, 50, 50);
	Image image7 = LoadImage("Image/7.png");ImageResize(&image7, 50, 50);
	switch (i) {
	case 0:
		return open_image; break;
	case 1:
		return image1; break;
	case 2:
		return image2;break;
	case 3:
		return image3;break;
	case 4:
		return image4;break;
	case 5:
		return image5;break;
	case 6:
		return image6;break;
	case 7:
		return image7;break;

	}
}

int main() {
	SetTraceLogLevel(LOG_NONE);

	setlocale(LC_ALL, "Russian");
	const int screenWidth = 800;
	const int screenHeight = 450;
	int width = 30;
	int height = 30;
	int numMines = 30;
	int a = 0;
	InitWindow(screenWidth, screenHeight, "Sapper");;
	Image default_image = LoadImage("Image/default.png");
	Image open_image = LoadImage("Image/empty.png"); ImageResize(&open_image, 50, 50);
	Image mine = LoadImage("Image/mine.png"); ImageResize(&mine, 50, 50);
	Image image1 = LoadImage("Image/1.png"); ImageResize(&image1, 50, 50);
	Image image2 = LoadImage("Image/2.png");ImageResize(&image2, 50, 50);
	Image image3 = LoadImage("Image/3.png");ImageResize(&image3, 50, 50);
	Image image4 = LoadImage("Image/4.png");ImageResize(&image4, 50, 50);
	Image image5 = LoadImage("Image/5.png");ImageResize(&image5, 50, 50);
	Image image6 = LoadImage("Image/6.png");ImageResize(&image6, 50, 50);
	Image image7 = LoadImage("Image/7.png");ImageResize(&image7, 50, 50);
	ImageResize(&default_image, 50, 50);
	ImageResize(&open_image, 50, 50);
	int coor_x = 5, coor_y = 3;
	cell field[30][30];

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			a = rand() % 10; if (a != 1) { a = 0; }
			field[j][i].set_condition(a);
			
		}
	}
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			a = min_count(field, j, i, width, height);
			field[j][i].set_around(a);
			
		}
	}
	
	Camera2D camera = { 0 };

	int x_perem = 0, y_perem = 0;
	int pointX = 0, pointY = 0;//Координаты левой верхней ячейки
	float x_cell = 0, y_cell = 0, bliz_coef = 1;
	int x_int_cell = 0, y_int_cell = 0;
	camera.zoom = 1.0f;
	int zoomMode = 0;   // 0-Mouse Wheel, 1-Mouse Move
	UnloadImage(default_image);
	SetTargetFPS(60);
	bool start = true;
	while (!WindowShouldClose())        
	{
		Vector2 Cursor = GetMousePosition();

		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			Vector2 delta = GetMouseDelta();
			delta = Vector2Scale(delta, -1.0f / camera.zoom);
			
			camera.target = Vector2Add(camera.target, delta);
			
			pointX += delta.x; pointY += delta.y;
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			
		
			cout << Cursor.x+pointX << " " << Cursor.y+pointY << endl;
			x_cell = (Cursor.x + pointX) * bliz_coef; x_cell /= 50;
			y_cell = (Cursor.y + pointY) * bliz_coef; y_cell /= 50;
			
			x_int_cell = (int)x_cell; y_int_cell = (int)y_cell;
			if (x_int_cell >= 0 && y_int_cell >= 0) {
				int j = x_int_cell, i = y_int_cell;
				if (field[j][i].get_condition() == 1) {
					field[j][i].set_texture(mine);
				}
				else {
					a = field[j][i].get_around();
					switch (a) {
					case 0:
						field[j][i].set_texture(open_image);
						empty_check(field, j, i, width, height);
						break;
					case 1:
						field[j][i].set_texture(image1);  break;
					case 2:
						field[j][i].set_texture(image2);break;
					case 3:
						field[j][i].set_texture(image3);break;
					case 4:
						field[j][i].set_texture(image4);break;
					case 5:
						field[j][i].set_texture(image5);break;
					case 6:
						field[j][i].set_texture(image6);break;
					case 7:
						field[j][i].set_texture(image7);break;

					}
					if (a != 0) {
						field[j][i].set_open(true);
					}
				}
					
			}
			
		}
		
		
		BeginDrawing();

		
		
		ClearBackground(RAYWHITE);
		BeginMode2D(camera);
		for (int i = 0;i < 30; i++) {
			for (int j = 0; j < 30; j++) {
				DrawTexture(field[j][i].get_texture(), j * 50, i*50, WHITE);	
			}
		}
		EndDrawing();
		//----------------------------------------------------------------------------------
	}


	CloseWindow();        // Close window and OpenGL context
	
	return 0;
}
