#ifndef BOARD_H
#define BOARD_H

typedef struct piece Piece;

typedef struct square {
	int x;
	int y;
	Piece** attackers;
	Piece* resident;
} Square;

int DrawBoard(void);

#endif
