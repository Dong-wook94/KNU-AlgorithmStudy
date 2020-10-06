import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Baekjoon10159 {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static int N, M;
    static boolean[][] compare;

    public static void main(String[] args) throws IOException {
        N = Integer.parseInt(br.readLine());
        M = Integer.parseInt(br.readLine());
        compare = new boolean[N + 1][N + 1];
        for (int i = 0; i < M; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int a = Integer.parseInt(st.nextToken());
            int b = Integer.parseInt(st.nextToken());
            compare[a][b] = true;
        }

        floydWarshall();

        for (int i = 1; i <= N; i++) {
            int cnt=0;
            for (int j = 1; j <= N; j++) {
                if(compare[i][j])
                    cnt++;
                if(compare[j][i])
                    cnt++;
            }
            System.out.println(N-cnt-1);
        }
    }

    private static void floydWarshall() {
        for (int k = 1; k <= N; k++) {
            for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= N; j++) {
                    if (i != j) {
                        if (compare[i][k] && compare[k][j]) {
                            compare[i][j] = true;
                        }
                    }
                }
            }
        }
    }
}
