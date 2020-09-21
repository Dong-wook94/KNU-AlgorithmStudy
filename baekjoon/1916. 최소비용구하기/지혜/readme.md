# 최소비용구하기

다익스트라 priority queue 이용함!

priority queue 사용하기 새로 알았다 

~~~c++
 priority_queue<Bus, vector<Bus>, cmp> pq;

struct cmp{
    bool operator()(Bus a,Bus b){
        return a.time < b.time;
    }
};

pq.top() // queue는 front 썼는데,,얘는 top임
  
  #include <limits.h> // INT_MAX, INT_MIN 사용시! 
~~~



