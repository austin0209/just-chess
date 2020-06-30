#include <stdlib.h>
#include <assert.h>
#include "board.h"
#include "pieces.h"
#include "consts.h"
#include "assets.h"

static Square* squares = NULL;

void InitBoard(void) {
	assert(squares == NULL);
	squares = (Square*) malloc(sizeof(Square) * NUM_COLS * NUM_ROWS);
	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLS; j++) {
			Square* sq = &squares[i * NUM_COLS + j];
			sq->row = i;
			sq->col = j;
			if ((i + j) % 2 == 1) {
				sq->c = DARKBLUE;
			} else {
				sq->c = LIGHTGRAY;
			}
			sq->attackers = NewHead();
			sq->resident = NULL;
		}
	}

	// Setup pieces
	for (int i = 0; i < NUM_ROWS; i++) {
		Square* sq1 = &squares[NUM_COLS + i];
		Square* sq2 = &squares[(NUM_ROWS - 2) * NUM_COLS + i];
		sq1->resident = NewPiece(PAWN_ID, BLACK_ID);
		sq2->resident = NewPiece(PAWN_ID, WHITE_ID);
	}
}

void DrawBoard(void) {
	assert(squares != NULL);
	for (int i = 0; i < NUM_COLS * NUM_ROWS; i++) {
		float sqX = squares[i].col * SQUARE_SIZE;
		float sqY = squares[i].row * SQUARE_SIZE;
		DrawRectangle(sqX, sqY, SQUARE_SIZE, SQUARE_SIZE, squares[i].c);
		if (squares[i].resident) {
			DrawPiece(squares[i].resident, sqX, sqY);
		}
	}
}

void DestroyBoard(void) {
	for (int i = 0; i < NUM_COLS * NUM_ROWS; i++) {
		free(squares[i].resident);
		DestroyList(squares[i].attackers);
	}
	free(squares);
}
