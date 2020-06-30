#include "raylib.h"
#include "pieces.h"
#include "board.h"
#include "assets.h"
#include "consts.h"

int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = SQUARE_SIZE * NUM_COLS;
	const int screenHeight = SQUARE_SIZE * NUM_ROWS;

	InitWindow(screenWidth, screenHeight, "The Game of Chess");
	LoadAssets();
	InitBoard();

	SetTargetFPS(60);				// Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())	// Detect window close button or ESC key
	{
		BeginDrawing();

			ClearBackground(BLACK);
			DrawBoard();

		EndDrawing();
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();		  // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
