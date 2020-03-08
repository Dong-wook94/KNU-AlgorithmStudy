//
//  17472.cpp
//  test
//
//  Created by 지혜 on 2020/03/08.
//  Copyright © 2020 지혜. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

typedef struct land{
    int row;
    int col;
    land(){}
    land(int a,int b){row=a;col=b;}
}land;
typedef struct cBridge{
    int island1;
    int island2;
    int length;
    cBridge(){}
    cBridge(int a,int b,int c){island1= a; island2 = b; length = c;}
}cBridge;

int map[11][11];
int visit[11][11]={0};
int n,m;
int cnt = 1;
int dir_r[4]={0,0,-1,1};// 오 왼 위 아래
int dir_c[4]={1,-1,0,0};
int bridge[7][7]={0};
int result = 99999;
vector<cBridge> bridgeList;
vector<int> checkB[7];


void find_brige(int start, int row, int col, int dir, int length){
    
    int nextR = row + dir_r[dir];
    int nextC = col + dir_c[dir];
    
    if(nextR < 0 || nextR >= n || nextC < 0 || nextC >= m ) return;
    
    if(map[nextR][nextC] == 0){
        find_brige(start,nextR,nextC,dir,length+1);
    }else{
        if(length > 1){
            int dest = map[nextR][nextC];
            if(bridge[start][dest] == 0) bridge[start][dest] = length;
            else{
                if(bridge[start][dest] > length ) bridge[start][dest] = length;
            }
        }
        return;
    }
}

int check_connect(){
    
    return 0;
}

void select_bridge(int idx, int sum){
    
    printf("sum  : %d\n",sum);
    
    if(check_connect() == 1){
        if(result > sum ) result = sum;
        return;
    }
    
    for(int i=idx; i<bridgeList.size(); i++){
        checkB[bridgeList[i].island1].push_back(bridgeList[i].island2);
        checkB[bridgeList[i].island2].push_back(bridgeList[i].island1);
        select_bridge(idx+1,sum+bridgeList[i].length);
        checkB[bridgeList[i].island1].pop_back();
        checkB[bridgeList[i].island2].pop_back();
    }
}

int main(){

    scanf("%d %d",&n,&m);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            scanf("%d",&map[i][j]);
        }
    }
    
    // 땅 번호매기기..
    vector<land> check[7];

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(visit[i][j] == 1) continue;
            if( map[i][j] == 1 ){
                visit[i][j] = 1;
                queue<land> q;
                vector<land> landCheck;
                
                q.push(land(i,j));
                landCheck.push_back(land(i,j));
                
                while(!q.empty()){
                    land cur = q.front();
                    q.pop();
                    for(int i=0; i<4; i++){
                        int nextR = cur.row+dir_r[i];
                        int nextC = cur.col+dir_c[i];
                        if(nextR < 0 || nextR >= n || nextC < 0 || nextC >= m || visit[nextR][nextC] == 1) continue;
                        if(map[nextR][nextC] == 1){
                            landCheck.push_back(land(nextR,nextC));
                            q.push(land(nextR,nextC));
                            visit[nextR][nextC]=1;
                        }
                    }
                }
                
                for(int k=0; k<landCheck.size(); k++){
                    map[landCheck[k].row][landCheck[k].col] = cnt;
                    check[cnt].push_back(land(landCheck[k].row,landCheck[k].col));
                }
                cnt+=1;
            }
        }
    }
    
//    printMap();
    
    // 섬 - 섬 다리길이 최소
    for(int i=1; i<cnt; i++){
        for(int j=0; j<check[i].size(); j++){
            int curR = check[i][j].row;
            int curC = check[i][j].col;
            for(int k=0; k<4; k++){
                int findR = curR + dir_r[k];
                int findC = curC + dir_c[k];
                if( findR < 0 || findR >= n || findC < 0 || findC >= m || map[findR][findC] == i) continue;
                find_brige(i, findR, findC, k, 1);
            }
        }
    }
    
    for(int i=1; i<cnt-1; i++){
        for(int j=i+1; j<cnt; j++){
            if(bridge[i][j] != 0){
                bridgeList.push_back(cBridge(i,j,bridge[i][j]));
            }
        }
    }
    
    select_bridge(0,0);
    if(result == 99999 ) result = -1;
    printf("%d\n",result);
    
    return 0;
}
