import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class Baekjoon17471 {
    static ArrayList<Integer> adjList[];
    static int population[];
    static int numPopulation;
    static boolean visited[];
    static int minGap= Integer.MAX_VALUE;
    static int countOfNode;
    static boolean isConnected;

    public static void checkConnected(int groupSize, int node, int groupName, int groupInfo){
        if(groupSize == countOfNode){
            isConnected = true;
            return;
        }
        for(int i=0;i<adjList[node].size();i++) {
            int nextNode = adjList[node].get(i);
            int nextGroupName = 0;
            int num = 1 << (nextNode - 1);
            if ((groupInfo & num) == num)
                nextGroupName = 1;
            if (!visited[nextNode] && nextGroupName == groupName) {
                visited[nextNode] = true;
                countOfNode++;
                checkConnected(groupSize, nextNode, groupName, groupInfo);
            }
        }
    }

    public static int getGap(int groupInfo) {
        ArrayList<Integer> A = new ArrayList<>();
        ArrayList<Integer> B = new ArrayList<>();

        int a=0,b=0;
        for(int i=1;i<=numPopulation;i++)
            visited[i] = false;
        divideArea(groupInfo, A, B);
        if(A.isEmpty() || B.isEmpty())
            return -1;

        if (isAreaConnected(groupInfo, A,1)) return -1;
        if (isAreaConnected(groupInfo,B,0))return -1;

        for(int num : A){
            a+=population[num];
        }
        for(int num : B){
            b+=population[num];
        }
        return Math.abs(a-b);
    }

    public static void divideArea(int groupInfo, ArrayList<Integer> a, ArrayList<Integer> b) {
        for (int i=1;i<=numPopulation;i++){
            int num = 1<<(i-1);
            if((groupInfo & num)==num)
                a.add(i);
            else
                b.add(i);
        }
    }

    public static boolean isAreaConnected(int groupInfo, ArrayList<Integer> a,int groupName) {
        countOfNode = 1;
        visited[a.get(0)] = true;
        isConnected = false;
        checkConnected(a.size(), a.get(0),groupName,groupInfo);
        if(!isConnected){
            return true;
        }
        return false;
    }

    public static void makeAllCase(){
        //0인 경우랑 전체가 1인경우 제외
        for(int i=1;i<(1<<numPopulation)-1;i++){
            int gap = getGap(i);
            if(gap>=0)
                minGap = Math.min(minGap, gap);
        }
    }

    public static void input() throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        numPopulation = Integer.parseInt(br.readLine());
        StringTokenizer st = new StringTokenizer(br.readLine());
        adjList = new ArrayList[numPopulation+1];
        population = new int[numPopulation+1];
        visited = new boolean[numPopulation+1];

        for(int i=1;i<=numPopulation;i++) {
            population[i] = Integer.parseInt(st.nextToken());
        }
        for(int i=1;i<=numPopulation;i++) {
            st = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(st.nextToken());
            adjList[i] = new ArrayList<Integer>();
            for (int j = 0; j < n; j++) {
                adjList[i].add(Integer.parseInt(st.nextToken()));
            }
        }

    }
    public static void main(String[] args) throws IOException {
        input();
        makeAllCase();
        if(minGap==Integer.MAX_VALUE)
            System.out.println("-1");
        else
            System.out.println(minGap);
    }
}
