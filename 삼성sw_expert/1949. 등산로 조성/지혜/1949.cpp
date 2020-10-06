//
//  1949.cpp
//  test
//
//  Created by 지혜 on 2020/10/05.
//  Copyright © 2020 지혜. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int map[9][9];
int visit[9][9];
int n,k;
int dir_r[4]={1,-1,0,0};
int dir_c[4]={0,0,1,-1};
int result=0;

void clearMap(){
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            map[i][j]=0;
            visit[i][j]=0;
        }
    }
}

vector<pair<int,int>> findHigh(int high){
    vector<pair<int,int>> v;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(map[i][j] == high) v.push_back(make_pair(i,j));
        }
    }
    return v;
}

void dfs(int row, int col, int dis, int cut){

    result = max(result,dis);
    int curH = map[row][col];

    for(int i=0; i<4; i++){
        int nextR = row +dir_r[i];
        int nextC = col +dir_c[i];
        if(nextR < 1 || nextC < 1 || nextR > n || nextC >n || visit[nextR][nextC]) continue;
        if(curH > map[nextR][nextC]){
            visit[nextR][nextC] = 1;
            dfs(nextR,nextC,dis+1,cut);
            visit[nextR][nextC] = 0;
        }else{
            if(cut == 0){
                int dif = map[nextR][nextC] - curH +1;
                if( dif <= k){
                    visit[nextR][nextC] = 1;
                    map[nextR][nextC] -= dif;
                    dfs(nextR,nextC,dis+1,cut+1);
                    visit[nextR][nextC] = 0;
                    map[nextR][nextC] += dif;
                }
            }
        }
     }

}

int main(){

    int caseNum;
    cin >> caseNum;

    for(int caseN=1; caseN<=caseNum; caseN++){
        cin >> n >> k;
        int high = 0;
        for(int i=1; i<=n; i++){
            for(int j=1; j<=n; j++){
                cin >> map[i][j];
                if(high < map[i][j]) high = map[i][j];
            }
        }

        vector<pair<int,int>> highList = findHigh(high);
        for(int i=0; i<highList.size(); i++){
            visit[highList[i].first][highList[i].second] = 1;
            dfs(highList[i].first, highList[i].second,1,0);
            visit[highList[i].first][highList[i].second] = 0;
        }
        printf("#%d %d\n",caseN, result);
        clearMap();
        result = 0;
    }
    return 0;
}
