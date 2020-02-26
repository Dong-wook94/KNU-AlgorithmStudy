import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Main  {

    static int[][] map = new int[201][201];
    static int row,col,k;
    static int row_cnt=3,col_cnt=3;

    public static void main(String[] args) throws IOException {


        init();
        System.out.println(calculate());

    }

    public static void init() throws IOException {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        row=Integer.parseInt(st.nextToken()); col=Integer.parseInt(st.nextToken()); k=Integer.parseInt(st.nextToken());

        for(int i=1;i<=3;i++) {
         st = new StringTokenizer(br.readLine());
            for (int j = 1; j <= 3; j++) {
                map[i][j] = Integer.parseInt(st.nextToken());
            }
        }

    }

    public static int calculate(){

        int time=0;

        while(map[row][col]!=k){

            if(row_cnt>=col_cnt){
                row_calculate();
                time++;
            }
            else{
                col_calculate();
                time++;
            }

            if(time>100)
                return -1;

        }

        return time;
    }

    public static void row_calculate(){

        int[] cnt;
        int insert_index=1;
        ArrayList<Node> row_arr;

        for(int i=1;i<=row_cnt;i++){
            cnt=new int[101];
            insert_index=1;
            for(int j=1;j<=col_cnt;j++){
                cnt[map[i][j]]++;
            }

            row_arr = makeArrayList(cnt);
            Collections.sort(row_arr,new MyComparator());

            while(!row_arr.isEmpty()){
                Node temp = row_arr.remove(0);
                map[i][insert_index]=temp.number;
                map[i][insert_index+1]=temp.count;
                insert_index+=2;

                if(insert_index>100)
                    break;
            }

            for(int j=insert_index;j<=200;j++)
                map[i][j]=0;

            if(col_cnt<insert_index-1)
                col_cnt=insert_index-1;
        }

    }


    public static void col_calculate(){

        int[] cnt;
        int insert_index=1;
        ArrayList<Node> col_arr;

        for(int i=1;i<=col_cnt;i++){
            cnt=new int[101];
            insert_index=1;
            for(int j=1;j<=row_cnt;j++){
                cnt[map[j][i]]++;
            }

            col_arr = makeArrayList(cnt);
            Collections.sort(col_arr,new MyComparator());

            while(!col_arr.isEmpty()){
                Node temp = col_arr.remove(0);
                map[insert_index][i]=temp.number;
                map[insert_index+1][i]=temp.count;
                insert_index+=2;

                if(insert_index>100)
                    break;
            }

            for(int j=insert_index;j<=200;j++)
                map[j][i]=0;

            if(row_cnt<insert_index-1)
                row_cnt=insert_index-1;
        }

    }

    public static ArrayList<Node> makeArrayList(int[] cnt){
        ArrayList<Node> temp= new ArrayList<>();

        for(int i=1;i<=100;i++){
            if(cnt[i]>0)
                temp.add(new Node(i,cnt[i]));
        }

        return temp;
    }

}

class MyComparator implements Comparator<Node>{
    @Override
    public int compare(Node n1,Node n2){
        if(n1.count>n2.count)
            return 1;
        else if(n1.count==n2.count){
            if(n1.number>n2.number)
                return 1;
            else
                return -1;
        }
        else
            return -1;
    }

}

class Node {
    int number;
    int count;

    Node(int number,int count){
        this.number=number;
        this.count= count;
    }

}
