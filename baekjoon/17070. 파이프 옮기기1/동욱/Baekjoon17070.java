import java.util.Scanner;

public class Baekjoon17070 {
    static int mapSize;
    static final int VERTICAL=0;
    static final int HORIZONTAL=1;
    static final int DIAGONAL=2;
    static int[][] map;
    static int cnt =0;

    public static boolean isPossible(int row,int col, int dir, int nextDir){
        if(row>mapSize || col>mapSize)
            return false;
        if(nextDir==DIAGONAL){
            if(row+1>mapSize || col +1>mapSize)
                return false;
            if(map[row+1][col]==0 && map[row][col+1]==0 && map[row+1][col+1]==0)
                return true;
            return false;
        }else if(nextDir==VERTICAL){
            if(col+1>mapSize)
                return false;
            if(map[row][col+1]==0)
                return true;
            return false;
        }else{//HORIZONTAL
            if(row+1>mapSize)
                return false;
            if(map[row+1][col]==0)
                return true;
            return false;
        }
    }
    public static void dfs(int row,int col,int dir){
        if(row ==mapSize && col == mapSize){
            cnt++;
            return;
        }

        for(int i=0;i<3;i++){
            if(dir==VERTICAL && i==HORIZONTAL)
                continue;
            if(dir==HORIZONTAL && i==VERTICAL)
                continue;
            if(isPossible(row,col,dir,i)){
                if(i==DIAGONAL)
                    dfs(row+1,col+1,i);
                else if(i==VERTICAL)
                    dfs(row,col+1,i);
                else{
                    dfs(row+1,col,i);
                }
            }

        }
    }

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        mapSize = scan.nextInt();
        map = new int[mapSize+1][mapSize+1];

        for(int i=1;i<=mapSize;i++){
            for(int j=1;j<=mapSize;j++){
                map[i][j] = scan.nextInt();
            }
        }
        dfs(1,2,VERTICAL);
        System.out.println(cnt);
    }
}
