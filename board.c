#include <stdlib.h>
#include "board.h"
#include "raylib.h"
#include "consts.h"

static Square* squares;

int InitBoard(void) {
	squares = (Square*) malloc(sizeof(Square) * NUM_COLS * NUM_ROWS);
	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLS; j++) {
			Square* sq = &squares[i * NUM_ROWS + j];
			sq->x = i * SQUARE_SIZE;
			sq->y = j * SQUARE_SIZE;
			sq->attackers = NewHead();
			sq->resident = NULL;
		}
	}
	return 0;
}

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
