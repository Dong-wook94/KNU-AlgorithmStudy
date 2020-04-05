import java.util.ArrayList;


public class Main{

    static int[][] board = {{0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,6,0,0,0,0},
                            {0,0,0,4,6,6,0,0,0,0},
                            {0,0,4,4,4,6,0,0,0,0},
                            {0,0,0,0,3,0,0,0,0,0},
                            {0,0,0,2,3,0,0,0,5,5},
                            {1,2,2,2,3,3,0,0,0,5},
                            {1,1,1,0,0,0,0,0,0,5}};

    static int N;



    public static void main(String args[]) {

        System.out.println(solution(board));

    }

    public static int solution(int[][] map){
        int answer=0;

        board=map;
        N=board[0].length;

        while(true){

            insertBlack();
            if(calculate()){
                answer++;
            }
            else
                break;
        }


        return answer;
    }

    public static void insertBlack(){

        for(int col=0;col<N;col++){
            for(int row=0; row<N;row++){
                if(board[row][col]==0 || board[row][col]==-1){
                    board[row][col]=-1;
                }
                else
                    break;
            }
        }

    }

    public static boolean calculate(){


        for(int row=0;row<N;row++){
            for(int col=0;col<N;col++){

                if(board[row][col]!= 0 && board[row][col]!=-1){

                    if(checkRemove(row,col)){
                        return true;
                    }
                }
            }
        }

        return false;

    }

    public static boolean checkRemove(int x,int y){

        boolean flag=false;
        Node cur;
        ArrayList<Node> indexArr = new ArrayList<>();

        if(scanBlock(x,y,2,3,0,indexArr))
            flag=true;
        else if(scanBlock(x,y,3,2,0,indexArr))
            flag=true;
        else if(scanBlock(x,y,2,3,1,indexArr))
            flag=true;
        else if(scanBlock(x,y,3,2,1,indexArr))
            flag=true;
        else if(scanFinger(x,y,indexArr))
            flag=true;

        if(flag){
            for(int i=0;i<indexArr.size();i++){
                cur=indexArr.get(i);
                board[cur.x][cur.y]=0;
            }
        }

        return flag;



    }


    public static boolean scanBlock(int x,int y,int rowWeight,int colWeight,int scanDir,ArrayList<Node> indexArr){
        int blackCnt=0;
        int numCnt=0;
        int number=board[x][y];

        indexArr.removeAll(indexArr);


        if(scanDir==0) {
            for (int row = x; row < x + rowWeight; row++) {

                for (int col = y; col < y + colWeight; col++) {

                    if(row<0 || row>=N || col<0 || col>=N)
                        return false;

                    indexArr.add(new Node(row,col));

                    if(board[row][col]==-1)
                        blackCnt++;
                    else if(board[row][col]==number)
                        numCnt++;
                    else if(board[row][col]!=number)
                        return false;
                }
            }

        }
        else{
            for (int row = x; row < x + rowWeight; row++) {


                for (int col = y; col > y - colWeight; col--) {

                    if(row<0 || row>=N || col<0 || col>=N)
                        return false;

                    indexArr.add(new Node(row,col));

                    if(board[row][col]==-1)
                        blackCnt++;
                    else if(board[row][col]==number)
                        numCnt++;
                    else if(board[row][col]!=number)
                        return false;
                }
            }

    }

        if(blackCnt==2 && numCnt==4)
            return true;
        else
            return false;
    }

    public static boolean scanFinger(int x,int y,ArrayList<Node> indexArr){

        int nx,ny;

        indexArr.removeAll(indexArr);

        if(!(y-1>=0 && y+1<=N-1 && board[x][y-1]==-1 && board[x][y+1]==-1))
            return false;
        else{
            indexArr.add(new Node(x,y-1));
            indexArr.add(new Node(x,y+1));
        }

        nx=x+1;

        for(ny=y-1;ny<(y-1)+3;ny++){

            if(nx<0 || nx>=N || ny<0 || ny>=N)
                return false;

            if(board[nx][ny]!=board[x][y])
                return false;
            else{
                indexArr.add(new Node(nx,ny));
            }
        }

        return true;
    }

}

class Node {

    int x;
    int y;

    Node(int x, int y) {
        this.x = x;
        this.y = y;
    }

}


