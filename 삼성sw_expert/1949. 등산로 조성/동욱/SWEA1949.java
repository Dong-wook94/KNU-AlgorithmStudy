/////////////////////////////////////////////////////////////////////////////////////////////
// 기본 제공코드는 임의 수정해도 관계 없습니다. 단, 입출력 포맷 주의
// 아래 표준 입출력 예제 필요시 참고하세요.
// 표준 입력 예제
// int a;
// double b;
// char g;
// String var;
// long AB;
// a = sc.nextInt();                           // int 변수 1개 입력받는 예제
// b = sc.nextDouble();                        // double 변수 1개 입력받는 예제
// g = sc.nextByte();                          // char 변수 1개 입력받는 예제
// var = sc.next();                            // 문자열 1개 입력받는 예제
// AB = sc.nextLong();                         // long 변수 1개 입력받는 예제
/////////////////////////////////////////////////////////////////////////////////////////////
// 표준 출력 예제
// int a = 0;                            
// double b = 1.0;               
// char g = 'b';
// String var = "ABCDEFG";
// long AB = 12345678901234567L;
//System.out.println(a);                       // int 변수 1개 출력하는 예제
//System.out.println(b); 		       						 // double 변수 1개 출력하는 예제
//System.out.println(g);		       						 // char 변수 1개 출력하는 예제
//System.out.println(var);		       				   // 문자열 1개 출력하는 예제
//System.out.println(AB);		       				     // long 변수 1개 출력하는 예제
/////////////////////////////////////////////////////////////////////////////////////////////

import java.io.*;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class SWEA1949
{
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    static int[][] map;
    static int topHeight;
    static ArrayList<Mountain> topList;
    static int maxLength = 0;
    static int dirRow[] = {1,0,-1,0};
    static int dirCol[] = {0,-1,0,1};
    static boolean[][] visited;
    public static void main(String args[]) throws Exception
    {
      // System.setIn(new FileInputStream("input.txt"));

        int T = Integer.parseInt(br.readLine());

        for(int test_case = 1; test_case <= T; test_case++)
        {
            System.out.print("#"+test_case+" ");
            testCase();
        }
    }

    private static void testCase() throws IOException {
        StringTokenizer st = new StringTokenizer(br.readLine());
        int N = Integer.parseInt(st.nextToken());
        int K = Integer.parseInt(st.nextToken());
        topHeight = 0;
        topList = new ArrayList<>();
        maxLength = 0;
        map = new int[N][N];
        visited = new boolean[N][N];
        for(int i=0;i<N;i++){
            st = new StringTokenizer(br.readLine());
            for(int j=0;j<N;j++){
                map[i][j] = Integer.parseInt(st.nextToken());
                if(map[i][j]>topHeight){
                    topHeight = map[i][j];
                    topList.clear();
                    topList.add(new Mountain(i,j,topHeight));
                }
                else if(map[i][j]==topHeight){
                    topList.add(new Mountain(i,j,topHeight));
                }
            }
        }
        for(int i=0;i<topList.size();i++){
            Mountain cur = topList.get(i);
            visited[cur.row][cur.col] = true;
            dfs(cur,K,1,true);
            visited[cur.row][cur.col] = false;
        }
        System.out.println(maxLength);
    }

    private static void dfs(Mountain cur, int k, int length,boolean chance) {
        if(maxLength<length)
            maxLength =length;

        for(int i=0;i<4;i++){
            int nextRow = cur.row + dirRow[i];
            int nextCol = cur.col + dirCol[i];
            if(nextRow<0 || nextCol<0 || nextRow>=map.length || nextCol>=map.length)
                continue;
            if(!visited[nextRow][nextCol]){
                if(map[nextRow][nextCol]<cur.height){
                    visited[nextRow][nextCol] = true;
                    dfs(new Mountain(nextRow,nextCol,map[nextRow][nextCol]),k,length+1,chance);
                    visited[nextRow][nextCol] = false;
                }
                else{
                    if(!chance)
                        continue;
                    int cut = map[nextRow][nextCol]-cur.height+1 ;
                    if(cut<=k){
                        visited[nextRow][nextCol] = true;
                        int temp = map[nextRow][nextCol];
                        map[nextRow][nextCol] = (cur.height -1);
                        dfs(new Mountain(nextRow,nextCol,map[nextRow][nextCol]),k - cut,length+1,false);
                        map[nextRow][nextCol] = temp;
                        visited[nextRow][nextCol] = false;
                    }
                }
            }
        }
    }

    static class Mountain{
        int row;
        int col;
        int height;

        public Mountain(int row, int col, int height) {
            this.row = row;
            this.col = col;
            this.height = height;
        }
    }
}