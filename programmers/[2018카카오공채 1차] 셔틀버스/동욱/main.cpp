#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Time{
private:
    int hour;
    int min;
    int m_time;
public:
    Time(string time){
        hour=stoi(time.substr(0,2));
        min = stoi(time.substr(3,2));
        m_time = 60*hour+min;
    }
    
    int getMinuate(){
        return m_time;
    }
    
    bool operator<(Time t)const{
        return this->m_time < t.m_time;
    }
};
typedef struct Bus{
    int time;
    vector<Time> crews;
}Bus;

string getTime(int t) {
    int hour = t / 60;
    int min = t % 60;
    string h, m;
    if (hour < 10)
        h = "0" + to_string(hour);
    else
        h = to_string(hour);
    if (min < 10)
        m = "0" + to_string(min);
    else
        m = to_string(min);

    return h + ":" + m;
}

vector<Bus> bus;

vector<Time> crew_infos;

string solution(int n, int t, int m, vector<string> timetable) {
    string answer = "";
    
    for(int i=0;i<timetable.size();i++){
        crew_infos.push_back(timetable[i]);
    }
    sort(crew_infos.begin(),crew_infos.end());
    
    int bus_time=540;
    
    for(int i=0;i<n;i++){
        Bus temp;
        temp.time = bus_time;
        bus.push_back(temp);
        bus_time = bus_time + t;
    }
    
    for(int i=0;i<crew_infos.size();i++){
        for(int j=0;j<bus.size();j++){
            if(crew_infos[i].getMinuate()<=bus[j].time && bus[j].crews.size()<m){
                bus[j].crews.push_back(crew_infos[i]);
                break;
            }
        }
    }
    
    if(bus[bus.size()-1].crews.size()<m){
        answer = getTime(bus[bus.size()-1].time);
    }
    else{
        int last_crew_idx = bus[bus.size()-1].crews.size()-1;
        answer = getTime(bus[bus.size()-1].crews[last_crew_idx].getMinuate()-1);
    }
    
    return answer;
}
