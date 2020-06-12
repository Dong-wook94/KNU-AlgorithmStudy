import java.io.*;
import java.util.*;

public class Main {
	private static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

	private static int N, M; // number, minimum memory
	private static int A[], m[]; // byte, cost
	private static int dp[][];
	private static int res = Integer.MAX_VALUE;

	public static void main(String[] args) throws IOException {
		input();
		solution();
		
		System.out.println(res);
	}

	// input & init code
	private static void input() throws IOException {
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());

		A = new int[N];
		m = new int[N];
		dp = new int[N][10001];

		st = new StringTokenizer(br.readLine());
		for (int i = 0; i < N; i++)
			A[i] = Integer.parseInt(st.nextToken());

		st = new StringTokenizer(br.readLine());
		for (int i = 0; i < N; i++)
			m[i] = Integer.parseInt(st.nextToken());

	}

	// solution code
	private static void solution() {
		dp[0][m[0]] = A[0];

		for (int i = 1; i < N; i++) {
			for (int j = 0; j <= 10000; j++) {
				if (j - m[i] >= 0)
					dp[i][j] = Math.max(dp[i][j], dp[i - 1][j - m[i]] + A[i]);
				dp[i][j] = Math.max(dp[i][j], dp[i - 1][j]);
				if (dp[i][j] >= M) {
					res = Math.min(res, j);
				}
			}
		}

	}
}
