#include <stdlib.h>
#include <assert.h>
#include "board.h"
#include "pieces.h"
#include "consts.h"
#include "assets.h"

static Square* squares = NULL;
static void UpdatePawn(Piece*, int, int);
static void UpdateKnight(Piece*, int, int);

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
				case PAWN_ID:
					UpdatePawn(p, row, col);
					break;
				case KNIGHT_ID:
					UpdateKnight(p, row, col);
					break;
			}
		}
	}
}

static void UpdatePawn(Piece* p, int row, int col) {
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
	Square* left;
	Square* right;
	if (col > 0) left = ahead - 1;
	if (col < 7) right = ahead + 1;
	if (p->side == BLACK_ID) {
		Square* temp = left;
		left = right;
		right = temp;
	}
	if (left && left->resident) Push(p->attacking, left);
	if (right && right->resident) Push(p->attacking, right);
}

static void UpdateKnight(Piece* p, int row, int col) {
	if (row > 1) {
		if (col > 0) {
			// left availiable
			Square* sq = &squares[(row - 2) * NUM_COLS + col - 1];
			Push(p->attacking, sq);
		}
		if (col < 7) {
			// right availiable
			Square* sq = &squares[(row - 2) * NUM_COLS + col + 1];
			Push(p->attacking, sq);
		}
	}
	if (row < 6) {
		if (col > 0) {
			// left availiable
			Square* sq = &squares[(row + 2) * NUM_COLS + col - 1];
			Push(p->attacking, sq);
		}
		if (col < 7) {
			// right availiable
			Square* sq = &squares[(row + 2) * NUM_COLS + col + 1];
			Push(p->attacking, sq);
		}
	}
	if (col > 1) {
		if (row > 0) {
			// top availiable
			Square* sq = &squares[(row - 1) * NUM_COLS + col - 2];
			Push(p->attacking, sq);
		}
		if (row < 7) {
			// bot availiable
			Square* sq = &squares[(row + 1) * NUM_COLS + col - 2];
			Push(p->attacking, sq);
		}
	}
	if (col < 6) {
		if (row > 0) {
			// top availiable
			Square* sq = &squares[(row - 1) * NUM_COLS + col + 2];
			Push(p->attacking, sq);
		}
		if (row < 7) {
			// bot availiable
			Square* sq = &squares[(row + 1) * NUM_COLS + col + 2];
			Push(p->attacking, sq);
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
		DestroyPiece(squares[i].resident);
	}
	free(squares);
}
