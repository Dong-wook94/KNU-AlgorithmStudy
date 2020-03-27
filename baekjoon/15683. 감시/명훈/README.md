# 감시

## 문제 알고리즘
- dfs

## 풀이방법
1. dfs를 통한 완전탐색
2. 카메라를 다 체크한 경우, 카메라가 보는 위치를 -1로 다 바꾸고 처리한다.

- 핵심 코드
~~~c++
pair<int, int> dir[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int N, M, ans = MAX * MAX;  // input file, Anwser
int board[MAX][MAX];        // input array
int cpyboard[MAX][MAX];     // cpy array
bool visited[MAX][MAX][4];  // visited dir
vector<pair<int, int>> camera;  // camera vector
vector<int> angle;              // check all angle about camera

int getBlindSize(){
    int cnt = 0;
    for(int i=0; i<N; i++)
        for(int j=0; j<M; j++)
            if(cpyboard[i][j] == 0)
                cnt++;
    return cnt;
}

void cpyBoard(){
    for(int i=0; i<N; i++)
        for(int j=0; j<M; j++)
            cpyboard[i][j] = board[i][j];
}

void dfs(int cnt){
    // end state
    if(cnt == camera.size()){
        for(int i=0; i<angle.size(); i++){
            int y = camera[i].first;
            int x = camera[i].second;
            
            for(int j=0; j<4; j++){
                if(visited[y][x][j]){
                    int nextY = y + dir[(angle[i] + j) % 4].first;
                    int nextX = x + dir[(angle[i] + j) % 4].second;
                    
                    while (true) {
                        if(cpyboard[nextY][nextX] == 6)
                            break;
                        if(0 > nextY || nextY >= N || 0 > nextX || nextX >= M)
                            break;
                        if(cpyboard[nextY][nextX] == 0)
                            cpyboard[nextY][nextX] = -1;
                        
                        nextY += dir[(angle[i] + j) % 4].first;
                        nextX += dir[(angle[i] + j) % 4].second;
                    }
                }
            }
        }
        ans = min(ans, getBlindSize());
        cpyBoard();
        return;
    }
    
    // recursive, check 4 dir angle in all camera
    for(int i=0; i<4; i++){
        angle.push_back(i);
        dfs(cnt + 1);
        angle.pop_back();
    }
}
~~~

## 문제 후 느낀점
- 최초 문제를 풀 때, dfs로 문제를 풀었는데 시간초과가 발생했다.
- 다른사람을 통해 문제점을 확인해보니 전체 카메라가 됬는 경우에만 처리를 하는 것을 확인했다.
