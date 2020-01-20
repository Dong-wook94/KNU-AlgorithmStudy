# 게리맨더링2

주어진 조건에 맞추어 각 영역을 표시해주는게 중요하다.

~~~c++
// x, y, d1, d2를 뽑는 경우를 4중 for 문으로 구한뒤 각 case 마다 div_sect 를 진행, min 을 구한다
for (int x = 1; x <= arr_siz; x++) {
		for (int y = 1; y <= arr_siz; y++) {
			for (int d1 = 1; d1 < arr_siz; d1++) {
				for (int d2 = 1; d2 < arr_siz; d2++) {
					if (x + d1 + d2 <= arr_siz && y + d2 <= arr_siz&&y-d1>=1) {
						div_sect(x, y, d1, d2);
						temp = solv_min();
						if (min_popul > temp) {
							min_popul = temp;
					}
				}
			}
		}
	}
}

// 각 값이 주어졌을 때 구역을 나누어 주는 함수
void div_sect(int x,int y,int d1, int d2) {
	initial_back();
	//1구역
	for (int i = 1; i < x + d1; i++) {
		조건
	}
	//2구역
	for (int i = 1; i <= x + d2; i++) {
		조건
	}
	//3구역
	for (int i = x+d1; i <= arr_siz; i++) {
		조건
	}
	//4구역
	for (int i = x+d2+1; i <=arr_siz; i++) {
		조건
	}
	for (int i = 1; i <= arr_siz; i++) {
		나머지
	}
	//현재상태가 0이면 5로 하자
}
~~~