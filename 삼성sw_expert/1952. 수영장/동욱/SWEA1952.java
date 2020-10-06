import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class SWEA1952 {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static int[] prices;
    static int[] plan;
    static int result;
    public static void main(String args[]) throws Exception {
        int T = Integer.parseInt(br.readLine());
        for(int test_case = 1; test_case <= T; test_case++){
            System.out.print("#"+test_case+" ");
            testCase();
        }
    }

    private static void testCase() throws IOException {
        prices = new int[4];
        plan = new int[13];
        StringTokenizer st = new StringTokenizer(br.readLine());
        for(int i=0;i<4;i++){
            prices[i] = Integer.parseInt(st.nextToken());
        }
        st = new StringTokenizer(br.readLine());
        for(int i=1;i<=12;i++){
            plan[i] = Integer.parseInt(st.nextToken());
        }
        result = Integer.MAX_VALUE;
        dfs(1,0);
        System.out.println(result);
    }

    private static void dfs(int month, int money) {
        if(month>12){
            result = Math.min(result,money);
            return;
        }
        if(month==1){
            dfs(month+12,money+prices[3]);
        }
        if(month+2<=12){
            dfs(month+3,money+prices[2]);
        }
        if(plan[month]>0){
            dfs(month+1,money+prices[1]);
            dfs(month+1,money+plan[month]*prices[0]);
        }
        else{
            dfs(month+1,money);
        }
    }
}
