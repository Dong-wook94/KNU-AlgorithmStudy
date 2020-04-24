

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.StringTokenizer;



public class Main{

  static int[][] map;
  static ArrayList<Node> indexList = new ArrayList<>();
  static int appleCnt,N;
  static HashMap<Integer,String> changelist = new HashMap<>();


  public static void main(String argv[]) throws IOException {

    init();
    System.out.println(calculate());

  }

  public static void init() throws IOException {

    int K,L;
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st;
    N = Integer.parseInt(br.readLine());
    map=new int[N][N];
    K = Integer.parseInt(br.readLine());
    appleCnt=K;
    for(int i=0;i<K;i++){
      st = new StringTokenizer(br.readLine());
      int row = Integer.parseInt(st.nextToken());
      int col = Integer.parseInt(st.nextToken());
      map[row-1][col-1]=-1;
    }
    L = Integer.parseInt(br.readLine());

    for(int i=0;i<L;i++){
      st = new StringTokenizer(br.readLine());
      int index=Integer.parseInt(st.nextToken());
      String dir = st.nextToken();
      changelist.put(index,dir);
    }

  }

  public static int calculate(){

    int dx[]={0,1,0,-1};
    int dy[]={1,0,-1,0};
    int headIndex=0;
    int tailIndex=0;
    int curX,curY,tailX,tailY;
    int dir=0;
    int curTime=0;
    indexList.add(new Node(0,0)); // 0 0 에서 시작한다.

    while(true){
      curX=indexList.get(headIndex).x; // head
      curY=indexList.get(headIndex).y;
      tailX = indexList.get(tailIndex).x; // tail
      tailY = indexList.get(tailIndex).y;

      curX+=dx[dir]; // head move.
      curY+=dy[dir];

      curTime++;

      if(curX<0 || curX>=N || curY <0 || curY>=N){ // 벽에 부딪힐 때
        return curTime;
      }
      if(map[curX][curY]==1){  // 자기 몸에 부딪힐 때
        return curTime;
      }

      if(map[curX][curY]==-1){ // 사과를 만났을 때
        map[curX][curY]=1; // 머리로 늘리고
        indexList.add(new Node(curX,curY)); // 뱀의 길이를 늘린다.
        headIndex++;
      }
      else{ // 사과를 만나지 않았을 때
        map[curX][curY]=1; // 머리 늘리기
        map[tailX][tailY]=0; // 꼬리 줄이기
        indexList.add(new Node(curX,curY)); // 머리 index추가
        indexList.remove(tailIndex); // 꼬리쪽 index 제거
      }

      dir=checkTime(curTime,dir); // 1초에서 시작
    }

  }

  public static int checkTime(int curTime,int dir) {

    if (changelist.containsKey(curTime)) {
      if (changelist.get(curTime).equals("L")) {
        dir = (4 + (dir - 1)) % 4;
      } else if (changelist.get(curTime).equals("D")) {
        dir = (dir + 1) % 4;
      }
    }

    return dir;
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
