#ifndef BOARD_H
#define BOARD_H

typedef struct piece Piece;

typedef struct square {
	int x; // Actual screen x 
	int y; // Actual screen y
	Piece** attackers;
	Piece* resident;
} Square;

int DrawBoard(void);

#endif
