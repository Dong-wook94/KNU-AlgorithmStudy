import java.io.IOException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class Baekjoon2623 {
    static int N;
    static int M;
    static ArrayList<Integer>[] graph;
    static int[] countOfInDegree;
    static Queue<Integer> queue;
    static ArrayList<Integer> result = new ArrayList<>();

    public static void main(String[] args) throws IOException {
        Scanner scan = new Scanner(System.in);

        N = scan.nextInt();
        M = scan.nextInt();
        graph = new ArrayList[N+1];
        countOfInDegree = new int[N+1]; //초기값 0이라서 int배열
        queue = new LinkedList<>();
        initGraph(scan);

        for(int i=1;i<=N;i++){
            if(countOfInDegree[i]==0)
                queue.add(i);
        }
        if(queue.isEmpty()){
            System.out.println(0);
            return;
        }
        arrangeOrder();
        if(result.size()!=N)
            System.out.println(0);
        else {
            for (int num : result) {
                System.out.println(num);
            }
        }
    }

    public static void arrangeOrder() {
        while(!queue.isEmpty()){
            int node = queue.poll();
            result.add(node);
            for(int i=0;i<graph[node].size();i++){
                countOfInDegree[graph[node].get(i)]--;
                if(countOfInDegree[graph[node].get(i)]==0){
                    queue.add(graph[node].get(i));
                }
            }
            graph[node].clear();
        }
    }

    public static void initGraph(Scanner scan) {
        for(int i=1;i<=N;i++){
            graph[i] = new ArrayList<>();
        }
        for(int i=0;i<M;i++){
            int num = scan.nextInt();
            int from = scan.nextInt();
            int to =0;
            for(int j=1;j<num;j++){
                to = scan.nextInt();
                graph[from].add(to);
                countOfInDegree[to]++;
                from = to;
            }

        }
    }
}
