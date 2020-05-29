import java.io.*;
import java.util.*;

public class Main {
	private static final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	private static final int[] dx = { 0, 1, 0, -1 };
	private static final int[] dy = { 1, 0, -1, 0 };

	private static int N, M, T;
	private static int board[][];
	private static boolean visited[][];
	private static int depth = 0;
	private static int result = 0;

	public static void main(String[] args) throws IOException {
		init();
		solution();

		System.out.println(result);
	}

	// init & input code
	public static void init() throws IOException {
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		T = Integer.parseInt(st.nextToken());
		board = new int[N][M];

		for (int i = 0; i < N; i++) {
			st = new StringTokenizer(br.readLine());
			for (int j = 0; j < M; j++) {
				board[i][j] = Integer.parseInt(st.nextToken());
			}
		}
	}

	// solution code
	public static void solution() throws IOException {
		StringTokenizer st;
		for (int i = 0; i < T; i++) {
			st = new StringTokenizer(br.readLine());
			int x = Integer.parseInt(st.nextToken());
			int d = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());

			for (int j = 1; x * j - 1 < N; j++) {
				turn(board[x * j - 1], d, k);	// turn
			}
			remove();
		}

		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				if (board[i][j] != -1)
					result += board[i][j];
	}

	// turn using by deque
	private static void turn(int[] line, int d, int k) {
		Deque<Integer> q = new LinkedList<>();

		for (int i = 0; i < line.length; i++)
			q.addLast(line[i]);

		switch (d) {
		case 0: // clockwise direction
			for (int i = 0; i < k; i++) {
				int tmp = q.pollLast();
				q.addFirst(tmp);
			}
			break;
		case 1: // counter clockwise direction
			for (int i = 0; i < k; i++) {
				int tmp = q.pollFirst();
				q.addLast(tmp);
			}
			break;
		}

		int i = 0;
		while (!q.isEmpty()) {
			line[i] = q.poll();
			i++;
		}
	}

	// remove
	// delete connected same value
	private static void remove() {
		visited = new boolean[N][M];
		double sum = 0;
		int count = 0;
		boolean flag = false;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (!visited[i][j] && board[i][j] != -1) {
					depth = 0;
					dfs(i, j, board[i][j]);
					if (depth == 1) {
						visited[i][j] = false;
						sum += board[i][j];
						count++;
					} else {
						flag = true;
					}
				}
			}
		}

		if (flag) {
			for (int i = 0; i < N; i++)
				for (int j = 0; j < M; j++)
					if (visited[i][j])
						board[i][j] = -1;
		} else {
			for (int i = 0; i < N; i++)
				for (int j = 0; j < M; j++) {
					if (board[i][j] > sum / count)
						board[i][j]--;
					else if (board[i][j] != -1 && board[i][j] < sum / count)
						board[i][j]++;
				}
		}
	}

	// dfs
	// (y, x, value) => check all same value
	private static void dfs(int y, int x, int value) {
		depth++;
		visited[y][x] = true;

		for (int dir = 0; dir < 4; dir++) {
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (nx < 0)
				nx = M - 1;
			if (nx >= M)
				nx = 0;
			if (isInBoard(ny, nx) && !visited[ny][nx] && board[ny][nx] == value)
				dfs(ny, nx, value);
		}
	}

	// is in board
	// (y, x) => boolean
	private static boolean isInBoard(int y, int x) {
		if (y < 0 || y >= N || x < 0 || x >= M)
			return false;
		return true;
	}
}
