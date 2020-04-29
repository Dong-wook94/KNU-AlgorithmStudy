import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;
import java.util.jar.JarEntry;

public class Main{

  static final int plus = 0;
  static final int minus = 1;
  static final int mult = 2;
  static final int divide = 3;

  static List<Integer> indexList = new ArrayList<>();
  static int maxValue=Integer.MIN_VALUE;
  static int minValue=Integer.MAX_VALUE;

  static int[] numArr;
  static int[] operArr;

  public static void main(String argv[]) throws IOException {

    init();
    dfs(0,0);

    System.out.println(maxValue);
    System.out.println(minValue);
  }

  public static void init() throws IOException {
    int numCnt;

    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(br.readLine());
    numCnt=Integer.parseInt(st.nextToken());

    numArr=new int[numCnt];
    st=new StringTokenizer(br.readLine());
    for(int i=0;i<numCnt;i++){
        numArr[i]=Integer.parseInt(st.nextToken());
    }

    st=new StringTokenizer(br.readLine());
    operArr=new int[4];

    for(int i=0;i<4;i++){
      operArr[i]=Integer.parseInt(st.nextToken());
    }

  }

  public static void dfs(int index,int cnt){

    if(cnt==numArr.length-1){
      calculate();
      return ;
    }

    for(int num=index;num<operArr.length;num++){
      if(operArr[num]!=0){
        operArr[num]--;
        indexList.add(num);
        dfs(0,cnt+1);
        operArr[num]++;
        indexList.remove(indexList.size()-1);
      }
    }

  }

  public static void calculate() {
    List<Integer> operList = new ArrayList<>();

    int sum=0;

    for (int i = 0; i < indexList.size(); i++) {
      operList.add(indexList.get(i));
    }

    sum=numArr[0];
    for(int j=0,i=1;i<numArr.length;i=i+1,j=j+1){
        sum=oper(sum,operList.get(j),numArr[i]);
    }

    maxValue=Math.max(maxValue,sum);
    minValue = Math.min(minValue, sum);

  }

  public static int oper(int num1,int oper,int num2){
    if(oper==plus){
      return num1+num2;
    }
    else if(oper == minus){
      return num1-num2;
    }
    else if(oper == mult){
      return num1*num2;
    }
    else if(oper == divide){
      int divide = Math.abs(num1) / Math.abs(num2);

      if(num1<0 && num2>0 || num1>0 && num2<0){
        divide=divide*-1;
      }
      return divide;
    }

    return -1;
  }
}