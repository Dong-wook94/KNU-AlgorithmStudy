//
//  17281.cpp
//  test
//
//  Created by 지혜 on 2020/05/17.
//  Copyright © 2020 지혜. All rights reserved.
//

#include <stdio.h>
int team[50][9]={0};
int visit[9]={0};
int order[9]={0};
int n;
int result = 0;

//안타: 타자와 모든 주자가 한 루씩 진루한다. : 1
//2루타: 타자와 모든 주자가 두 루씩 진루한다. : 2
//3루타: 타자와 모든 주자가 세 루씩 진루한다. : 3
//홈런: 타자와 모든 주자가 홈까지 진루한다. : 4
//아웃: 모든 주자는 진루하지 못하고, 공격 팀에 아웃이 하나 증가한다. : 0

int calScore(){
    int score = 0;
    int turn = 0;
    int ground[3]={0};
    
    for(int i=0; i<n; i++){
        int out = 0;
        for(int j=0; j<3; j++) ground[j]=0;
        
        while(1){
            int play = team[i][order[turn]];
            if( play == 0){
                out += 1;
            }else if(play == 1){
                if(ground[2]){
                    ground[2]=0;
                    score+=1;
                }
                for(int j=1; j>=0; j--){
                    if(ground[j]){
                        ground[j]=0;
                        ground[j+1]=1;
                    }
                }
                ground[0]=1;
            }else if(play == 2){
                for(int j=2; j>0; j--){
                    if(ground[j]){
                        ground[j] = 0;
                        score+=1;
                    }
                }
                if(ground[0]){
                    ground[0]=0;
                    ground[2]=1;
                }
                ground[1]=1;
            }else{
                for(int j=2; j>=0; j--){
                    if(ground[j]){
                        ground[j] = 0;
                        score+=1;
                    }
                }
                if(play == 3) ground[2] = 1;
                else score+=1;
            }
            turn = (turn+1)%9;
            if(out >= 3) break;
        }
    }
    return score;
}

void dfs(int cur){
    if(cur >= 9){
        int score = calScore();
        if( result < score ) result = score;
        return;
    }
    
    if(cur == 3){
        dfs(cur+1);
        return;
    }
    
    for(int i=1; i<9; i++){
        if(visit[i] == 1) continue;
        visit[i] = 1;
        order[cur] = i;
        dfs(cur+1);
        visit[i] = 0;
    }
}

int main(){

    scanf("%d",&n);
    for(int i=0; i<n; i++){
        for(int j=0; j<9; j++){
            scanf("%d",&team[i][j]);
        }
    }
    order[3]=0;
    dfs(0);
    printf("%d\n",result);
    return 0;
}
