import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {

    static int[][] save_map;
    static int[][] map_status;
    static int[] dx={0,0,1,-1};
    static int[] dy={1,-1,0,0};

    static Virus[] selected;
    static ArrayList<Virus> virus_arr;
    static int virus_cnt=-1;
    static int empty_block;

    static int min_time=10000;
    static int M,N;


    public static void main(String[] args) throws IOException {
        init();
        dfs(0,0);

        if(min_time==10000)
            System.out.println(-1);
        else
            System.out.println(min_time);
    }

    public static void init() throws IOException {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;

        String input=br.readLine();
        st=new StringTokenizer(input);
        N=Integer.parseInt(st.nextToken()); M=Integer.parseInt(st.nextToken());
        int in;

        save_map=new int[N][N];
        map_status=new int[N][N];
        selected=new Virus[M];
        virus_arr=new ArrayList<>();

        for(int i=0;i<N;i++){
            st=new StringTokenizer(br.readLine());

            for(int j=0;j<N;j++) {
                in = Integer.parseInt(st.nextToken());
                if(in==1){ // wall
                    save_map[i][j]=1;
                }
                else if(in==2){
                    virus_arr.add(new Virus(i,j,0));
                    virus_cnt++;
                    save_map[i][j]=2;
                }
                else if(in==0)
                    empty_block++;

            }
        }

    }


    public static void dfs(int num,int depth){ // 조합

        if(depth==M){
            int time = bfs();

            if(time!=100000) {
                min_time = Math.min(min_time, time);
            }

            return;
        }
        else{

            for(int index=num;index<=virus_cnt;index++){
                selected[depth]=virus_arr.get(index);
                dfs(index+1,depth+1); // 씨발 이게 문제네
            }
        }


    }

    public static int bfs(){

        Queue<Virus> que=new LinkedList<>();

        int newX,newY,newMove;
        int max_Move=-1;
        int remain_block=empty_block;

        for(int i=0;i<N;i++)
            System.arraycopy(save_map[i],0,map_status[i],0,N);

        for(int i=0;i<M;i++){
            que.offer(selected[i]);
            map_status[selected[i].X][selected[i].Y]=1; //visit
        }

        if (remain_block == 0) {
            return 0;
        }

        while(!que.isEmpty()){


            Virus cur = que.remove();

            for(int i=0;i<4;i++){
                newX=cur.X+dx[i];
                newY=cur.Y+dy[i];
                newMove=cur.move+1;

                if(newX <0 || newX >=N || newY < 0 || newY >=N)
                    continue;

                if(map_status[newX][newY]!=1){
                    que.offer(new Virus(newX,newY,newMove));
                    max_Move=Math.max(max_Move,newMove);

                    if(map_status[newX][newY]==0) {
                        remain_block--;

                    }

                    map_status[newX][newY]=1; // visit.

                }


            }

            if (remain_block == 0) {
                return max_Move;
            }

        }

        return 100000;

    }

}

class Virus{
    int X;
    int Y;
    int move;

    public Virus(int X,int Y,int move){
        this.X=X;
        this.Y=Y;
        this.move=move;
    }
}