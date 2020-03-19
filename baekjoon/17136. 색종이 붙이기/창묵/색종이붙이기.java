import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {

    static int[][] map = new int[10][10];
    static int[] paperCnt = new int[6];
    static int restOne;
    static int minValue=26;

    public static void main(String args[]) throws IOException {

        init();
        dfs(0,0,0);

        if(minValue==26)
            System.out.println(-1);
        else
            System.out.println(minValue);

    }

    public static void init() throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        for (int row = 0; row < 10; row++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            for (int col = 0; col < 10; col++) {
                map[row][col] = Integer.parseInt(st.nextToken());
                if (map[row][col] == 1)
                    restOne++;
            }
        }

        Arrays.fill(paperCnt, 5);
    }


    public static void dfs(int x, int y, int depth) {

        if (restOne == 0) {
            minValue = Math.min(minValue, depth);
        }

        if (depth > minValue) {
            return;
        }

        if(y>=10){
            y=0;
            x+=1;
            if(x>=10)
                return;
        }

        if (map[x][y] != 1) {
            dfs(x, y + 1, depth);
            return;
        }

        for (int paperIndex = 5; paperIndex > 0; paperIndex--) {

            if (paperCnt[paperIndex] == 0)
                continue;

            if (checkPaper(paperIndex, x, y)) {
                paste(x, y, paperIndex, 0);
                paperCnt[paperIndex]--;
                restOne-=paperIndex*paperIndex;

                dfs(x, y + 1, depth + 1);

                paste(x, y, paperIndex, 1);
                paperCnt[paperIndex]++;
                restOne+=paperIndex*paperIndex;
            }
        }


    }

    public static boolean checkPaper(int paperIndex, int x, int y) {

        int paperCnt=paperIndex*paperIndex;

        for (int row = x; row < x + paperIndex; row++) {

            for (int col = y; col < y + paperIndex; col++) {
                try{
                    if(map[row][col]==1)
                        paperCnt--;
                }
                catch(Exception e){
                    return false;
                }
            }
        }

        if(paperCnt==0)
            return true;
        else
            return false;

    }

    public static void paste(int x, int y,int paperIndex, int val) {
        for (int row = x; row < x + paperIndex; row++) {
            for (int col = y; col < y + paperIndex; col++) {
                map[row][col] = val;
            }
        }
    }

}