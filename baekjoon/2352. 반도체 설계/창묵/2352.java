import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;



public class Main{

  static int LineCnt;
  static int[] linkIndex;
  static List<Integer> link=new ArrayList<>();



  public static void main(String argv[]) throws IOException {

    init();
    System.out.println(calculate());
  }

  public static void init() throws IOException {

    BufferedReader br =new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st;
    LineCnt=Integer.parseInt(br.readLine());

    linkIndex=new int[LineCnt];

    st=new StringTokenizer(br.readLine());
    for(int i=0;i<LineCnt;i++){
        linkIndex[i]=Integer.parseInt(st.nextToken());
      }
    }

    public static int calculate(){

    link.add(linkIndex[0]);

    for(int i=1;i<LineCnt;i++){
      if(link.get(link.size()-1)<linkIndex[i]){
        link.add(linkIndex[i]);
      }
      else{
        int index=0;
        for(int j=0;j<link.size();j++){
          if(link.get(j)>linkIndex[i]) {
            index = j;
            break;
          }
        }
        link.remove(index);
        link.add(index,linkIndex[i]);
      }

    }

    return link.size();

  }



}




