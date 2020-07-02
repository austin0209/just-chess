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
				sq->c = DARKBROWN;
			} else {
				sq->c = BEIGE;
			}
			sq->resident = NULL;
		}
	}

	// Setup pawns.
	for (int i = 0; i < NUM_ROWS; i++) {
		Square* sq1 = &squares[NUM_COLS + i];
		Square* sq2 = &squares[(NUM_ROWS - 2) * NUM_COLS + i];
		sq1->resident = NewPiece(PAWN_ID, BLACK_ID);
		sq2->resident = NewPiece(PAWN_ID, WHITE_ID);
	}
	// Rooks
	squares[0].resident = NewPiece(ROOK_ID, BLACK_ID);
	squares[7].resident = NewPiece(ROOK_ID, BLACK_ID);
	squares[NUM_COLS * 7].resident = NewPiece(ROOK_ID, WHITE_ID);
	squares[NUM_COLS * 7 + 7].resident = NewPiece(ROOK_ID, WHITE_ID);
	// Knights
	squares[1].resident = NewPiece(KNIGHT_ID, BLACK_ID);
	squares[6].resident = NewPiece(KNIGHT_ID, BLACK_ID);
	squares[NUM_COLS * 7 + 1].resident = NewPiece(KNIGHT_ID, WHITE_ID);
	squares[NUM_COLS * 7 + 6].resident = NewPiece(KNIGHT_ID, WHITE_ID);
	// Bishops
	squares[2].resident = NewPiece(BISHOP_ID, BLACK_ID);
	squares[5].resident = NewPiece(BISHOP_ID, BLACK_ID);
	squares[NUM_COLS * 7 + 2].resident = NewPiece(BISHOP_ID, WHITE_ID);
	squares[NUM_COLS * 7 + 5].resident = NewPiece(BISHOP_ID, WHITE_ID);
	// King and queen
	squares[3].resident = NewPiece(QUEEN_ID, BLACK_ID);
	squares[4].resident = NewPiece(KING_ID, BLACK_ID);
	squares[NUM_COLS * 7 + 3].resident = NewPiece(QUEEN_ID, WHITE_ID);
	squares[NUM_COLS * 7 + 4].resident = NewPiece(KING_ID, WHITE_ID);
	UpdateBoard();
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

void UpdateBoard(void) {
	assert(squares != NULL);
	for (int i = 0; i < NUM_COLS * NUM_ROWS; i++) {
		Square* sq = squares + i;
		Piece* p = sq->resident;
		if (p) {
			Empty(p->attacking);
			int row = i / NUM_COLS;
			int col = i % NUM_COLS;
			switch (p->id) {
				case PAWN_ID: ;
					Square* ahead = NULL;
					if (p->side == WHITE_ID) {
						ahead = &squares[(row - 1) * NUM_COLS + col];
					} else {
						ahead = &squares[(row + 1) * NUM_COLS + col];
					}
					if (!ahead->resident) {
						Push(p->attacking, ahead);
						if (p->state == UNMOVED) {
							Square* ahead2;
							if (p->side == WHITE_ID) {
								ahead2 = &squares[(row - 2) * NUM_COLS + col];
							} else {
								ahead2 = &squares[(row + 2) * NUM_COLS + col];
							}
							if (!ahead2->resident) Push(p->attacking, ahead2);
						}
					}
					break;
			}
		}
	}
}

Square* GetSquareAt(int posX, int posY) {
	int tgtRow = (int) (posY / SQUARE_SIZE);
	int tgtCol = (int) (posX / SQUARE_SIZE);
	Square* tgtSquare = &squares[tgtRow * NUM_COLS + tgtCol];
	return tgtSquare;
}

void DestroyBoard(void) {
	assert(squares != NULL);
	for (int i = 0; i < NUM_COLS * NUM_ROWS; i++) {
		free(squares[i].resident);
	}
	free(squares);
}
