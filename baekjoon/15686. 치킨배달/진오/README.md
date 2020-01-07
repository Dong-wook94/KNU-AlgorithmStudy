# 15686. 치킨배달

> 조합을 통한 치킨집 선택후 최단거리 최신화, 브루트포스문제, 삼성 기출문제



## 풀이과정

1. 치킨집을 고른다.(조합)
2. 치킨집에서 최단 거리를 구한다.()
3. 그중 최솟값을 구한다.


## 사용 함수

bool CompareLocation(const location &x, const location &y);
// sort 나 next permutation 을 사용하기 위한 Comp 함수를 임의로 customizing 함

void Comb( int now, int count, vector<location> chicken, vector <location> combo);
// 현재 vector의 index, 현재뽑은 조합의 수, chicken 집의 좌표가 들어가있는 vector, N개를 뽑는 조합을 넣을 vector
//  변수를 통해 , Recursive Algorithm 으로 조합을 추출

int BruteForce_dist(vector<location> combo);
// N개를 뽑은 조합을 대상으로 치킨 거리를 구해준다.
// chicken Combination n 개의 예시 대상으로 해당 함수 실행

int min_distance(int row, int col, vector<location>combo);
// 집의 좌표가 주어졌을 경우, 가장 짧은 치킨 집까지의 거리를 구해줌
// BruteForce_dist 에 사용된다.

## 조합 코드 

~~~c++
void Comb(int now,int count,vector<location> chicken,vector <location> combo) { 
// now 는 지금 까지뽑은 배열위치, count 는 몇개 뽑았는지, chicken 은 현재 좌표가 들어가있는 곳, 조합된 좌표를 위해 combi 라는 vector 를 하나 더 만듬.
	
	if (count == max_chick) {
		for (auto it = combo.begin(); it != combo.end(); it++) {
			cout << "(" << (*it).row << ",";
			cout << (*it).col << ") ";
		}
		cout << "\n";
		if (min_dist > BruteForce_dist(combo)){
			min_dist = BruteForce_dist(combo);
			min_combo = combo;
		}
		return;
	}
	for (int i = now+1; i < chicken.size(); i++) {
			combo.push_back(chicken[i]); // 일단 이자리를 대상으로 조합을 구할거다!
			Comb(i, count + 1, chicken, combo); //다음 자리로 넘어간다.
			combo.pop_back();
			count = combo.size();
	}
}
~~~





문제 링크 : https://www.acmicpc.net/problem/15686



