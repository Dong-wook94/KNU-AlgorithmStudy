import java.util.ArrayList;
import java.util.StringTokenizer;

public class Main{


    static String m="ABC";
    static String[] musicinfos={"12:00,12:14,HELLO,C#ABC#FGABC#", "13:00,13:05,WORLD,ABCDEF"};
    static ArrayList<Music> musicArr = new ArrayList<>();

    static Music result;
    public static void main(String[] argv){

        System.out.println(solution(m,musicinfos));
    }

    public static String solution(String m, String[] musicinfos){

        divideMusic();
        scanMusic();

        if(result==null){
            return "(None)";
        }
        else
            return result.title;
    }

    public static void scanMusic(){

        String allMelody;
        Music cur;
        for(int index=0;index<musicArr.size();index++){
            cur=musicArr.get(index);
            allMelody=returnMelody(cur);


            if(m.charAt(m.length()-1)=='#'){ // 끝에 # 붙어있는지
                if(allMelody.contains(m)){
                    refreshResult(cur);
                }
            }
            else{
                allMelody=allMelody.replace(m+"#","");
                if(allMelody.contains(m)){
                    refreshResult(cur);
                }
            }

        }



    }


    public static void refreshResult(Music cur){
        if(result==null){
            result=cur;
        }
        else{
            if(result.size<cur.size){ // 음악길이가 더 길때
                result=cur;
            }
        }
    }

    public static void divideMusic(){

        StringTokenizer st;
        String startTime,endTime,title,melody;

        for(int index=0;index<musicinfos.length;index++){
            st = new StringTokenizer(musicinfos[index],",");
            startTime=st.nextToken();
            endTime=st.nextToken();
            title=st.nextToken();
            melody=st.nextToken();
            musicArr.add(new Music(startTime,endTime,title,melody,index));
        }

    }

    public static String returnMelody(Music cur){
        String returnString = "";
        int size=calculateTime(cur);
        int index=0;
        cur.size=size;

        for(int cnt=0;cnt<size;cnt++){
            returnString=returnString+cur.melody.charAt(index%cur.melody.length());

            if(cur.melody.charAt(index%cur.melody.length())=='#')
                cnt--;

            index++;
        }

        return returnString;
    }

    public static int calculateTime(Music cur){
        StringTokenizer st = new StringTokenizer(cur.startTime,":");
        int startHour = Integer.parseInt(st.nextToken());
        int startMinute = Integer.parseInt(st.nextToken());
        st = new StringTokenizer(cur.endTime,":");
        int endHour = Integer.parseInt(st.nextToken());
        int endMinute = Integer.parseInt(st.nextToken());

        return (endHour-startHour)*60+(endMinute-startMinute);
    }


}

class Music{
    String startTime,endTime,title,melody;
    int size;
    int index;

    Music(String startTime,String endTime,String title,String melody,int index){
        this.startTime=startTime;
        this.endTime=endTime;
        this.title=title;
        this.melody=melody;
        this.index=index;
    }
}
