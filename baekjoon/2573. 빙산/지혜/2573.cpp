//
//  2573.cpp
//  test
//
//  Created by 지혜 on 2020/05/03.
//  Copyright © 2020 지혜. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <utility>
#include <queue>
using namespace std;
typedef struct land{
    pair<int,int> location;
    int h;
    int melt;
    land(){}
    land(int a,int b,int c){location.first = a; location.second = b; h=c;}
}land;
int map[300][300]={0};
int visit[300][300]={0};
int n,m;
int dir_r[4]={0,0,-1,1};
int dir_c[4]={1,-1,0,0};
vector<land> ice;

int check_melt(int row, int col){
    int result = 0;
    for(int i=0; i<4; i++){
        int nextR = row + dir_r[i];
        int nextC = col + dir_c[i];
        if( nextR < 0 || nextC < 0 || nextR >= n || nextC >= m) continue;
        if(map[nextR][nextC] == 0) result++;
    }
    return result;
}

void clear_visit(){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            visit[i][j] = 0;
        }
    }
}

int devide_ice(){
    clear_visit();
    queue<pair<int,int>> q;
    for(int i=0; i<ice.size(); i++){
        int curR = ice[i].location.first;
        int curC = ice[i].location.second;
        if(visit[curR][curC] != 0) continue;
        if(visit[curR][curC] == 0 && i != 0) return 1;
        q.push(make_pair(curR,curC));
        visit[curR][curC] = 1;
        while(!q.empty()){
            pair<int,int> cur = q.front();
            q.pop();
            for(int i=0; i<4; i++){
                int nextR = cur.first + dir_r[i];
                int nextC = cur.second + dir_c[i];
                if( nextR < 0 || nextC < 0 || nextR >= n || nextC >= m || visit[nextR][nextC] == 1 || map[nextR][nextC] == 0 ) continue;
                q.push(make_pair(nextR,nextC));
                visit[nextR][nextC] = 1;
            }
        }
    }
    
    return 0;
}

int main(){
    
    scanf("%d %d",&n,&m);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            scanf("%d",&map[i][j]);
            if(map[i][j] != 0 ) ice.push_back(land(i,j,map[i][j]));
        }
    }
    
    int result = 1;
    while(1){
        for(int i=0; i<ice.size(); i++){
            ice[i].melt = check_melt(ice[i].location.first,ice[i].location.second);
        }
        for(int i=0; i<ice.size(); i++){
            ice[i].h -= ice[i].melt;
            if(ice[i].h <= 0 ) ice[i].h = 0;
            map[ice[i].location.first][ice[i].location.second] = ice[i].h;
            if(ice[i].h <= 0 ){ ice.erase(ice.begin()+i); i--;}
        }
    
        if(devide_ice() == 1 ){
            printf("%d\n", result);
            return 0;
        }
        else{
            if(ice.size() == 0 ){
                printf("0\n");
                return 0;
            }
        }
        result++;
    }
}
