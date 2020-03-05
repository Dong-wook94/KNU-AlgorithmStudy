import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Main{

    static char[][] map;

    static int N,M;
    static int[] dx = {0,0,-1,1};
    static int[] dy = {-1,1,0,0};

    static Node init_red,init_blue,hole;
    static Queue<Marble> q = new LinkedList<>();

    public static void main(String args[]) throws IOException {

        init();
        bfs(init_red,init_blue);

    }

    public static void init() throws IOException {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        String temp;
        N=Integer.parseInt(st.nextToken()); M=Integer.parseInt(st.nextToken());
        map=new char[N][M];

        for(int i=0;i<N;i++){
            temp=br.readLine();
            for(int j=0;j<M;j++){
                map[i][j]=temp.charAt(j);

                if(map[i][j]=='R'){
                    init_red=new Node(i,j);
                }
                else if(map[i][j]=='B'){
                    init_blue=new Node(i,j);
                }
                else if(map[i][j]=='O'){
                    hole=new Node(i,j);
                }
            }
        }
    }

    public static void bfs(Node red,Node blue) {

        Marble scan;
        int cur_depth;


        q.offer(new Marble(red,blue,0));

        while(!q.isEmpty()){
            scan=q.poll();
            cur_depth=scan.depth;

            if(cur_depth>=10) {
                System.out.println(-1);
                System.exit(0);
            }

            for(int i=0;i<4;i++){
                moving(i,scan,cur_depth);
            }

        }

        System.out.println(-1);

    }

    public static void moving(int index,Marble scan,int cur_depth){

        boolean red_pass=false;
        boolean blue_pass=false;
        int new_redX,new_redY,new_blueX,new_blueY;
        Marble newScan;

        new_redX=scan.red.x; new_redY=scan.red.y; new_blueX=scan.blue.x; new_blueY=scan.blue.y;

        while(true){
            new_redX+=dx[index]; new_redY+=dy[index];
            if(map[new_redX][new_redY]=='#'){
                if(index==0)
                    new_redY+=1;
                else if(index==1)
                    new_redY-=1;
                else if(index==2)
                    new_redX+=1;
                else if(index==3)
                    new_redX-=1;
                break;
            }
            if(map[new_redX][new_redY]=='O') {
                red_pass = true;
                break;
            }
        }

        while(true){
            new_blueX+=dx[index]; new_blueY+=dy[index];
            if(map[new_blueX][new_blueY]=='#'){

                if(index==0)
                    new_blueY+=1;
                else if(index==1)
                    new_blueY-=1;
                else if(index==2)
                    new_blueX+=1;
                else if(index==3)
                    new_blueX-=1;

                break;
            }


            if(map[new_blueX][new_blueY]=='O') {
                blue_pass = true;
                break;
            }
        }

        if(blue_pass==true)
            return ;
        if(red_pass==true) {
            System.out.println(cur_depth+1);
            System.exit(0);
        }

        if(new_redX==new_blueX && new_redY==new_blueY) { // 다 옮겼을 때 두 구슬이 같은 위치에 위치한다면
            if (index == 0) { // 왼쪽
                if(scan.red.y-scan.blue.y>0)
                    new_redY=new_blueY+1;
                else if(scan.red.y-scan.blue.y<0)
                    new_blueY=new_redY+1;

            } else if (index == 1) { // 오른쪽
                if(scan.red.y-scan.blue.y>0)
                    new_blueY=new_redY-1;
                else if(scan.red.y-scan.blue.y<0)
                    new_redY=new_blueY-1;

            } else if (index == 2) { // 위쪽
                if(scan.red.x-scan.blue.x>0)
                    new_redX=new_blueX+1;
                else if(scan.red.x-scan.blue.x<0)
                    new_blueX=new_redX+1;

            } else if (index == 3) { // 아래쪽
                if(scan.red.x-scan.blue.x>0)
                    new_blueX=new_redX-1;
                else if(scan.red.x-scan.blue.x<0)
                    new_redX=new_blueX-1;
            }
        }

        if(scan.red.x==new_redX && scan.red.y==new_redY && scan.blue.x==new_blueX && scan.blue.y==new_blueY){
            return ;
        }
        else {
            newScan=new Marble(new Node(new_redX,new_redY),new Node(new_blueX,new_blueY),cur_depth+1);
            q.offer(newScan);
        }
    }
}

class Marble{
    Node red;
    Node blue;
    int depth;

    Marble(Node red,Node blue,int depth){
        this.red=red;
        this.blue=blue;
        this.depth=depth;
    }
}

class Node{
    int x;
    int y;

    Node(int x,int y){
        this.x = x;
        this.y = y;
    }
}
