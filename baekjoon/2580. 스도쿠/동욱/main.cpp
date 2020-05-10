#include <stdio.h>
#include <stdlib.h>

using namespace std;

queue<pair<int,int>> q;

int Map[9][9];
int set_row[9];
int set_col[9];
int set_square[3][3];

bool isPossible(int row, int col,int num){
    int union_num = set_row[row] | set_col[col] | set_square[row/3][col/3];
    
    if(union_num & (1<<num))
        return false;
    return true;
}

void dfs(int cnt){
    if(cnt==81){
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                printf("%d ",Map[i][j]);
            }
            printf("\n");
        }
        exit(0);
    }
    
    int row = cnt/9;
    int col = cnt%9;
    
    if(Map[row][col])
        dfs(cnt+1);
    else{
        for(int i=1; i<=9;i++){
            if(isPossible(row,col,i)){
                Map[row][col] = i;
                set_row[row]+= (1<<i);
                set_col[col]+= (1<<i);
                set_square[row/3][col/3] += (1<<i);
                dfs(cnt+1);
                Map[row][col] = 0;
                set_row[row]-= (1<<i);
                set_col[col]-= (1<<i);
                set_square[row/3][col/3] -= (1<<i);
                
            }
        }
    }
    
    
}

int main() {
    
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            int input;
            scanf("%d",&input);
            Map[i][j] = input;
            if(input!=0){
                set_row[i]+= (1<<input);
                set_col[j]+= (1<<input);
                set_square[i/3][j/3] += (1<<input);
            }
        }
    }
    dfs(0);

    
    return 0;
}
