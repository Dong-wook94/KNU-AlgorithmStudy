#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX 12 + 1
struct knight_pos {
    int y;
    int x;
    int dir;
};

pair<int, int> dir[5] = { {0, 0}, {0, 1},{0, -1},{-1, 0},{1, 0} };
int N, K;
int board[MAX][MAX];
vector<int> order[MAX][MAX];
vector<knight_pos> knight;

bool isInRange(int y, int x) {
    if (y >= 1 && y <= N && x >= 1 && x <= N)
        return true;
    return false;
}

int main(int argc, const char* argv[]) {
    // input
    int r, c, d;
    cin >> N >> K;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            scanf("%d", &board[i][j]);
    for (int i = 0; i < K; i++) {
        scanf("%d %d %d", &r, &c, &d);
        knight.push_back({ r, c, d });
        order[r][c].push_back(i);
    }

    // solution
    int turn = 0;
    while (true) {
        if (turn > 1000)
            break;
        turn++;
        for (int i = 0; i < K; i++) {
            int curY = knight[i].y;
            int curX = knight[i].x;
            int nextY = curY + dir[knight[i].dir].first;
            int nextX = curX + dir[knight[i].dir].second;

            // 다음칸이 나가는 경우이거나 파란색인 경우
            if (!isInRange(nextY, nextX) || board[nextY][nextX] == 2) {
                if (knight[i].dir == 1 || knight[i].dir == 2)    // 순서바꾸기
                    knight[i].dir = 3 - knight[i].dir;
                else
                    knight[i].dir = 7 - knight[i].dir;
                nextY = curY + dir[knight[i].dir].first;
                nextX = curX + dir[knight[i].dir].second;
            }

            // 다음칸이 나가거나 파란색인 경우, 다시
            if (!isInRange(nextY, nextX) || board[nextY][nextX] == 2)
                continue;
            else if (board[nextY][nextX] == 0) {  // 하얀색
                int idx = -1;
                for (int j = 0; j < order[curY][curX].size(); j++) {
                    int t = order[curY][curX][j];
                    if (t == i)
                        idx = j;
                    if (idx == -1) continue;     // 없는 경우

                    knight[t].y = nextY;
                    knight[t].x = nextX;
                    order[nextY][nextX].push_back(t);
                    if (order[nextY][nextX].size() >= 4) {
                        cout << turn << "\n";
                        return 0;
                    }
                }
                int cnt = (int)order[curY][curX].size();
                for (int j = idx; j < cnt; j++)
                    order[curY][curX].pop_back();
            }
            else {                               // 빨간색
                int idx = -1;
                for (int j = (int)order[curY][curX].size() - 1; j >= 0; j--) {
                    int t = order[curY][curX][j];
                    if (t == i) {
                        idx = j;
                        break;
                    }
                }
                for (int j = (int)order[curY][curX].size() - 1; j >= idx; j--) {
                    int t = order[curY][curX][j];
                    knight[t].y = nextY;
                    knight[t].x = nextX;
                    order[nextY][nextX].push_back(t);
                    if (order[nextY][nextX].size() >= 4) {
                        cout << turn << "\n";
                        return 0;
                    }
                }
                int cnt = (int)order[curY][curX].size();
                for (int j = idx; j < cnt; j++)
                    order[curY][curX].pop_back();
            }
        }
    }
    cout << "-1\n" << "\n";

    return 0;
}
