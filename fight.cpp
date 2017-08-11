#include <stdio.h>
#include <string.h>

#define FIGHT_NUM 20
#define FIGHT_NAME "python pipe.py ./refree ./player1 ./player2"
#define BUFF_SIZE 256

int main() {
    char in[256];
    int player1_win = 0;
    for (int i = 0; i < FIGHT_NUM; i++) {
        FILE *r_pipe = popen(FIGHT_NAME, "r");
        while (true) {
            fgets(in, BUFF_SIZE, r_pipe);
            if (!strcmp(in, "[1] is win\n")) {
                player1_win++;
                break;
            } else if (!strcmp(in, "[2] is win\n")) {
                break;
            } else {
                ;
            }
        }
        pclose(r_pipe);
        fflush(stdin);
    }
    printf("Player1 win rate: %.1lf%%\n",
            (double)100 * player1_win / FIGHT_NUM);
    return 0;
}
