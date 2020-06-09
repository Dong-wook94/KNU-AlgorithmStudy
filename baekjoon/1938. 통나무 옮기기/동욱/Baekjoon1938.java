import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;

public class Baekjoon1938 {
    static final int VERTICAL=0;
    static final int HORIZONTAL=1;
    static int mapSize;

    static int map[][];
    static boolean visited[][][];
    static int dirRow[]={0,1,0,-1,-1,-1,1,1};
    static int dirCol[]={1,0,-1,0,-1,1,-1,1};
    static Log start;
    static Log destination;


    public static void main(String[] args) throws IOException {
        inputData();
        bfs();
        if(destination.dist==Integer.MAX_VALUE)
            System.out.println(0);
        else
            System.out.println(destination.dist);

    }

    private static void bfs() {
        Queue<Log> q = new LinkedList<>();
        q.add(start);
        visited[start.row][start.col][start.dir] = true;
        while(!q.isEmpty()){
            Log cur = q.poll();
            //System.out.println(cur.row+","+cur.col+","+cur.dir+":"+cur.dist);
            if(cur.isEnd()){
                destination.dist = Math.min(destination.dist,cur.dist);
                continue;
            }

            //먼저 이동 체
            for(int d=0;d<4;d++){
                int nextRow = cur.row + dirRow[d];
                int nextCol = cur.col + dirCol[d];

                if(!isAbleToMove(nextRow,nextCol,cur.dir))
                    continue;
                if(visited[nextRow][nextCol][cur.dir])
                    continue;
                visited[nextRow][nextCol][cur.dir] = true;
                q.add(new Log(nextRow,nextCol,cur.dir,cur.dist+1));
            }
            //회전
            if(isAbleToTurn(cur)){
                int nextDir = (cur.dir+1)%2;
                if(visited[cur.row][cur.col][nextDir])
                    continue;
                visited[cur.row][cur.col][nextDir] = true;
                q.add(new Log(cur.row,cur.col,nextDir,cur.dist+1));
            }

        }

    }

    private static boolean isAbleToTurn(Log cur){
        for(int i=0;i<8;i++){
            int r = cur.row + dirRow[i];
            int c = cur.col + dirCol[i];
            if(r<0||r>=mapSize||c<0||c>=mapSize)
                return false;
            if(map[r][c]==1)
                return false;
        }
        return true;
    }
    private static boolean isAbleToMove(int nextRow, int nextCol, int dir) {
        if(dir==VERTICAL){
            if(nextRow<0||nextRow>=mapSize||nextCol-1<0||nextCol+1>=mapSize)
                return false;
            if(map[nextRow][nextCol+1]==1||map[nextRow][nextCol-1]==1||map[nextRow][nextCol]==1)
                return false;
        }else{
            if(nextRow-1<0||nextRow+1>=mapSize||nextCol<0||nextCol>=mapSize)
                return false;
            if(map[nextRow+1][nextCol]==1||map[nextRow-1][nextCol]==1||map[nextRow][nextCol]==1)
                return false;
        }
        return true;
    }

    public static void inputData() throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        mapSize = Integer.parseInt(br.readLine());
        map = new int[mapSize][mapSize];
        visited = new boolean[mapSize][mapSize][2];
        int cnt=0;
        int cntE=0;

        for(int i=0;i<mapSize;i++){
            String newStr = br.readLine();
            String[] input = newStr.split("");

            for(int j=0;j<mapSize;j++){
                if(input[j].equals("0")){
                    map[i][j]=0;
                }else if(input[j].equals("1")){
                    map[i][j]=1;
                }else if(input[j].equals("B")){
                    if(cnt==0){
                        if(j+1<mapSize&&input[j+1].equals("B")){
                            start = new Log(i,j+1,VERTICAL,0);
                        }else{
                            start = new Log(i+1,j,HORIZONTAL,0);
                        }
                        cnt++;
                    }
                    map[i][j]=0;
                }else{//E일
                    if(cntE==0){
                        if(j+1<mapSize&&input[j+1].equals("E")){
                            destination = new Log(i,j+1,VERTICAL,Integer.MAX_VALUE);
                        }else{
                            destination = new Log(i+1,j,HORIZONTAL,Integer.MAX_VALUE);
                        }
                        cntE++;
                    }
                    map[i][j]=0;
                }

            }
        }
    }

    static class Log{
        int row;
        int col;
        int dir; //0 가로 1 세
        int dist;
        public Log(int row, int col, int dir,int dist) {
            this.row = row;
            this.col = col;
            this.dir = dir;
            this.dist = dist;
        }
        public boolean isEnd(){
            if(this.row==destination.row && this.col == destination.col && this.dir == destination.dir)
                return true;
            return false;
        }
    }


}
