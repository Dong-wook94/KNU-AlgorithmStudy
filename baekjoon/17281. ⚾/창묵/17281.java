import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.StringTokenizer;


public class Main{

  static int gameCnt;
  static int[][] ability;
  static int maxValue=Integer.MIN_VALUE;
  static List<Integer> playerArr = new ArrayList<>();
  static boolean[] check = new boolean[9];

  public static void main(String argv[]) throws IOException {

    init();
    dfs(1,0);
    System.out.println(maxValue);
  }

  public static void init() throws IOException {

    BufferedReader br =new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st;
    gameCnt=Integer.parseInt(br.readLine());

    ability=new int[gameCnt][9];
    for(int i=0;i<gameCnt;i++){
      st=new StringTokenizer(br.readLine());
      for(int j=0;j<9;j++){
        ability[i][j]=Integer.parseInt(st.nextToken());
      }
    }
  }

  public static void dfs(int number,int cnt){
    int value;
    if(cnt==8){
      playerArr.add(3,0);
      value=calculate();
      maxValue=Math.max(value,maxValue);
      playerArr.remove(3);
      return;
    }


    for(int index=number;index<9;index++){
      if(check[index]==false){
        check[index]=true;
        playerArr.add(index);
        dfs(1,cnt+1);
        check[index]=false;
        playerArr.remove(playerArr.size()-1);
      }
    }
  }

  public static int calculate(){
    int outCnt,groundPlayerCnt,curIndex,what;
    int curPlayer;
    int value=0;
    boolean[] ground = new boolean[4];

    curIndex=0;

    for(int i=0;i<gameCnt;i++){ // next Game
      outCnt =0;
      groundPlayerCnt=0;
      Arrays.fill(ground,false);

      while(true) {
        curPlayer = playerArr.get(curIndex);
        what=ability[i][curPlayer];

        if(what==0)
          outCnt++;
        else if(what==4){
          value+=groundPlayerCnt+1;
          Arrays.fill(ground,false);
          groundPlayerCnt = 0;
        }
        else{ // what 1 , 2 , 3
          int nj;

          for(int j=3;j>=1;j--){
            if(ground[j]==true){
              nj=j+what;

              if(nj>=4){
                value++;
                groundPlayerCnt--;
                ground[j]=false;
              }
              else {
                ground[j] = false;
                ground[nj] = true;
              }

            }
          }
          ground[what]=true; // insert ground
          groundPlayerCnt++;
        }

        curIndex=(curIndex+1)%9; // next Player

        if(outCnt==3)
          break;

      }
    }

    return value;
  }


}