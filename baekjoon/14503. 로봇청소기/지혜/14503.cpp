//
//  14503.cpp
//  test
//
//  Created by 지혜 on 2020/04/07.
//  Copyright © 2020 지혜. All rights reserved.
//

#include <stdio.h>
#include <utility>
using namespace std;
typedef struct robot{
    int row;
    int col;
    int dir; // 0 북 1 동 2 남 3 서
    robot(){};
    robot(int a,int b, int c){row=a;col=b;dir=c;}
}robot;
int n,m;
int map[50][50];
int dir_r[4]={-1,0,1,0};
int dir_c[4]={0,1,0,-1};
robot r;
int result=0;

int backDir(int dir){
    if(dir == 0 ) return 2;
    else if(dir == 1) return 3;
    else if(dir == 2) return 0;
    else return 1;
}
int leftDir(int dir){
    if(dir == 0) return 3;
    else if(dir == 1) return 0;
    else if(dir == 2) return 1;
    else return 2;
}
int main(){

    scanf("%d %d",&n,&m);
    scanf("%d %d %d",&r.row,&r.col,&r.dir);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            scanf("%d",&map[i][j]);
        }
    }
    
    int check = 0;
    
    while(1){
        int curD = r.dir;
        int curR = r.row;
        int curC = r.col;
        
        if(check == 2) break;
        
        if(map[curR][curC] == 0 && check == 0){
            map[curR][curC] = 2;
            result+=1;
        }
       
        int nextD = curD;
        int find = 0;
        for(int i=0; i<4; i++){
            nextD = leftDir(nextD);
            int nextR = curR+dir_r[nextD];
            int nextC = curC+dir_c[nextD];
            if(nextR < 0 || nextC < 0 || nextR >= n || nextC >= m || map[nextR][nextC] != 0) continue;
            if(map[nextR][nextC] == 0){
                r.row = nextR;
                r.col = nextC;
                r.dir = nextD;
                find = 1;
                check = 0;
                break;
            }
        }
        
        
        if(find == 0){
            int backD = backDir(curD);
            int nextR = curR+dir_r[backD];
            int nextC = curC+dir_c[backD];
            if(nextR < 0 || nextC < 0 || nextR >= n || nextC >=m || map[nextR][nextC] == 1) check = 2;
            else{
                r.row = nextR;
                r.col = nextC;
                check = 1;
            }
        }
        
    }
    
    printf("%d\n",result);
    
    return 0;
}
