#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <stdlib.h>
using namespace std;
typedef struct change{
    int row;
    int col;
    int value;
    change(){}
    change(int a,int b,int c){row=a; col=b; value=c;}
}change;

typedef struct air{
    int row;
    int col;
    air(){}
    air(int a,int b){row=a;col=b;}
}air;
// 오른쪽 아래 왼쪽 위쪽
int dir_r[4] = {1,0,-1,0};
int dir_c[4] = {0,-1,0,1};
int r,c,t; // t초가 지난 후 방에 남아 있는 미세 먼지 양?
vector<vector<int>> home;
 // 공기청정기 위치
vector<air> a;
queue<change> q;

void diffusion(){
    
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            if(home[i][j] != 0){
                int cur_dust = home[i][j];
                int spread_dust = cur_dust/5;
                int check=0;
                for(int k=0; k<4; k++){
                    int row = i+dir_r[k];
                    int col = j+dir_c[k];
                    if( row >= 0 && row < r && col >=0 && col < c && home[row][col]!= -1){
                        check+=1;
                        q.push(change(row,col,spread_dust));
                    }
                }
                home[i][j] = cur_dust - spread_dust*check;
            }
        }
    }
    
    while(!q.empty()){
        change qc = q.front();
        home[qc.row][qc.col] += qc.value;
        q.pop();
    }
}

void air_cleaner(){
    
    // 오른쪽으로 먼지 옮기기
    for(int j=0; j<c; j++){
        int r1 = a[0].row;
        int r2 = a[1].row;
        if(j!=c-1){
            if(j!=0){
                q.push(change(r1,j+1,home[r1][j]));
                q.push(change(r2,j+1,home[r2][j]));
            }else {
                q.push(change(r1,j+1,0));
                q.push(change(r2,j+1,0));
            }
        }
    }
    
    // 맨 끝쪽 줄
    for(int i=0; i<r; i++){
        int col = c-1;
        if( i <= a[0].row && i>0 ){
            // 위쪽으로 먼지 움직이기
            q.push(change(i-1,col,home[i][col]));
        }else if( i >= a[1].row && i<r-1 ){
            // 아래쪽으로 먼지 움직이기
            q.push(change(i+1,col,home[i][col]));
        }
    }
    
    // 왼쪽으로 먼지 옮기기
    for(int j=1; j<c; j++){
        int r1 = 0;
        int r2 = r-1;
        q.push(change(r1,j-1,home[r1][j]));
        q.push(change(r2,j-1,home[r2][j]));
    }
    
    // 맨 첫번째 줄
    for(int i=0; i<r; i++){
        int col = 0;
        if(i < a[0].row-1){
            // 아래로 먼지 옮기기
            q.push(change(i+1,col,home[i][col]));
        }else if( i > a[1].row + 1){
            // 위로 먼지 옮기기
             q.push(change(i-1,col,home[i][col]));
        }
    }
        
    while(!q.empty()){
        change qc = q.front();
        home[qc.row][qc.col] = qc.value;
        q.pop();
    }
}

int main(){
    
    scanf("%d %d %d",&r,&c,&t);
    
    for(int i=0; i<r; i++){
        vector<int> element(c);
        home.push_back(element);
    }
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            scanf("%d",&home[i][j]);
            if(home[i][j] == -1){
                a.push_back(air(i,j));
            }
        }
    }
    
    for(int i=0; i<t; i++){
        diffusion();
        air_cleaner();
    }
    
   
    int result = 0;
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            if(home[i][j] != -1){
                result += home[i][j];
            }
        }
    }
    printf("%d\n",result);
    
    return 0;
}
