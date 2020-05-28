import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Baekjoon1987 {
    static final int COUNT_OF_ALPHABET = 26;
    static int rowSize;
    static int colSize;
    static char[][] map;
    static boolean[] visited;
    static int[] dirRow={1,0,-1,0};
    static int[] dirCol={0,-1,0,1};
    static int maxDistance=0;
    public static void input() throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        rowSize = Integer.parseInt(st.nextToken());
        colSize = Integer.parseInt(st.nextToken());
        map = new char[rowSize+1][colSize+1];
        visited = new boolean[COUNT_OF_ALPHABET];
        for(int i=1;i<=rowSize;i++){
            String str = br.readLine();
            for(int j=1;j<=colSize;j++){
                map[i][j] = str.charAt(j-1);
            }
        }
    }

    public static void dfs(int row, int col, int cnt){
        visited[map[row][col]-'A'] = true;
        for(int i=0;i<4;i++){
            int nextRow = row + dirRow[i];
            int nextCol = col + dirCol[i];

            if(isRange(nextRow, nextCol)){
                if(!visited[map[nextRow][nextCol]-'A'])
                    dfs(nextRow,nextCol,cnt+1);
            }
        }
        visited[map[row][col]-'A'] = false;
        maxDistance = Math.max(maxDistance,cnt);
    }

    public static boolean isRange(int nextRow, int nextCol) {
        return nextRow>0 && nextCol>0 && nextRow<=rowSize && nextCol<=colSize;
    }

    public static void main(String[] args) throws IOException {
        input();
        dfs(1,1,1);
        System.out.println(maxDistance);
    }
}
