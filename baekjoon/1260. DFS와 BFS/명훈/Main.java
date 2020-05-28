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
