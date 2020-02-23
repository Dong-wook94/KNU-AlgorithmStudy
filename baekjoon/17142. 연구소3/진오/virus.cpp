#include <iostream>
#include <vector>
#include <queue>
#define MAX 51
#define MAX_VALUE 999999
using namespace std;


struct location{
	int row;
	int col;
};

int active_virus;
int something=0;
int min_time= MAX_VALUE;
int flag = 0; // 칸이 가득 꽉찼나?

int arr[MAX][MAX] = { 0, };
int visit[MAX][MAX] = { 0, };
int arr_siz;
void Comb(int now, int count, vector<location> virus, vector <location> combo);
int bfs(vector <location> combo);
void initialized_visit();
void ClearQueue(queue<location> &someQueue);
int main() {
	vector < location> virus;
	location temp;
	vector < location> combo;

	cin >> arr_siz;
	cin >> active_virus;

	for (int i = 0; i < arr_siz; i++) {
		for (int j = 0; j < arr_siz; j++) {
			cin>>arr[i][j];
			if (arr[i][j] >0) {
				something++;// 벽이나 비활성화 virus
				if (arr[i][j] == 2) {
					temp.row = i;
					temp.col = j;
					virus.push_back(temp);
				}
			}
		}
	}
	Comb(-1,0,virus,combo);
	if (min_time == MAX_VALUE) {
		cout << -1;
	}
	else 
		cout << min_time;
}

void Comb(int now, int count, vector<location> virus, vector <location> combo) {

	if (count == active_virus) {
		if (min_time> bfs(combo)) {
			min_time = bfs(combo);
		}
		return;
	}
	for (int i = now + 1; i < virus.size(); i++) {
		combo.push_back(virus[i]); // 일단 이자리를 대상으로 조합을 구할거다!
		Comb(i, count + 1, virus, combo); //다음 자리로 넘어간다.
		combo.pop_back();
		count = combo.size();
	}
}
int bfs(vector <location> combo) {
	queue <location> q;
	queue <location> temp_q;

	location a;
	location temp;
	int time=0;

	while (!combo.empty()) {
		q.push(combo.back());
		combo.pop_back();
	}
	initialized_visit();
	while (!q.empty()) {
		if (flag == arr_siz * arr_siz) {
			return time;
		}
		temp_q = q;
		ClearQueue(q);
		while (!temp_q.empty()) {
			if (flag == arr_siz * arr_siz) {
				break;
			}
			temp = temp_q.front();
			temp_q.pop();
			visit[temp.row][temp.col] = 1;
			//1 ,2 ,0 일때 어떻게 갈지 정해야되고 count 세는거 해놓아야함. 
			a.row = temp.row + 1;
			a.col = temp.col;
			if (a.row < arr_siz&&visit[a.row][a.col] != 1) {
				q.push(a);
				if (visit[a.row][a.col] != 2) {
					flag++;
				}
				visit[a.row][a.col] = 1;
			}
			a.row = temp.row - 1;
			a.col = temp.col;
			if (a.row >= 0 && visit[a.row][a.col] != 1) {
				q.push(a);
				if (visit[a.row][a.col] != 2) {
					flag++;
				}
				visit[a.row][a.col] = 1;
			}
			a.row = temp.row;
			a.col = temp.col + 1;
			if (a.col < arr_siz&&visit[a.row][a.col] != 1) {
				q.push(a);
				if (visit[a.row][a.col] != 2) {
					flag++;
				}
				visit[a.row][a.col] = 1;
				
			}
			a.row = temp.row;
			a.col = temp.col - 1;
			if (a.col >= 0 && visit[a.row][a.col] != 1) {
				q.push(a);
				if (visit[a.row][a.col] != 2) {
					flag++;
				}
				visit[a.row][a.col] = 1;
			}
		}
		time++;
	}

	if (flag == arr_siz * arr_siz) {
		return time;
	}
	else
		MAX_VALUE;
}
void initialized_visit() {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			visit[i][j] = arr[i][j];
		}
	}
	flag = 0;
	flag = something; // 이바이러스 까진 안가도 됨
}

void ClearQueue(queue<location> &someQueue)
{
	queue<location> empty;
	someQueue=empty;
}
