#include <stdio.h>
#include <stdlib.h>

#define board_size 19

int board[board_size+1][board_size+1];
//┏ ┃ ┓ ━ ┛ ┗ ┣ ┻ ┳ ┫ ╋ ○ ●
int dx[4][2][4]={
    {{-1,-2,-3,-4}, {1,2,3,4}},
    {{-1,-2,-3,-4}, {1,2,3,4}},
    {{0,0,0,0},{0,0,0,0}},
    {{-1,-2,-3,-4},{1,2,3,4}}
};
int dy[4][2][4]={
    {{0,0,0,0},{0,0,0,0}},
    {{1,2,3,4},{-1,-2,-3,-4}},
    {{1,2,3,4},{-1,-2,-3,-4}},
    {{-1,-2,-3,-4},{1,2,3,4}}
};
int Is_win(int turn, int pox, int poy)
{
    for(int a=0; a<4; a++)
    {
        int cnt=1;
        for(int b=0; b<2; b++)
        {
            for(int c=0; c<4; c++){
                int nx=pox+dx[a][b][c],ny=poy+dy[a][b][c];

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
bool three_ch(int turn, int pox, int poy)
{
    //  fprintf(stderr,"tttt\n");
    int x[3],y[3];
    for(int a=0; a<4; a++)
    {
        int cnt=1;
        for(int b=0; b<2; b++)
        {
            for(int c=0; c<4; c++)
            {
                int nx=pox+dx[a][b][c],ny=poy+dy[a][b][c];
                if(nx<1 || ny>board_size || nx<1 || ny>board_size) break;
                if(board[nx][ny]==turn)
                {
                    if(cnt==3)
                    {
                        cnt=4;
                        break;
                    }
                    x[cnt]=nx,y[cnt]=ny;
                    cnt++;
                }
                else break;
            }
        }
        if(cnt==3)
        {
            for(int i=0; i<3; i++)
            {
                for(int j=0; j<4; j++)
                {
                    int cnt2=1;
                    if(a==j) continue;
                    for(int k=0; k<2; k++)
                    {
                        for(int l=0; l<4; l++)
                        {
                            int nx2=x[i]+dx[j][k][l],ny2=y[i]+dy[j][k][l];
                            if(nx2<1 || nx2>board_size || ny2<1 || ny2>board_size) break;
                            if(board[nx2][ny2]==turn)
                                cnt2++;
                            else break;
                        }
                    }
                    //  fprintf(stderr,"qwetrt\n");
                    if(cnt2==3){
                        //  fprintf(stderr,"nonono\n");
                        return true;
                    }
                }
            }
        }
    }
    //fprintf(stderr,"please\n");
    return false;
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


        for(int i=1;i<=board_size*2-1;++i){
            for(int j=1;j<=board_size*2-1;++j){
                if(i&1 && j&1){
                    if(board[i/2+1][j/2+1]==1)
                        fprintf(stderr,"○");
                    else if(board[i/2+1][j/2+1]==2)
                        fprintf(stderr,"●");
                    else fprintf(stderr," ");
                }
                else if(!(i&1) && !(j&1))
                    fprintf(stderr,"╋");
                else if(i&1) fprintf(stderr,"┃");
                else if(j&1) fprintf(stderr,"━");
            }
            fprintf(stderr,"\n");
        }
        //  fprintf(stderr,"!122211\n");
        if(three_ch(turn,x,y)==true)
        {
            //  fprintf(stderr,"????\n");
            printf("3*3 rule violation\n");
            fflush(stdout);
            //fprintf(stderr,"%d , %d 는 3*3 규칙에 위반되므로 다른 자리에 돌을 놓아주세요.\n",x,y);
        }
        //  fprintf(stderr,"12244444321111\n");
        if(Is_win(turn,x,y)==turn)
        {
            //  fprintf(stderr,"11111\n");
            printf("[%d] is win\n ",turn);
            fflush(stdout);
            break;
        }
        //  fprintf(stderr,"555555\n");
        printf("draw\n");
        fflush(stdout);
    }
    return 0;
}

