#include <iostream>
#include <algorithm>
using namespace std;

const int H_MAX = 30 + 2;
const int N_MAX = 10 + 2;

int N, M, H;
bool board[H_MAX][N_MAX];
int ans = 4;

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

}

int main(int argc, const char* argv[]) {
    int a, b;

    // input
    cin >> N >> M >> H;
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &a, &b);
        board[a][b] = true;
    }

    // solution
    dfs(1, 0);

    // output
    if (ans == 4)
        cout << "-1\n";
    else
        cout << ans << "\n";

    return 0;
}
