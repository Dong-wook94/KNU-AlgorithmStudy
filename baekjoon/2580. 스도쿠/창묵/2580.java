import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;


public class Main{

  static int[][] map;

  static List<Node> nodeList = new ArrayList<>();
  static List<Integer> valueList = new ArrayList<>();

  public static void main(String argv[]) throws IOException {

    init();
    dfs(1,0);

  }

  public static void init() throws IOException {



    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st;
    map=new int[9][9];

    for(int i=0;i<9;i++){
      st = new StringTokenizer(br.readLine());
      for(int j=0;j<9;j++){
        map[i][j] = Integer.parseInt(st.nextToken());

        if(map[i][j]==0){
          nodeList.add(new Node(i,j));
        }
      }
    }
  }

  public static void dfs(int num,int index){

    if(index==nodeList.size()){
      printMap();
      System.exit(0);
      return ;
    }

    for(int value=num;value<=9;value++){
      Node cur = nodeList.get(index);
      if(checkRow(cur,value)&&checkCol(cur,value)&&checkSquare(cur,value)){
        map[cur.x][cur.y]=value;
        dfs(1,index+1);
        map[cur.x][cur.y]=0;
      }
    }
  }

  public static void printMap(){
    for(int i=0;i<9;i++){
      for (int j=0;j<9;j++){
        System.out.printf("%d ",map[i][j]);
      }
      System.out.println();
    }
  }


  public static boolean checkRow(Node node,int val){
    int curCol = node.y;
    for(int i=0;i<9;i++){
      if(map[i][curCol]==val)
        return false;
    }

    return true;
  }

  public static boolean checkCol(Node node,int val){
    int curRow = node.x;

    for(int i=0;i<9;i++){
      if(map[curRow][i]==val){
        return false;
      }
    }

    return true;
  }
  public static boolean checkSquare(Node node,int val){
    int squareX = node.x / 3;
    int squareY = node.y / 3;

    for(int curRow=squareX*3;curRow<(squareX*3)+3;curRow++){
      for(int curCol=squareY*3;curCol<(squareY*3)+3;curCol++){
        if(map[curRow][curCol]==val){
          return false;
        }
      }
    }

    return true;
  }



}

class Node {

  int x;
  int y;

  Node(int x, int y) {
    this.x = x;
    this.y = y;
  }
}

