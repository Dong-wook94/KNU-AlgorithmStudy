#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX 100
#define K_MAX 6 + 1

pair<int, int> dir[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
int N, M, label = 0;
int board[MAX][MAX];
bool visited[MAX][MAX];
int k_board[K_MAX][K_MAX];
int parent[K_MAX];
vector<pair<int, pair<int, int>>> graph;
int answer = 0;

void bfs(int y, int x, int label) {
    queue<pair<int, int>> q;
    q.push({ y, x });
    board[y][x] = label;
    visited[y][x] = true;

    while (!q.empty()) {
        int curY = q.front().first;
        int curX = q.front().second;
        q.pop();
        for (int d = 0; d < 4; d++) {
            int nextY = curY + dir[d].first;
            int nextX = curX + dir[d].second;
            if (0 <= nextY && nextY < N && 0 <= nextX && nextX < M) {
                if (!visited[nextY][nextX] && board[nextY][nextX]) {
                    q.push({ nextY, nextX });
                    board[nextY][nextX] = label;
                    visited[nextY][nextX] = true;
                }
            }
        }
    }
}

void make_bridge(int y, int x) {
    int graph_id = board[y][x];
    for (int d = 0; d < 4; d++) {
        int cnt = 0;
        while (true) {
            int nextY = y + dir[d].first * (cnt + 1);
            int nextX = x + dir[d].second * (cnt + 1);

            if (0 > nextY || nextY >= N || 0 > nextX || nextX >= M)
                break;
            else if (board[nextY][nextX] == graph_id)
                break;
            else if (board[nextY][nextX] == 0) {
                cnt++;
                continue;
            }
            else {
                if (cnt >= 2) {
                    int graph_id2 = board[nextY][nextX];
                    if (k_board[graph_id][graph_id2]) {
                        k_board[graph_id][graph_id2] = min(cnt, k_board[graph_id][graph_id2]);
                        k_board[graph_id2][graph_id] = min(cnt, k_board[graph_id][graph_id2]);
                    }
                    else {
                        k_board[graph_id][graph_id2] = cnt;
                        k_board[graph_id2][graph_id] = cnt;
                    }
                }
                break;
            }
        }
    }
}

int collapsingFind(int n) {
    int root;
    for (root = n; parent[root] >= 1; root = parent[root]);
    for (int i = n; i != root; i = parent[i])
        parent[i] = root;
    return root;
}

void weightedUnion(int i, int j) {
    int temp = parent[i] + parent[j];
    if (parent[i] > parent[j]) {
        parent[i] = j;
        parent[j] = temp;
    }
    else {
        parent[j] = i;
        parent[i] = temp;
    }
}

void kruskal() {
    for (int i = 1; i <= label; i++)
        for (int j = i; j <= label; j++)
            if (k_board[i][j])
                graph.push_back(make_pair(k_board[i][j], make_pair(i, j)));
    sort(graph.begin(), graph.end());
    for (int i = 1; i <= label; i++)
        parent[i] = -1;
    for (int i = 0; i < graph.size(); i++) {
        int p = collapsingFind(graph[i].second.first);
        int q = collapsingFind(graph[i].second.second);
        if (p != q) {
            weightedUnion(p, q);
            answer += graph[i].first;
        }
    }
}

bool isAllConnected() {
    bool flag = false;
    for (int i = 1; i <= label; i++) {
        if (parent[i] == -1)
            return false;
        if (parent[i] < -1) {
            if (flag)   // 제일 큰 부모는 하나만 있어야한다.
                return false;
            flag = true;
        }
    }
    return true;
}

int main(int argc, const char* argv[]) {
    // input
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            scanf("%d", &board[i][j]);

    // solution 1 - bfs
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (!visited[i][j] && board[i][j]) {
                label++;
                bfs(i, j, label);
            }
    // solution 2 - make bridge
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (board[i][j])
                make_bridge(i, j);
    // solution 3 - kruskal
    kruskal();

    // output
    if (isAllConnected())
        cout << answer << "\n";
    else
        cout << "-1\n";

    return 0;
}
