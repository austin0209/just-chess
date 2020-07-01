#include <stddef.h>
#include "raylib.h"
#include "pieces.h"
#include "board.h"
#include "assets.h"
#include "consts.h"

static Piece* floatingPiece;

void UpdateInput(void) {
	Square* sq = GetSquareAt(GetMouseX(), GetMouseY());
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		if (sq->resident && !floatingPiece) {
			floatingPiece = sq->resident;
		}
	} else {
		floatingPiece = NULL;
	}
}

int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = SQUARE_SIZE * NUM_COLS;
	const int screenHeight = SQUARE_SIZE * NUM_ROWS;

	InitWindow(screenWidth, screenHeight, "The Game of Chess");
	LoadAssets();
	InitBoard();

	SetTargetFPS(30);
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())	// Detect window close button or ESC key
	{
		UpdateInput();
		BeginDrawing();
			ClearBackground(BLACK);
			DrawBoard();
			if (floatingPiece) {
				DrawPieceCenter(floatingPiece, GetMouseX(), GetMouseY());
			}
		EndDrawing();
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();		  // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
