import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Main {

    static int N,M,land_number;
    static int[][] map;
    static int[][] min_distance;
    static int[] parent;
    static int[] dx={1,-1,0,0};
    static int[] dy={0,0,1,-1};
    static int result=0;

    static Queue<Node> q = new LinkedList<>();
    static Queue<Node> distance = new LinkedList<>();

    public static void main(String args[]) throws IOException {

        int count=0;

        init();
        findCost();
        setMinCost();

        for(int i=1;i<=land_number;i++){
            if(parent[i]==-1)
                count++;
        }

        if(count!=1)
            System.out.println(-1);
        else
            System.out.println(result);



    }

    public static void init() throws IOException {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        map = new int[N][M];

        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(br.readLine());
            for (int j = 0; j < M; j++) {
                map[i][j] = Integer.parseInt(st.nextToken());

                if(map[i][j]==1)
                    map[i][j]=-1;
            }
        }

        for(int i=0;i<N;i++){
            for(int j=0;j<M;j++) {
                if (map[i][j] == -1)
                    landering(i,j,++land_number);
            }
        }

        for(int i=0;i<land_number+1;i++)

        parent=new int[land_number+1];
        min_distance=new int[land_number+1][land_number+1];
        Arrays.fill(parent,-1);

    }

    public static void landering(int x, int y,int number){

        int nx,ny;

        map[x][y]=number;
        q.offer(new Node(x,y,number));

        for(int i=0;i<4;i++){
            nx=x+dx[i];
            ny=y+dy[i];

            if(nx<0 || nx>=N || ny<0 || ny>=M)
                continue;
            else if(map[nx][ny]==-1)
                    landering(nx,ny,number);

        }
    }

    public static void findCost(){

        Node scan;
        int nx,ny,landnumber,step;
        while(!q.isEmpty()){
            scan=q.poll();

            for(int i=0;i<4;i++){
                nx=scan.start;
                ny=scan.end;
                landnumber=scan.cost;
                step=-1;

                while(true){
                    nx+=dx[i];
                    ny+=dy[i];
                    step++;
                    if (nx < 0 || nx >= N || ny<0 || ny>=M)
                        break;

                    if(map[nx][ny]!=0){

                        if(map[nx][ny]!=landnumber)
                            distance.add(new Node(map[scan.start][scan.end],map[nx][ny],step));

                        break;
                    }
                }
            }
        }

    }

    public static void setMinCost(){

        Node scan;
        ArrayList<Node> min = new ArrayList<>();

        while(!distance.isEmpty()){
            scan=distance.poll();

            if(scan.cost==1)
                continue;

            if(min_distance[scan.start][scan.end]==0){
                min_distance[scan.start][scan.end]=scan.cost;
                min_distance[scan.end][scan.start]=scan.cost;
            }

            if(min_distance[scan.start][scan.end]>scan.cost || min_distance[scan.end][scan.start]>scan.cost){
                min_distance[scan.start][scan.end]=scan.cost;
                min_distance[scan.end][scan.start]=scan.cost;
            }

        }

        for(int i=1;i<=land_number;i++){
            for(int j=i+1;j<=land_number;j++){
                if(min_distance[i][j]==0)
                    continue;

                min.add(new Node(i,j,min_distance[i][j]));
            }
        }
        Collections.sort(min,new mycomparator());

        makeMst(min);


    }

    public static void makeMst(ArrayList<Node> min){

        Node temp;
        for(int i=0;i<min.size();i++){
            temp=min.get(i);
            if(union(temp.start,temp.end)){
                result+=temp.cost;
            }
        }

    }

    public static boolean union(int a,int b){
        a=find(a); b=find(b);
        if(a!=b){
            parent[b]=a;
            return true;
        }
        return false;
    }

    public static int find(int a){
        if(parent[a]<0) {
            return a;
        }
        else return parent[a]=find(parent[a]);
    }

}
class mycomparator implements Comparator<Node>{

    @Override
    public int compare(Node a,Node b){
        if(a.cost>b.cost)
            return 1;
        else
            return -1;
    }
}
class Node{

    int start;
    int end;
    int cost;

    Node(int start,int end,int cost){
        this.start=start;
        this.end=end;
        this.cost=cost;
    }
}