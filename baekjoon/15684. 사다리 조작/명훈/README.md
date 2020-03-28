# 사다리 조작
> 삼성 역량 테스트 기출문제

## 문제 알고리즘
- dfs

## 풀이방법
1. dfs를 통해 모든 경로를 확인한다.
2. 사다리는 순서가 없으므로 계속 내려가게 확인하면 된다.

- 핵심 코드
~~~c++
bool isValidLadder(int i, int j) {
    if (board[i][j - 1] || board[i][j] || board[i][j + 1])
        return false;
    return true;
}

bool isCorrectLadder() {
    for (int j = 1; j <= N; j++) {
        int pos = j;
        for (int i = 1; i <= H; i++) {
            if (board[i][pos])
                pos++;
            else if (board[i][pos - 1])
                pos--;
        }
        if (pos != j)
            return false;
    }
    return true;
}


void dfs(int s_i, int cnt) {
    // end state
    if (cnt > 3) {
        return;
    }
    if (isCorrectLadder()) {
        ans = min(ans, cnt);
        return;
    }
    // recursive
    for (int i = s_i; i <= H; i++) {
        for (int j = 1; j <= N; j++) {
            if (isValidLadder(i, j)) {
                board[i][j] = true;
                dfs(i, cnt + 1);
                board[i][j] = false;
            }
        }
    }
}bool isValidLadder(int i, int j) {
    if (board[i][j - 1] || board[i][j] || board[i][j + 1])
        return false;
    return true;
}

bool isCorrectLadder() {
    for (int j = 1; j <= N; j++) {
        int pos = j;
        for (int i = 1; i <= H; i++) {
            if (board[i][pos])
                pos++;
            else if (board[i][pos - 1])
                pos--;
        }
        if (pos != j)
            return false;
    }
    return true;
}


void dfs(int s_i, int cnt) {
    // end state
    if (cnt > 3) {
        return;
    }
    if (isCorrectLadder()) {
        ans = min(ans, cnt);
        return;
    }
    // recursive
    for (int i = s_i; i <= H; i++) {
        for (int j = 1; j <= N; j++) {
            if (isValidLadder(i, j)) {
                board[i][j] = true;
                dfs(i, cnt + 1);
                board[i][j] = false;
            }
        }
    }
}
~~~

## 문제 후 느낀점
- dfs 변형 문제
