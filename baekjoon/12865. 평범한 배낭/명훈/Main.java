import java.io.*;
import java.util.*;

public class Main {
	private static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

	private static int[] W, V, max_value;	// weight, value, max value
	private static int N, K;				// N -> item number, K -> Max Weight

	public static void main(String[] args) throws IOException {
		init();
		solution();

		System.out.println(max_value[K]);
	}

	// init & input code
	private static void init() throws IOException {
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(st.nextToken());

		W = new int[N + 1];
		V = new int[N + 1];
		max_value = new int[K + 1];
		for (int i = 1; i <= N; i++) {
			st = new StringTokenizer(br.readLine());
			W[i] = Integer.parseInt(st.nextToken());
			V[i] = Integer.parseInt(st.nextToken());
		}
	}

	// solution code
	private static void solution() {
		for (int i = 1; i <= N; i++)
			for (int j = K; j >= 1; j--)
				if (W[i] <= j)
					max_value[j] = Math.max(max_value[j], max_value[j - W[i]] + V[i]);
	}
}
