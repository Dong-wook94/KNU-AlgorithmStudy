import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Baekjoon12865 {
    static int N,K;
    static int[] weight;
    static int[] value;
    static int[] dp;


    public static void main(String[] args) throws IOException {
        inputData();
        for(int i=1;i<=N;i++){
            for(int j=K; j>=0;j--){
                if(weight[i]<=j)
                    dp[j] = Math.max(dp[j] , dp[j- weight[i]]+ value[i]);
            }
        }
        System.out.println(dp[K]);
    }

    public static void inputData() throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        weight = new int[N+1];
        value = new int[N+1];
        dp = new int[K+1];

        for(int i=1;i<=N;i++){
            st = new StringTokenizer(br.readLine());
            weight[i] = Integer.parseInt(st.nextToken());
            value[i] = Integer.parseInt(st.nextToken());
        }
    }
}
