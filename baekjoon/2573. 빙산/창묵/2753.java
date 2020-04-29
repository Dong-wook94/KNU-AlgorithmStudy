import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.StringTokenizer;


public class Main {

  static int N,M;
  static int[][] map;
  static List<Node> nodeList=new ArrayList<>();

  static int[] dx ={0,0,1,-1};
  static int[] dy ={-1,1,0,0};
  public static void main(String argv[]) throws IOException {

    init();
    System.out.println(calculate());
  }

  public static void init() throws IOException {

    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(br.readLine());
    N=Integer.parseInt(st.nextToken());
    M=Integer.parseInt(st.nextToken());
    map=new int[N][M];

    for(int i=0;i<N;i++){
      st=new StringTokenizer(br.readLine());
      for(int j=0;j<M;j++){
        map[i][j]=Integer.parseInt(st.nextToken());
        if(map[i][j]!=0){
          nodeList.add(new Node(i,j,map[i][j]));
        }
      }
    }

  }

  public static void checkmeltCnt(){
    Node cur;
    int nx,ny;

    for(int i=0;i<nodeList.size();i++){
      cur=nodeList.get(i);
      cur.meltCnt=0;


        for(int j=0;j<4;j++){
          nx=cur.x+dx[j];
          ny=cur.y+dy[j];

          if(map[nx][ny]==0)
            cur.meltCnt++;
        }

    }

  }

  public static int calculate(){

    int year=0;

    while(true){
      year++;
      checkmeltCnt();
      melting();

      if(nodeList.size()==0)
        return 0;

      if(mapping()){
        return year;
      }
      else{
        if(nodeList.size()==1)
          return 0;
      }

    }

  }

  public static boolean mapping(){

    int[][] mapTemp=copyMap();
    Queue<Node> queue = new LinkedList<>();
    queue.add(nodeList.get(0));
    Node cur;
    int nx,ny;
    int meltCnt=nodeList.size()-1;


    while(!queue.isEmpty()){
      cur=queue.poll();
      for(int i=0;i<4;i++){
        nx=cur.x+dx[i];
        ny=cur.y+dy[i];
        mapTemp[cur.x][cur.y]=-1;

        if(mapTemp[nx][ny]!=-1 && mapTemp[nx][ny]!=0){
          mapTemp[nx][ny]=-1;
          meltCnt--;
          queue.add(new Node(nx,ny,mapTemp[nx][ny]));
        }
      }
    }

    if(meltCnt>0)
      return true;
    else
      return false;

  }

  public static int[][] copyMap(){

    int[][] mapTemp = new int[N][M];

    for(int i=0;i<N;i++){
      for(int j=0;j<M;j++){
        mapTemp[i][j] = map[i][j];
      }
    }

    return mapTemp;
  }

  public static void melting(){

    Node cur;

    for(int i=0;i<nodeList.size();i++){
      cur=nodeList.get(i);
      cur.height=cur.height-cur.meltCnt;
      if(cur.height<=0){
        map[cur.x][cur.y]=0;
        nodeList.remove(i);

        i--;
      }
    }

  }


}


class Node{
  int x;
  int y;
  int height;
  int meltCnt;

  Node(int x,int y, int height){
    this.x=x;
    this.y=y;
    this.height=height;
    meltCnt=0;
  }
}