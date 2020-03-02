import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Main  {

    static int N,M,H; // N 가로, H 세로
    static int value=100000;
    static boolean[][] map;
    static ArrayList<Node> lader;
    static Node[] selected;

    public static void main(String[] args) throws IOException {


        init();

        if(M!=0) {
            dfs(1, 1, 1);
            dfs(1, 1, 2);
            dfs(1, 1, 3);
        }
        else
            value=0;

        if(value==100000)
            value=-1;

        System.out.println(value);


    }

    public static void init() throws IOException {

        int index1,index2;

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        N=Integer.parseInt(st.nextToken()); M=Integer.parseInt(st.nextToken()); H=Integer.parseInt(st.nextToken());
        map=new boolean[N+1][H+1];
        selected=new Node[4];
        lader=new ArrayList<Node>();

        for(int i=1;i<=M;i++){
            st=new StringTokenizer(br.readLine());
            index1=Integer.parseInt(st.nextToken()); index2=Integer.parseInt(st.nextToken());
            map[index2][index1]=true;
        }

        for(int i=1;i<N;i++){
            for(int j=1;j<=H;j++){
                lader.add(new Node(i,j));
            }
        }

    }

    public static int calculate(int count){

        Node temp;
        boolean[][] copy_map=new boolean[N+1][H+1];

        int col,row,start;

        for(int i=1;i<=N;i++)
            System.arraycopy(map[i],1,copy_map[i],1,H);

        for(int i=1;i<selected.length;i++) {

            if(selected[i]==null)
                continue;

            temp = selected[i];
            if (copy_map[temp.x][temp.y] == true)
                count--;
            else {
                copy_map[temp.x][temp.y] = true;
            }
        }

        for(col=1;col<=N;col++){

            start=col;
            row=1;
            while(row!=H+1) {

                if (copy_map[start][row] == true) { // 오른쪽 이동
                    start++;
                    row++;
                }
                else if (start - 1 > 0 && copy_map[start - 1][row] == true) { // 왼쪽이동
                    start--;
                    row++;
                }
                else
                    row++;
            }

            if(start==col)
                continue;
            else
                break;
        }

        if(col==N+1)
            return count;
        else
            return -1;


    }

    public static void dfs(int num,int depth,int C){

        int count;

        if(depth==C+1){
            count=calculate(C);
            if(count!=-1){
                value=Math.min(value,count);
            }
            return;
        }

        for(int index=num;index<=lader.size();index++){
            if(lader.get(index-1).visit==false) {
                selected[depth] = lader.get(index - 1);
                lader.get(index-1).visit=true;
            }
            dfs(index+1,depth+1,C);
            lader.get(index-1).visit=false;
        }

    }
}

class Node{
    int x;
    int y;
    boolean visit;

    Node(int x,int y){
        this.x=x;
        this.y=y;
        this.visit = false;
    }
}
