#include <stdlib.h>
#include <assert.h>
#include "board.h"
#include "consts.h"

static Square* squares = NULL;

void InitBoard(void) {
	assert(squares == NULL);
	squares = (Square*) malloc(sizeof(Square) * NUM_COLS * NUM_ROWS);
	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLS; j++) {
			Square* sq = &squares[i * NUM_ROWS + j];
			sq->x = i * SQUARE_SIZE;
			sq->y = j * SQUARE_SIZE;
			if ((i + j) % 2 == 1) {
				sq->c = DARKBLUE;
			} else {
				sq->c = LIGHTGRAY;
			}
			sq->attackers = NewHead();
			sq->resident = NULL;
		}
	}
}

void DrawBoard(void) {
	assert(squares != NULL);
	for (int i = 0; i < NUM_COLS * NUM_ROWS; i++) {
		DrawRectangle(squares[i].x, squares[i].y, SQUARE_SIZE, SQUARE_SIZE, squares[i].c);
	}
}

void DestroyBoard(void) {
	for (int i = 0; i < NUM_COLS * NUM_ROWS; i++) {
		free(squares[i].resident);
		DestroyList(squares[i].attackers);
	}
	free(squares);
}
