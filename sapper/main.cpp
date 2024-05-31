#include "raylib.h"
#include<thread>
#include <iostream>
#include <string>
#include "raymath.h"
#include "rlgl.h"
#include <ctime>
#pragma warning(disable : 4996)
using namespace std; //Сиай окутал потолок
class cell {
public:
	
	cell() {
		around = 0; condition = 0;
		default_image = LoadImage("image/default.png");
		default_texture = LoadTextureFromImage(default_image);
		UnloadImage(default_image);
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
		if (open) {
			return texture;
		}
		else {
			return default_texture;
		}
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
	Image default_image;
	Texture2D texture; //Его текстура
	Texture2D default_texture;
	
	
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
void openEmptyCells(cell(* grid)[30], int x, int y, int width, int height) {
	if (x < 0 || x >= width || y < 0 || y >= height || grid[x][y].is_open() || grid[x][y].get_condition() == 1)
		return;

	grid[x][y].set_open(true);
	
	if (grid[x][y].get_around() == 0) {
		openEmptyCells(grid, x-1, y, width, height);
		openEmptyCells(grid, x+1, y, width, height);
		openEmptyCells(grid, x, y-1, width, height);
		openEmptyCells(grid, x, y+1, width, height);
		openEmptyCells(grid, x - 1, y-1, width, height);
		openEmptyCells(grid, x - 1, y+1, width, height);
		openEmptyCells(grid, x + 1, y+1, width, height);
		openEmptyCells(grid, x + 1, y-1, width, height);
	}
	
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
void around_check(cell(*grid)[30], int x, int y, int width, int height, int &count, bool flag) {
	if (x < 0 || x >= width || y < 0 || y >= height) { return; }

	count += (grid[x][y].get_condition() == -1 ? 1 : 0);
	
	if (flag) {
		if (grid[x - 1][y].get_condition() == -1) around_check(grid, x - 1, y, width, height, count, false);
		if (grid[x + 1][y].get_condition() == -1) around_check(grid, x + 1, y, width, height, count, false);
		if (grid[x][y - 1].get_condition() == -1) around_check(grid, x, y - 1, width, height, count, false);
		if (grid[x][y + 1].get_condition() == -1) around_check(grid, x, y + 1, width, height, count, false);
		if (grid[x - 1][y - 1].get_condition() == -1) around_check(grid, x - 1, y - 1, width, height, count, false);
		if (grid[x - 1][y + 1].get_condition() == -1) around_check(grid, x - 1, y + 1, width, height, count, false);
		if (grid[x + 1][y + 1].get_condition() == -1) around_check(grid, x + 1, y + 1, width, height, count, false);
		if (grid[x + 1][y - 1].get_condition() == -1) around_check(grid, x + 1, y - 1, width, height, count, false);
	}
	

}
void open_around(cell(*grid)[30], int x, int y, int width, int height, bool flag, bool& alive) {
	if (x < 0 || x >= width || y < 0 || y >= height) { return; }
	
	if (grid[x][y].get_condition() == 1) { alive = false; cout << "bom" << endl; grid[x][y].set_open(true); }
	if (flag) {
		open_around(grid, x - 1, y, width, height, false, alive);
		open_around(grid, x - 1, y-1, width, height, false, alive);
		open_around(grid, x - 1, y+1, width, height, false, alive);
		open_around(grid, x + 1, y, width, height, false, alive);
		open_around(grid, x + 1, y-1, width, height, false, alive);
		open_around(grid, x + 1, y+1, width, height, false, alive);
		open_around(grid, x, y-1, width, height, false, alive);
		open_around(grid, x, y+1, width, height, false, alive);
	}
	else {	
	
		if (grid[x][y].get_around() == 0 && grid[x][y].get_condition()!=1) {
			openEmptyCells(grid, x, y, width, height);
		}
		else {
			grid[x][y].set_open(true);
		}
	}

}
int main() {
	srand(time(0));
	SetTraceLogLevel(LOG_NONE);
	bool first_klick = true, alive = true;
	int start_x, start_y;
	setlocale(LC_ALL, "Russian");
	const int screenWidth = 800;
	const int screenHeight = 450;
	int width = 30;
	int height = 30;
	int numMines = 0;
	int a = 0;
	InitWindow(screenWidth, screenHeight, "Sapper");;
	Image default_image = LoadImage("Image/default.png");
	Image open_image = LoadImage("Image/empty.png"); ImageResize(&open_image, 50, 50);
	Image mine = LoadImage("Image/mine.png"); ImageResize(&mine, 50, 50);
	Image flag = LoadImage("Image/flag.png"); ImageResize(&flag, 50, 50);
	Image image1 = LoadImage("Image/1.png"); ImageResize(&image1, 50, 50);
	Image image2 = LoadImage("Image/2.png");ImageResize(&image2, 50, 50);
	Image image3 = LoadImage("Image/3.png");ImageResize(&image3, 50, 50);
	Image image4 = LoadImage("Image/4.png");ImageResize(&image4, 50, 50);
	Image image5 = LoadImage("Image/5.png");ImageResize(&image5, 50, 50);
	Image image6 = LoadImage("Image/6.png");ImageResize(&image6, 50, 50);
	Image image7 = LoadImage("Image/7.png");ImageResize(&image7, 50, 50);
	cell field[30][30];

	Rectangle rec{ 300, 200, 200, 50 };
	
	Camera2D camera = { 0 };
	char bombs[50]; strcpy(bombs, "Bombs count"); 
	int pointX = 0, pointY = 0;//Координаты левой верхней ячейки
	float x_cell = 0, y_cell = 0;
	int x_int_cell = 0, y_int_cell = 0;
	camera.zoom = 1.0f;
	int zoomMode = 0;   // 0-Mouse Wheel, 1-Mouse Move
	
	SetTargetFPS(60);
	bool start = true;
	while (!WindowShouldClose())        
	{
		if (first_klick) {
			alive = true;
		}
		Vector2 Cursor = GetMousePosition();
		if (!alive) {
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				
				if ((Cursor.x >= screenWidth / 2 - 55) && (Cursor.x <= screenWidth / 2 +155) && (Cursor.y >=   screenHeight / 2) && (Cursor.y <=  screenHeight / 2 + 50)) {
					
					numMines = 0;
					for (int i = 0; i < height; i++) {
						for (int j = 0; j < width; j++) {
							field[i][j].set_open(false);
						}
					}
					
					first_klick = true;
				}
			}
			
		}
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			Vector2 delta = GetMouseDelta();
			delta = Vector2Scale(delta, -1.0f / camera.zoom);
			
			camera.target = Vector2Add(camera.target, delta);
			
			pointX += delta.x; pointY += delta.y;
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && alive) {
			if (!first_klick) {
				
				x_cell = (Cursor.x + pointX) * bliz_coef; x_cell /= 50;
				y_cell = (Cursor.y + pointY) * bliz_coef; y_cell /= 50;

				x_int_cell = (int)x_cell; y_int_cell = (int)y_cell;
				if (x_cell >= 0 && y_cell >= 0) {
					int j = x_int_cell, i = y_int_cell;
					if (field[j][i].get_condition() != -1) {
						if (field[j][i].get_condition() == 1) {
							field[j][i].set_texture(mine);
							field[j][i].set_open(true);
							alive = false;
						}
						else {
							a = field[j][i].get_around();
							if (a != 0)field[j][i].set_open(true);
							switch (a) {
							case 0:
								field[j][i].set_texture(open_image);
								openEmptyCells(field, j, i, width, height);
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
			}
			else {
				x_cell = (Cursor.x + pointX); x_cell /= 50;
				y_cell = (Cursor.y + pointY); y_cell /= 50;
				if (y_cell >= 0 && x_cell >= 0) {
					start_x = (int)x_cell; start_y = (int)y_cell;
					for (int i = 0; i < height; i++) {
						for (int j = 0; j < width; j++) {
							if (start_x - 1 <= j && j <= start_x + 1 && start_y - 1 <= i && i <= start_y + 1) {
								field[j][i].set_condition(0);
							}
							else {
								a = rand() % 6; if (a != 1) { a = 0; }
								field[j][i].set_condition(a);
								if (a == 1) {
									numMines += 1;
								}

							}
						}
					}


					for (int i = 0; i < height; i++) {
						for (int j = 0; j < width; j++) {
							a = min_count(field, j, i, width, height);
							field[j][i].set_around(a);
							switch (a) {
							case 0:
								if (field[j][i].get_condition() != 1) {
									field[j][i].set_image(open_image);
								}
								else {
									field[j][i].set_image(mine);

								}
								break;

							case 1:
								field[j][i].set_image(image1); break;
							case 2:
								field[j][i].set_image(image2); break;
							case 3:
								field[j][i].set_image(image3); break;
							case 4:
								field[j][i].set_image(image4); break;
							case 5:
								field[j][i].set_image(image5); break;
							case 6:
								field[j][i].set_image(image6); break;
							case 7:
								field[j][i].set_image(image7); break;

							}

						}
					}
					field[start_x][start_y].set_around(0); field[start_x][start_y].set_image(open_image);
					openEmptyCells(field, start_x, start_y, width, height);
					first_klick = false;
				}
			}
			
		}
		if (IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON) && alive && !first_klick) {
			x_cell = (Cursor.x + pointX); x_cell /= 50;
			y_cell = (Cursor.y + pointY); y_cell /= 50;
			
			x_int_cell = (int)x_cell; y_int_cell = (int)y_cell;
			if (x_int_cell >= 0 && y_int_cell >= 0) {
				int j = x_int_cell, i = y_int_cell;
					if (field[j][i].get_condition() != -1 && !field[j][i].is_open()) { // обезвреживание
						field[j][i].set_texture(flag);
						field[j][i].set_condition(-1);
						field[j][i].set_open(true);
						numMines -= 1;
						
					} 
					else if (field[j][i].get_condition() == -1){ //отмена обезвреда
						
						
						if (field[j][i].get_around() != 0) {
							field[j][i].set_condition(0);
							field[j][i].set_texture(image_number_set(field[j][i].get_around()));
						}
						else {
							field[j][i].set_condition(1);
							field[j][i].set_texture(mine);
						}
						field[j][i].set_open(false);
						numMines += 1;
						
					}
					else if (field[j][i].get_condition() == 0) {
						a = field[j][i].get_around();
						int count = 0; around_check(field, j, i, width, height, count, true);
						if (count == a) {
							open_around(field, j, i, width, height, true, alive);
						}
						
					}
				
			}

		}
		
		
			
			BeginDrawing();
			ClearBackground(RAYWHITE);
			BeginMode2D(camera);
			
			if (numMines >= 100) {
				string s = to_string(numMines);
				
				bombs[11] = s[0]; bombs[12] = s[1]; bombs[13] = s[2]; bombs[14] = '\0';
			}
			else if (numMines >= 10) {
				string s = to_string(numMines);
				
				bombs[11] = s[0]; bombs[12] = s[1]; bombs[13] = '\0';
			}
			else {
				bombs[11] = numMines + '0'; bombs[12] = '\0';
			}
			for (int i = 0;i < 30; i++) {
				for (int j = 0; j < 30; j++) {
					DrawTexture(field[j][i].get_texture(), j * 50, i * 50, WHITE);
					
				} 
			}
			
			if (!alive) {
				DrawText(bombs, pointX, pointY, 50, RED);
				rec.x = pointX + screenWidth / 2 - 55; rec.y = pointY + screenHeight / 2;
				DrawRectangleRec(rec, GREEN);
				DrawText("AGAIN?", pointX+ screenWidth / 2 - 50, pointY + screenHeight / 2,  50, BLACK);
			}
			else {
				DrawText(bombs, pointX, pointY, 50, RED);
			}
			EndDrawing();
		
		
		//----------------------------------------------------------------------------------
	}


	CloseWindow();        // Close window and OpenGL context
	
	return 0;
}
