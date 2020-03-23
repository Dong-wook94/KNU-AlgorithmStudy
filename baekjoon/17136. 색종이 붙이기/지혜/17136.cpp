//
//  17136.cpp
//  test
//
//  Created by 지혜 on 2020/03/22.
//  Copyright © 2020 지혜. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <utility>
using namespace std;

int map[10][10];
int paper[6]={0,5,5,5,5,5}; // 5*5 , 4*4, 3*3, 2*2, 1*1
int result = 99999;
vector<pair<int,int>> hide;

int checkAttach(int row, int col, int size){
    
    for(int i=row; i<row+size; i++){
        for(int j=col; j<col+size; j++){
            if(i>=10 || j>=10 || map[i][j]==0) return 0;
        }
    }
    return 1;

}

int checkEnd(){
    for(int i=0; i<hide.size(); i++){
        if(map[hide[i].first][hide[i].second] == 1) return 0;
    }
    return 1;
}

vector<int> changeHide(int hideNum, int row, int col, int size){
    vector<int> v;
    for(int i=hideNum; i<hide.size(); i++){
        if(hide[i].first >= row && hide[i].first <row+size && hide[i].second >=col && hide[i].second <col+size){
            v.push_back(i);
        }
    }
    return v;
}

int findNextHideNum(int curNum){
    for(int i=curNum; i<hide.size(); i++){
        if(map[hide[i].first][hide[i].second] == 1) return i;
    }
    return (int)hide.size();
}

void dfs(int hideNum, int cnt){

    if(hideNum >= hide.size()){
        if(checkEnd() == 1){
            if(result > cnt ){ result = cnt;}
        }
        return;
    }
    
    int curR = hide[hideNum].first;
    int curC = hide[hideNum].second;
    
    for(int i=5; i>=0; i--){
        if(paper[i]>0){
            if( checkAttach(curR,curC,i) == 1 ){
                // 종이 붙일 수 있음
                paper[i]-=1;
                vector<int> change = changeHide(hideNum,curR,curC,i);
                for(int j=0; j<change.size(); j++){
                    map[hide[change[j]].first][hide[change[j]].second] = 0;
                }
                int nextNum = findNextHideNum(hideNum);
                dfs(nextNum,cnt+1);
                for(int j=0; j<change.size(); j++){
                    map[hide[change[j]].first][hide[change[j]].second] = 1;
                }
                paper[i]+=1;
            }
        }
    }
    
}

int main(){
    
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            scanf("%d",&map[i][j]);
            if(map[i][j] == 1){
                hide.push_back(make_pair(i,j));
            }
        }
    }
    
    if(hide.empty()){
        printf("0\n");
        return 0;
    }else{
        dfs(0,0);
        if(result == 99999){result = -1;}
        printf("%d\n",result);
    }
    return 0;
}
