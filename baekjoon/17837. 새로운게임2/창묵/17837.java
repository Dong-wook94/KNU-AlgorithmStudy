import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Main {

    static int N, K;
    static map_node[][] map;
    static ArrayList<Node> chess = new ArrayList<>();

    static int[] dx = {0, 0, -1, 1};
    static int[] dy = {1, -1, 0, 0};

    public static void main(String[] args) throws IOException {

        int turn = 0;
        boolean pass = false;

        init();
        while (pass != true) {
            turn++;

            for (int i = 0; i < K; i++) {
                if (calculate(i) == true) {
                    pass = true;
                    break;
                }
            }

            if (turn > 1000)
                break;
        }

        if (pass)
            System.out.println(turn);
        else
            System.out.println(-1);

    }

    public static void print() {

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                System.out.print("[");
                for (int k = 0; k < map[i][j].stacked_chess.size(); k++) {
                    System.out.printf("%d ", map[i][j].stacked_chess.get(k).chess_number);
                }
                System.out.print("]");
            }
            System.out.println();
        }

    }

    public static void init() throws IOException {

        int row, col, dir;
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());

        map = new map_node[N][N];

        for (int i = 0; i < N; i++) { // init map
            st = new StringTokenizer(br.readLine());
            for (int j = 0; j < N; j++) {
                map[i][j] = new map_node(0, Integer.parseInt(st.nextToken()), new ArrayList<Node>());
            }
        }

        for (int i = 0; i < K; i++) { // init chess
            st = new StringTokenizer(br.readLine());
            row = Integer.parseInt(st.nextToken()) - 1;
            col = Integer.parseInt(st.nextToken()) - 1;
            dir = Integer.parseInt(st.nextToken()) - 1;
            chess.add(new Node(row, col, dir, i));
            (map[row][col].stacked_chess).add(chess.get(i));
        }

    }

    public static boolean calculate(int number) {

        final int white = 0;
        final int red = 1;
        final int blue = 2;
        int newX, newY, cur_chess_index;
        boolean check=false;

        ArrayList<Node> cur_stacked_arr;
        Node cur;

        cur = chess.get(number);
        cur_stacked_arr = map[cur.x][cur.y].stacked_chess;
        cur_chess_index = cur_stacked_arr.indexOf(cur); // 현재 체스말이 이동하기전 맵의 몇번째에 쌓여있는지

        newX = cur.x + dx[cur.dir]; // 다음 이동할 좌표
        newY = cur.y + dy[cur.dir];

        if (newX >= 0 && newX < N && newY >= 0 && newY < N) { // 이동하려는 체스말이 범위 내에 있으면

            if (map[newX][newY].color == blue) {
                check=move(cur, cur_chess_index, blue);
            } else if (map[newX][newY].color == red) {
                check=move(cur, cur_chess_index, red);
            } else {
                check=move(cur, cur_chess_index, white);
            }
        }

        else{ // 범위내에 없으면
            check=move(cur,cur_chess_index,blue);
        }

        if(check==true)
            return true;
        else
            return false;
    }

    public static boolean move(Node cur,int cur_chess_index,int color){

        final int red = 1;
        final int blue = 2;

        int blueX,blueY,newX,newY,changeX,changeY;

        ArrayList<Node> move_chess_arr=new ArrayList<Node>();
        ArrayList<Node> cur_stacked_arr=map[cur.x][cur.y].stacked_chess;

        blueX = cur.x + dx[changeDir(cur.dir)];
        blueY = cur.y + dy[changeDir(cur.dir)];
        newX = cur.x+dx[cur.dir];
        newY = cur.y+dy[cur.dir];

        if(color==blue){
            changeX=blueX;
            changeY=blueY;
            cur.dir=changeDir(cur.dir);

            if (blueX < 0 || blueX >= N || blueY < 0 || blueY >= N) {
                return false;
            }

            if(map[changeX][changeY].color==blue)
                return false;
        }
        else{
            changeX=newX;
            changeY=newY;
        }

        cur.x = changeX;
        cur.y = changeY;
        move_chess_arr.add(cur);
        cur_stacked_arr.remove(cur_chess_index);

        for (int i = cur_chess_index; i < cur_stacked_arr.size(); ) { // 나머지 체스말
            cur = cur_stacked_arr.get(cur_chess_index);
            cur.x = changeX;
            cur.y = changeY;
            move_chess_arr.add(cur);
            cur_stacked_arr.remove(cur_chess_index);
        }

        if (map[changeX][changeY].color == red) {
            Collections.reverse(move_chess_arr);
        }

        map[changeX][changeY].stacked_chess.addAll(move_chess_arr); // 흰색이면 그냥 merge.

        if(map[changeX][changeY].stacked_chess.size()>=4)
            return true;

        return false;
    }

    public static int changeDir(int index){

        if(index==0 || index==1){
            if(index==0)
                index=1;
            else
                index=0;
        }
        else if(index==2 || index ==3){
            if(index==2)
                index=3;
            else
                index=2;
        }

        return index;
    }

}

class Node{
    int x;
    int y;
    int dir;
    int chess_number;

    Node(int x,int y, int dir,int chess_number){
        this.x=x;
        this.y=y;
        this.dir=dir;
        this.chess_number=chess_number;
    }
}

class map_node{
    int chess_cnt;
    int color;
    ArrayList<Node> stacked_chess;

    map_node(int chess_cnt,int color,ArrayList<Node> stacked_chess){
        this.chess_cnt=chess_cnt;
        this.color=color;
        this.stacked_chess=stacked_chess;
    }
}

