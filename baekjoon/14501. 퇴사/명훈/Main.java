import java.io.*;
import java.util.*;

public class Main {
	private static final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

	private static int N, result = 0;
	private static int[] T, P, dp;

	public static void main(String[] args) throws IOException {
		init();
		solution();

		System.out.println(result);
	}

	// init & input code
	private static void init() throws IOException {
		N = Integer.parseInt(br.readLine());
		T = new int[N + 2];
		P = new int[N + 2];
		dp = new int[N + 2];
		for (int i = 1; i <= N; i++) {
			String[] s = br.readLine().split(" ");
			T[i] = Integer.parseInt(s[0]);
			P[i] = Integer.parseInt(s[1]);
		}
	}

	// solution code
	private static void solution() {
		for (int i = 1; i <= N + 1; i++) {
			for (int j = 1; j < i; j++) {
				// j번째 날에서 일을 안한 경우
				dp[i] = Math.max(dp[i], dp[j]);

				// j번째 날에서 T[j]만큼 일하면 j + T[j] 날에 보상 P[j]를 받음
				if (j + T[j] == i) {
					dp[i] = Math.max(dp[i], dp[j] + P[j]);
				}
			}
			result = Math.max(result, dp[i]);
		}
	}
}
