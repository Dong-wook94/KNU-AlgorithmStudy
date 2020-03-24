# 기둥과 보 설치

추가는 그냥 시키는 대로 하면된다



문제는 삭제이다.

삭제를 하기전에 먼저 없애보고 지금 상태가 유지가 가능한지 체크를 하는 방식을 선택하였다.

코드가 많이 길어졌는데 이렇게 푸는게 맞는건지 모르겠다.

~~~c++
bool canMaintainBeam(int x, int y, int n) {
	if (existPillar(x, y - 1, n) || existPillar(x + 1, y - 1, n))//양쪽한곳에 기둥이 있는 경우
		return true;
	if (existBeam(x - 1, y, n) && existBeam(x + 1, y, n))// 보가 왼쪽 오른쪽 모두에 둘다있을때
		return true;
	return false;
}
bool canMaintainPillar(int x, int y, int n) {
	if (y == 0) //바닥
		return true;
	//왼쪽 또는 오른쪽에 보가있거나 바로아래에 기둥이 있는 경우
	if (existBeam(x - 1, y, n) || existBeam(x, y, n) || existPillar(x, y - 1, n))
		return true;
	return false;
}

~~~

이부분이 어떤 보나 기둥을 삭제했을때 유지가 가능한지 판단해주는 함수이다.