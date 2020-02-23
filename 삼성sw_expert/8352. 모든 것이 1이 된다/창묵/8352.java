import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {

    static int tc,year,month,day,hour,minute,second,day_limit;
    static String value;
    static Case[] reward;
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String[] args) throws IOException {
        tc = Integer.parseInt(br.readLine());
        reward = new Case[tc];

        for (int i = 0; i < tc; i++) {
            init();
            calculate(i);
        }

        for (int i = 0; i < tc; i++) {
            System.out.printf("#%d %d/%02d/%02d %02d:%02d:%02d\n",i+1,reward[i].year,reward[i].month,reward[i].day,reward[i].hour,reward[i].minute,reward[i].second);
        }

    }
    public static void init() throws IOException {

        StringTokenizer st1 = new StringTokenizer(br.readLine());
        StringTokenizer st2 = new StringTokenizer(st1.nextToken());
        StringTokenizer st3 = new StringTokenizer(st1.nextToken());

        year=Integer.parseInt(st2.nextToken("/"));
        month=Integer.parseInt(st2.nextToken("/"));
        day=Integer.parseInt(st2.nextToken());

        hour=Integer.parseInt(st3.nextToken(":"));
        minute=Integer.parseInt(st3.nextToken(":"));
        second=Integer.parseInt(st3.nextToken());
        value=br.readLine();

    }

    public static void calculate(int index){

        int add_second,add_minute,add_hour,add_day;
        long decimal = Integer.parseInt(value,2);

        dayLimit(month);
        add_day = (int)(decimal / 86400);
        decimal %=86400;
        add_hour = (int)(decimal / 3600);
        decimal %=3600;
        add_minute = (int)(decimal / 60);
        add_second = (int)(decimal % 60);

        second+=add_second; minute+=add_minute; hour+=add_hour; day+=add_day;

        if(second>=60){
            second-=60;
            minute++;
        }
        if(minute>=60){
            minute-=60;
            hour++;
        }
        if(hour>=24){
            hour-=24;
            day++;
        }

        while(day>day_limit){
            day-=day_limit;
            month++;

            if(month>12){
                month=1;
                year++;
            }

            dayLimit(month);
        }

        reward[index]=new Case(year,month,day,hour,minute,second);

    }

    public static void dayLimit(int month){
        if(month==4 || month == 6 || month == 9 || month == 11)
            day_limit=30;
        else if(month == 2) {
            if ((year % 400 == 0) || (year % 100 != 0 && year % 4 == 0))
                day_limit = 29;
            else
                day_limit = 28;
        }
        else
            day_limit=31;
    }

}

class Case{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

    Case(int year,int month,int day,int hour,int minute,int second){
        this.year=year;
        this.month=month;
        this.day=day;
        this.hour=hour;
        this.minute=minute;
        this.second=second;
    }
}