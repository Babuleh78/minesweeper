#include "raylib.h"
#include<thread>
#include <iostream>
#include <cstring>
#include "raymath.h"
#include "rlgl.h"
using namespace std;
class cell {
public:

	cell() {
		around = 0; condition = 0;
		image = LoadImage("image/default.png");
		
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

private:
	int condition; //ћина - 1 пусто - 0 ќбезврежена = -1 78 - стена?
	int around; //сколько вокруг
	Image image;

};


int min_count(cell(*field)[10], int x, int y, int width, int height) {
	int a = 0;
	if (field[x][y].get_condition() == 1) {
		return 0;
	}
	if (x == 0 && y == 0) {//Ћевый верхний угол
		return field[1][0].get_condition() + field[1][1].get_condition() + field[0][1].get_condition();
	}
	else if (y == 0 && x != width - 1) {//верхн€€ граница
		return  field[x - 1][0].get_condition() + field[x + 1][0].get_condition() + field[x - 1][1].get_condition() + field[x][1].get_condition() + field[x + 1][1].get_condition();
	}
	else if (y == 0 && x == width - 1) {//правый верхний угол
		return field[x - 1][0].get_condition() + field[x - 1][1].get_condition() + field[x][1].get_condition();
	}
	else if (x == 0 && y != height - 1) {//лева€ граница
		return  field[0][y + 1].get_condition() + field[0][y - 1].get_condition() + field[1][y - 1].get_condition() + field[1][y + 1].get_condition() + field[1][y].get_condition();
	}
	else if (y == height - 1 && x == 0) {//Ћевый нижний угол
		return field[0][y - 1].get_condition() + field[1][y].get_condition() + field[1][y - 1].get_condition();
	}
	else if (y == height - 1 && x != width - 1) {//нижн€€ граница
		return  field[x - 1][y].get_condition() + field[x + 1][y].get_condition() + field[x + 1][y - 1].get_condition() + field[x - 1][y - 1].get_condition() + field[x][y - 1].get_condition();
	}
	else if (y == height - 1 && x == width - 1) {//правый нижний угол
		return field[x][y - 1].get_condition() + field[x - 1][y].get_condition() + field[x - 1][y - 1].get_condition();
	}
	else if (x == width - 1 && y != 0) {//права€ граница
		return  field[x - 1][y].get_condition() + field[x - 1][y + 1].get_condition() + field[x - 1][y - 1].get_condition() + field[x][y + 1].get_condition() + field[x][y - 1].get_condition();
	}
	else {
		return field[x - 1][y].get_condition() + field[x - 1][y - 1].get_condition() + field[x - 1][y + 1].get_condition() + field[x][y - 1].get_condition() + field[x][y + 1].get_condition() + field[x + 1][y - 1].get_condition() + field[x + 1][y + 1].get_condition() + field[x + 1][y].get_condition();
	}
	cout << "ќбосралс€";
	return 5678;
}
int main(void)
{
	int width = 10;
	int height = 10;
	int numMines = 10;
	int a = 0;
    const int screenWidth = 800;
    const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Sapper");;

	Image default_image = LoadImage("Image/default.png");
	ImageResize(&default_image, 100, 100);
	Texture2D texture = LoadTextureFromImage(default_image);
	
    UnloadImage(default_image);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM
	int coor_x = 5, coor_y = 3;
	cell field[10][10];
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
	camera.zoom = 1.0f;
	int zoomMode = 0;   // 0-Mouse Wheel, 1-Mouse Move
	
	SetTargetFPS(60);
	bool start = true;
	while (!WindowShouldClose())        // Detect window close button or ESC key
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			Vector2 delta = GetMouseDelta();
			delta = Vector2Scale(delta, -1.0f / camera.zoom);
			camera.target = Vector2Add(camera.target, delta);
		}

		if (zoomMode == 0)
		{
			// Zoom based on mouse wheel
			float wheel = GetMouseWheelMove();
			if (wheel != 0)
			{
				// Get the world point that is under the mouse
				Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

				// Set the offset to where the mouse is
				camera.offset = GetMousePosition();

				// Set the target to match, so that the camera maps the world space point 
				// under the cursor to the screen space point under the cursor at any zoom
				camera.target = mouseWorldPos;

				// Zoom increment
				float scaleFactor = 1.0f + (0.25f * fabsf(wheel));
				if (wheel < 0) scaleFactor = 1.0f / scaleFactor;
				camera.zoom = Clamp(camera.zoom * scaleFactor, 0.125f, 64.0f);
			}
		}
		
		BeginDrawing();

		
		
		ClearBackground(RAYWHITE);
		BeginMode2D(camera);

		for (int i = 0;i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				
				DrawTexture(texture, j * 110, i*110, GREEN);
			}
		}
		EndDrawing();
		
	}


	CloseWindow();        // Close window and OpenGL context
   

    return 0;
}