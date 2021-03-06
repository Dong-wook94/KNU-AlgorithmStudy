# 17471. 게리멘더링

## 문제해결 사진

![image](https://user-images.githubusercontent.com/42582516/82911365-c6fbce00-9fa6-11ea-8f96-9e0a3b77d3be.png)

## 문제 알고리즘

- dfs

## 풀이방법

1. dfs로 구역을 강제로 정해준다.
2. 해당 구역들이 정확하게 2개의 구역으로 나눠지는 경우에만, 차이를 구한다.

- 핵심 코드

```java
import java.io.*;
import java.util.*;

public class Main {
    private static final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    // private static final BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

    private static int N;
    private static int[] score;
    private static int[] supporter;
    private static boolean visited[];
    private static boolean graph[][];
    private static int minDiff = Integer.MAX_VALUE;

    public static void main(String[] args) throws IOException {
        init();
        solution();
    }

    public static void init() throws IOException {
        N = Integer.parseInt(br.readLine());
        score = new int[N + 1];
        supporter = new int[N + 1];
        visited = new boolean[N + 1];
        graph = new boolean[N + 1][];

        for (int i = 0; i <= N; i++) {
            graph[i] = new boolean[N + 1];
        }

        StringTokenizer st = new StringTokenizer(br.readLine());
        for (int i = 1; i <= N; i++) {
            score[i] = Integer.parseInt(st.nextToken());
        }

        for (int i = 1; i <= N; i++) {
            st = new StringTokenizer(br.readLine());

            int M = Integer.parseInt(st.nextToken());
            for (int j = 0; j < M; j++) {
                int node = Integer.parseInt(st.nextToken());
                graph[i][node] = true;
            }
        }

        // for(int i=1; i<=N; i++) {
        // for(int j=0; j<graph[i].size(); j++)
        // System.out.print(graph[i].get(j) + " ");
        // System.out.println("");
        // }
    }

    public static void solution() {
        dfs(1);

        if (minDiff == Integer.MAX_VALUE)
            System.out.println(-1);
        else
            System.out.println(minDiff);

    }

    static void dfs(int cnt) {
        // end state
        if (cnt == N + 1) {
            // seperate two area
            int areaSum_1 = 0;
            int areaSum_2 = 0;
            for (int i = 1; i <= N; i++) {
                if (supporter[i] == 1)
                    areaSum_1 += score[i];
                else
                    areaSum_2 += score[i];
            }

            // connect area
            Arrays.fill(visited, false);
            int count = 0;
            for (int i = 1; i <= N; i++) {
                if (!visited[i]) {
                    connectArea(i, supporter[i]);
                    count++;
                }
            }

            // if 2 area, then get difference for 2 area
            if (count == 2) {
                if (minDiff > Math.abs(areaSum_1 - areaSum_2))
                    minDiff = Math.abs(areaSum_1 - areaSum_2);
            }
            return;
        }

        for (int e = 1; e <= 2; e++) {
            supporter[cnt] = e;
            dfs(cnt + 1);
        }
    }

    // 해당 지역에서 연결 가능한 모든 지역을 체크
    static void connectArea(int from, int areaNum) {
        visited[from] = true;
        for (int i = 1; i <= N; i++) {
            if (graph[from][i] && !visited[i] && supporter[i] == areaNum) {
                connectArea(i, areaNum);
            }
        }
    }
}

```

## 문제 후 느낀점

- 구역 분리에서 생각이 많았다.
