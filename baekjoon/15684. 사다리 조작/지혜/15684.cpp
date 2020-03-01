#include <stdio.h>
#include <vector>
using namespace std;

int n,m,h; // n 세로선 개수 m 가로선 개수 h 가로선 놓을 수 있는 위치
int map[31][11]={0}; // 0 아래로
int result = 99999;

void print_map(){
    for(int i=1; i<=h; i++){
        for(int j=1; j<=n; j++){
            printf("%d ",map[i][j]);
        }
        printf("\n");
    }
    printf(">>>>>>\n");
}

int check_ladder(){
    int check = 0;
    
    for(int i=1; i<=n; i++){
        int startR = 1;
        int startC = i;
        while(1){
            if(startR == h){
                if(map[startR][startC] != 0 ) startC = map[startR][startC];
                if(startC != i) check = 1;
                break;
            }
            if(map[startR][startC] != 0){
                startC = map[startR][startC];
            }
            startR+=1;
        }
        if(check == 1 ) return 0;
    }
    return 1;
}

void dfs(int row,int col,int cnt){

    if(cnt>3){return;}
    if(check_ladder() == 1 ){
        if(result > cnt){
            result = cnt;
        }
        return;
    }

    // 사다리 추가
    for(int i=row; i<=h; i++){
        for(int j=col; j<n; j++){
            if(map[i][j] == 0 && map[i][j+1] == 0){
                // 사다리 설치
                map[i][j] = j+1; map[i][j+1] = j;
                if(j+2 > n-1){
                    dfs(i+1,1,cnt+1);
                }else dfs(i,j+2,cnt+1);
                map[i][j] = 0; map[i][j+1] = 0;
            }
        }
        col=1;
    }
}

int main(){
    
    scanf("%d %d %d",&n,&m,&h);
    for(int i=0; i<m; i++){
        int c,d;
        scanf("%d %d",&c,&d);
        map[c][d] = d+1;
        map[c][d+1] = d;
    }
    
    dfs(1,1,0);
    if(result == 99999) result = -1;
    printf("%d\n",result);
    return 0;
}
