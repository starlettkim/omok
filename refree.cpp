#include <stdio.h>
#include <stdlib.h>

#define board_size 12

int board[board_size+1][board_size+1];
const int dx[] = {-1,-1,-1,0,0,1,1,1,0};
const int dy[] = {-1,0,1,-1,1,-1,0,1,0};
int dxx[4][2][4]={
    {{-1,-2,-3,-4}, {1,2,3,4}},
    {{-1,-2,-3,-4}, {1,2,3,4}},
    {{0,0,0,0},{0,0,0,0}},
    {{-1,-2,-3,-4},{1,2,3,4}}
};
int dyy[4][2][4]={
    {{0,0,0,0},{0,0,0,0}},
    {{1,2,3,4},{-1,-2,-3,-4}},
    {{1,2,3,4},{-1,-2,-3,-4}},
    {{-1,-2,-3,-4},{1,2,3,4}}
};
//┏ ┃ ┓ ━ ┛ ┗ ┣ ┻ ┳ ┫ ╋ ○ ●
bool chk_range(int &x, int &y, int k, int turn);
bool three_ch(int turn, int pox, int poy);
int Is_win(int turn, int pox, int poy);

void printBoard(){
    for(int i=1;i<=board_size*2-1;++i){
        for(int j=1;j<=board_size*2-1;++j){
            if(i&1 && j&1){
                if(board[i/2+1][j/2+1]==1)
                    fprintf(stderr,"O");
                else if(board[i/2+1][j/2+1]==2)
                    fprintf(stderr,"X");
                else {
                    if(i==1){
                        if(j==1) fprintf(stderr,"┏");
                        else if(j==board_size*2-1) fprintf(stderr,"┓");
                        else fprintf(stderr,"┳");
                    }
                    else if(i==board_size*2-1){
                        if(j==1) fprintf(stderr,"┗");
                        else if(j==board_size*2-1) fprintf(stderr,"┛");
                        else fprintf(stderr,"┻");
                    }
                    else if(j==1) fprintf(stderr,"┣");
                    else if(j==board_size*2-1) fprintf(stderr,"┫");
                    else fprintf(stderr,"╋");
                }
            }
            else if(!(i&1) && !(j&1))
                fprintf(stderr," ");
            else if(i&1) fprintf(stderr,"━");
            else if(j&1) fprintf(stderr,"┃");
        }
        fprintf(stderr,"\n");
    }

}

int main()
{
    int x,y;
    int turn=1;
    while(1)
    {
        scanf("%d %d",&x,&y);
        fflush(stdin);

        scanf("%d",&turn);
        fflush(stdin);

        board[x][y]=turn;

        printBoard();
        if(three_ch(turn,x,y)==true)
        {
            printf("3*3 rule violation\n");
            fflush(stdout);
        }
        if(Is_win(turn,x,y)==turn)
        {
            printf("[%d] is win\n ",turn);
            fflush(stdout);
            break;
        }
        printf("draw\n");
        fflush(stdout);
    }
    return 0;
}
bool chk_range(int &x, int &y, int k, int turn){
    x += dx[k]; y += dy[k];
    if(x<1 || x>board_size || y<1 || y>board_size)
        return false;
    if(board[x][y]==turn) return true;
    return false;
}

bool three_ch(int turn, int pox, int poy)
{
    // 33 판정 없음.
    return false;

    int cnt[8] = {1,1,1,1,1,1,1,1};
    for(int k=0;k<8;++k){
        int x = pox, y = poy;
        while(chk_range(x,y,k,turn)){
            cnt[k]++;
            cnt[7-k]++;
        }
        if(chk_range(x,y,8,3-turn)){
            cnt[k] = cnt[7-k] = -987654321;
            continue;
        }

        while(chk_range(x,y,k,turn))
            cnt[k]++;
        if(chk_range(x,y,8,3-turn))
            cnt[k]=-987654321;
    }

    int three = 0;
    for(int k=0;k<4;++k){
        if(cnt[k]==3 || cnt[7-k]==3)
            three++;
    }
    return three > 1;
}
int Is_win(int turn, int pox, int poy)
{
    for(int a=0; a<4; a++)
    {
        int cnt=1;
        for(int b=0; b<2; b++)
        {
            for(int c=0; c<4; c++){
                int nx=pox+dxx[a][b][c],ny=poy+dyy[a][b][c];

                if(nx<1 || nx>board_size
                        || ny<1 || ny>board_size)
                    break;

                if(board[nx][ny]==turn)
                    cnt++;
                else break;
            }
        }
        if(cnt==5)
            return turn;
    }
    return 0;
}

