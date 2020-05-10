//
//  2580.cpp
//  test
//
//  Created by 지혜 on 2020/05/10.
//  Copyright © 2020 지혜. All rights reserved.

#include <stdio.h>
#include <utility>
#include <vector>
#include <stdlib.h>
using namespace std;
int map[9][9];
vector<pair<int,int>> blank;

void sdoku(int bNum){
    int num[10]={0};
    
    if( bNum == blank.size() ){
        for(int i=0; i<9; i++){
            for(int j=0; j<9; j++){
                printf("%d ",map[i][j]);
            }
            printf("\n");
        }
        exit(0);
    }
    
    int curR = blank[bNum].first;
    int curC = blank[bNum].second;
    
    // 가로줄 세로줄 보기
    for(int i=0; i<9; i++){
        num[map[curR][i]]++;
        num[map[i][curC]]++;
    }
    
    // block 보기
    int blockR = curR/3;
    int blockC = curC/3;
    
    for(int i=blockR*3; i<blockR*3+3; i++){
        for(int j=blockC*3; j<blockC*3+3; j++){
            num[map[i][j]]++;
        }
    }
    
    for(int i=1; i<10; i++){
        if(num[i] != 0) continue;
        map[curR][curC] = i;
        sdoku(bNum+1);
        map[curR][curC] = 0;
    }
    
}

int main(){
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            scanf("%d",&map[i][j]);
            if(map[i][j] == 0)
                blank.push_back({i,j});
        }
    }
    
    sdoku(0);
    return 0;
}
