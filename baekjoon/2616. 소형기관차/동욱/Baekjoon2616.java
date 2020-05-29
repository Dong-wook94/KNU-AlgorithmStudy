import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Baekjoon2616 {

    static int[][] dp;
    static int[] train, sum;
    static int maxLength=0;

    public static void main(String[] args) throws IOException {
        BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int numOfCarriage = Integer.parseInt(st.nextToken());

        train = new int[numOfCarriage+1];
        st = new StringTokenizer(br.readLine());
        sum = new int[numOfCarriage+1];
        for(int i=1;i<=numOfCarriage;i++){
            train[i] = Integer.parseInt(st.nextToken());
            sum[i] = sum[i-1]+train[i];
        }

        maxLength = Integer.parseInt(br.readLine());
        dp = new int[4][numOfCarriage+1];

        for(int i=1;i<4;i++){
            for(int j=i*maxLength;j<=numOfCarriage;j++){
                dp[i][j] = Math.max(dp[i][j-1],(sum[j]-sum[j-maxLength])+ dp[i-1][j-maxLength]);
            }
        }
        System.out.println(dp[3][numOfCarriage]);


    }
}
