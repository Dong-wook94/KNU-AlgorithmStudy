
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Baekjoon2931 {

    static int rowSize;
    static int colSize;
    static char[][] map;
    static boolean[][] visited;
    static Position Src,Dest;
    static Map<Character, Object> pipe;
    static Map<String,Character> print;
    static int dirRow[] = {0,1,0,-1};
    static int dirCol[] = {1,0,-1,0};
    public static class Position{
        int row,col;
        public Position(int row, int col) {
            this.row = row;
            this.col = col;
        }
    }

    public static boolean isRange(int nextRow,int nextCol){
        if(nextRow<0||nextRow>=rowSize || nextCol<0 || nextCol>=colSize)
            return false;
        return true;
    }
    public static boolean isPipe(int nextRow,int nextCol){
        if(map[nextRow][nextCol]=='.')
            return false;
        return true;
    }
    public static String bfs(){
        Queue<Position> q = new LinkedList<>();
        visited[Src.row][Src.col]=true;
        for(int i=0;i<4;i++){
            int nextRow = Src.row + dirRow[i];
            int nextCol = Src.col + dirCol[i];
            if(!isRange(nextRow,nextCol)||!isPipe(nextRow,nextCol))
                continue;
            q.add(new Position(nextRow,nextCol));
            visited[nextRow][nextCol] = true;
            break;//모스크바는 하나의 블록과만 인접함.
        }

        while(!q.isEmpty()){
            Position cur = q.poll();
            visited[cur.row][cur.col] = true;
            char curPipe = map[cur.row][cur.col];
            if(curPipe=='.'){//길이 끊어져 있는
                String temp ="";
                for(int i=0;i<4;i++){
                    int nextRow = cur.row + dirRow[i];
                    int nextCol = cur.col + dirCol[i];
                    if(!isRange(nextRow,nextCol)||!isPossible(nextRow,nextCol,i))
                        temp+="0";
                    else
                        temp+="1";
                }
                return (cur.row+1)+" "+(cur.col+1)+" "+print.get(temp);
            }
            boolean[] pipeInfo = (boolean[]) pipe.get(curPipe);
            for(int i=0;i<4;i++){
                int nextRow = cur.row + dirRow[i];
                int nextCol = cur.col + dirCol[i];
                if(!isRange(nextRow,nextCol)||visited[nextRow][nextCol]||!pipeInfo[i]) continue;
                q.add(new Position(nextRow,nextCol));
                visited[nextRow][nextCol] = true;
            }
        }
        return "";
    }

    public static boolean isPossible(int row, int col, int i) {
        switch (map[row][col]){
            case '|':
                if(i==1||i==3)
                    return true;
                return false;
            case '-':
                if(i==0||i==2)
                    return true;
                return false;
            case '+':
                return true;
            case '1':
                if(i==0||i==1)
                    return false;
                return true;
            case '2':
                if(i==0||i==3)
                    return false;
                return true;
            case '3':
                if(i==2||i==3)
                    return false;
                return true;
            case '4':
                if(i==1||i==2)
                    return false;
                return true;
            default:
                return false;
        }
    }

    public static void main(String[] args) throws IOException {
        initData();
        String result = bfs();
        System.out.println(result);
    }

    public static void initData() throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        rowSize = Integer.parseInt(st.nextToken());
        colSize = Integer.parseInt(st.nextToken());
        map = new char[rowSize][colSize];
        visited = new boolean[rowSize][colSize];
        pipe = new HashMap<Character, Object>();
        print = new HashMap<String,Character>();
        pipe.put('|',new boolean[] {false,true,false,true});
        pipe.put('-',new boolean[] {true,false,true,false});
        pipe.put('+',new boolean[] {true,true,true,true});
        pipe.put('1',new boolean[] {true,true,false,false});
        pipe.put('2',new boolean[] {true,false,false,true});
        pipe.put('3',new boolean[] {false,false,true,true});
        pipe.put('4',new boolean[] {false,true,true,false});
        print.put("0101",'|');
        print.put("1010",'-');
        print.put("1111",'+');
        print.put("1100",'1');
        print.put("1001",'2');
        print.put("0011",'3');
        print.put("0110",'4');

        for(int i=0;i<rowSize;i++){
            String str = br.readLine();
            for(int j=0;j<colSize;j++){
                char ch = str.charAt(j);
                map[i][j] = ch;
                if(ch =='M')
                    Src = new Position(i,j);
                else if(ch == 'Z')
                    Dest = new Position(i,j);
            }
        }
    }
}
