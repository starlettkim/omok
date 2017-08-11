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
    const int MY_WEIGHT[]       = { 0, 0, 10, 40, 160, (int)1e8 };
    const int OPPONENT_WEIGHT[] = { 0, 0, 10, 35, 150, (int)1e7 };

    const double WEIGHT_SPACE = 0.8;

    // 네 가지 방향.
    int dr[] = { 0, 1, 1, 1 };
    int dc[] = { 1, 1, 0, -1 };

    board[row][col] = (is_my_turn ? ME : OPPONENT);

    //
    vector<int> vec_score;

    for (int i = 0; i < 4; i++) {
        int max_score = 0;
        for (int j = 0; j < 5; j++) {
            int cnt = 0;
            int score = 0;
            double weight = 1;
            for (int k = 0; k < 5; k++) {
                int chk_row = row + dr[i] * (j - k);
                int chk_col = col + dc[i] * (j - k);
                if (chk_row <= 0 || chk_row > BOARD_SIZE ||
                        chk_col <= 0 || chk_col > BOARD_SIZE ||
                        board[chk_row][chk_col] == (is_my_turn ? OPPONENT : ME)) {
                    score = 0;
                    break;
                } else if (board[chk_row][chk_col] == (is_my_turn ? ME : OPPONENT)) {
                    score += MY_WEIGHT[++cnt] * weight;
                } else {
                    weight *= WEIGHT_SPACE;
                }
            }
            if (max_score < score) {
                max_score = score;
            }
        }
        vec_score.push_back(max_score);
    }

    board[row][col] = 0;
    int ret = 0;
    for (auto i : vec_score) {
        ret += i;
    }
    return ret;
}

int main() {
    srand((unsigned int)time(NULL));
    vector<Position> empty_pos;
    for (int i = 1; i <= BOARD_SIZE; i++) {
        for (int j = 1; j <= BOARD_SIZE; j++) {
            empty_pos.push_back({i, j});
        }
    }
    int start = 0;
    while (true) {
        int row, col;
        scanf("%d %d", &row, &col);
        if (row || col) {
            start = 1;
        }
        fflush(stdin);
        board[row][col] = OPPONENT;
        for (int i = 0; i < empty_pos.size(); i++) {
            if (empty_pos[i].row == row && empty_pos[i].col == col) {
                empty_pos.erase(empty_pos.begin() + i);
            }
        }
        if (empty_pos.empty()) {
            break;
        }

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
        if (!start) {
            pick_pos = { BOARD_SIZE / 2, BOARD_SIZE / 2 };
        } else if (max_value) {
            pick_pos = max_pos[rand() % max_pos.size()];
        } else {
            pick_pos = empty_pos[empty_pos.size() / 2];
        }
        max_pos.clear();

        board[pick_pos.row][pick_pos.col] = ME;
        printf("%d %d\n", pick_pos.row, pick_pos.col);
        fflush(stdout);
        for (int i = 0; i < empty_pos.size(); i++) {
            if (empty_pos[i].row == pick_pos.row && empty_pos[i].col == pick_pos.col) {
                empty_pos.erase(empty_pos.begin() + i);
            }
        }
        if (empty_pos.empty()) {
            break;
        }
    }
    return 0;
}
