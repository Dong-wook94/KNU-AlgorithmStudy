#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

#define MAX 20

enum DIR{DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT};
int N, ans;
int board[MAX][MAX];


// copy B -> A
void cpyBoard(int A[][MAX], int B[][MAX]){
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            A[i][j] = B[i][j];
}

// Move
int Move(int dir, int A[][MAX]){
    int Max_Value = 0;
    switch (dir) {
        case DIR_UP:
            for(int i=0; i<N; i++){
                int Value = -1;
                int Idx = N;
                for(int j=N-1; j>=0; j--){
                    if(A[i][j] == 0)    continue;
                    if(A[i][j] == Value){
                        A[i][Idx] = A[i][Idx] * 2;
                        Value = -1;
                    }
                    else {
                        Value = A[i][j];    Idx--;
                        A[i][Idx] = A[i][j];
                    }
                    Max_Value = max(Max_Value, A[i][Idx]);
                }
                for(int j=Idx-1; j>= 0; j--) A[i][j] = 0;
            }
            break;
        case DIR_DOWN:
            for(int i=0; i<N; i++){
                int Value = -1;
                int Idx = -1;
                for(int j=0; j<N; j++){
                    if(A[i][j] == 0)    continue;
                    if(A[i][j] == Value){
                        A[i][Idx] = A[i][Idx] * 2;
                        Value = -1;
                    }
                    else{
                        Value = A[i][j];    Idx++;
                        A[i][Idx] = A[i][j];
                    }
                    Max_Value = max(Max_Value, A[i][Idx]);
                }
                for(int j=Idx+1; j<N; j++) A[i][j] = 0;
            }
            break;
        case DIR_LEFT:
            for(int j=0; j<N; j++){
                int Value = -1;
                int Idx = N;
                for(int i=N-1; i>= 0; i--){
                    if(A[i][j] == 0)    continue;
                    if(A[i][j] == Value){
                        A[Idx][j] = A[Idx][j] * 2;
                        Value = -1;
                    }
                    else{
                        Value = A[i][j];    Idx--;
                        A[Idx][j] = A[i][j];
                    }
                    Max_Value = max(Max_Value, A[Idx][j]);
                }
                for(int i=Idx-1; i>=0; i--) A[i][j] = 0;
            }
            break;
        case DIR_RIGHT:
            for(int j=0; j<N; j++){
                int Value = -1;
                int Idx = -1;
                for(int i=0; i<N; i++){
                    if(A[i][j] == 0)    continue;
                    if(A[i][j] == Value){
                        A[Idx][j] = A[Idx][j] * 2;
                        Value = -1;
                    }
                    else {
                        Value = A[i][j];    Idx++;
                        A[Idx][j] = A[i][j];
                    }
                    Max_Value = max(Max_Value, A[Idx][j]);
                }
                for(int i=Idx+1; i<N; i++) A[i][j] = 0;
            }
            break;
    }
    return Max_Value;
}

// if A = B return true, else false
bool isSameMap(int A[][MAX], int B[][MAX]){
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            if(A[i][j] != B[i][j])
                return false;
    return true;
}

// if expected value is more than ans return true, else false
bool isExpectedValue(int next_max, int next_cnt){
    int remain_cnt = 10 - next_cnt;
    int expect_max = next_max * pow(2, remain_cnt);
    
    if(ans >= expect_max) return false;
    return true;
}

// dfs
void dfs(int cnt, int State[][MAX], int Max_Value){
    if(cnt == 10){
        ans = Max_Value;
        return;
    }
    for(int i=0; i<4; i++){
        int nState[MAX][MAX];
        int nMax_Value;
        int nCnt = cnt + 1;
        
        cpyBoard(nState, State);
        nMax_Value = Move(i, nState);
        
        if(isSameMap(State, nState)) continue;
        if(isExpectedValue(nMax_Value, nCnt)) dfs(nCnt, nState, nMax_Value);
    }
}

int main(int argc, const char * argv[]) {
    // input
    cin >> N;
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++){
            scanf("%d", &board[i][j]);
            if(board[i][j] > ans)
                ans = board[i][j];
        }
    
    // solution
    dfs(0, board, ans);
    
    // output
    cout << ans << "\n";
    return 0;
}
