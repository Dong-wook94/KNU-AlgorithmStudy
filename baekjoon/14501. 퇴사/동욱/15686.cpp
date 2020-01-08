#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <stdlib.h>
using namespace std;

typedef struct value {
	int x;
	int y;
	int v;
	int ck; // 기본값 0, ck = -1 이면 없어진 값
	value();
	value(int a, int b, int c) { x = a; y = b; v = c; ck = 0; }
}value;

typedef struct circle {
	int num;
	vector<value> v;
	circle(int a) { num = a; }
}circle;

typedef struct command {
	int xi; // xi 배수인 원판을
	int d; // 0(시계) 1(반시계)
	int k; // k칸 돌려!
	command() {}
	command(int a, int b, int c) { xi = a; d = b; k = c; }
}command;

vector<command> cmd;
vector<circle> c;
queue<value> q;
int n, m, t; // 반지름 1~n ,  한 원판에 m개 정수 , t번 회전
int result;
bool check;

bool cmp(value &a, value &b) {
	if (a.y < b.y)
		return true;
	else
		return false;
}

void rotate(int xi, int d, int k) {

	for (int i = xi; i <= n; i++) {
		// 배수인 원판
		if (i%xi == 0) {
			if (d == 0) {
				// 시계방향
				for (int j = 0; j < c[i].v.size(); j++) {
					int cur_y = c[i].v[j].y;
					if (cur_y + k > m) {
						c[i].v[j].y = cur_y + k - m;
					}
					else {
						c[i].v[j].y = cur_y + k;
					}
				}
			}
			else {
				// 반시계방향
				for (int j = 0; j < c[i].v.size(); j++) {
					int cur_y = c[i].v[j].y;
					if (cur_y - k < 1) {
						c[i].v[j].y = m + cur_y - k;
					}
					else {
						c[i].v[j].y = cur_y - k;
					}
				}
			}
			sort(c[i].v.begin(), c[i].v.end(), cmp);
		}
	}

}

void q_erase() {

	while (!q.empty()) {
		value a = q.front();
		if (c[a.x].v[a.y - 1].ck != -1) {
			c[a.x].v[a.y - 1].v = -1; // v값도 -1로 변화시켜버릴거야.. 이거 안하면 나중에..비교할 때 똑같다고 없애버림ㅠ 또라인가봐..
			c[a.x].v[a.y - 1].ck = -1; // ck 값 -1로 바꿔줌 , y값이랑 실제 index랑 1 차이남..구질구질..
			check = true;
		}
		q.pop();
	}

}

void erase() {
	check = false;
	result = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < c[i].v.size(); j++) {
			if (c[i].v[j].ck == 0) {
				if (c[i].v[j].y == 1) {
					if (c[i].v[j].v == c[i].v[j + 1].v) {
						q.push(c[i].v[j]);
					}

					// 히히..인덱스 차이 나는거 못찾는 바보가 여기있넹 실제 인덱스랑 1 차이난다..바보지혜야..
					if (c[i].v[j].v == c[i].v[c[i].v.size() - 1].v) {
						q.push(c[i].v[c[i].v.size() - 1]);
						q.push(c[i].v[j]);
					}
				}
				else if (c[i].v[j].y == m) {
					if (c[i].v[j].v == c[i].v[j - 1].v) {
						q.push(c[i].v[j]);
					}
				}
				else {
					if (c[i].v[j].v == c[i].v[j + 1].v || c[i].v[j].v == c[i].v[j - 1].v) {
						q.push(c[i].v[j]);
					}
				}

				if (c[i].v[j].x == 1) {
					if (c[i].v[j].v == c[i + 1].v[j].v) {
						q.push(c[i].v[j]);
					}
				}
				else if (c[i].v[j].x == n) {
					if (c[i].v[j].v == c[i - 1].v[j].v) {
						q.push(c[i].v[j]);
					}
				}
				else {
					if (c[i].v[j].v == c[i - 1].v[j].v || c[i].v[j].v == c[i + 1].v[j].v) {
						q.push(c[i].v[j]);
					}
				}
			}

		}
	}

	q_erase();

	int sum = 0;
	int count = 0;

	if (check == false) {
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < c[i].v.size(); j++) {
				if (c[i].v[j].ck == 0) {
					sum += c[i].v[j].v;
					count += 1;
				}
			}
		}

		double avg = (double)sum / count;
		//printf("avg : %f \n",avg);
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < c[i].v.size(); j++) {
				if (c[i].v[j].ck == 0) {
					if (c[i].v[j].v > avg) c[i].v[j].v -= 1;
					else if (c[i].v[j].v == avg) c[i].v[j].v += 0;
					else c[i].v[j].v += 1;
					result += c[i].v[j].v;
				}
			}
		}
	}
	else {
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < c[i].v.size(); j++) {
				if (c[i].v[j].ck == 0) {
					result += c[i].v[j].v;
				}
			}
		}
	}
}

int main() {

	scanf("%d %d %d", &n, &m, &t);

	//원판 개수만큼 circle 배열 초기화
	for (int i = 0; i <= n; i++) {
		c.push_back(circle(i));
	}

	// 원판에 들어있는 숫자 배열에 넣기
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int cur;
			scanf("%d", &cur);
			c[i].v.push_back(value(i, j, cur));
		}
	}

	for (int i = 0; i < t; i++) {
		int l, m, n;
		scanf("%d %d %d", &l, &m, &n);
		cmd.push_back(command(l, m, n));
	}

	for (int i = 0; i < cmd.size(); i++) {
		rotate(cmd[i].xi, cmd[i].d, cmd[i].k);
		erase();
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < m; j++) {
				printf("%d ", c[i].v[j].v);
			}
			printf("\n");
		}
		printf("%d\n", result);
	}


	return 0;
}