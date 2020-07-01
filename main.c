#include <stddef.h>
#include "raylib.h"
#include "pieces.h"
#include "board.h"
#include "assets.h"
#include "consts.h"

static Piece* floatingPiece;
static Square* originalSquare;

void UpdateInput(void) {
	Square* sq = GetSquareAt(GetMouseX(), GetMouseY());
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		if (sq->resident && !floatingPiece) {
			floatingPiece = sq->resident;
			originalSquare = sq;
			sq->resident = NULL;
		}
	} else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
		if (originalSquare) {
			if (sq->resident && sq->resident->side == floatingPiece->side) {
				originalSquare->resident = floatingPiece;
			} else {
				sq->resident = floatingPiece;
			}
			originalSquare = NULL;
		}
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
