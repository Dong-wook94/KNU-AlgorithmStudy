#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

#define MAX 100
struct line {
	int from;
	int to;
	int weight;
};

struct position {
	int row;
	int col;
};

vector <line> edge;
vector <line> answer_edge;
int parent[MAX];
//F 는 출력한 횟수로 하자

int F = 0;
void initial(int n);
void kruskal(int n, int m);
int col_find(int n);
void weighted_union(int i, int j);
void bfs(int row, int col, int number);
void make_bridge();
void find_island(int row, int col);
bool Comp(line a, line b);

int arr[MAX][MAX];
int visit[MAX][MAX];
queue <position> q;
int row_siz;
int col_siz;

int main() {

	int number = 1;
	int sum=0;
	cin >> row_siz;
	cin >> col_siz;

	for (int i = 0; i < row_siz; i++) {
		for (int j = 0; j < col_siz; j++) {
			cin >> arr[i][j];
			visit[i][j] = arr[i][j];
		}
	}

	//n 은 버텍스 갯수
	//m 은 edge 갯수
	//kruskal(n, m);
	for (int i = 0; i < row_siz; i++) {
		for (int j = 0; j < col_siz; j++) {
			if (visit[i][j] == 1) {
				bfs(i, j, number);
				number++;
			}
		}
	}
	make_bridge();
	sort(edge.begin(), edge.end(), Comp);
	kruskal(number, edge.size());
	for (int i = 0; i < answer_edge.size(); i++)
	{
		sum+=answer_edge[i].weight;
	}
	if (sum == 0) {
		cout << -1;
	}
	else
		cout << sum;
	
	return 0;
}

void kruskal(int n, int m) {

	int edge_count = 0;
	line next_edge;
	int from_ver;
	int to_ver;
	int find_i;
	int find_j;
	line temp;
	
	F = 0;
	initial(n);

	while (1) {
		if (edge_count >= m) {
			break;
		} // edgecount 검사
		next_edge = edge[edge_count];

		edge_count++;//e= next_edge;
		
		
		
		from_ver = next_edge.from;

		to_ver = next_edge.to; //(i,j)=e;

		find_i = col_find(from_ver);

		find_j = col_find(to_ver);

		if (find_i != find_j) {

			weighted_union(find_i, find_j);

			//COUT 해야됨 하거나 vector 에 쌓아놓거나
			temp.from = from_ver;
			temp.to = to_ver;
			temp.weight = next_edge.weight;
			answer_edge.push_back(temp);
			F++;
		}
		if (F>(n - 1)) {
			break;
		}
	}
}

int col_find(int n) {
	int r;
	int s;

	for (r = n; parent[r] >= 0; r = parent[r]);
	while (n != r) {
		s = parent[n];
		parent[n] = r;
		n = s;
	}
	return r;

}
void weighted_union(int i, int j) {
	int temp = parent[i] + parent[j];
	if (parent[i]>parent[j]) {
		parent[i] = j;
		parent[j] = temp;
	}
	else {
		parent[j] = i;
		parent[i] = temp;
	}
}

void initial(int n) {
	int i;
	for (i = 0; i<n; i++) {
		parent[i] = -1;
	}
}
void bfs(int row, int col,int number) {
	position start;
	start.row = row;
	start.col = col;
	q.push(start);
	visit[start.row][start.col] = 0; //0을 지나간걸로하자
	arr[start.row][start.col] = number;
	while (!q.empty()) {
		position temp = q.front();
		position push_temp;
		//push 할때 집어넣을것
		q.pop();
		if (temp.row + 1 < row_siz) {
			if (visit[temp.row + 1][temp.col] != 0) {
				push_temp.row = temp.row + 1;
				push_temp.col = temp.col;
				visit[push_temp.row][push_temp.col] = 0;
				arr[push_temp.row][push_temp.col] = number;
				q.push(push_temp);
			}
		}
		if (temp.col + 1 < col_siz) {
			if (visit[temp.row][temp.col+1] != 0) {
				push_temp.col = temp.col + 1;
				push_temp.row = temp.row;
				visit[push_temp.row][push_temp.col] = 0;
				arr[push_temp.row][push_temp.col] = number;
				q.push(push_temp);
			}
		}
		if (temp.row - 1 >= 0) {
			if (visit[temp.row - 1][temp.col] != 0) {
				push_temp.row = temp.row - 1;
				push_temp.col = temp.col;
				visit[push_temp.row][push_temp.col] = 0;
				arr[push_temp.row][push_temp.col] = number;
				q.push(push_temp);
				
			}
		}
		if (temp.col -1 >= 0) {
			if (visit[temp.row][temp.col - 1] != 0) {
				push_temp.col = temp.col - 1;
				push_temp.row = temp.row;
				visit[push_temp.row][push_temp.col] = 0;
				arr[push_temp.row][push_temp.col] = number;
				q.push(push_temp);
			}
		}
	}
}
void make_bridge() {

	for (int i = 0; i < row_siz; i++) {
		for (int j = 0; j < col_siz; j++) {
			if (arr[i][j] != 0) {
				find_island(i, j);
			}
			// 0과 자기들 빼고 가장 먼저닿는 숫자 찾기
		}
	}
}
void find_island(int row, int col) {
	int weight = 0;
	int k;
	line temp;
	for (int i = row+1; i < row_siz; i++) {
		if (arr[i][col] == arr[row][col]) {
			break;
		}
		if (arr[i][col] != 0) {
			weight = i - (row + 1);
			if (weight >= 2) {
				for (k = 0; k < edge.size(); k++) {
					if (edge[k].from == arr[i][col] && edge[k].to == arr[row][col]) {
						if (edge[k].weight > weight) {
							edge[k].weight = weight;
						}
						break;
					}
					else if (edge[k].to == arr[i][col] && edge[k].from == arr[row][col]) {
						if (edge[k].weight > weight) {
							edge[k].weight = weight;
						}
						break;
					}
				}
				if (k == edge.size()) {
					if (arr[i][col] > arr[row][col]) {
						temp.from = arr[row][col];
						temp.to = arr[i][col];
						temp.weight = weight;
					}
					else {
						temp.to = arr[row][col];
						temp.from = arr[i][col];
						temp.weight = weight;
					}
					edge.push_back(temp);
				}
			}
			//여기선 k 가 size 보다 클경우 즉 없을경우만 다뤄주면 될듯
			break;
		}
	}
	for (int i = row-1; i >= 0; i--) {
		if (arr[i][col] == arr[row][col]) {
			break;
		}
		if ( arr[i][col] != 0) {
			weight = row-(i+1);
			if (weight >= 2) {
				for (k = 0; k < edge.size(); k++) {
					if (edge[k].from == arr[i][col] && edge[k].to == arr[row][col]) {
						if (edge[k].weight > weight) {
							edge[k].weight = weight;
						}
						break;
					}
					else if (edge[k].to == arr[i][col] && edge[k].from == arr[row][col]) {
						if (edge[k].weight > weight) {
							edge[k].weight = weight;
						}
						break;
					}
				}
				if (k == edge.size()) {
					if (arr[i][col] > arr[row][col]) {
						temp.from = arr[row][col];
						temp.to = arr[i][col];
						temp.weight = weight;
					}
					else {
						temp.to = arr[row][col];
						temp.from = arr[i][col];
						temp.weight = weight;
					}
					edge.push_back(temp);
				}
			}
			break;
		}
	}
	for (int j = col+1; j < col_siz; j++) {
		if (arr[row][j] == arr[row][col]) {
			break;
		}
		if (arr[row][j] != 0) {
			weight = j - (col + 1);
			if (weight >= 2) {
				for (k = 0; k < edge.size(); k++) {
					if (edge[k].from == arr[row][j] && edge[k].to == arr[row][col]) {
						if (edge[k].weight > weight) {
							edge[k].weight = weight;
						}
						break;
					}
					else if (edge[k].to == arr[row][j] && edge[k].from == arr[row][col]) {
						if (edge[k].weight > weight) {
							edge[k].weight = weight;
						}
						break;
					}
				}
				if (k == edge.size()) {
					if (arr[row][j] > arr[row][col]) {
						temp.from = arr[row][col];
						temp.to = arr[row][j];
						temp.weight = weight;
					}
					else {
						temp.to = arr[row][col];
						temp.from = arr[row][j];
						temp.weight = weight;
					}
					edge.push_back(temp);
				}
			}
			break;
		}
	}
	for (int j = col-1; j >= 0; j--) {
		if (arr[row][j] == arr[row][col]) {
			break;
		}
		if ( arr[row][j] != 0) {
			weight = col-(j+1);
			if (weight >= 2) {
				for (k = 0; k < edge.size(); k++) {
					if (edge[k].from == arr[row][j] && edge[k].to == arr[row][col]) {
						if (edge[k].weight > weight) {
							edge[k].weight = weight;
						}
						break;
					}
					else if (edge[k].to == arr[row][j] && edge[k].from == arr[row][col]) {
						if (edge[k].weight > weight) {
							edge[k].weight = weight;
						}
						break;
					}
				}
				if (k == edge.size()) {
					if (arr[row][j] > arr[row][col]) {
						temp.from = arr[row][col];
						temp.to = arr[row][j];
						temp.weight = weight;
					}
					else {
						temp.to = arr[row][col];
						temp.from = arr[row][j];
						temp.weight = weight;
					}
					edge.push_back(temp);
				}
			}
			break;
		}
	}
}
bool Comp(line a, line b) {

	if (a.weight == b.weight) {
		return a.from<b.from;
	}
	else {
		return a.weight < b.weight;
	}

}


