import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Baekjoon1916 {
    static int N,M;
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static ArrayList<Node>[] graph;
    static int[] distance;

    public static void main(String[] args) throws IOException {
        N = Integer.parseInt(br.readLine());
        M = Integer.parseInt(br.readLine());
        graph = new ArrayList[N+1];
        distance = new int[N+1];

        Arrays.fill(distance,Integer.MAX_VALUE);
        for(int i=1;i<=N;i++){
            graph[i] = new ArrayList<>();
        }
        for(int i=0;i<M;i++){
            StringTokenizer st = new StringTokenizer(br.readLine());
            int src = Integer.parseInt(st.nextToken());
            int dest = Integer.parseInt(st.nextToken());
            int dist = Integer.parseInt(st.nextToken());
            graph[src].add(new Node(dest,dist));
        }
        StringTokenizer st = new StringTokenizer(br.readLine());
        int start = Integer.parseInt(st.nextToken());
        int end = Integer.parseInt(st.nextToken());

        dijkstra(start);

        System.out.println(distance[end]);
    }

    private static void dijkstra(int start) {
        distance[start] = 0;
        PriorityQueue<Node> pq = new PriorityQueue<>();

        pq.add(new Node(start,0));

        while(!pq.isEmpty()){
            int cur = pq.poll().dest;

            for(Node node : graph[cur]){
                int dist = distance[cur] + node.dist;
                if(distance[node.dest] > dist){
                    distance[node.dest] = dist;
                    pq.add(new Node(node.dest, distance[node.dest]));
                }
            }

        }

    }

    static class Node implements Comparable<Node>{
        int dest;
        int dist;

        public Node(int dest, int dist) {
            this.dest = dest;
            this.dist = dist;
        }

        @Override
        public String toString() {
            return "Node{" +
                    "dest=" + dest +
                    ", dist=" + dist +
                    '}';
        }

        @Override
        public int compareTo(Node o) {//오름차
            return this.dist - o.dist;
        }
    }
}
