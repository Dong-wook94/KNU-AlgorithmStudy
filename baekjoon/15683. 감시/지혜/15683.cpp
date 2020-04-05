//
//  15683.cpp
//  test
//
//  Created by 지혜 on 2020/04/04.
//  Copyright © 2020 지혜. All rights reserved.
//
#include <stdio.h>
#include <utility>
#include <vector>
using namespace std;
typedef struct cctv{
    int type;
    pair<int,int> location;
    cctv(){}
    cctv(int a,int b,int c){type=a;location.first=b;location.second=c;}
}cctv;
typedef struct save{
    vector<pair<int,int>> change;
}save;
int n,m;
int map[8][8];
vector<cctv> input;
vector<pair<int,int>> input5;
int result = 99999;
int dirCctv2[2][2]={{0,1},{2,3}};
int dirCctv3[4][2]={{0,2},{0,3},{1,2},{1,3}};
int dirCctv4[4][3]={{0,2,3},{0,1,2},{0,1,3},{1,2,3}};

int countBlindSpot(){
    int count = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(map[i][j] == 0) count++;
        }
    }
    return count;
}

vector<pair<int,int>> changeMap(int row,int col,int dir){
    vector<pair<int,int>> change;
    switch (dir) {
        case 0:
            // 위
            for(int i=row-1; i>=0; i--){
                if(map[i][col] == 6) break;
                else if(map[i][col] == 0) change.push_back(make_pair(i,col));
            }
            break;
        case 1:
            // 아래
            for(int i=row+1; i<n; i++){
                if(map[i][col] == 6) break;
                else if(map[i][col] == 0) change.push_back(make_pair(i,col));
            }
            break;
        case 2:
            // 왼
            for(int i=col-1; i>=0; i--){
                if(map[row][i] == 6) break;
                else if(map[row][i] == 0) change.push_back(make_pair(row,i));
            }
            break;
        case 3:
            // 오른
            for(int i=col+1; i<m; i++){
                if(map[row][i] == 6) break;
                else if(map[row][i] == 0) change.push_back(make_pair(row,i));
            }
            break;
        default:
            break;
    }
    return change;
}

void cctv_watch(int cctvNum){
    if(cctvNum >= (int)input.size()){
        int blindSpot = countBlindSpot();
        if(result > blindSpot) result = blindSpot;
        return;
    }
    
    save saveChange[4];
    for(int i=0; i<4; i++){
        saveChange[i].change = changeMap(input[cctvNum].location.first,input[cctvNum].location.second,i);
    }
    
    switch (input[cctvNum].type) {
        case 1:
            for(int i=0; i<4; i++){
                for(int j=0; j<saveChange[i].change.size(); j++){
                    map[saveChange[i].change[j].first][saveChange[i].change[j].second] = -1;
                }
                cctv_watch(cctvNum+1);
                for(int j=0; j<saveChange[i].change.size(); j++){
                    map[saveChange[i].change[j].first][saveChange[i].change[j].second] = 0;
                }
            }
            break;
        case 2:
            for(int i=0; i<2; i++){
                for(int j=0; j<2; j++){
                    for(int k=0; k<saveChange[dirCctv2[i][j]].change.size(); k++){
                        map[saveChange[dirCctv2[i][j]].change[k].first][saveChange[dirCctv2[i][j]].change[k].second] = -1;
                    }
                }
                cctv_watch(cctvNum+1);
                for(int j=0; j<2; j++){
                    for(int k=0; k<saveChange[dirCctv2[i][j]].change.size(); k++){
                        map[saveChange[dirCctv2[i][j]].change[k].first][saveChange[dirCctv2[i][j]].change[k].second] = 0;
                    }
                }
            }
            break;
        case 3:
            for(int i=0; i<4; i++){
                for(int j=0; j<2; j++){
                    for(int k=0; k<saveChange[dirCctv3[i][j]].change.size(); k++){
                        map[saveChange[dirCctv3[i][j]].change[k].first][saveChange[dirCctv3[i][j]].change[k].second] = -1;
                    }
                }
                cctv_watch(cctvNum+1);
                for(int j=0; j<2; j++){
                    for(int k=0; k<saveChange[dirCctv3[i][j]].change.size(); k++){
                        map[saveChange[dirCctv3[i][j]].change[k].first][saveChange[dirCctv3[i][j]].change[k].second] = 0;
                    }
                }
            }
            break;
        case 4:
            for(int i=0; i<4; i++){
                for(int j=0; j<3; j++){
                    for(int k=0; k<saveChange[dirCctv4[i][j]].change.size(); k++){
                        map[saveChange[dirCctv4[i][j]].change[k].first][saveChange[dirCctv4[i][j]].change[k].second] = -1;
                    }
                }
                cctv_watch(cctvNum+1);
                for(int j=0; j<3; j++){
                    for(int k=0; k<saveChange[dirCctv4[i][j]].change.size(); k++){
                        map[saveChange[dirCctv4[i][j]].change[k].first][saveChange[dirCctv4[i][j]].change[k].second] = 0;
                    }
                }
            }
            break;
        case 5:
            for(int i=0; i<4; i++){
                for(int j=0; j<saveChange[i].change.size(); j++){
                    map[saveChange[i].change[j].first][saveChange[i].change[j].second] = -1;
                }
            }
            cctv_watch(cctvNum+1);
            for(int i=0; i<4; i++){
                for(int j=0; j<saveChange[i].change.size(); j++){
                    map[saveChange[i].change[j].first][saveChange[i].change[j].second] = 0;
                }
            }
            break;
        default:
            break;
    }
    
}

int main(){
    
    scanf("%d %d",&n,&m);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            scanf("%d",&map[i][j]);
            if(map[i][j] > 0 && map[i][j] < 6){
                input.push_back(cctv(map[i][j],i,j));
            }
        }
    }
    
    cctv_watch(0);
    printf("%d\n",result);
    return 0;
}
