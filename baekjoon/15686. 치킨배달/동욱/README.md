# 15686. 치킨배달

> 조합을 통한 치킨집 선택후 최단거리 최신화, 브루트포스문제, 삼성 기출문제



## 풀이과정

1. 치킨집을 고른다.(조합)
2. 치킨집에서 최단 거리를 구한다.()
3. 그중 최솟값을 구한다.



## 조합 코드 

~~~c++
void comb() {
	//마스킹용 벡터를 만들어 조합구현
	for (int i = 0; i < chickens.size()-M; i++)
		Select.push_back(0);
	for (int i = 0; i < M; i++)//선택된집은 1, M개 삽입
		Select.push_back(1);
	do {
		choiced.clear();
		for (int i = 0; i < Select.size(); i++) {
			if (Select[i] == 1)//선택된 치킨집은 choiced vector에 삽입
				choiced.push_back(chickens[i]);
		}
		min_distance = min(min_distance, cal_distance());
		
	} while (next_permutation(Select.begin(), Select.end()));
}
~~~





문제 링크 : https://www.acmicpc.net/problem/15686



