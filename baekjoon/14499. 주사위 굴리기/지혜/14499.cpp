//
//  14499.cpp
//  test
//
//  Created by 지혜 on 2020/05/10.
//  Copyright © 2020 지혜. All rights reserved.
//

#include <stdio.h>
int dice[6]={0};

void move(int cmd) {
    if (cmd == 1) {
        int tmp = dice[1];
        dice[1] = dice[5];
        dice[5] = dice[3];
        dice[3] = dice[2];
        dice[2] = tmp;
    }
    else if (cmd == 2) {
        int tmp = dice[1];
        dice[1] = dice[2];
        dice[2] = dice[3];
        dice[3] = dice[5];
        dice[5] = tmp;
    }
    else if (cmd == 4) {
        int tmp = dice[0];
        dice[0] = dice[2];
        dice[2] = dice[4];
        dice[4] = dice[5];
        dice[5] = tmp;
    }
    else {
        int tmp = dice[0];
        dice[0] = dice[5];
        dice[5] = dice[4];
        dice[4] = dice[2];
        dice[2] = tmp;
    }
}

int main(){
    int n,m,x,y,k;
    int map[20][20]={0};
    int dir_r[5]={0,0,0,-1,1}; // 동 1 서 2 북 3 남 4
    int dir_c[5]={0,1,-1,0,0};


    scanf("%d %d %d %d %d",&n,&m,&x,&y,&k);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            scanf("%d",&map[i][j]);
        }
    }

    for(int i=0; i<k; i++){
        int cmd;
        scanf("%d",&cmd);
        int nextX = x + dir_r[cmd];
        int nextY = y + dir_c[cmd];
        if(nextX < 0 || nextY < 0 || nextX >= n || nextY >= m ) continue;
        move(cmd);
        if(map[nextX][nextY] == 0) map[nextX][nextY] = dice[5];
        else{
            dice[5] = map[nextX][nextY];
            map[nextX][nextY] = 0;
        }
        printf("%d\n",dice[2]);
        x = nextX;
        y = nextY;
    }
    return 0;
}
