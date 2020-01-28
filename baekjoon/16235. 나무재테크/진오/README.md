# 나무재테크

☘️ 로봇이 뿌리는 비료 판, 나무 판, 현재 비료상황 세가지 이차원배열을 사용한다

나무 판은 2차원 배열에 각 원소마다 vector <int> 의 자료형을 갖도록 하여 같은지역에 여러 나무가 쌓일 수 있도록 한다.
(C 로 구현할 경우 각 위치마다 트리의 갯수를 보관하거나, 링크드 리스트로 구현해야 할 것 같다.)

사실 봄,여름이 제일 어렵다
나무 밥먹고, 밥못먹으면 죽는 거까지 구현한다면 별로 어렵지 않을 것

~~~C++
void eating_food(int i, int j) {
	int k;
	sort(tree[i][j].begin(), tree[i][j].end());
	for ( k = 0; k < tree[i][j].size(); k++) { // k 는 현재 어느것 까지먹었는지 나타냄
		if (map[i][j] - tree[i][j][k] >= 0) {
			map[i][j] = map[i][j] - tree[i][j][k];
			tree[i][j][k]++;
		}
		else {
			break;
		}
	}
	while (true) {
		if (tree[i][j].size() <= k) // k 보다 떨어져나간 지금이 작거나 같으면 - K갯수 만큼 남기겠다
		{
			break;
		}
		else {
			map[i][j] += tree[i][j].back() / 2;
			tree[i][j].pop_back();
		}
	}
}
~~~