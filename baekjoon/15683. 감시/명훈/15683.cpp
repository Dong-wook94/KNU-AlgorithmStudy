#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX 8

// y--, x++, y++, x--
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

int main(int argc, const char * argv[]) {
    // input
    cin >> N >> M;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            scanf("%d", &board[i][j]);
            if(board[i][j] > 0 && board[i][j] < 6)
                camera.push_back({i, j});
            switch (board[i][j]) {
                case 1:
                    visited[i][j][0] = true;
                    break;
                case 2:
                    visited[i][j][0] = true;
                    visited[i][j][2] = true;
                    break;
                case 3:
                    visited[i][j][0] = true;
                    visited[i][j][1] = true;
                    break;
                case 4:
                    visited[i][j][0] = true;
                    visited[i][j][1] = true;
                    visited[i][j][2] = true;
                    break;
                case 5:
                    visited[i][j][0] = true;
                    visited[i][j][1] = true;
                    visited[i][j][2] = true;
                    visited[i][j][3] = true;
                    break;
            }
        }
    }
    
    // solution
    cpyBoard();
    dfs(0);
    
    // output
    cout << ans << "\n";
    
    return 0;
}
