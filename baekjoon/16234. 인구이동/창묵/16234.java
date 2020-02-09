import java.util.Scanner;
import java.lang.Math;

public class Main {

    static int map_size;
    static int least_data;
    static int maximum_data;

    static int sum;
    static int member_cnt;
    static int move_cnt;
    static int total_move_cnt;

    static int[][] map;
    static int[][] visit;
    static int[][] location;

    static int[] dx={0,0,-1,1};
    static int[] dy={1,-1,0,0};

    public static void main(String[] args) {

        setMap();

        while(true){
            calculate();

            if(move_cnt==0)
                break;
            else
                total_move_cnt++;

            init();

        }
        System.out.print(total_move_cnt);
    }

    public static void init(){
        move_cnt=0;

        for(int i=0;i<map_size;i++)
            for(int j=0;j<map_size;j++)
                visit[i][j]=0;
    }

    public static void setMap(){

        Scanner in = new Scanner(System.in);

        map_size=in.nextInt();
        least_data=in.nextInt();
        maximum_data=in.nextInt();

        map = new int[map_size][map_size];
        visit=new int[map_size][map_size];
        location=new int[(int)Math.pow(map_size,2)+1][2];

        for(int i=0;i<map_size;i++){
            for(int j=0;j<map_size;j++){
                map[i][j]=in.nextInt();
            }
        }
    }

    public static void dfs(int X,int Y){

        int newX,newY;
        int bias;

        for(int i=0;i<4;i++){
            newX=X+dx[i];
            newY=Y+dy[i];

            if(newX <0 || newY <0 || newX >=map_size || newY >=map_size)
                continue;

            if(visit[newX][newY]==0){

                bias=Math.abs(map[newX][newY]-map[X][Y]);

                if(bias>=least_data && bias <=maximum_data){
                    visit[newX][newY]=1;

                    location[++member_cnt][0]=newX;
                    location[member_cnt][1]=newY;
                    sum+=map[newX][newY];

                    dfs(newX,newY);
                }


            }
        }

    }

    public static void calculate(){

        for(int i=0;i<map_size;i++){

            for(int j=0;j<map_size;j++){

                if(visit[i][j]==0) {

                    visit[i][j] = 1;
                    location[++member_cnt][0]=i;
                    location[member_cnt][1]=j;

                    sum=sum+map[i][j];
                    dfs(i, j);
                }

                if(member_cnt>=1)
                    move();
            }

        }

    }

    public static void move(){

        int average_sum=sum/member_cnt;

            for (int i = 1; i <= member_cnt; i++) {
                map[location[i][0]][location[i][1]] = average_sum;

                location[i][0] = 0;
                location[i][1] = 0;
            }

            if(member_cnt!=1)
                move_cnt=1;

            sum=0;
            member_cnt=0;
    }
}
