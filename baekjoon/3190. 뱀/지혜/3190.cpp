//
//  3190.cpp
//  test
//
//  Created by 지혜 on 2020/04/26.
//  Copyright © 2020 지혜. All rights reserved.
//

#include <stdio.h>
#include <utility>
#include <queue>
using namespace std;

int switch_dir(int dir,char c){
    if(dir == 0){
        if(c == 'L') return 2;
        else return 3;
    }else if(dir == 1){
        if(c == 'L') return 3;
        else return 2;
    }else if(dir ==2){
        if(c == 'L') return 1;
        else return 0;
    }else{
        if(c == 'L') return 0;
        else return 1;
    }
}

int main(){

    int n,k,l;
    int map[101][101]={0};
    int dir_r[4]={0,0,-1,1}; // 오0 왼1 위2 아래3
    int dir_c[4]={1,-1,0,0};
    char change_dir[100001];
    change_dir[0]='\0';

    scanf("%d",&n);
    scanf("%d",&k);
    for(int i=0; i<k; i++){
        int a,b;
        scanf("%d %d",&a,&b);
        map[a][b] = 1;
    }
    scanf("%d",&l);
    for(int i=0; i<l; i++){
        int a;
        char b;
        scanf("%d %c",&a,&b);
        change_dir[a] = b;
    }

    int result = 1;
    queue<pair<int,int>> q;
    q.push(make_pair(1,1));
    map[1][1] = 2;
    int headR = 1;
    int headC = 1;
    int dir = 0; // 오른쪽
    while(1){
        int nextR = headR + dir_r[dir];
        int nextC = headC + dir_c[dir];
        if(nextR < 1 || nextC < 1 || nextR > n || nextC >n || map[nextR][nextC] == 2) break;
        if(map[nextR][nextC] == 0){
            int removeR = q.front().first;
            int removeC = q.front().second;
            map[removeR][removeC] = 0;
            q.pop();
        }
        headR = nextR;
        headC = nextC;
        map[nextR][nextC] = 2;
        q.push(make_pair(nextR,nextC));
        if(change_dir[result] != '\0' ){
            dir = switch_dir(dir,change_dir[result]);
        }
        result++;
    }
    printf("%d\n",result);
    return 0;
}
