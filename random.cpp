#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

#define BOARD_SIZE  19
#define ME          1
#define OPPONENT    2

using namespace std;

int board[BOARD_SIZE + 1][BOARD_SIZE + 1];
typedef struct { int row, col; } Position;

/*
 * 인자로 들어온 (row, col) 위치에 돌을 놓았을 때 얻을 수 있는 기대값을 대충
 * 계산해보고 [0, 100] 사이의 정수로 리턴하는 함수.
 */
int evaluationFunction(int row, int col) {
    // N개의 돌이 연속되었을 경우에 대한 가중치값.
    // 심심할때 조정해보면서 놀도록 하자! ㅎㅅㅎ
    const int WEIGHT_2 = 20;
    const int WEIGHT_3 = 50;
    const int WEIGHT_4 = 80;
    const int WEIGHT_5 = 100;

    // 네 가지 방향.
    int dr[] = { 0, 1, 1, 1 };
    int dc[] = { 1, 1, 0, -1};

    // 
    vector<int> score;

    for (int i = 0; i < 4; i++) {
        // 직선 방향으로 5개의 돌 중 본인 돌의 개수.
        int cnt = 1;
        int opponent_cnt = 0;
        for (int j = 1; j < 5; j++) {
            int chk_row = row + dr[i] * j;
            int chk_col = col + dc[i] * j;
            if (chk_row <= 0 || chk_row > BOARD_SIZE || 
                chk_col <= 0 || chk_col > BOARD_SIZE ||
                board[row + dr[i] * j][col + dc[i] * j] == OPPONENT) {
                ++opponent_cnt;
            } else if (board[row + dr[i] * j][col + dc[i] * j] == ME) {
                ++cnt;
            }
        }
        if (!opponent_exists) {
            score.push_back(cnt);
        }

        for (j = 4; j > 0; j--) {
            int old_row = row + dr[i] * j;
            int old_col = col + dc[i] * j;
            int new_row = row + dr[i] * (j - 5);
            int new_col = col + dc[i] * (j - 5);
            // TODO: 범위밖 벗어났을때 예외처리(new_row/col)
            opponent_cnt -= (board[old_row][old_col] == OPPONENT);
            opponent_cnt += (board[new_row][new_col] == OPPONENT);
            cnt -= (board[old_row][old_col] == ME);
            cnt += (board[new_row][new_col] == ME);
            // TODO
        }
        
    }
}

int main() {
    while (true) {
        int row, col;
        scanf("%d %d", &row, &col);
        board[row][col] = OPPONENT;

        Position max_pos;
        int max_value = 0;
        for (int i = 1; i <= BOARD_SIZE; i++) {
            for (int j = 1; j <= BOARD_SIZE; j++) {
                if (!board[i][j]) {
                    // TODO: min-max tree 구성
                    int ret = evaluationFunction(i, j);
                    if (max_value < ret) {
                        max_value = ret;
                        max_pos = ({i, j});
                    }
                }
            }
        }

        board[max_pos.row][max_pos.col] = ME;
        printf("%d %d\n", max_pos.row, max_pos.col);
        fflush(stdout);
    }
    return 0;
}
