import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Main{


    static int[][] map=new int[3][3];
    static int[] dx={0,0,1,-1};
    static int[] dy={1,-1,0,0};

    static int startX,startY;
    static int target=123456780;


    public static void main(String[] args) throws IOException {

        init();
        System.out.println(bfs());

    }

    public static void init() throws IOException {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;

        for(int i=0;i<3;i++){
            st=new StringTokenizer(br.readLine());
            for(int j=0;j<3;j++){
                map[i][j]=Integer.parseInt(st.nextToken());

                if(map[i][j]==0){
                    startX=i;
                    startY=j;
                }
            }
        }

    }

    public static int bfs(){

        Queue<Node> q=new LinkedList<>();
        HashSet<Integer> set = new HashSet<Integer>();
        Node scan;
        int mapCode;
        int x,y,depth,nx,ny;
        int[][] curMap=new int[3][3];

        if(makeCode(map)==target)
            return 0;

        q.add(new Node(startX,startY,0,makeCode(map)));



        while(!q.isEmpty()){
            scan=q.poll();
            x=scan.x;
            y=scan.y;
            depth=scan.depth;
            makeMap(scan.mapCode,curMap);

            for(int i=0;i<4;i++){
                nx=x+dx[i];
                ny=y+dy[i];

                if(nx <0 || nx>=3 || ny<0 || ny>=3)
                    continue;

                swap(curMap,x,y,nx,ny);
                mapCode=makeCode(curMap);

                if(mapCode==target)
                    return depth+1;

                if(!set.contains(mapCode)) {
                    q.add(new Node(nx, ny,depth+1,mapCode));
                    set.add(mapCode);
                }
                swap(curMap,nx,ny,x,y);

            }
        }

        return -1;

    }

    public static int makeCode(int[][] map){
        int returnCode=0;

        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                returnCode*=10;
                returnCode+=map[i][j];
            }
        }

        return returnCode;
    }

    public static void makeMap(int mapCode,int [][] curMap){

        int div=10;

        for(int i=2;i>-1;i--){
            for(int j=2;j>-1;j--){
                curMap[i][j]=(mapCode%div)/(div/10);
                mapCode-=mapCode%div;
                div*=10;
            }
        }

    }

    public static void swap(int[][]map, int x1,int y1,int x2,int y2){

        int temp;

        temp=map[x1][y1];
        map[x1][y1]=map[x2][y2];
        map[x2][y2]=temp;

    }

}

class Node{

    int x;
    int y;
    int depth;
    int mapCode;

    Node(int x,int y,int depth,int mapCode){
        this.x=x;
        this.y=y;
        this.depth=depth;
        this.mapCode=mapCode;
    }
}