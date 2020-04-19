//
//  15685.cpp
//  test
//
//  Created by 지혜 on 2020/04/19.
//  Copyright © 2020 지혜. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <utility>
using namespace std;
typedef struct dragon{
    int x;
    int y;
    int d;
    int g;
}dragon;

int n;
int dir_r[4]={0,-1,0,1};
int dir_c[4]={1,0,-1,0};
int map[101][101]={0};
dragon curve[20];
int result = 0;

void print_p(vector<int> p){
    for(int i=0; i<p.size(); i++){
        printf("%d ",p[i]);
    }
    printf("\n");
}

int main(){
    
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        scanf("%d %d %d %d",&curve[i].y,&curve[i].x,&curve[i].d,&curve[i].g);
        map[curve[i].x][curve[i].y] = 1;
    }
    
    for(int i=0; i<n; i++){
        vector<int> dir;
        dir.push_back(curve[i].d);
        for(int j=0; j<curve[i].g; j++){
            int len = (int) dir.size()-1;
            for(int k=len; k>=0; k--){
                dir.push_back((dir[k]+1)%4);
            }
            
        }
        
        int nextX = curve[i].x;
        int nextY = curve[i].y;
        
        for(int j=0; j<dir.size(); j++){
            nextX += dir_r[dir[j]];
            nextY += dir_c[dir[j]];
            if( nextX < 0 || nextY < 0 || nextX > 100 || nextY > 100) continue;
            map[nextX][nextY] = 1;
        }
    }
    
    for(int i=0; i<100; i++){
        for(int j=0; j<100; j++){
            if(map[i][j] && map[i][j+1] && map[i+1][j] && map[i+1][j+1]) result++;
        }
    }
    
    printf("%d\n",result);
    
    return 0;
}
