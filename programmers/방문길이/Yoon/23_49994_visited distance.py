from _collections import deque
import copy

nxt = [0,0]
cur = [0,0]
visited = []

direction = {'U':[0,1],
             'D':[0,-1],
             'R':[1,0],
             'L':[-1,0]
             }

"""
집합의 원소는 변경가능한 자료형은 쓸수 없다 / 
리스트의 자료형은 무엇이든 가능함 
리스트와 집합의 이용법을 적절히 이용할 줄 알아야함
"""

def visited_path_check(cur, nxt) :
    print("hi")
    if [cur,nxt] in visited or [nxt,cur] in visited :
        return 0
    else :
        visited.append([cur, nxt])
        return 1

def range_validate(cur) :
    if cur[0]>5 or cur[0]<-5 :
        return 0
    elif cur[1]>5 or cur[1]<-5 :
        return 0
    else : return 1

def solution(dirs) :
    distance = 0
    global cur,nxt
    for _ in dirs :

        nxt[0] = cur[0]+ direction.get(_)[0]
        nxt[1] = cur[1]+ direction.get(_)[1]

        # 좌표옮길수 있는지 체크
        if range_validate(nxt) == 0 :
            continue
        # 갔던길 체크
        if visited_path_check(cur, nxt) == 1 :
            print("in")
            visited.append([cur,nxt])
            distance += 1
        cur = nxt.copy()
        print(_,"   pos : ",cur,"    dis : ",distance)
    return distance



dirs = input()
print(dirs)
solution(dirs)
