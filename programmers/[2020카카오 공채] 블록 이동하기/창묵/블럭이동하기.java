import java.util.LinkedList;
import java.util.Queue;

public class Main{


    static boolean[][][] visit;

    static int N;
    static int minValue=10000;

    static final int horizon = 0;
    static final int vertical = 1;

    public static void main(String args[]){

        int[][] board={{0, 0, 0, 1, 1},{0, 0, 0, 1, 0},{0, 1, 0, 1, 1},{1, 1, 0, 0, 1},{0, 0, 0, 0, 0}};
        System.out.println(solution(board));
    }

    public static int solution(int[][] board){
        int answer=0;
        N=board.length;
        visit=new boolean[board.length][board.length][2];

        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(board[i][j]==1) {
                    visit[i][j][horizon] = true;
                    visit[i][j][vertical] = true;
                }
            }
        }

        bfs(new Node(0,0,0,1,0,horizon),board);

        answer=minValue;

        return answer;

    }

    public static void bfs(Node cur,int[][] board){

        Node scan;
        Queue<Node> q = new LinkedList<Node>();

        visit[0][0][horizon]=true;
        q.add(cur);

        while(!q.isEmpty()){

            scan=q.poll();
          //  System.out.printf("(%d,%d) (%d,%d) dir : %s depth : %d\n",scan.x1,scan.y1,scan.x2,scan.y2,scan.dir,scan.depth);
            if((scan.x2==N-1 && scan.y2==N-1)){

                if(scan.depth>minValue)
                    continue;

                minValue=Math.min(minValue,scan.depth);
            }

            scanSurround(scan,q,board);
            Rotate(scan,q,board);

        }

    }

    public static void scanSurround(Node cur,Queue<Node> q,int[][] board){

        int nx1,nx2,ny1,ny2;
        int[] dx={0,0,1,-1}; // 오,왼,아래,위
        int[] dy={1,-1,0,0};

        for(int i=0;i<4;i++){

            nx1=cur.x1+dx[i];
            ny1=cur.y1+dy[i];

            if(cur.dir==horizon){
                nx2=nx1;
                ny2=ny1+1;
            }
            else{ // vertical
                nx2=nx1+1;
                ny2=ny1;
            }

            if(!checkBound(nx1,nx2,ny1,ny2,board))
                continue;


            if(visit[nx1][ny1][cur.dir]==false){
                visit[nx1][ny1][cur.dir] = true;
                q.add(new Node(nx1, nx2, ny1, ny2, cur.depth + 1, cur.dir));
            }

        }


    }

    public static void Rotate(Node cur,Queue<Node> q,int[][] board){

        int nx1,nx2,ny1,ny2,ndir;
        int wallx,wally;
        int[] rotatex={-1,0,0,-1};
        int[] rotatey={1,0,1,0};

        int[][] wall={{0,-1},{1,1},{1,-1},{0,1}};

            for(int i=0;i<4;i++) {

                if(cur.dir==horizon){
                    nx1=cur.x1+rotatex[i];
                    ny1=cur.y1+rotatey[i];
                    nx2=nx1+1;
                    ny2=ny1;
                    ndir=vertical;
                    wallx=wall[i][0]+nx1;
                    wally=wall[i][1]+ny1;
                }
                else{
                    nx1=cur.x1+rotatey[i];
                    ny1=cur.y1+rotatex[i];
                    nx2=nx1;
                    ny2=ny1+1;
                    ndir=horizon;
                    wallx=wall[i][1]+nx1;
                    wally=wall[i][0]+ny1;
                }


                if (!checkBound(nx1, nx2, ny1, ny2,board))
                    continue;

                if (!wallCheck(wallx, wally,board))
                    continue;

                if (visit[nx1][ny1][ndir] == false) {
                    visit[nx1][ny1][ndir] = true;
                    q.add(new Node(nx1, nx2, ny1, ny2, cur.depth + 1, ndir));
                }


            }

    }

    public static boolean checkBound(int x1,int x2,int y1,int y2,int[][] board){

        if(x1 <0 || x1 >=N || x2 <0 || x2>=N || y1<0 || y1 >=N || y2<0 || y2>=N)
            return false;

        if(board[x1][y1]!=0 || board[x2][y2]!=0)
            return false;

        return true;

    }

    public static boolean wallCheck(int wallx,int wally,int[][] board){

        if((wallx<0 || wally<0 || wallx>=N || wally>=N))
            return false;

        if(!(wallx<0 || wally<0 || wallx>=N || wally>=N)){
            if(board[wallx][wally]==0)
                return true;
        }
        return false;
    }

}

class Node{
    int x1,y1;
    int x2,y2;
    int depth;
    int dir;

    Node(int x1,int x2,int y1,int y2,int depth,int dir){
        this.x1=x1;
        this.x2=x2;
        this.y1=y1;
        this.y2=y2;
        this.depth=depth;
        this.dir=dir;
    }
}