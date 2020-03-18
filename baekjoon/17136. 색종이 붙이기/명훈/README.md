# 17136. 색종이 붙이기

## 문제 알고리즘
- 브루트 포스

## 풀이방법
1. dfs를 통한 탐색
2. 색종이 크기안에 빈칸(0)이 있는 경우나 색종이를 잘 붙인 경우는 효율적으로 다음 dfs를 설정한다.

- 핵심 코드
~~~c++
void dfs(int y, int x){
	// if line is end
	if (x == MAX) {
		dfs(y + 1, 0);
		return;
	}
	// end state
	if (y == MAX) {
		answer = min(answer, cnt);
		return;
	}
	// if board is empty, check the next position
	if (board[y][x] == 0) {
		dfs(y, x + 1);
		return;
	}

	// check all possibility (loop : len 5 -> 1)
	for (int l = 5; l >= 1; l--) {
		if (confetti[l] == 0 || y + l > MAX || x + l > MAX)
			continue;
		
		bool flag = false;
		for (int i = y; i < y + l; i++){
			for (int j = x; j < x + l; j++){
				if (board[i][j] == 0) {
					flag = true;
					break;
				}
			}
			if (flag == true)
				break;
		}
		if (flag == true)
			continue;

		confetti[l]--;
		cnt++;
		for (int i = y; i < y + l; i++)
			for (int j = x; j < x + l; j++)
				board[i][j] = 0;

		dfs(y, x + l);

		for (int i = y; i < y + l; i++)
			for (int j = x; j < x + l; j++)
				board[i][j] = 1;
		cnt--;
		confetti[l]++;
	}
}


~~~


### 

