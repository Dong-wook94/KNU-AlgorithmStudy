# 2048

## 문제 알고리즘
- dfs
- 백트레킹

## 풀이방법
- 다른 풀이를 참고했다.
1. 기본적으로 dfs를 통해서 완전 탐색을 한다.
2. 그러나, 효율적인 탐색을 위해서 두가지 방법을 사용한다.
    - 그 다음으로 움직일 수 있는 경우가 현재 가지고 있는 답보다 적은 경우, 진행하지 않는다.
    - 현재의 맵이 이전의 맵과 같은 경우, 진행하지 않는다.
3. 위의 두 방법으로 dfs를 진행하여 문제를 해결한다.

- 핵심 코드
~~~c++
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
~~~

## 문제 후 느낀점
- 백트레킹을 이용해서 dfs를 푸는 문제였다.
- 세상에는 잘하는 사람이 너무 많다.

