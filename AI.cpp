// OVER C++11

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <time.h>

#define BOARD_SIZE  12
#define ME          1
#define OPPONENT    2

using namespace std;

int board[BOARD_SIZE + 1][BOARD_SIZE + 1];
typedef struct { int row, col; } Position;

/*
 * 인자로 들어온 (row, col) 위치에 돌을 놓았을 때 얻을 수 있는 기대값을 대충
 * 계산해서 리턴하는 함수.
 */
int evaluationFunction(int row, int col, bool is_my_turn) {
    // N개의 돌이 연속되었을 경우에 대한 가중치값.
    // 심심할때 조정해보면서 놀도록 하자! ㅎㅅㅎ
    const int WEIGHT_2 = 10;
    const int WEIGHT_3 = 40;
    const int WEIGHT_4 = 160;
    const int WEIGHT_5 = 1e8;
    
    const int OPPONENT_WEIGHT_2 = 10;
    const int OPPONENT_WEIGHT_3 = 35;
    const int OPPONENT_WEIGHT_4 = 150;
    const int OPPONENT_WEIGHT_5 = 1e7;

    // 네 가지 방향.
    int dr[] = { 0, 1, 1, 1 };
    int dc[] = { 1, 1, 0, -1};

    //
    vector<int> score;

    for (int i = 0; i < 4; i++) {
        // 직선 방향으로 5개의 돌 중 본인 돌의 개수.
        int cnt = 1;
        int opponent_cnt = 0;
        int max_score = 0;
        for (int j = 1; j < 5; j++) {
            int chk_row = row + dr[i] * j;
            int chk_col = col + dc[i] * j;
            if (chk_row <= 0 || chk_row > BOARD_SIZE || 
                chk_col <= 0 || chk_col > BOARD_SIZE ||
                board[row + dr[i] * j][col + dc[i] * j] == (is_my_turn ? OPPONENT : ME)) {
                ++opponent_cnt;
            } else if (board[row + dr[i] * j][col + dc[i] * j] == (is_my_turn ? ME : OPPONENT)) {
                ++cnt;
            }
        }
        if (opponent_cnt == 0 && max_score < cnt) {
            max_score = cnt;
        }

        for (int j = 4; j > 0; j--) {
            int old_row = row + dr[i] * j;
            int old_col = col + dc[i] * j;
            int new_row = row + dr[i] * (j - 5);
            int new_col = col + dc[i] * (j - 5);
            if (new_row <= 0 || new_row > BOARD_SIZE ||
                new_col <= 0 || new_col > BOARD_SIZE) {
                break;
            }
            opponent_cnt -= (board[old_row][old_col] == (is_my_turn ? OPPONENT : ME));
            opponent_cnt += (board[new_row][new_col] == (is_my_turn ? OPPONENT : ME));
            cnt -= (board[old_row][old_col] == (is_my_turn ? ME : OPPONENT));
            cnt += (board[new_row][new_col] == (is_my_turn ? ME : OPPONENT));
            if (opponent_cnt == 0 && max_score < cnt) {
                max_score = cnt;
            }
        }

        score.push_back(max_score);
    }
    
    // 생각보다 시간이 없어서 예정보다 더 대충 짜게 되었다.
    int ret = 0;
    for (auto i : score) {
        switch (i) {
            case 2:
                ret += (is_my_turn ? WEIGHT_2 : OPPONENT_WEIGHT_2); break;
            case 3:
                ret += (is_my_turn ? WEIGHT_3 : OPPONENT_WEIGHT_3); break;
            case 4:
                ret += (is_my_turn ? WEIGHT_4 : OPPONENT_WEIGHT_4); break;
            case 5:
                ret += (is_my_turn ? WEIGHT_5 : OPPONENT_WEIGHT_5); break;
        }
    }
    printf("%d, %d: %d\n", row, col, ret);
    return ret;
}

int main() {
    srand((unsigned int)time(NULL));
    while (true) {
        int row, col;
        scanf("%d %d", &row, &col);
        fflush(stdin);
        board[row][col] = OPPONENT;

        vector<Position> max_pos;
        int max_value = 0; 
        for (int i = 1; i <= BOARD_SIZE; i++) {
            for (int j = 1; j <= BOARD_SIZE; j++) {
                if (!board[i][j]) {
                    int ret = evaluationFunction(i, j, 1) + evaluationFunction(i, j, 0);
                    if (max_value < ret) {
                        max_value = ret;
                        max_pos.clear();
                    }
                    if (max_value == ret) {
                        max_pos.push_back({i, j});
                    }
                }
            }
        }

        Position pick_pos;
        if (max_value) {
            pick_pos = max_pos[rand() % (int)max_pos.size()];
        } else {
            pick_pos = {BOARD_SIZE / 2, BOARD_SIZE / 2};
        }
        max_pos.clear();

        board[pick_pos.row][pick_pos.col] = ME;
        printf("%d %d\n", pick_pos.row, pick_pos.col);
        fflush(stdout);
    }
    return 0;
}
