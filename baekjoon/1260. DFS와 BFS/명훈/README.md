# 1260 DFS, BFS

## 문제해결 사진

![image](https://user-images.githubusercontent.com/42582516/83108798-47334800-a0fb-11ea-8fed-cde6c1c98b18.png)

## 문제 알고리즘

- BFS

- DFS

## 풀이방법

1. graph(리스트 배열)을 만들어서 노드를 양방향으로 연결한다.

2. DFS, BFS를 출력한다.

- 핵심 코드

```java
import java.io.*;
import java.util.*;

public class Main {
    private static final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    private static int N, M, V;
    private static boolean[] visited;
    private static ArrayList<Integer>[] graph;

    public static void main(String[] args) throws IOException {
        init();
        solution();
    }

    // init & input code
    public static void init() throws IOException {
        StringTokenizer st = new StringTokenizer(br.readLine());

        // N, M, V
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        V = Integer.parseInt(st.nextToken());

        visited = new boolean[N + 1];
        graph = new ArrayList[N + 1];
        for (int i = 1; i <= N; i++) {
            graph[i] = new ArrayList<Integer>();
        }

        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(br.readLine());
            int from = Integer.parseInt(st.nextToken());
            int to = Integer.parseInt(st.nextToken());

            graph[from].add(to);
            graph[to].add(from);
        }
    }

    // solution code
    public static void solution() throws IOException {
        // sorting
        for (int i = 1; i <= N; i++) {
            Collections.sort(graph[i]);
        }

        // print dfs
        Arrays.fill(visited, false);
        dfs(V);
        System.out.println("");

        // print bfs
        Arrays.fill(visited, false);
        bfs(V);
        System.out.println("");
    }

    static void dfs(int from) throws IOException {
        if (visited[from])
            return;
        visited[from] = true;
        System.out.print(from + " ");
        for (int to : graph[from]) {
            if (!visited[to]) {
                dfs(to);
            }
        }
    }

    static void bfs(int start) throws IOException {
        Queue<Integer> queue = new LinkedList<Integer>();
        queue.add(start);
        visited[start] = true;

        while (!queue.isEmpty()) {
            int from = queue.poll();
            System.out.print(from + " ");
            for (int to : graph[from]) {
                if (!visited[to]) {
                    visited[to] = true;
                    queue.add(to);
                }
            }
        }
    }
}

```

## 문제 후 느낀점

- 오랜만에 보는 문제. 자바로 다시 풀어봄.
- C++랑 시간 차이...
