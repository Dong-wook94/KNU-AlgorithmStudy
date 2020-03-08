# 주사위 윷놀이



## 풀이과정

#### 맵형성

맵을 형성하는 부분에서 실수가 일어났는데 너무 발견하는데 오래걸렸다.

규칙적인부분과 불규칙적인 부분이 있어서

~~~c++
int Map[4][22] = { {},
{ 10,13,16,19,25,30,35,40},
{20,22,24,25,30,35,40},
{30,28,27,26,25,30,35,40} };

void makeMap() {
	//일반경로
	for (int i = 0; i <= 20; i++) {
		Map[0][i] = i * 2;
	}
}
~~~

일반적인 경로는 for문을 통해 나머지는 그냥 다 직접 기입했다.

근데 저기서 중간에 하나를 빠뜨려서 고생을좀 했다.

#### 나머지 로직

맵을 형성한후에는

1. 4가지말이 이동하는 모든 경우를 dfs를 통해 구한다.
2. 돌리면서 신경써야될 조건이 있다. 처리해준다.
   1. 중복되는 경로처리
   2. 도착하는거 처리
3. 10 번째 턴이 지난경우 결과의 합을 도출하여 갱신시킨다.



### 중복되는 경로처리

초반에 나눠지는 부분을 다른 배열로 만드는 방법을 사용해 맵을 만들었는데

그부분 덕에 복잡한 과정이 하나더 추가되었다. 

![image](https://user-images.githubusercontent.com/36303777/76162419-f7d71e80-6180-11ea-812a-f2d28a0d8fce.png)



저기 중복되는 부분에서 1,2,3이 중복되는곳은 1로

0,1,2,3이 모두 중복되는 곳은 0으로 맞춰주는 작업을 해준다.

~~~c++
Pos syncMap(Pos cur) {//씽크맞추기
	
	if (cur.path == 1) {
		if (cur.index >= PATH1_END_INDEX - 1) //40지점이후
			return Pos(0, cur.index + 13); //0번째 경로로 변경
	}

	else if (cur.path == 2) {
		if (cur.index >= PATH2_END_INDEX - 1)
			return Pos(0, cur.index + 14);
		else if (cur.index >= 3)
			return Pos(1, cur.index + 1);
	}
	else if (cur.path == 3) {
		if (cur.index >= PATH3_END_INDEX - 1)
			return Pos(0, cur.index + 13);
		else if (cur.index >= 4)
			return Pos(1, cur.index);
	}
	return cur;
}
~~~

그리고 겹침 처리는 다음과 검사한다.

~~~c++
bool checkOverlap(Pos cur,Pos horses[]) {
	for (int i = 0; i < 4;i++) {
		if (checkEnded(cur)) //종료지점은 겹침에서 제외
			return false;
		if (cur.index == horses[i].index && cur.path == horses[i].path)
			return true;
	}
	return false;
}
~~~

### 종료

종료검사는 아래와 같이 한다.

~~~c++
bool checkEnded(Pos cur) {
	if (cur.path == 0 && cur.index >= PATH0_END_INDEX) {
		return true;
	}
	return false;
}
~~~

~~~c++
bool checkAllEnded(Pos horses[]) {
	for (int i = 0; i < 4; i++) {
		if (!checkEnded(horses[i]))
			return false;
	}
	return true;
}
~~~



요새 실수잘 안하는데  예상하지 못한곳에서 틀려서 시간을 많이썼다. 틀린코드 찾기위해 다시짤때 썼던 코드 복붙을 지양해야될거같다. 