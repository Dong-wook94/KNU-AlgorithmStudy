# 14500.테트로미노

> 삼성 SW 기출문제

### 풀이방법

![img](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/14500/1.png)

위의 도형중에 `ㅜ `모양의 도형을 제외하고는 dfs를 통해 모양을 만들수 있다. 

따로구분할 필요없이 dfs를 통해 방문했던곳만 다시 안방문하도록 하면 저모양들이 생긴다.

~~~c++
void dfs(int row,int col,int block_cnt,int sum) {
	if (block_cnt == 3) {
		max_sum = max(sum, max_sum);
		return;
	}
	visited[row][col] = 1;
	for (int d = 0; d < 4; d++) {
		int next_row = row + dir_row[d];
		int next_col = col + dir_col[d];

		if (next_row >= 0 && next_col >= 0 && next_row < row_size&&next_col < col_size) {
			if (visited[next_row][next_col] == 0) {
				dfs(next_row, next_col, block_cnt + 1, sum + map[next_row][next_col]);
			}
		}
	}
	visited[row][col] = 0;
}
~~~



하지만 `ㅜ`모양의 도형은 dfs로 만들수 없기 때문에  ㅏ,ㅓ,ㅗ,ㅜ 모양으로 한번씩 다 일일히 돌린다.

~~~c++
void exception_shape() {
	for (int i = 0; i < row_size - 2; i++) {

		for (int j = 0; j < col_size - 1; j++) {
			sum = 0;
			sum += map[i][j];
			sum += map[i + 1][j];
			sum += map[i + 2][j];
			sum += map[i + 1][j + 1];
			max_sum = max(sum, max_sum);//ㅏ
			sum = 0;
			sum += map[i + 1][j];
			sum += map[i][j + 1];
			sum += map[i + 1][j + 1];
			sum += map[i + 2][j + 1];
			max_sum = max(sum, max_sum);//ㅓ
		}
	}
	for (int i = 0; i < row_size - 1; i++) {

		for (int j = 0; j < col_size - 2; j++) {
			sum = 0;
			sum += map[i][j + 1];
			sum += map[i + 1][j];
			sum += map[i + 1][j + 1];
			sum += map[i + 1][j + 2];
			max_sum = max(sum, max_sum);//ㅗ
			sum = 0;
			sum += map[i][j];
			sum += map[i][j + 1];
			sum += map[i][j + 2];
			sum += map[i + 1][j + 1];
			max_sum = max(sum, max_sum);//ㅜ
		}
	}
}
~~~



이렇게 다돌려서 max_sum을 구하면 된다. 