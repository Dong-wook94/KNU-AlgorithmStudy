#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <stdlib.h>
#include <math.h>
using namespace std;

int n,m; // 세로 n * 가로 m
int dir_r[4] = {0,1,0,-1};
int dir_c[4] = {-1,0,1,0};
int map[501][501];
int visit[501][501];
int sum = 0;
int result = 0;
int preR, preC;

void dfs(int row, int col, int count){
    if(count >= 4) return;

    for(int i=0; i<4; i++){
        int nextR = row + dir_r[i];
        int nextC = col + dir_c[i];
        if(nextR < 0 || nextC < 0 || nextR >= n || nextC >= m || visit[nextR][nextC] == 1)
            continue;
        visit[nextR][nextC] = 1;
        sum += map[nextR][nextC];
        if(sum > result) result = sum;
        dfs(nextR,nextC,count+1);
        sum -= map[nextR][nextC];
        visit[nextR][nextC]=0;
    }
}

int main(){

    scanf("%d %d",&n,&m);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            scanf("%d",&map[i][j]);
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            visit[i][j] = 1;
            sum += map[i][j];
            preR = i; preC = j;
            dfs(i,j,1);
            sum = 0;
            visit[i][j] = 0;
        }
    }

    // ㅗ 모양...처리...
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            for(int k=0; k<4; k++){
                int exception_sum = 0;
                int nextR = i + dir_r[k];
                int nextC = j + dir_c[k];
                if(nextR >= 0 && nextC >= 0 && nextR < n && nextC < m ){
                    if(nextR == i && nextR-1 >= 0 && nextR+1 < n){
                        exception_sum =map[i][j]+ map[nextR][nextC]+map[nextR-1][nextC]+map[nextR+1][nextC];
                    }

                    if(nextC == j && nextC-1 >=0 && nextC+1 < m){
                        exception_sum = map[i][j]+map[nextR][nextC]+map[nextR][nextC-1]+map[nextR][nextC+1];
                    }

                    if(result < exception_sum) result = exception_sum;
                }
            }
        }
    }
    printf("%d\n",result);
    return 0;
}
