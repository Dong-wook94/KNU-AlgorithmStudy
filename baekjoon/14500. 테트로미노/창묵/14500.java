import java.util.Scanner;

public class Main {

    static int block_cnt;
    static int map_row;
    static int map_cul;
    static int max_sum;

    static int[][] map = new int[500][500];
    static int[][] visit = new int[500][500];

    static int[] dx={0,0,-1,1};
    static int[] dy={1,-1,0,0};

    static int[][] ex={{0,0,1},{0,0,-1},{-1,1,0},{-1,1,0}};
    static int[][] ey={{-1,1,0},{-1,1,0},{0,0,1},{0,0,-1}};


    public static void main(String[] args) {

        initMap();
        calculator();
        System.out.print(max_sum);

    }

    public static void initMap(){
        Scanner in = new Scanner(System.in);
        map_row=in.nextInt();
        map_cul=in.nextInt();

        for(int i=0;i<map_row;i++){
            for(int j=0;j<map_cul;j++){
                map[i][j]=in.nextInt();
            }
        }
    }

    public static void except(int X,int Y,int cnt,int total){

        int newX,newY;

        for(int i=0;i<4;i++){

            cnt=1;
            total=map[X][Y];

            for(int j=0;j<3;j++) {
                newX = X + ex[i][j];
                newY = Y + ey[i][j];

                if(newX < 0 || newY <0 || newX >= map_row || newY >= map_cul)
                    break;

                else{
                    total=map[newX][newY]+total;

                    if(++cnt==4){

                        if(total>max_sum)
                            max_sum=total;
                    }
                }
            }
        }
    }
    public static void dfs(int X,int Y,int cnt,int total){

        int newX,newY;

        if(cnt==4){
            if(total>max_sum)
                max_sum=total;
            return;
        }

        for(int i=0;i<dx.length;i++){
            newX = X + dx[i];
            newY = Y + dy[i];

            if(newX < 0 || newY <0 || newX >= map_row || newY >= map_cul)
                continue;

            if(visit[newX][newY]==0){
                visit[newX][newY]=1;
                dfs(newX,newY,cnt+1,total+map[newX][newY]);
                visit[newX][newY]=0;
            }
        }

    }

    public static void calculator(){

        for(int i=0;i<map_row;i++){

            for(int j=0;j<map_cul;j++){

                if(visit[i][j]==0) {
                    visit[i][j] = 1;
                    dfs(i,j,1, map[i][j]);
                    visit[i][j]=0;
                }

                except(i,j,1,map[i][j]);
            }
        }
    }

}
