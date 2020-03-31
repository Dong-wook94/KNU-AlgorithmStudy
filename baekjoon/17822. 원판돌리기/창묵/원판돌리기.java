    import java.io.BufferedReader;
    import java.io.IOException;
    import java.io.InputStreamReader;
    import java.util.*;


    public class Main {

        static int N, M, T;
        static int map[][];
        static int Nmap[][];
        static Node[] Test;

        static int[] dx={1,-1,0,0};
        static int[] dy={0,0,1,-1};

        public static void main(String args[]) throws IOException {

            init();
            System.out.println(printValue());

        }

        public static void init() throws IOException {

            int wheelNum, dir, weight;

            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            StringTokenizer st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());
            M = Integer.parseInt(st.nextToken());
            T = Integer.parseInt(st.nextToken());
            map = new int[N][M];
            Test = new Node[T];

            for (int i = 0; i < N; i++) {
                st = new StringTokenizer(br.readLine());
                for (int j = 0; j < M; j++) {
                    map[i][j] = Integer.parseInt(st.nextToken());
                }
            }
            for (int i = 0; i < T; i++) {
                st = new StringTokenizer(br.readLine());
                wheelNum = Integer.parseInt(st.nextToken());
                dir = Integer.parseInt(st.nextToken());
                weight = Integer.parseInt(st.nextToken());
                Test[i]=new Node(wheelNum,dir,weight);
            }

            for(int i=0;i<Test.length;i++){
                rotation(Test[i].x, Test[i].y, Test[i].value);
                findValue();
                map=mapCopy(Nmap);
            }
        }


        public static void rotation(int wheelNum, int dir, int weight) {

            List<Integer> list = new ArrayList<>();

            for (int row = 0; row < N; row++) {
                if ((row+1) % wheelNum != 0)
                    continue;

                for (int col = 0; col < M; col++) {
                    list.add(map[row][col]);
                }

                if (dir == 0) {
                    for (int col = 0; col < M; col++) {
                        map[row][(col + weight) % M] = list.get(col);
                    }
                }
                else if (dir == 1) {
                    for (int col = 0; col < M; col++) {
                        map[row][Math.abs((M + (col - weight))) % M] = list.get(col);
                    }
                }

                list.removeAll(list);
            }
        }


        public static void findValue() {

            Nmap=mapCopy(map);

            for (int row = 0; row < N; row++) {
                for (int col = 0; col < M; col++) {
                    if (Nmap[row][col] != -10000) {
                        bfs(new Node(row, col, Nmap[row][col]));
                    }
                }
            }

            if(sameMap()){
                insertMeanValue();
            }
        }

        public static void insertMeanValue(){
            List<Node> valueList = new LinkedList<>();
            Node cur;
            float numCnt=0;
            float sum=0;
            for(int row =0; row<N;row++){
                for(int col=0;col<M;col++){
                    if(Nmap[row][col]!=-10000) {
                        valueList.add(new Node(row, col, Nmap[row][col]));
                        sum+=Nmap[row][col];
                        numCnt++;
                    }
                }
            }

            for(int i=0;i<valueList.size();i++){
                cur=valueList.get(i);
                if(Nmap[cur.x][cur.y]>sum/numCnt){
                    Nmap[cur.x][cur.y]--;
                }
                else if(Nmap[cur.x][cur.y]<sum/numCnt)
                    Nmap[cur.x][cur.y]++;
            }
        }

        public static boolean sameMap(){
            for(int i=0;i<N;i++){
                for(int j=0;j<M;j++){
                    if(map[i][j]!=Nmap[i][j])
                        return false;
                }
            }

            return true;
        }

        public static int[][] mapCopy(int[][] map){
            int[][] temp=new int[N][M];

            for (int row = 0; row < N; row++) {
                for (int col = 0; col < M; col++) {
                   temp[row][col]=map[row][col];
                }
            }
            return temp;
        }

        public static int printValue(){
            int sum=0;
            for(int i=0;i<N;i++){
                for(int j=0;j<M;j++){
                    if(map[i][j]!=-10000)
                        sum+=map[i][j];
                }
            }

            return sum;
        }

        public static void bfs(Node start){

            int nx,ny;
            Node cur;
            Queue<Node> q= new LinkedList<>();

            q.add(start);

            while(!q.isEmpty()) {
                cur = q.poll();

                for (int i = 0; i < 4; i++) {
                    nx = cur.x + dx[i];
                    ny = cur.y + dy[i];

                    if(ny==-1){
                        ny=M-1;
                    }
                    else if(ny==M){
                        ny=0;
                    }

                    if (nx < 0 || nx >= N || ny < 0 || ny >= M)
                        continue;
                    if (Nmap[nx][ny] == cur.value) {
                        q.add(new Node(nx,ny,Nmap[nx][ny]));
                        Nmap[cur.x][cur.y]=-10000;
                        Nmap[nx][ny]=-10000;
                    }
                }
            }

        }


    }

    class Node{
        int x;
        int y;
        int value;

        Node(int x,int y,int value){
            this.x=x;
            this.y=y;
            this.value=value;
        }
    }

