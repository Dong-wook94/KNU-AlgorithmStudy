#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int mapSize, inputSize;

vector<pair<int,int>> adjList[101][101];
bool visited[101][101];
bool light[101][101];
int dirRow[4] = {1,0,-1,0};
int dirCol[4] = {0,-1,0,1};
int cnt=0;
queue<pair<int,int>> q;

void turnOnLight(int row, int col) {
    for(int i=0;i<adjList[row][col].size();i++){
        pair<int,int> nextRoom = adjList[row][col][i];
        if(!light[nextRoom.first][nextRoom.second]){
            //printf("%d,%d\n",nextRoom.first,nextRoom.second);
            light[nextRoom.first][nextRoom.second] = true;
            cnt++;
        }
    }
}

bool isRange(int row, int col){
    if(row<=0||col<=0||row>mapSize||col>mapSize)
        return false;
    return true;
}



static void initVisited() {
    for(int i=1;i<=mapSize;i++){
        for(int j=1;j<=mapSize;j++){
            visited[i][j] = false;
        }
    }
}

void bfs(){
    initVisited();
    visited[1][1]=true;
    q.push(make_pair(1, 1));
    while(!q.empty()){
        int row = q.front().first;
        int col = q.front().second;
        q.pop();
        turnOnLight(row, col);
        for(int i=0;i<4;i++){
            int nextRow = row+dirRow[i];
            int nextCol = col+dirCol[i];
            
            if(isRange(nextRow, nextCol)&&light[nextRow][nextCol]&&!visited[nextRow][nextCol]){
                visited[nextRow][nextCol] = true;
                q.push(make_pair(nextRow,nextCol));
            }
        }
    }
    
}

int main() {
    scanf("%d %d",&mapSize,&inputSize);
    
    for(int i=0;i<inputSize;i++){
        int x,y,a,b;
        scanf("%d %d %d %d",&x,&y,&a,&b);
        adjList[x][y].push_back(make_pair(a,b));
    }
    
    cnt=1;
    light[1][1] = true;
    int before_cnt = 0;
    do{
        before_cnt = cnt;
        bfs();
    }while(cnt!=before_cnt);
   
    
    printf("%d\n",cnt);
    return 0;
}
