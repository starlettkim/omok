#include <stdio.h>
#define BOARD_SIZE 19

const int BLACK = 1;
const int WHITE = 2;
int board[BOARD_SIZE][BOARD_SIZE] = { 1, 2 };

void printBoard() {
	int i, j;
	for (i = 0; i < BOARD_SIZE; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j] == BLACK) {
				printf("¡Ü");
			} else if (board[i][j] == WHITE) {
				printf("¡Û");
			} else {
				if (i == 0) {
					if (j == 0) printf("¦£");
					else if (j == BOARD_SIZE - 1) printf("¦¤");
					else printf("¦¨");
				} else if (i == BOARD_SIZE - 1) {
					if (j == 0) printf("¦¦");
					else if (j == BOARD_SIZE - 1) printf("¦¥");
					else printf("¦ª");
				} else {
					if (j == 0) printf("¦§");
					else if (j == BOARD_SIZE - 1) printf("¦©");
					else printf("¦«");
				}
			}
		}
		printf("\n");
	}
}

void updateBoard(int row, int col, int turn) {
	board[row][col] = turn;
}

int main() {
	printBoard();
	return 0;
}