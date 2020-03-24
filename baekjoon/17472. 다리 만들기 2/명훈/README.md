# 다리만들기2

## 문제 알고리즘
- bfs, MST

## 풀이방법
1. bfs를 통해 각 섬에 번호를 붙인다
2. 완전 탐색을 통해 다리를 만든다.
3. kruskal algorithm을 통한 MST를 만든다.
4. 모두 연결된 경우에 한해서 출력하고 그 외에는 -1을 출력한다.

- 핵심 코드
~~~c++
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
~~~

## 문제 후 느낀점
- 쉬운 문제였으나, 잘못된 부분을 빠르게 잡아내지 못해서 고민이였던 문제.
- 동욱이형의 collapsingFind와 weightedUnion이 맘에 들어서 사용했다.
- 이 문제 덕분에 백준 성공률이 박살이 났다... 

