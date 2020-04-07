import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {

    static int[][] map;

    static int curX, curY, curDir;


    static int[] dx = {-1, 0, 1, 0}; // 북 동 남 서
    static int[] dy = {0, 1, 0, -1};

    public static void main(String[] argv) throws IOException {

        init();
        System.out.println(calculate());

    }

    public static void init() throws IOException {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int N = Integer.parseInt(st.nextToken());
        int M = Integer.parseInt(st.nextToken());

        map = new int[N][M];
        st = new StringTokenizer(br.readLine());
        curX = Integer.parseInt(st.nextToken());
        curY = Integer.parseInt(st.nextToken());
        curDir = Integer.parseInt(st.nextToken());

        for (int row = 0; row < N; row++) {
            st = new StringTokenizer(br.readLine());
            for (int col = 0; col < M; col++) {
                map[row][col] = Integer.parseInt(st.nextToken());
            }
        }

    }

    public static int calculate() {

        int cleanSpace = 0;
        int count = 0;
        int nDir=curDir;
        int nx, ny;

        while (true) {

            if (count == 4) {
                if (moveBack(curX, curY, curDir)) {
                    curX = curX + dx[curDir] * -1;
                    curY = curY + dy[curDir] * -1;
                    count = 0;
                } else {
                    break;
                }
            }

            if (map[curX][curY] == 0) {
                map[curX][curY] = -1;
                cleanSpace++;
            }

            nDir = (4 + (nDir - 1)) % 4;
            nx = curX + dx[nDir];
            ny = curY + dy[nDir];

            if (map[nx][ny] == 0) {
                curX = nx;
                curY = ny;
                curDir = nDir;
                count = 0;
            } else
                count++;

        }

        return cleanSpace;
    }

    public static boolean moveBack(int x, int y, int dir) {
        int nx = x + (dx[dir] * -1);
        int ny = y + (dy[dir] * -1);

        if(map[nx][ny]==-1 || map[nx][ny]==0)
            return true;
        else
            return false;
    }

}

