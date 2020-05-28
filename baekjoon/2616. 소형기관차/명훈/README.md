# 2616 소형기관차

## 문제해결 사진

![image](https://user-images.githubusercontent.com/42582516/83102315-236a0500-a0ef-11ea-9bec-dbc7a6f4b5a7.png)

## 문제 알고리즘

- DP

## 풀이방법

1. 해당 위치 지점을 포함한 횟수 dp 배열을 구해서 푼다.

![image](https://user-images.githubusercontent.com/42582516/83102942-a9d31680-a0f0-11ea-89b1-c3cb715b6d78.png)

- 핵심 코드

```java
import java.io.*;
import java.util.*;

public class Main {
    private static final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    private static int N, M; // N => number of train, M = count of valid train
    private static int[][] dp; // dp[][] data
    private static int MaxValue = 0; // Max Value

    public static void main(String[] args) throws IOException {
        init();
        solution();

        System.out.println(MaxValue);
    }

    // init & input code
    public static void init() throws IOException {
        N = Integer.parseInt(br.readLine());

        dp = new int[4][];
        for (int i = 0; i < 4; i++) {
            dp[i] = new int[N + 1];
            Arrays.fill(dp[i], 0);
        }

        StringTokenizer st = new StringTokenizer(br.readLine());
        for (int i = 1; i <= N; i++) {
            dp[0][i] = Integer.parseInt(st.nextToken());
        }
        M = Integer.parseInt(br.readLine());
    }

    // solution code
    public static void solution() {
        // one time
        for (int i = M; i <= N; i++) {
            dp[1][i] = sumUpTo(0, i);
        }
        // two time
        for (int i = 2 * M; i <= N; i++) {
            dp[2][i] = dp[1][i] + getMaxValue(1, i - M);
        }
        // three time & get MaxValue
        for (int i = 3 * M; i <= N; i++) {
            dp[3][i] = dp[1][i] + getMaxValue(2, i - M);
            if (MaxValue < dp[3][i])
                MaxValue = dp[3][i];
        }
    }

    // get sum to
    static int sumUpTo(int time, int index) {
        int sum = 0;
        for (int i = 0; i < M; i++) {
            sum += dp[time][index - i];
        }
        return sum;
    }

    // get MaxValue from Index
    static int getMaxValue(int time, int index) {
        int value = 0;
        for (int i = M; i <= index; i++) {
            if (value < dp[time][i])
                value = dp[time][i];
        }
        return value;
    }
}

```

## 문제 후 느낀점

- 기분 좋게 풀린 문제
