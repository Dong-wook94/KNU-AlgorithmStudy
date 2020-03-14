import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main{

    static int[][] map;
    static int[][] mapCopy;

    static int[][] tc;
    static int[] dx={0,1,0,-1};
    static int[] dy={1,0,-1,0};
    static ArrayList<Node> select = new ArrayList<Node>();

    static boolean[] visit;

    static int minValue=100000;

    static int N,M,K;


    public static void main(String[] args) throws IOException {


        init();
        permutation(0,0);

        System.out.println(minValue);
    }

    public static void init() throws IOException {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        N=Integer.parseInt(st.nextToken());
        M=Integer.parseInt(st.nextToken());
        K=Integer.parseInt(st.nextToken());

        map=new int[N+1][M+1];
        mapCopy=new int[N+1][M+1];
        tc=new int[K][3];
        visit=new boolean[K];

        for(int i=1;i<=N;i++){
            st=new StringTokenizer(br.readLine());
            for(int j=1;j<=M;j++){
                map[i][j]=Integer.parseInt(st.nextToken());
            }
        }

        for(int i=0;i<K;i++){
            st=new StringTokenizer(br.readLine());
            for(int j=0;j<3;j++)
                tc[i][j]=Integer.parseInt(st.nextToken());

        }

    }

    public static void permutation(int number,int cnt){



        if(cnt==K){
            calculate();
            findMin();
            return ;
        }
        else{

            for(int index=number;index<K;index++){

                if(visit[index]==false) {
                    select.add(new Node(tc[index][0], tc[index][1], tc[index][2]));
                    visit[index]=true;
                    permutation(0,cnt+1);
                    select.remove(select.size()-1);
                    visit[index]=false;
                }

            }

        }


    }

    public static void calculate() {

        int startX, startY, endX, endY, nx, ny, cx, cy;
        int dr, insertValue;
        int nextTemp;
        Queue<Node> q=new LinkedList<Node>();
        Node cur;

        for(int i=1;i<=N;i++){
            for(int j=1;j<=M;j++)
                mapCopy[i][j]=map[i][j];
        }

        for(int i=0;i<select.size();i++)
            q.add(select.get(i));

        while (!q.isEmpty()) {

            cur=q.poll();
            startX=cur.r-cur.s;
            startY=cur.c-cur.s;
            endX=cur.r+cur.s;
            endY=cur.c+cur.s;


            while (true) {

                if (startX == endX
                        && startY == endY)
                    break;

                cx = startX;
                cy = startY;

                insertValue = mapCopy[cx][cy];

                for (dr = 0; dr < 4; dr++) {
                    nx = cx;
                    ny = cy;

                    while (true) {
                        cx = nx;
                        cy = ny;
                        nx += dx[dr];
                        ny += dy[dr];

                        if (nx < startX
                                || nx > endX
                                || ny > endY
                                || ny < startY) { // lineEnd
                            break;
                        }
                        nextTemp = mapCopy[nx][ny];
                        mapCopy[nx][ny] = insertValue;
                        insertValue = nextTemp;
                    }
                }
                startX++;
                startY++;
                endX--;
                endY--;

            }

        }
    }

    public static void findMin(){

        for(int i=1;i<=N;i++){
            int sum=0;
            for(int j=1;j<=M;j++){
                sum+=mapCopy[i][j];
            }
            minValue=Math.min(sum,minValue);
        }

    }

}

class Node{
    int r;
    int c;
    int s;

    Node(int r,int c,int s){
        this.r = r;
        this.c = c;
        this.s = s;
    }
}