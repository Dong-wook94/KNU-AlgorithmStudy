import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {

    static int[][] map;
    static int N,L;

    public static void main(String[] args) throws IOException {
        init();
        System.out.println(calculate());
    }

    public static void init() throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        N=Integer.parseInt(st.nextToken());
        L=Integer.parseInt(st.nextToken());

        map=new int[N][N];

        for(int i=0;i<N;i++){
            st=new StringTokenizer(br.readLine());
            for(int j=0;j<N;j++)
                map[i][j]=Integer.parseInt(st.nextToken());
        }


    }

    public static int calculate() {

        int[] equal_cnt=new int[N];
        int[] index_arr=new int[N];
        boolean[] install;
        boolean pass=false; // flag

        int row, col,i;
        int current_height = -1;
        int pass_road = 0;
        int install_index;
        int install_cnt=1;

        //col

        for (col = 0; col < N; col++) {

            current_height = map[0][col];
            equal_cnt[0] = 1;
            install_cnt = 1;
            install=new boolean[N];

            for (row = 1; row < N; row++) {
                if (map[row][col] == current_height)
                    equal_cnt[row] = equal_cnt[row - 1] + 1;

                else { // not equal height.

                    if (Math.abs(map[row][col] - current_height) == 1) {
                        current_height = map[row][col];
                        equal_cnt[row] = 1;
                        index_arr[install_cnt++] = row - 1;
                    } else
                        break;
                }
            }

            if (row == N) {

                for (i = 1; i < install_cnt; i++) {
                    install_index = index_arr[i];
                    pass=false;
                    if (map[install_index][col] - map[install_index + 1][col] == -1 && equal_cnt[install_index] >= L) {

                        for (int j = install_index; j > install_index - L; j--) {

                            if(install[j] == false){
                                install[j]=true;
                                pass=true;
                            }
                            else
                                pass=false;
                        }

                    }
                    else if(install_index+L >= N)
                        break;

                    else if (map[install_index][col] - map[install_index + 1][col] == 1 && equal_cnt[install_index + L] >= L) {

                        for (int j = install_index + 1; j < install_index + 1 + L; j++) {

                            if(install[j] == false){
                                install[j]=true;
                                pass=true;
                            }
                            else
                                pass=false;
                        }
                    }
                    if(pass==false)
                        break;
                }

                if (i == install_cnt)
                    pass_road++;

            }
        }



        //row
        for (row = 0; row < N; row++) {

            current_height = map[row][0];
            equal_cnt[0]=1;
            install_cnt=1;
            install=new boolean[N];

            for (col = 1; col < N; col++) {
                if (map[row][col] == current_height)
                    equal_cnt[col]=equal_cnt[col-1]+1;

                else { // not equal height.

                    if (Math.abs(map[row][col] - current_height) == 1) {
                        current_height = map[row][col];
                        equal_cnt[col]=1;
                        index_arr[install_cnt++]=col-1;
                    } else
                        break;
                }
            }


            if (col == N){

                for(i=1;i<install_cnt;i++){
                    install_index=index_arr[i];
                    pass = false;

                    if (map[row][install_index] - map[row][install_index+1] == -1 && equal_cnt[install_index] >= L) {

                        for(int j=install_index;j>install_index-L;j--){

                            if(install[j]==false) {
                                install[j] = true;
                                pass = true;
                            }
                            else
                                pass=false;
                        }

                    }
                    else if(install_index+L >=N)
                        break;
                    else if (map[row][install_index] - map[row][install_index+1] == 1 && equal_cnt[install_index + L] >= L) {

                        for(int j=install_index+1;j<install_index+1+L;j++) {

                            if(install[j]==false) {
                                install[j] = true;
                                pass = true;
                            }
                            else
                                pass=false;
                        }
                    }
                    if(pass==false)
                        break;
                }

                if(i==install_cnt)
                    pass_road++;

            }
        }
        return pass_road;

    }

}