
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;


public class Main{

  static int N,M,startX,startY;
  static final int east = 1;
  static final int west = 2;
  static final int north = 3;
  static final int south = 4;

  static List<Integer> dirList = new ArrayList<>();

  static int[][] map;
  static int[] dice= new int[6];





  public static void main(String argv[]) throws IOException {

    init();
    calculate();

  }

  public static void init() throws IOException {

    int cnt;

    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(br.readLine());
    N=Integer.parseInt(st.nextToken());
    M=Integer.parseInt(st.nextToken());
    startX=Integer.parseInt(st.nextToken());
    startY=Integer.parseInt(st.nextToken());
    cnt = Integer.parseInt(st.nextToken());
    map = new int[N][M];

    for(int i=0;i<N;i++){
      st = new StringTokenizer(br.readLine());
      for(int j=0;j<M;j++){
        map[i][j] = Integer.parseInt(st.nextToken());
      }
    }

    st = new StringTokenizer(br.readLine());
    for(int i=0;i<cnt;i++){
      dirList.add(Integer.parseInt(st.nextToken()));
    }
  }

  public static void calculate(){

    int nx=startX;
    int ny=startY;
    int prevx,prevy;
    int dir;
    int dx[]={0,0,-1,1};
    int dy[]={1,-1,0,0};

    for(int i=0;i<dirList.size();i++){
        dir=dirList.get(i)-1;
        prevx = nx;
        prevy = ny;
        nx+=dx[dir];
        ny+=dy[dir];

        if(nx<0 || nx>=N || ny<0 || ny>=M) {
          nx=prevx;
          ny=prevy;
          continue;
        }
        move(nx,ny,dir+1);
    }

  }

  public static void move(int x,int y,int dir){

      if(dir==east){
        swap(dice,3,5);
        swap(dice,1,4);
        swap(dice,4,5);
      }
      else if(dir==west){
        swap(dice,3,4);
        swap(dice,1,5);
        swap(dice,4,5);
      }
      else if(dir==south){
        swap(dice,0,3);
        swap(dice,1,2);
        swap(dice,0,2);
      }
      else if(dir==north){
        swap(dice,2,3);
        swap(dice,0,1);
        swap(dice,0,2);
      }

    if(map[x][y]==0){
      map[x][y]=dice[3];
    }
    else{
      dice[3]=map[x][y];
      map[x][y]=0;
    }

    System.out.println(dice[1]);

  }
  public static void swap(int[] arr,int index1,int index2){
    int temp;
    temp=arr[index1];
    arr[index1]=arr[index2];
    arr[index2]=temp;
  }
}