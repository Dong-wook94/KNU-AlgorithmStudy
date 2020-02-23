#include <stdio.h>
#include <string>
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
//typedef struct devide{
//    int cal_time[4]={0};
//    int value;
//    int count=0;
//    devide(){}
//    devide(int a){value=a;}
//}devide;
int tc;
//int devideTimeArray[3] = {60,60,24};

//devide calculate(devide *time){
//    if(time->count == 3 ) return *time;
//    if(time->value/devideTimeArray[time->count] != 0){
//        time->cal_time[time->count] = time->value%devideTimeArray[time->count];
//        time->value = time->value/devideTimeArray[time->count];
//        time->cal_time[time->count+1] = time->value;
//        time->count+=1;
//        return calculate(time);
//    }else{
//        time->cal_time[time->count] = time->value;
//        return *time;
//    }
//}

int main(){
    scanf("%d",&tc);
    
    for(int testcase=1; testcase<=tc; testcase++){
        int inputTime[6];
        string time;

        scanf("%d/%d/%d %d:%d:%d",&inputTime[5],&inputTime[4],&inputTime[3],&inputTime[2],&inputTime[1],&inputTime[0]);
        cin >> time;


        int addTime[4]={0};
        for(int i=0; i<time.length(); i++){
            int value = pow(2,i);
            addTime[3] += value/86400;
            value %=86400;
            addTime[2] += value/3600;
            value %=3600;
            addTime[1] += value/60;
            addTime[0] += value%60;
        }
        
        if(addTime[0]/60 !=0){
            addTime[1]+=addTime[0]/60;
            addTime[0] = addTime[0]%60;
        }
        
        if(addTime[1]/60 !=0){
            addTime[2] += addTime[1]/60;
            addTime[1] = addTime[1]%60;
        }
        
        if(addTime[2]/24 != 0){
            addTime[3] += addTime[2]/24;
            addTime[2] = addTime[2]%24;
        }

        // 초 더하기
        int addSec =inputTime[0] + addTime[0];
        if(addSec/60 != 0 ){
            inputTime[0] = addSec%60;
            inputTime[1] += addSec/60;
        }else inputTime[0] = addSec;

        //분 더하기
        int addMin = inputTime[1] + addTime[1];
        if(addMin/60 != 0 ){
            inputTime[1] = addMin%60;
            inputTime[2] += addMin/60;
        }else inputTime[1] = addMin;

        int m_day[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
        //시간 더하기
        int addHour = inputTime[2] + addTime[2];
        if(addHour/24 != 0 ){
            inputTime[2] = addHour%24;
            int day_check = inputTime[3] + addHour/24;
            if(inputTime[5]%400 == 0 || (inputTime[5]%100!=0 && inputTime[5]%4==0)){
                // 윤년
                m_day[2] = 29;
            }
            if(m_day[inputTime[4]] < day_check){
                inputTime[3] = day_check - m_day[inputTime[4]];
                if(inputTime[4]+1 > 12){ inputTime[4] = 1; inputTime[5]+=1;}
                else inputTime[4]+=1;
            }else inputTime[3] = day_check;
        }else inputTime[2] = addHour;

        m_day[2]= 28;

        //일 더하기

        // 년이 바뀌는지..볼거야ㅠ..
        int addDay = inputTime[3]+addTime[3];
//        printf("addDay : %d\n",addDay);
        if(addDay/1461 != 0 ){
            inputTime[5] += 4*(addDay/1461);
            addDay = addDay%1461;
        }
//        printf("addDay : %d\n",addDay);
        while(1){
            int dev_d=365;
            if(inputTime[5]%400 == 0 ){
                // 윤년
                dev_d = 366;
            }
            if(inputTime[5]%100 !=0  && inputTime[5]%4 == 0) dev_d = 366;
            if(addDay/dev_d == 0) break;
            else{
                if(inputTime[4] != 2) dev_d = 365;
                inputTime[5]+=1;
                addDay-=dev_d;
            }
        }
//        printf("***%d\n",addDay);
        while(1){
            m_day[2]= 28;
            if(inputTime[5]%400 == 0 || (inputTime[5]%100!=0 && inputTime[5]%4==0)){
                // 윤년
                m_day[2]=29;
            }
            if(addDay <= m_day[inputTime[4]]){ inputTime[3] = addDay; break;}
            else{
                addDay-=m_day[inputTime[4]];
                if(inputTime[4]+1>12){inputTime[4] = 1; inputTime[5]+=1;}
                else inputTime[4]+=1;
            }
        }
        printf("#%d %d/%02d/%02d %02d:%02d:%02d\n",testcase,inputTime[5],inputTime[4],inputTime[3],inputTime[2],inputTime[1],inputTime[0]);
    }
    
    return 0;
}
