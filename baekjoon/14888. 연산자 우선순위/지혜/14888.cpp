//
//  14888.cpp
//  test
//
//  Created by 지혜 on 2020/05/03.
//  Copyright © 2020 지혜. All rights reserved.
//

#include <stdio.h>
#include <limits.h>
using namespace std;
int op[4]={0};
int n;
int result_max = INT_MIN;
int result_min = INT_MAX;
int num[11]={0};

void cal(int front, int cur){
    if(cur >= n ){
        if(front > result_max) result_max = front;
        if(front < result_min) result_min = front;
        return;
    }
    
    int new_front = front;
    for(int i=0; i<4; i++){
        if(op[i] == 0) continue;
        if(i == 0){
            // 덧
            new_front += num[cur];
        }else if(i == 1){
            // 뺄
            new_front -= num[cur];
        }else if(i == 2){
            // 곱
            new_front *= num[cur];
        }else{
            // 나누기
            new_front /= num[cur];
        }
        op[i]-=1;
        cal(new_front, cur+1);
        op[i]+=1;
        new_front = front;
    }
}

int main(){

    scanf("%d",&n);
    for(int i=0; i<n; i++){
        scanf("%d",&num[i]);
    }
    for(int i=0; i<4; i++){
        scanf("%d",&op[i]);
    }
    cal(num[0],1);
    printf("%d\n",result_max);
    printf("%d\n",result_min);
    return 0;
}
