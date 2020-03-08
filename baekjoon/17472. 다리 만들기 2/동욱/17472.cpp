#include <stdio.h>
#include <queue>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
int Map[10][10];
int visited[10][10];
int graph[11][11];
typedef struct Graph {
	int src, dest, value;
	Graph() {}
	Graph(int s, int d, int v) {
		src = s;
		dest = d;
		value = v;
	}
};
vector<Graph> vec_graph;
int N, M;
queue<pair<int, int>> q;

int dir_row[4] = { -1,0,1,0 };
int dir_col[4] = { 0,1,0,-1 };
vector<int> parent;

bool checkRange(int r, int c) {
	if (r >= 0 && c >= 0 && r < N&&c < M)
		return true;
	return false;
}

void bfs(pair<int, int> v, int num_island) {
	q.push(v);
	Map[v.first][v.second] = num_island;
	while (!q.empty()) {
		v = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int next_row = v.first + dir_row[i];
			int next_col = v.second + dir_col[i];
			if (checkRange(next_row, next_col) && Map[next_row][next_col] < 0) {
				Map[next_row][next_col] = num_island;
				q.push(make_pair(next_row, next_col));
			}
		}
	}
}

void updateMinDistOfBridge(int a, int b, int &cnt)
{
	if (graph[a][b] == 0)
		graph[a][b] = cnt;
	else {
		graph[a][b] = min(graph[a][b], cnt);
	}
}

void checkBridge() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (Map[i][j] > 0) {
				int src_node = Map[i][j];
				for (int d = 0; d < 4; d++) {
					int cnt = 0;
					while (1) {
						int next_row = i + dir_row[d] * (cnt + 1);
						int next_col = j + dir_col[d] * (cnt + 1);

						if (!checkRange(next_row, next_col))
							break;
						else if (Map[next_row][next_col] == src_node)
							break;
						else if (Map[next_row][next_col] == 0) {
							cnt++;
							continue;
						}
						else {
							if (cnt > 1) {//최소길이 2이상
								int dest_node = Map[next_row][next_col];
								//작 -> 큰
								if (src_node < dest_node) {
									updateMinDistOfBridge(src_node, dest_node, cnt);
								}
								else {
									updateMinDistOfBridge(dest_node, src_node, cnt);
								}
							}
							break;
						}

					}
				}
			}
		}
	}
}

void initParent(int n) {
	for (int i = 0; i <= n; i++) {
		parent.push_back(-1);
	}
}

int collapsingFind(int n) {
	int root;

	for (root = n; parent[root] >= 1; root = parent[root]) {}

	for (int i = n; i != root; i = parent[i]) {
		parent[i] = root;
	}

	return root;
}

void weightedUnion(int i, int j) {
	int temp;

	temp = parent[i] + parent[j];

	if (parent[i] > parent[j]) {
		parent[i] = j;
		parent[j] = temp;
	}
	else {
		parent[j] = i;
		parent[i] = temp;
	}
}

bool checkAllConnect(int n) {
	int root;
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		if (parent[i] == -1)
			return false;
		if (parent[i] < -1) {
			if (cnt >0)
				return false;
			cnt++;
		}
	}
	return true;
}

bool cmp(const Graph &a, const Graph &b) {
	return a.value < b.value;
}
int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &Map[i][j]);
			if (Map[i][j] == 1)
				Map[i][j] = -1;
		}
	}
	//각섬 구분하기
	int num_island = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {

			if (Map[i][j] < 0) {//음수일때 아직 구분안된섬
				num_island++;
				bfs(make_pair(i, j), num_island);

			}
		}
	}
	checkBridge();
	initParent(num_island);
	int result = 0;
	for (int i = 1; i < num_island; i++) {
		for (int j = i + 1; j <= num_island; j++) {
			if (graph[i][j] > 0) {
				vec_graph.push_back(Graph(i, j, graph[i][j]));
			}
		}
	}
	sort(vec_graph.begin(), vec_graph.end(), cmp);
	for (int i = 0; i < vec_graph.size(); i++) {
		int p = collapsingFind(vec_graph[i].src);
		int q = collapsingFind(vec_graph[i].dest);

		if (p != q) {
			weightedUnion(p, q);
			//printf("%d %d %d\n", vec_graph[i].src, vec_graph[i].dest, vec_graph[i].value);
			result += vec_graph[i].value;
		}
	}

	if (checkAllConnect(num_island)) {
		printf("%d", result);
	}
	else {
		printf("-1\n");
	}
}

