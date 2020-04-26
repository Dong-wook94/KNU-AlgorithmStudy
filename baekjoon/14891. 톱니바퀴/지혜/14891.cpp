//
//  14891.cpp
//  test
//
//  Created by 지혜 on 2020/04/26.
//  Copyright © 2020 지혜. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;
int r[4]={0};
string s[4];

string rotation(int num, int dir){
    string result;
    if(dir == 1){
        // 시계
        string temp = s[num].substr(0,s[num].length()-1);
        result = s[num].back();
        result += temp;
        
    }else{
        // 반시계
        string temp = s[num].substr(1,s[num].length());
        result = temp;
        result += s[num].front();
    }
    return result;
}

void r_clear(){
    for(int i=0; i<4; i++){
        r[i]=0;
    }
}

void r_right(int cur){
    if(cur >= 3) return;
    if(s[cur][2] != s[cur+1][6]){
        if(r[cur] == -1) r[cur+1] = 1;
        else r[cur+1] = -1;
        r_right(cur+1);
    }else return;
}

void r_left(int cur){
    if(cur < 1) return;
    if(s[cur][6] != s[cur-1][2]){
        if(r[cur] == -1 ) r[cur-1] = 1;
        else r[cur-1] = -1;
        r_left(cur-1);
    }else return;
}

int main(){
    int k;
    for(int i=0; i<4; i++){
        cin >> s[i];
    }
    scanf("%d",&k);
    for(int i=0; i<k; i++){
        int num,dir;
        scanf("%d %d",&num,&dir);
        num-=1;
        r[num] = dir;
        r_left(num);
        r_right(num);
        for(int i=0; i<4; i++){
            if(r[i] != 0){
                s[i] = rotation(i,r[i]);
            }
        }
        r_clear();
    }
    int result = 0;
    if(s[0][0] == '1' ) result +=1;
    if(s[1][0] == '1' ) result +=2;
    if(s[2][0] == '1' ) result +=4;
    if(s[3][0] == '1' ) result +=8;
    printf("%d\n",result);
    
    return 0;
}

