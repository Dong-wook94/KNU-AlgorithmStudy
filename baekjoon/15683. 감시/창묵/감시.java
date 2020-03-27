import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Main{

    static int N,M;
    static int[][] map;

    static int[] dx={0,1,0,-1};
    static int[] dy={1,0,-1,0};

    static ArrayList<CCTV> cctvArr=new ArrayList<CCTV>();
    static ArrayList<Integer> list = new ArrayList<>();
    static int remain;
    static int minValue;

    public static void main(String argv[]) throws IOException {

        init();
        dfs(0,0);
        System.out.println(minValue);
    }

    public static void init() throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        N=Integer.parseInt(st.nextToken());
        M=Integer.parseInt(st.nextToken());
        map=new int[N][M];
        minValue=N*M;


        for(int i=0;i<N;i++){
            st=new StringTokenizer(br.readLine());
            for(int j=0;j<M;j++){
                map[i][j]=Integer.parseInt(st.nextToken());
                if(map[i][j]==0)
                    remain++;
                else if(map[i][j]!=6){
                    cctvArr.add(new CCTV(i,j,map[i][j],0));
                }
            }
        }
    }

    public static void dfs(int index,int cnt){

        int value;
        int newRemain=remain;
        if(cnt==cctvArr.size()){
            value=calculate(newRemain);
            minValue=Math.min(value,minValue);
            return;
        }
        else{

            for(int i=index;i<4;i++){
                list.add(i);
                dfs(0,cnt+1);
                list.remove(list.size()-1);
            }

        }

    }

    public static int calculate(int curRemain){

        int[][] mapTemp=new int[N][M];

        for(int i=0;i<N;i++){
            for(int j=0;j<M;j++)
                mapTemp[i][j]=map[i][j];
        }

        for(int i=0;i<list.size();i++){
            (cctvArr.get(i)).dir=list.get(i);
        }

        for(int index=0;index<cctvArr.size();index++){
            curRemain=checkSpace(cctvArr.get(index),curRemain,mapTemp);
        }


        return curRemain;
    }

    public static int checkSpace(CCTV cur,int curRemain,int[][] map){
        int nx,ny;
        int ndir;
        ArrayList<Integer> dirArr;

        dirArr=makeDirArr(cur);

        for(int scanNum=0;scanNum<dirArr.size();scanNum++) {
            ndir=dirArr.get(scanNum);
            nx=cur.x;
            ny=cur.y;
            while (true) {
                nx += dx[ndir];
                ny += dy[ndir];

                if((nx < 0 || nx >= N || ny < 0 || ny >= M))
                    break;

                if (map[nx][ny] == 6)
                    break;
                else if (map[nx][ny] == 0) {
                    map[nx][ny] = -1;
                    curRemain--;
                }
            }

        }

        return curRemain;
    }

    public static ArrayList<Integer> makeDirArr(CCTV cur){
        ArrayList<Integer> temp=new ArrayList<>();
        if(cur.number==1){
            temp.add(cur.dir%4);
        }
        else if(cur.number==2){
            temp.add(cur.dir%4);
            temp.add((cur.dir+2)%4);
        }
        else if(cur.number==3){
            temp.add(cur.dir%4);
            temp.add((cur.dir+1)%4);
        }
        else if(cur.number==4){
            temp.add(cur.dir%4);
            temp.add((cur.dir+1)%4);
            temp.add((cur.dir+2)%4);
        }
        else if(cur.number==5){
            temp.add(0);
            temp.add(1);
            temp.add(2);
            temp.add(3);
        }

        return temp;
    }

}

class CCTV{
    int x;
    int y;
    int number;
    int dir;

    CCTV(int x,int y,int number,int dir){
        this.x=x;
        this.y=y;
        this.number=number;
        this.dir=dir;
    }
}