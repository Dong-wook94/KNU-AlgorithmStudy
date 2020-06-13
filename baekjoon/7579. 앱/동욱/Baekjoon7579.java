import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Baekjoon7579 {

    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static int N,M;
    static int memoryByte[];
    static int cost[];
    static int dp[][];
    static int result=Integer.MAX_VALUE;

    public static void main(String[] args) throws IOException {
        inputData();
        dp[1][cost[1]] = memoryByte[1];
        for(int i=2;i<=N;i++){
            for(int j=0;j<=10000;j++){
                if(j-cost[i]>=0){
                    dp[i][j] = Math.max(dp[i][j],dp[i-1][j-cost[i]]+memoryByte[i]);
                }
                dp[i][j] = Math.max(dp[i][j],dp[i-1][j]);

                if(dp[i][j]>=M){
                    result = Math.min(result,j);
                }
            }
        }

        System.out.println(result);

    }

    public static void inputData() throws IOException {
        StringTokenizer st = new StringTokenizer(br.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        memoryByte = new int[N+1];
        cost = new int[N+1];
        dp = new int[N+1][10001];
        st = new StringTokenizer(br.readLine());
        for(int i=1;i<=N;i++){
            memoryByte[i] = Integer.parseInt(st.nextToken());
        }
        st = new StringTokenizer(br.readLine());
        for(int i=1;i<=N;i++){
            cost[i] = Integer.parseInt(st.nextToken());
        }
    }
}
