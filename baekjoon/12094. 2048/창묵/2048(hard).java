import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Main {

    static int[][] map;

    static int[] dx = {0, 0, -1, 1};
    static int[] dy = {1, -1, 0, 0}; // 왼쪽으로 미는것, 오른쪽으로미는것, 아래쪽으로 미는것, 위쪽으로 미는것 ( 반대다 )

    static ArrayList<Integer> list = new ArrayList<>();
    static int maxValue=-1;
    static int N;
    static final int left = 0;
    static final int right = 1;
    static final int down = 2;
    static final int up = 3;

    public static void main(String argv[]) throws IOException {

        init();
        dfs(0, 0,mapCopy(map));
        System.out.println(maxValue);
    }

    public static void init() throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        N = Integer.parseInt(st.nextToken());
        map = new int[N][N];


        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(br.readLine());
            for (int j = 0; j < N; j++) {
                map[i][j] = Integer.parseInt(st.nextToken());
            }
        }
    }

    public static void dfs(int index, int cnt,int[][] prevState) {

        int value;
        int[][] curState;

        if (cnt > 10) {
            return;
        }
        else {

            for (int i = index; i < 4; i++) {

                curState=mapCopy(prevState);
                value=calculate(i,curState);
                maxValue= Math.max(value,maxValue);

                if(expectedValue(value,cnt+1))
                    dfs(0, cnt + 1,curState);
                else
                    continue;

                if(sameMap(curState,prevState))
                    continue;
            }

        }

    }

    public static int calculate(int dir,int[][] mapTemp) {


        int nx, ny,startPoint,index;
        int curMaxValue=-1;
        int prev = 0;

        ArrayList<Node> arr = new ArrayList<>();


            if (dir == left || dir == right) {
                if (dir == left)
                    startPoint = -1;
                else
                    startPoint = N;

                for (int row = 0; row < N; row++) {
                    ny = startPoint;
                    arr.removeAll(arr);
                    while (true) {
                        ny += dy[dir];

                        if (ny < 0 || ny >= N)
                            break;
                        if (mapTemp[row][ny] != 0) {

                            if (!arr.isEmpty() && arr.get(prev).val == mapTemp[row][ny] && arr.get(prev).combine == false) {
                                arr.get(prev).val *= 2;
                                arr.get(prev).combine = true;
                                curMaxValue=Math.max(arr.get(prev).val,curMaxValue);
                            } else {
                                arr.add(new Node(mapTemp[row][ny]));
                                prev = arr.size() - 1;
                                curMaxValue=Math.max(mapTemp[row][ny],curMaxValue);
                            }
                            mapTemp[row][ny]=0;
                        }
                    }

                    index = startPoint;

                    if(dir==left) {
                        for (int i = 0; i < arr.size(); i++)
                            mapTemp[row][++index] = arr.get(i).val;
                    }
                    else{
                        for (int i = 0; i < arr.size(); i++)
                            mapTemp[row][--index] = arr.get(i).val;
                    }

                }
            }
            else if(dir==up || dir==down){

                if(dir==down)
                    startPoint=N;
                else
                    startPoint=-1;

                for(int col=0;col<N;col++){
                    nx=startPoint;
                    arr.removeAll(arr);

                    while (true) {
                        nx += dx[dir];

                        if (nx < 0 || nx >= N)
                            break;
                        if (mapTemp[nx][col] != 0) {

                            if (!arr.isEmpty() && arr.get(prev).val == mapTemp[nx][col] && arr.get(prev).combine == false) {
                                arr.get(prev).val *= 2;
                                arr.get(prev).combine = true;
                                curMaxValue=Math.max(arr.get(prev).val,curMaxValue);
                            } else {
                                arr.add(new Node(mapTemp[nx][col]));
                                prev = arr.size() - 1;
                                curMaxValue=Math.max(mapTemp[nx][col],curMaxValue);
                            }
                            mapTemp[nx][col]=0;

                        }
                    }
                    index=startPoint;

                    if(dir==down) {
                        for (int i = 0; i < arr.size(); i++)
                            mapTemp[--index][col] = arr.get(i).val;
                    }
                    else{
                        for (int i = 0; i < arr.size(); i++)
                            mapTemp[++index][col] = arr.get(i).val;
                    }
                }
            }

        return curMaxValue;
    }

    public static boolean sameMap(int[][] mapA,int[][] mapB){
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(mapA[i][j]!=mapB[i][j])
                    return false;
            }
        }

        return true;
    }

    public static boolean expectedValue(int curMaxValue,int cnt){

        if(curMaxValue*Math.pow(2,10-cnt)>maxValue)
            return true;
        else
            return false;
    }

    public static int[][] mapCopy(int map[][]){
        int temp[][] = new int[N][N];

        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                temp[i][j]=map[i][j];
            }
        }

        return temp;
    }

}

class Node{
    int val;
    boolean combine;

    Node(int val){
        this.val=val;
    }
}