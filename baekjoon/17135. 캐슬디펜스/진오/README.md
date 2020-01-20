# 캐슬디펜스


## 풀이과정

1. 조합으로 궁수가 위치하는곳 선정한다
2. 궁수마다 가까운곳 제거한다. 여기서 주의할점이 둘다가까울때 왼쪽에있는 적을 제거한다.
   * 처음 구현할 때 왼쪽에 있는 적을 고려하는 것을 같은 row 에 있을 때만 고려하여 j=0; j<row_size;j++   if(min>temp) 를 통해 구현하여 오답이 났었다.
   * 더 가까운 row 일 지라도 col 값에 따라 거리가 같을 수 있기 때문에 if(min==temp && col>j) 인 경우도 고려해야 한다.

~~~C++
// 궁수의 위치 조합
void Comb(int now, int count, int archer, vector <int> combo) { 
	int temp;
	if (count == 3) {
		temp=BruteForce_kill(combo);
		if (max_kill < temp) {
			max_kill = temp;
		}
		rollback_arr();	
		return;
	}
	for (int i = now + 1; i <= archer; i++) {
		combo.push_back(i); // 일단 이자리를 대상으로 조합을 구할거다!
		Comb(i, count + 1, archer, combo); //다음 자리로 넘어간다.
		combo.pop_back();
		count = combo.size();
	}
}

// 가장 가까운 적 쏘기

void shoot(int archer,int *row, int *col) { // 쏠 위치를 row col 에 저장해서 보내자
	
	int min = MAX;
	int temp=0;
	int flag = 0;

	*row = -1;// 없는경우를 가정
	*col = -1;
	
	for (int i = row_siz-1; i>= 0; i--) { // 0부터 배열 시작
		for (int j = 0; j < col_siz; j++) {
			if (arr[i][j] > 0) {
				temp = abs(i - row_siz) + abs(j - archer);
				if (min > temp&&temp<=range) {
					min = temp;
					*row = i;
					*col = j;
				}
				else if (min == temp && temp <= range && (*col) > j) {
					*row = i;
					*col = j;
				}
			}
		}
		if (range < row_siz - i) { // 직선조차 초과해버리면 더이상 돌릴 이유 없음
			break;
		}
	}
}
~~~