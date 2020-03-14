import java.util.*;


public class Main {

    static int[][] build_frame={ {0,0,0,1},{2,0,0,1},{4,0,0,1},{0,1,1,1},{1,1,1,1},{2,1,1,1},{3,1,1,1},{2,0,0,0},{1,1,1,0},{2,2,0,1}};
    static TreeMap<String,Node> map=new TreeMap<>();
    static int n=6;
    static final int pillar = 0;
    static final int barrage =1;


    public static void main(String[] args){

        System.out.println(Arrays.deepToString(solution(n,build_frame)));
    }

    public static int[][] solution(int n,int[][] build_frame){
        int [][] answer;
        int x,y,structure,install;
        int cnt=-1;
        Iterator<String> it;
        String key;
        Node temp;

        for(int i=0;i<build_frame.length;i++){
            x=build_frame[i][0];
            y=build_frame[i][1];
            structure=build_frame[i][2];
            install=build_frame[i][3];
            calculate(x,y,structure,install,n);
        }


        answer=new int[map.size()][3];
        it=map.keySet().iterator();

        while(it.hasNext()){
            key=it.next();
            temp=map.get(key);
            answer[++cnt][0]=temp.x;
            answer[cnt][1]=temp.y;
            answer[cnt][2]=temp.structure;
        }

        return answer;
    }

    public static void calculate(int x,int y,int structure,int install,int n){

        Node cur=new Node(x,y,structure);
        String curKey;

        curKey=makeString(x,y,structure);


        if(install==1 && !map.containsKey(curKey)) {
            map.put(curKey,cur);
            if(!action()){
                map.remove(curKey);
            }
        }
        else if(install==0 && map.containsKey(curKey)){
            map.remove(curKey);
            if(!action()){
                map.put(curKey,cur);
            }
        }

    }

    public static boolean action(){
        Iterator<String> it;
        String tempKey;
        Node temp;
        boolean pass=false;

        it=map.keySet().iterator();

        while(it.hasNext()){
            tempKey=it.next();
            temp=map.get(tempKey);

            if(temp.structure==pillar)
                pass=checkPillar(temp.x,temp.y);
            else if(temp.structure==barrage)
                pass=checkBarrage(temp.x,temp.y);

            if(pass==false)
                return false;
        }

        return true;
    }

    public static boolean checkPillar(int x,int y){

        boolean Check=false;


        if(y==0) { // 바닥 위
            Check=true;
        }
        if(map.containsKey(makeString(x,y-1,pillar))){
            Check=true;
        }
        if(map.containsKey(makeString(x,y,barrage))){
            Check=true;
        }
        if(map.containsKey(makeString(x-1,y,barrage))){
            Check=true;
        }

        return Check;
    }


    public static boolean checkBarrage(int x ,int y){

        boolean Check=false;


        if(map.containsKey(makeString(x,y-1,pillar))){
            Check= true;
        }
        if (map.containsKey(makeString(x+1,y-1,pillar))){
            Check = true;
        }
        if (map.containsKey(makeString(x-1,y,barrage)) && map.containsKey(makeString(x+1,y,barrage))){
            Check = true;
        }

        return Check;

    }


    public static String makeString(int x,int y,int structure){

        return String.format("%03d.%03d.%03d",x,y,structure);
    }

}

class Node{
    int x;
    int y;
    int structure;

    Node(int x,int y,int structure){
        this.x=x;
        this.y=y;
        this.structure=structure;
    }
}

