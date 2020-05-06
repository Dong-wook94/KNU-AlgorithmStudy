#include <stdio.h>

typedef struct Dice {
    int up;
    int down;
    int left;
    int right;
    int front;
    int back;
}Dice;

Dice dice;
int N, M, x, y, K;
int Map[20][20];
int inst;
int dir_x[4] = {0,0,-1,1};
int dir_y[4] = {1,-1,0,0};
void move_Dice(int dir);
int main() {
    scanf("%d %d %d %d %d", &N, &M, &x, &y, &K);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &Map[i][j]);
        }
    }
    for (int i = 0; i < K; i++) {
        scanf("%d", &inst);//동 1 서 2 북 3 남 4
        move_Dice(inst-1);
    }
}

void move_Dice(int dir) {
    int next_x, next_y,temp;
    next_x = x + dir_x[dir];
    next_y = y + dir_y[dir];

    if (next_x < 0 || next_y < 0 || next_x >= N || next_y >= M)
        return;
    x = next_x;
    y = next_y;
    switch (dir) {
    case 0://동
        temp = dice.down;
        dice.down = dice.right;
        dice.right = dice.up;
        dice.up = dice.left;
        dice.left = temp;
        break;
    case 1://서
        temp = dice.down;
        dice.down = dice.left;
        dice.left = dice.up;
        dice.up = dice.right;
        dice.right = temp;
        break;
    case 2://북
        temp = dice.down;
        dice.down = dice.back;
        dice.back = dice.up;
        dice.up = dice.front;
        dice.front = temp;
        break;
    case 3://남
        temp = dice.down;
        dice.down = dice.front;
        dice.front = dice.up;
        dice.up = dice.back;
        dice.back = temp;
        break;
    }
    if (Map[x][y] == 0)
        Map[x][y] = dice.down;
    else {
        dice.down = Map[x][y];
        Map[x][y] = 0;
    }
    
    printf("%d\n", dice.up);
}
