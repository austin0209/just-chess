#include "raylib.h"
#include "assets.h"
#include "consts.h"

void LoadAssets() {
	Image img = LoadImage("assets/pieces.png");
	ImageResizeNN(&img, SQUARE_SIZE * 6, SQUARE_SIZE * 2);
	spriteSheet = LoadTextureFromImage(img);
}

