# 12865 평범한 배낭

## 문제해결 사진

![image](https://user-images.githubusercontent.com/42582516/83936272-13dc7180-a7fd-11ea-8da0-4b79ebe32ad5.png)


## 문제 알고리즘

- Knapsack

## 풀이방법

1. Weight 배열과 Value 배열, 그리고 Max value를 선언한다.

2. 물건 하나를 넣었을 때와 넣지 않았을 때를 체크하며 최대 가치를 계산한다.

- 핵심 코드

```java
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

```

## 문제 후 느낀점

- Knapsack 문제입니다.