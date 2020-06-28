#include "board.h"
#include "raylib.h"
#include "consts.h"

int DrawBoard(void) {
	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLS; j++) {
			int x = j * SQUARE_SIZE;
			int y = i * SQUARE_SIZE;
			Color c;
			if ((i + j) % 2 == 1) {
				c = DARKBLUE;
			} else {
				c = LIGHTGRAY;
			}
			DrawRectangle(x, y, SQUARE_SIZE, SQUARE_SIZE, c);
		}
	}
	return 0;
}
