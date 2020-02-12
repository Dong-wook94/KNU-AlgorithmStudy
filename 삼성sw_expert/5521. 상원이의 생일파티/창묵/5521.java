import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Queue;
import java.util.LinkedList;
import java.util.StringTokenizer;

public class Main {

    static int total_people;
    static int friend;
    static int invitation_cnt;
    static LinkedList graph[];

    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String[] args) throws IOException {

        int test_case;
        int[] test_result;
        test_case=Integer.parseInt(in.readLine());

        test_result=new int[test_case];


        for(int i=0;i<test_case;i++){

            StringTokenizer st = new StringTokenizer(in.readLine());
            total_people = Integer.parseInt(st.nextToken());
            friend = Integer.parseInt(st.nextToken());

            graph=makeGraph(total_people,friend);
            bfs(1);
            test_result[i]=invitation_cnt;
            invitation_cnt=0;
        }

        for(int i=0;i<test_case;i++)
            System.out.println("#"+(i+1)+" "+test_result[i]);
    }

    public static LinkedList[] makeGraph(int total_people,int friend) throws IOException {

        int people1,people2;

        LinkedList temp[];
        temp=new LinkedList[total_people+10];

        for(int i=1;i<=total_people;i++) {
            temp[i] = new LinkedList();
        }
        for(int i=0;i<friend;i++){
            StringTokenizer st = new StringTokenizer(in.readLine());
            people1 = Integer.parseInt(st.nextToken());
            people2 = Integer.parseInt(st.nextToken());
            temp[people1].add(people2);
            temp[people2].add(people1);
        }

        return temp;
    }


    public static void bfs(int start){

        boolean[] visit = new boolean[total_people+1];
        int[] check_arr = new int[total_people+10];

        int scan_index;
        int linked_index;
        int check_cnt=0;
        boolean check = false;


        Queue<Integer> Q = new LinkedList<>();

        Q.offer(start);
        visit[start]=true;

        while(!Q.isEmpty()){

            scan_index=Q.poll();

            for(int j=0;j<check_cnt;j++){
                if(scan_index==check_arr[j]) {
                    check = true;
                    break;
                }
                else
                    check=false;
            }

            for(int i=0;i<graph[scan_index].size();i++){

                    linked_index=(int)graph[scan_index].get(i);

                    if((scan_index ==1 || check== true) && visit[linked_index]==false) {

                        visit[linked_index] = true;
                        invitation_cnt++;

                        if(scan_index==1) {
                            Q.offer(linked_index);
                            check_arr[check_cnt++] = linked_index;
                        }

                    }
            }
        }

    }


}


