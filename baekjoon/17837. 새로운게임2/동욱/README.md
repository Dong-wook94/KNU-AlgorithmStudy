# 새로운 게임2
> 삼성 기출문제

방향 바꾸는게 매우 헷갈렸다.

방향만 바꾸는게 아니라 방향을 바꾸고 한칸을 이동해야된다.

근데 꽉막힌 공간에서는 이동하면 안된다.

그래서 `방향을 바꾼뒤 0번로직을 돌린다`.

그럼 양옆이 꽉 막힌 곳에서의 문제도 해결된다.

~~~c++
void moveChess(Chess cur, int next_row, int next_col, int chess_num) {
	int floor = findFloor(cur.row, cur.col, chess_num);
	int cnt=0;
	switch (map[next_row][next_col].color) {
	case 0:// 그냥
		cnt = 0;
		moveAllChess(cnt, floor, cur, next_row, next_col);
		break;
	case 1://쌓인말 순서변경
		
		reverseMoveAll(cur, floor, next_row, next_col);
		break;
	case 2://방향 변경
		cnt = 0;
		int dir = reverseDir(chess_num);
		chess_info[chess_num].dir = dir;
		cur = chess_info[chess_num];
		int nr = cur.row + dir_row[cur.dir];
		int nc = cur.col + dir_col[cur.dir];
		if (checkMapRange(nr, nc)) {
			if (map[nr][nc].color != 2)
				moveChess(cur, nr, nc, chess_num);
		}
		break;
	}
	
}
~~~

그리고 이번에 구조체를 계속 넘겼는데 callbtvalue라 그런지 

chess_info 변경후에 

`cur = chess_info[chess_num];`

를 초기화 해줘야 됐는데 까먹고 안해줘서 시간을 많이 쏟았다.