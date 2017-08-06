#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define board_size 19

int board[board_size+1][board_size+1];

int main()
{
    srand((unsigned int)time(NULL));
    int enemy_x,enemy_y,my_x,my_y;

    while(1){
        scanf("%d %d", &enemy_x, &enemy_y);
        fflush(stdin);
        //if(enemy_x != 0 && enemy_x != 0)
        board[enemy_x][enemy_y] = 2;// 2: enemy player

        //decision my_x, my_y
        /*for(int a=1; a<=19; a++)
          {
          if(board[a][0]==0)
          board[a][0]=1;
          printf("%d %d\n",a,0);
          fflush(stdout);
          }*/

        while(board[my_x = rand()%19+1][my_y = rand()%19+1]);
        board[my_x][my_y] = 1;// 1: player
        printf("%d %d\n", my_x, my_y);
        fflush(stdout);
    }
    return 0;
}

