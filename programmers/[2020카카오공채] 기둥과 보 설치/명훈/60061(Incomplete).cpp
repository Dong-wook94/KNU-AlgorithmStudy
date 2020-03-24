#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

#define MAX 100 + 1
#define PILLAR  0
#define FLOOR   1
#define BOTH    2

int board[MAX][MAX];
pair<int, int> dir[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

bool isInRange(int y, int x, int n) {
    if (y < 0 || y > n || x < 0 || x > n)
        return false;
    return true;
}

// 건설 가능한지 확인
bool isValidBuild(int n, int x, int y, int btype) {
    if (btype == FLOOR) {     // "보"
        // 보의 왼쪽이나 오른쪽 둘 중에 하나라도 기둥인 경우
        if ((y >= 1 && board[y - 1][x] % 2 == PILLAR) || (isInRange(y - 1, x + 1, n) && board[y - 1][x + 1] % 2 == PILLAR))
            return true;
        // 보의 양쪽이 보인 경우
        if ((x >= 1 && board[y][x - 1] >= FLOOR) && (x < n && board[y][x + 1] >= FLOOR))
            return true;
        // 그 외에는 항상 거짓
        return false;
    }
    else {                   // "기둥"
        // 기둥이 바닥에 있는 경우
        if (y == 0)
            return true;
        // 기둥의 아래가 보인 경우
        if (board[y][x] >= FLOOR || (x >= 1 && board[y][x - 1] >= FLOOR))
            return true;
        // 기둥의 아래가 기둥인 경우
        if (y >= 1 && board[y - 1][x] % 2 == PILLAR)
            return true;
        // 그 외에는 항상 거짓
        return false;
    }
}

// 삭제 가능한지 확인 후 삭제
void BuildDelete(int n, int x, int y, int btype) {
    if (btype == FLOOR) {     // "보"
        int tmp = board[y][x];  // 현재 상태 잠시 보관하고
        if (tmp == BOTH)        // 없었던 상태로 가정하고
            board[y][x] = PILLAR;
        else if (tmp == FLOOR && btype == FLOOR)
            board[y][x] = -1;
        else
            return;
        // 보의 왼쪽 부분 기준으로 다 확인
        for (int d = 0; d < 4; d++) {
            int nextY = y + dir[d].first;
            int nextX = x + dir[d].second;
            if (isInRange(nextY, nextX, n) && board[nextY][nextX] != -1) {
                // 그 주변을 다시 만들 수 없다면 종료
                if (board[nextY][nextX] == BOTH) {
                    if (!isValidBuild(n, nextX, nextY, 0) || !isValidBuild(n, nextX, nextY, 0)) {
                        board[y][x] = tmp;
                        return;
                    }
                }
                if (!isValidBuild(n, nextX, nextY, board[nextY][nextX])) {
                    board[y][x] = tmp;
                    return;
                }
            }
        }
        // 보의 오른쪽 부분 기준으로 다 확인
        for (int d = 0; d < 4; d++) {
            int nextY = y + dir[d].first;
            int nextX = x + 1 + dir[d].second;
            if (isInRange(nextY, nextX, n) && board[nextY][nextX] != -1) {
                // 그 주변을 다시 만들 수 없다면 종료
                if (board[nextY][nextX] == BOTH) {
                    if (!isValidBuild(n, nextX, nextY, 0) || !isValidBuild(n, nextX, nextY, 0)) {
                        board[y][x] = tmp;
                        return;
                    }
                }
                if (!isValidBuild(n, nextX, nextY, board[nextY][nextX])) {
                    board[y][x] = tmp;
                    return;
                }
            }
        }
        // 가능하므로 삭제한 부분을 유지해서 return
        return;
    }
    else {               // "기둥"
        int tmp = board[y][x];  // 현재 상태 잠시 보관하고
        if (tmp == BOTH)        // 없었던 상태로 가정하고
            board[y][x] = FLOOR;
        else if (tmp == PILLAR && btype == PILLAR)
            board[y][x] = -1;
        else
            return;
        // 보의 아래쪽 부분 기준으로 다 확인
        for (int d = 0; d < 4; d++) {
            int nextY = y + dir[d].first;
            int nextX = x + dir[d].second;
            if (isInRange(nextY, nextX, n) && board[nextY][nextX] != -1) {
                // 그 주변을 다시 만들 수 없다면 종료
                if (board[nextY][nextX] == BOTH) {
                    if (!isValidBuild(n, nextX, nextY, 0) || !isValidBuild(n, nextX, nextY, 0)) {
                        board[y][x] = tmp;
                        return;
                    }
                }
                if (!isValidBuild(n, nextX, nextY, board[nextY][nextX])) {
                    board[y][x] = tmp;
                    return;
                }
            }
        }
        // 보의 위쪽 부분 기준으로 다 확인
        for (int d = 0; d < 4; d++) {
            int nextY = y + 1 + dir[d].first;
            int nextX = x + dir[d].second;
            if (isInRange(nextY, nextX, n) && board[nextY][nextX] != -1) {
                // 그 주변을 다시 만들 수 없다면 종료
                if (board[nextY][nextX] == BOTH) {
                    if (!isValidBuild(n, nextX, nextY, 0) || !isValidBuild(n, nextX, nextY, 0)) {
                        board[y][x] = tmp;
                        return;
                    }
                }
                if (!isValidBuild(n, nextX, nextY, board[nextY][nextX])) {
                    board[y][x] = tmp;
                    return;
                }
            }
        }
        // 가능하므로 삭제한 부분을 유지해서 return
        return;
    }
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    // solution
    vector<vector<int>> ans;
    memset(board, -1, sizeof(board));
    for (int i = 0; i < build_frame.size(); i++) {
        vector<int> b_l = build_frame[i];

        if (b_l[3] == 1) {        // insert
            if (isValidBuild(n, b_l[0], b_l[1], b_l[2])) {
                if (board[b_l[1]][b_l[0]] == -1)
                    board[b_l[1]][b_l[0]] = b_l[2];
                else if (b_l[2] != board[b_l[1]][b_l[0]])
                    board[b_l[1]][b_l[0]] = 2;      // 겹쳐진 경우
            }
        }
        else {                   // delete
            BuildDelete(n, b_l[0], b_l[1], b_l[2]);
        }
    }

    // make answer
    for (int j = 0; j <= n; j++) {
        for (int i = 0; i <= n; i++) {
            if (board[i][j] != -1) {
                vector<int> ans_line;
                if (board[i][j] == BOTH) {
                    ans_line.push_back(j);
                    ans_line.push_back(i);
                    ans_line.push_back(0);
                    ans.push_back(ans_line);
                    ans_line.clear();
                    ans_line.push_back(j);
                    ans_line.push_back(i);
                    ans_line.push_back(1);
                    ans.push_back(ans_line);
                }
                else {
                    ans_line.push_back(j);
                    ans_line.push_back(i);
                    ans_line.push_back(board[i][j]);
                    ans.push_back(ans_line);
                }
            }
        }
    }
    return ans;
}

int main(int argc, const char* argv[]) {
    //vector<vector<int>> res1 = solution(5, {{1,0,0,1},{1,1,1,1},{2,1,0,1},{2,2,1,1},{5,0,0,1},{5,1,0,1},{4,2,1,1},{3,2,1,1}});
    //for(int i=0; i<res1.size(); i++)
        //printf("%d %d %d\n", res1[i][0], res1[i][1], res1[i][2]);

    vector<vector<int>> res2 = solution(5, { {0,0,0,1},{2,0,0,1},{4,0,0,1},{0,1,1,1},{1,1,1,1},{2,1,1,1},{3,1,1,1},{2,0,0,0},{1,1,1,0},{2,2,0,1} });
    for (int i = 0; i < res2.size(); i++)
        printf("%d %d %d\n", res2[i][0], res2[i][1], res2[i][2]);


    return 0;
}