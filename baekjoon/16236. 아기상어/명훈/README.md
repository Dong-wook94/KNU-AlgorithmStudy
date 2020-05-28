# 16236 아기상어

## 문제해결 사진

![image](https://user-images.githubusercontent.com/42582516/83132669-b1a8b000-a11c-11ea-83ba-8758b99906aa.png)

## 문제 알고리즘

- bfs

## 풀이방법

1. 상어가 있는 위치에서 제일 가까운 물고기를 찾는다.

2. 가까운 물고기가 여러개면 가장 윗쪽이고 왼쪽인 물고기를 찾아서 그 물고기의 위치를 이동하고 time을 더해준다.

- 핵심 코드

```java
import java.io.*;
import java.util.*;

public class Main {
	// class
	public static class Fish {
		int r;
		int c;
		int level;
		int size;

		Fish(int r, int c) {
			this.r = r;
			this.c = c;
			this.level = 2;
			this.size = 0;
		}
	}

	private static final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	private static final int[] dr = {0, 0, -1, 1};
	private static final int[] dc = {-1, 1, 0, 0};

	static int N;
	static int[][] board;
	static int[][] check;
	static Fish shark;
	static int time = 0;

	public static void main(String[] args) throws IOException {
		init();
		solution();

		System.out.println(time);
		br.close();
	}

	// init & input code
	private static void init() throws IOException {
		N = Integer.parseInt(br.readLine());
		board = new int[N][N];
		for (int i = 0; i < N; i++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			for (int j = 0; j < N; j++) {
				board[i][j] = Integer.parseInt(st.nextToken());
				if (board[i][j] == 9) {
					shark = new Fish(i, j);
					board[i][j] = 0;
				}
			}
		}
	}

	// solution code
	private static void solution() {
		int cnt = bfs();
		while(cnt > 0) {
			time += cnt;
			cnt = bfs();
		}
	}

	// bfs
	private static int bfs() {
		check = new int[N][N];
		Queue<Fish> q = new LinkedList<Fish>();
		check[shark.r][shark.c] = 1;
		q.offer(new Fish(shark.r, shark.c));

		Fish fish = new Fish(N, N);	// init
		int cnt = 0;

		// find eating fish
		loop: while(!q.isEmpty()) {
			int curR = q.peek().r;
			int curC = q.poll().c;

			for(int dir=0; dir<4; dir++) {
				int nextR = curR + dr[dir];
				int nextC = curC + dc[dir];

				// is in Board, no visited, valid eat
				if(isInBoard(nextR, nextC) && check[nextR][nextC] == 0 && board[nextR][nextC] <= shark.level) {
					check[nextR][nextC] = check[curR][curC] + 1;
					q.offer(new Fish(nextR, nextC));

					// bfs를 끝냄
					if(cnt != 0 && cnt < check[nextR][nextC])
						break loop;

					// if find fish that it could eat,
					if(0 < board[nextR][nextC] && board[nextR][nextC] < shark.level && cnt == 0) {
						cnt = check[nextR][nextC];
						fish.r = nextR;
						fish.c = nextC;
						fish.level = board[nextR][nextC];
					}
					// if many fish in same length, eat highest, leftest fish
					else if(cnt == check[nextR][nextC] && 0 < board[nextR][nextC] && board[nextR][nextC] < shark.level) {
						if(nextR < fish.r) {	// the hightest
							fish.r = nextR;
							fish.c = nextC;
							fish.level = board[nextR][nextC];
						} else if (nextR == fish.r && nextC < fish.c) {	// the leftest
							fish.r = nextR;
							fish.c = nextC;
							fish.level = board[nextR][nextC];
						}
					}
				}
				else if(isInBoard(nextR, nextC) && check[nextR][nextC] == 0) {
					check[nextR][nextC] = -1;
				}
			}
		}

		// if eat any fish
		if(fish.r != N && fish.c != N) {
			eatFish(fish);
		}
		return (cnt - 1);
	}

	// (r, c) => boolean
	private static boolean isInBoard(int r, int c) {
		if (r < 0 || r >= N || c < 0 || c >= N)
			return false;
		return true;
	}

	// eat fish, empty fish
	private static void eatFish(Fish fish) {
		// change position
		shark.r = fish.r;
		shark.c = fish.c;
		board[fish.r][fish.c] = 0;	// after eat fish, there is no fish
		shark.size++;

		// if eat enough fish, shark's level is up
		if(shark.level < 7 && shark.size == shark.level) {
			shark.level++;
			shark.size = 0;
		}
	}
}

```

## 문제 후 느낀점

- 아기상어
