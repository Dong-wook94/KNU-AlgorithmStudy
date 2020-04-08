import java.util.ArrayList;
import java.util.StringTokenizer;


public class Main{


    static String m="CC#BCC#BCC#BCC#B";
    static String[] musicinfos={"03:00,03:30,FOO,CC#B", "04:00,04:08,BAR,CC#BCC#BCC#B"};
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

        Music cur;
        String allMelody;

        for(int index=0;index<musicArr.size();index++){
            cur=musicArr.get(index);
            replaceAll(cur);
            allMelody=returnMelody(cur);

            if(allMelody.contains(m)){
                refreshResult(cur);
            }

        }
    }

    public static void replaceAll(Music cur){
        m = m.replace("A#","H");
        m = m.replace("C#","I");
        m = m.replace("D#","J");
        m = m.replace("F#","K");
        m = m.replace("G#","L");
        cur.melody = cur.melody.replace("A#","H");
        cur.melody = cur.melody.replace("C#","I");
        cur.melody = cur.melody.replace("D#","J");
        cur.melody= cur.melody.replace("F#","K");
        cur.melody = cur.melody.replace("G#","L");
    }


    public static void refreshResult(Music cur){
        if(result==null){
            result=cur;
        }
        else{
            if(result.size<cur.size){ // 음악길이가 더 길때
                result=cur;
            }
            else if(result.size==cur.size){
                if(cur.index<result.index)
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
        int repeatCount=size/cur.melody.length();
        int restCount=size%cur.melody.length();

        cur.size=size;

        for(int i=0;i<repeatCount;i++){
            returnString=returnString+cur.melody;
        }
        returnString=returnString+cur.melody.substring(0,restCount);

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
