# 17822 원판돌리기

## 문제해결 사진

![image](https://user-images.githubusercontent.com/42582516/83281390-0169a300-a213-11ea-84e3-1bf70765f58a.png)

## 문제 알고리즘

- DP

## 풀이방법

1. DP를 통해서 j번째 날에 일을 했는지 안했는지에 따라 최대 이익을 결정해준다.

- 핵심 코드

```java
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


```

## 문제 후 느낀점

- 처음에 로직을 비슷한 방향으로 잡았는데 왜 틀렸는지 이해 못한 문제.
