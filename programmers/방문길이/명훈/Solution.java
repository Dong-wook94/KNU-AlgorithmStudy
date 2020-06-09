import java.util.*;

public class Solution {
	private static int[][] board;
	private static boolean[][][][] visited;

	// solution code
	public static int solution(String dirs) {
		int answer = 0;
		board = new int[11][11]; // 0 ~ 10 => -5 ~ 5
		visited = new boolean[11][11][11][11];
		int curY = 5;
		int curX = 5;

		for (int i = 0; i < dirs.length(); i++) {
			int nextY = 0, nextX = 0;

			switch (dirs.charAt(i)) {
				case 'U':
					nextY = curY - 1;
					nextX = curX;
					break;
				case 'D':
					nextY = curY + 1;
					nextX = curX;
					break;
				case 'R':
					nextY = curY;
					nextX = curX + 1;
					break;
				case 'L':
					nextY = curY;
					nextX = curX - 1;
					break;
			}
			if (!isInBoard(nextY, nextX))
				continue;

			if (!visited[nextY][nextX][curY][curX] && !visited[curY][curX][nextY][nextX]) {
				visited[nextY][nextX][curY][curX] = true;
				answer++;
			}

			curY = nextY;
			curX = nextX;
		}
		return answer;
	}

	// check is in board
	private static boolean isInBoard(int y, int x) {
		if (y < 0 || y > 10 | x < 0 || x > 10)
			return false;
		return true;
	}

	public static void main(String[] args) {
		System.out.println(solution("ULURRDLLU"));
		System.out.println(solution("LULLLLLLU"));

	}

}
