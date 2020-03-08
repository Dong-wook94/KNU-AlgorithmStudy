//
//  17825.cpp
//  test
//
//  Created by 지혜 on 2020/03/08.
//  Copyright © 2020 지혜. All rights reserved.
//

#include <stdio.h>

int dice[10];
int checkMap[34]={0};
int score[]={
    0,
    2,4,6,8,10,
    12,14,16,18,20
    ,22,24,26,28,30,
    32,34,36,38,40,
    0,
    13,16,19,25,30,
    35,28,27,26,22,
    24};
int moveMap[]={
    1,2,3,4,5,
    6,7,8,9,10,
    11,12,13,14,15,
    16,17,18,19,20,
    21,21,23,24,25,
    26,27,20,29,30,
    25,32,25
};
int turn[34]={0};
int horse[4]={0};
int result = 0;

void dfs(int diceNum, int sum){
    if(diceNum > 9){
        if(sum > result) result = sum;
        return;
    }

    for(int i=0; i<4; i++){
        int cur = horse[i];
        int moveNum = dice[diceNum];


        int moveStart = cur;
        if(turn[moveStart] != 0 ){
            moveNum-=1;
            moveStart = turn[moveStart];
        }

        while(1){
            if(moveNum == 0 ) break;
            moveStart = moveMap[moveStart];
            moveNum -= 1;
        }

        if( moveStart != 21 && checkMap[moveStart] != 0 ) continue;

        checkMap[cur] = 0;
        checkMap[moveStart] = 1;
        horse[i] = moveStart;

//        printf(">>> sum : %d / %d : %d\n",sum,moveStart,score[moveStart]);
        dfs(diceNum+1,sum+score[moveStart]);

        horse[i] = cur;
        checkMap[cur] = 1;
        checkMap[moveStart] = 0;

    }
}

int main(){

    for(int i=0; i<10; i++){
        scanf("%d",&dice[i]);
    }

    turn[5]=22;
    turn[10]=31;
    turn[15]=28;
    turn[25]=26;

    dfs(0,0);
    printf("%d\n", result);
    return 0;
}
