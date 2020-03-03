import java.util.ArrayList;
import java.util.Scanner;

public class Main{

    static int[][] path={
            {0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,-1},
            {10,13,16,19,25,30,35,40,-1},
            {20,22,24,25,30,35,40,-1},
            {30,28,27,26,25,30,35,40,-1}};

    static int max_value;
    static int[] G = new int[4];
    static int[] dice = new int[10];
    static int[] route=new int[10];
    static ArrayList<Integer> selected=new ArrayList<>();

    public static void main(String[] args){


        Scanner in = new Scanner(System.in);

        for(int i=0;i<dice.length;i++){
            dice[i]=in.nextInt();
        }

        for(int i=1; i<=4;i++){
            repermutation(0,0,i);
        }

        System.out.println(max_value);

    }

    public static void repermutation(int number,int cnt,int horse_cnt){

        if(cnt==dice.length){
                if(max_value<calculate(horse_cnt)){
                    max_value=calculate(horse_cnt);
                    for(int i=0;i<selected.size();i++)
                        route[i]=selected.get(i);
                }
                return;

        }
        else{

            for(int index=number;index<horse_cnt;index++){
                selected.add(index);
                repermutation(number,cnt+1,horse_cnt);
                selected.remove(selected.size()-1); // Last delete
            }

        }


    }

    public static int calculate(int horse_cnt){

        Node[] horse=new Node[horse_cnt];
        int horse_index,plus_value,dice_value,cur_pathline,cur_postion,cur_value;
        int sum=0;


        for(int i=0;i<horse_cnt;i++)
            horse[i]=new Node();

        for(int dice_index=0;dice_index<dice.length;dice_index++){
            horse_index=selected.get(dice_index);
            dice_value=dice[dice_index];

            cur_pathline=horse[horse_index].cur_pathline;
            cur_postion=horse[horse_index].cur_pos;

            if(horse[horse_index].value==-1 || horse[horse_index].cur_pos+dice_value>=path[cur_pathline].length-1){
                plus_value=0;
                horse[horse_index].cur_pos=path[cur_pathline].length-1;
                horse[horse_index].value=-1;
            }
            else{
                horse[horse_index].value=path[cur_pathline][cur_postion+dice_value];
                horse[horse_index].cur_pos=cur_postion+dice_value;
                plus_value=horse[horse_index].value;
            }

            if(horse[horse_index].cur_pathline==0) { // 0일때만 경로가 바뀌는경우가생김
                if (horse[horse_index].value == 10) { // 방향 변경
                    horse[horse_index].cur_pathline = 1;
                    horse[horse_index].cur_pos = 0;
                } else if (horse[horse_index].value == 20) { // 방향 변경
                    horse[horse_index].cur_pathline = 2;
                    horse[horse_index].cur_pos = 0;
                } else if (horse[horse_index].value == 30) { // 방향 변경
                    horse[horse_index].cur_pathline = 3;
                    horse[horse_index].cur_pos = 0;
                }
            }

            if(horse[horse_index].value!=-1 && horse[horse_index].value!=0) { // 도착점이 아닐때는 다른 말이 놓여져있는지 탐색을 진행해야한다

                cur_value=horse[horse_index].value;

                for (int other_horse = 0; other_horse < horse.length; other_horse++) { // 말이 이미있는곳에 움직이는경우는 탐색하면안된다.
                    if(other_horse == horse_index)
                        continue;

                    if(cur_value==horse[other_horse].value){ // 중복탐색

                        if(cur_value==25 || cur_value ==35 || cur_value == 40){ // 25,35,40은 pathline 1,2,3에 다같이 존재하기때문에, 그리고 윷놀이판에 1개만존재
                                return -1;
                        }
                        else if(cur_value == 30){ // 30같은경우는 pathline 1에도 존재하는데 이는 같은 칸이 아니다.

                            if(horse[horse_index].cur_pathline==1 && horse[other_horse].cur_pathline==1)
                                return -1;
                            else if(horse[horse_index].cur_pathline!=1 && horse[other_horse].cur_pathline!=1)
                                return -1;
                        }
                        else{
                            if(horse[horse_index].cur_pathline==horse[other_horse].cur_pathline) // 나머지 수 같은 경우는 postion만 같으면 값이 중복된다.
                                return -1;
                        }
                    }

                }

            }

            sum+=plus_value;

        }

        return sum;
    }
}


class Node{

    int value;
    int cur_pos;
    int cur_pathline;

    Node(){
        this.value=0;
        this.cur_pos=0;
        this.cur_pathline=0;
    }
}