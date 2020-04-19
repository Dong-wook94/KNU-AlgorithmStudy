import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main{

  static ArrayList<ArrayList<Integer>> station = new ArrayList<>();
  static int[] distance;
  static int N,K,M;

  public static void main(String argv[]) throws IOException {

    init();
    findNode();

    if(distance[N]==0)
      System.out.println(-1);
    else
      System.out.println(distance[N]);

  }

  public static void init() throws IOException {

    int index;

    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st= new StringTokenizer(br.readLine());
    N=Integer.parseInt(st.nextToken());
    K=Integer.parseInt(st.nextToken());
    M=Integer.parseInt(st.nextToken());

    distance=new int[N+M+1];

   for(int i=0;i<=N+M;i++){
     station.add(new ArrayList());
   }

   for(int i=1;i<=M;i++){
     st=new StringTokenizer(br.readLine());
     for(int j=0;j<K;j++){
        index=Integer.parseInt(st.nextToken());
        station.get(N+i).add(index);
        station.get(index).add(N+i);
     }
   }

  }

  public static void findNode(){

    Queue<Integer> que = new LinkedList<>();
    que.add(1);
    distance[1]=1;
    int cur;
    int nindex;

    while(!que.isEmpty()){
      cur=que.poll();

      if(cur==N)
        break;

      for(int i=0;i<station.get(cur).size();i++){
        nindex=station.get(cur).get(i);

        if(nindex>N && distance[nindex]==0){
          distance[nindex]=distance[cur];
          que.add(nindex);
        }
        else if(distance[nindex]==0){
          distance[nindex]=distance[cur]+1;
          que.add(nindex);
        }
      }
    }


  }
}
