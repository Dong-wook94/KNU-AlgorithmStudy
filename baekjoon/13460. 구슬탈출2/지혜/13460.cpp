//
//  13460.cpp
//  test
//
//  Created by 지혜 on 2020/03/08.
//  Copyright © 2020 지혜. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;
typedef struct ball{
    int row;
    int col;
    ball(){}
    ball(int a,int b){row=a;col=b;}
}ball;
int n,m;
char map[11][11];
int dir_r[4]={0,0,-1,1};// 오 왼 위 아래
int dir_c[4]={1,-1,0,0};
int result = 11;

void dfs(ball red, ball blue,int cnt){
    if(cnt>10) return;
    if(map[blue.row][blue.col] == 'O') return;
    if(map[red.row][red.col] == 'O'){
        if(result > cnt) result = cnt;
        return;
    }

    for(int i=0; i<4; i++){
        ball nextR,nextB;
        nextR.row = red.row;
        nextR.col = red.col;
        nextB.row = blue.row;
        nextB.col = blue.col;

        while(1){
            nextR.row += dir_r[i];
            nextR.col += dir_c[i];
            if(map[nextR.row][nextR.col] == 'O') break;
            if(map[nextR.row][nextR.col] == '#'){
                nextR.row -= dir_r[i];
                nextR.col -= dir_c[i];
                break;
            }
        }

        while(1){
            nextB.row += dir_r[i];
            nextB.col += dir_c[i];
            if(map[nextB.row][nextB.col] == 'O') break;
            if(map[nextB.row][nextB.col] == '#'){
                nextB.row -= dir_r[i];
                nextB.col -= dir_c[i];
                break;
            }
        }

        if( nextR.row == nextB.row && nextR.col == nextB.col && map[nextR.row][nextR.col] != 'O'){
            if(i == 0){
                // 오
                if(red.col > blue.col){
                    nextB.col -= 1;
                }else nextR.col -=1;
            }else if(i == 1){
                // 왼
                if(red.col < blue.col){
                    nextB.col += 1;
                }else nextR.col += 1;
            }else if(i == 2){
                // 위
                if(red.row < blue.row){
                    nextB.row += 1;
                }else nextR.row +=1;
            }else if(i == 3){
                // 아래
                if(red.row > blue.row){
                    nextB.row -= 1;
                }else nextR.row -=1;
            }
        }

        dfs(nextR,nextB,cnt+1);

    }
}

int main(){

    scanf("%d %d",&n,&m);

    ball red;
    ball blue;
    char input;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            scanf("%c",&input);
            switch(input){
                case 'R' :
                    red.row = i;
                    red.col = j;
                    map[i][j] = '.';
                    break;
                case 'B' :
                    blue.row = i;
                    blue.col = j;
                    map[i][j] = '.';
                    break;
                case 'O' :
                    map[i][j] = 'O';
                    break;
                case '.' :
                    map[i][j] = '.';
                    break;
                case '#' :
                    map[i][j] = '#';
                    break;
                default :
                    j--;
                    break;
            }
        }
    }
    
    dfs(red,blue,0);
    if(result == 11) result = -1;
    printf("%d\n",result);
    return 0;
}
