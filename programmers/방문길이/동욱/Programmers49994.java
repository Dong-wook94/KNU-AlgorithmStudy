import java.util.HashSet;
import java.util.Set;

public class Programmers49994 {
    static Set<Path> pathSet = new HashSet<>();

    static int dirRow[] = {-1,0,0,1};
    static int dirCol[] = {0,-1,1,0};
    public static int solution(String dirs) {
        int answer = 0;
        int x = 0;
        int y = 0;
        Path path1 = null;
        Path path2 = null;
        for(int i=0;i<dirs.length();i++){
            int dir = getDir(dirs.charAt(i));
            int nextX = x + dirRow[dir];
            int nextY = y + dirCol[dir];

            if(!isRange(nextX, nextY))
                continue;
            path1 = new Path(x,y,nextX,nextY);
            path2 = new Path(nextX,nextY,x,y);
            x = nextX;
            y = nextY;

            if(!pathSet.contains(path1)){
                pathSet.add(path1);
                pathSet.add(path2);
            }
        }
        answer = pathSet.size()/2;
        return answer;
    }

    public static boolean isRange(int nextX, int nextY) {
        return nextX>=-5&&nextY>=-5 && nextX<=5 &&nextY<=5;
    }

    private static int getDir(char c) {
        switch (c){
            case 'U':
                return 0;
            case 'L':
                return 1;
            case 'R':
               return 2;
            case 'D':
                return 3;
            default:
                return -1;
        }
    }

    static class Path {
        int curX,curY,nextX,nextY;

        public Path(int curX, int curY, int nextX, int nextY) {
            this.curX = curX;
            this.curY = curY;
            this.nextX = nextX;
            this.nextY = nextY;
        }

        public void setReverse(){
            int tempX = curX;
            int tempY = curY;
            curX = nextX;
            curY = nextY;
            nextX = tempX;
            nextY = tempY;
        }

        public int getCurX() {
            return curX;
        }

        public int getCurY() {
            return curY;
        }

        public int getNextX() {
            return nextX;
        }

        public int getNextY() {
            return nextY;
        }

        @Override
        public int hashCode() {
            return Integer.toString(curX).hashCode()+ Integer.toString(curY).hashCode() + Integer.toString(nextX).hashCode()+ Integer.toString(nextY).hashCode();
        }

        @Override
        public boolean equals(Object obj) {
            if(obj instanceof Path){
                Path path = (Path) obj;
                return path.getCurX()==curX && path.getCurY() ==curY && path.getNextX() ==nextX && path.getNextY()==nextY;
            }
            return false;
        }


    }

    public static void main(String[] args) {
        String dirs = "ULURRDLLU";
        int result = solution(dirs);
        System.out.println(result);
    }
}
