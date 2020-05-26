
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Stack;
import java.util.StringTokenizer;



public class Main{


  static LinkedList<Integer>[] list;
  static Stack<Integer> result = new Stack<>();

  static boolean check[];
  static boolean visit[];
  static boolean cycle;
  static int N;


  public static void main(String argv[]) throws IOException {

    init();

    for(int i=1;i<=N;i++){
      if(!check[i])
        dfs(i);
      if(cycle==true)
        break;
    }
      if(cycle==false) {
        for (int i = 0; i < N; i++) {
          System.out.println(result.pop());
        }
      }

  }

  public static void init() throws IOException {

    int M,prev,cur;
    BufferedReader br =new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st;


    st=new StringTokenizer(br.readLine());
    N=Integer.parseInt(st.nextToken());
    M=Integer.parseInt(st.nextToken());

    check=new boolean[N+1];
    visit=new boolean[N+1];
    list=new LinkedList[N+1];

    for(int i=1;i<=N;i++){
      list[i]=new LinkedList<>();
    }

    for(int i=1;i<=M;i++){
      st=new StringTokenizer(br.readLine());
      int k=Integer.parseInt(st.nextToken());
      prev=Integer.parseInt(st.nextToken());
      for(int j=1;j<k;j++){
        cur=Integer.parseInt(st.nextToken());
        list[prev].add(cur);
        prev=cur;
      }
    } // make LinkedList.


  }

  public static void dfs(int cur){

    if(visit[cur]==true){
      System.out.println(0);
      cycle= true;
      return;
    }


    int size=list[cur].size();
    int next;

    for(int i=0;i<size;i++){
      next=list[cur].get(i);
      if(check[next]==false){
        visit[cur]=true;
        dfs(next);
      }
    }
    check[cur]=true;
    result.push(cur);
    Arrays.fill(visit,false);
  }

}