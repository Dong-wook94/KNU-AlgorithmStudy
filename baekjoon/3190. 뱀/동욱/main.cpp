#include <stdio.h>
#include <queue>
#include <stdlib.h>
#define APPLE 2
#define SNAKE 1
using namespace std;
typedef struct Snake {
    int row;
    int col;
    Snake(int r, int c) {
        row = r;
        col = c;
    }
}Snake;

queue<Snake> snake;
int N;//보드크기
int K;//사과개수
int n_turn;
int Map[101][101];
int dir=0;
int dir_row[4] = {0,1,0,-1};
int dir_col[4] = {1,0,-1,0};
int total_sec=0;
void MoveSnake(int second);
int main() {
    int row, col, sec;
    char turn;
    scanf("%d", &N);
    scanf("%d", &K);
    for (int i = 0; i < K; i++) {
        scanf("%d %d", &row, &col);
        Map[row][col] = 2;//사과는  2
    }
    snake.push(Snake(1, 1));
    Map[1][1] = 1;
    scanf("%d", &n_turn);
    for (int i = 0; i <n_turn; i++) {
        scanf("%d %c", &sec, &turn);
        MoveSnake(sec-total_sec);
        switch (turn) {
        case 'L':
            dir = (dir + 3) % 4;
            break;
        case 'D':
            dir = (dir + 1) % 4;
            break;
        }
    }
    MoveSnake(100000);//이후 쭉직진
}
void MoveSnake(int second) {
    int next_row, next_col;
    for (int i = 0; i < second; i++) {
        total_sec++;
        next_row = snake.back().row + dir_row[dir];
        next_col = snake.back().col + dir_col[dir];
        snake.push(Snake(next_row,next_col));
        if (next_row<1 || next_col<1 || next_row>N || next_col>N) {
            printf("%d", total_sec);
            exit(0);
        }
        else if(Map[next_row][next_col] == APPLE) {
            Map[next_row][next_col] = SNAKE;
        }
        else if (Map[next_row][next_col] == SNAKE) {
            printf("%d", total_sec);
            exit(0);
        }
        else if (Map[next_row][next_col] == 0) {
            Map[next_row][next_col] = 1;
            Map[snake.front().row][snake.front().col] = 0;
            snake.pop();
        }
        //맵 출력해보기
        /*printf("\nsec :%d\n",total_sec);
        for (int k = 1; k <=N; k++) {
            for (int j = 1; j <=N; j++) {
                printf("%d ", Map[k][j]);
            }
            printf("\n");
        }*/
    }
}
