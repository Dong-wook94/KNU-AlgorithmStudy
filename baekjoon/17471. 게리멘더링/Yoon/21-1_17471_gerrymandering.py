from collections import deque
import math

graph= []
sec_A = []
sec_B = []
idx = []

#combination for dividing section into 2
def combination(idx,r) :
    def generate(chosen) :
        if len(chosen) == r:
            for i in chosen:
                print(str(i) + " ")
            print(chosen)
            return

        start = idx.index(chosen[-1]) +1 if chosen else 0
        for nxt in range(start, len(idx)):
            chosen.append(idx[nxt])
            generate(chosen)

            chosen.pop()

    generate([])

#구역을 dfs로 탐색 --> visited의 개수가 sec의 구역개수와 다르면 조건 충족 X
#check the nodes of section is linked with each other
#seaching wiht DFS //
def dfs_linking (graph, sec, root):

    visited =[]
    stack = [root]
    while stack :
        n = stack.pop()
        if n not in visited:
            visited.append(n)
            stack += sec[n] - set(visited)
            # n의 자식들을 이미 들른것 빼고 스택에 넣음

    if len(visited) != len(sec) :
        print(sec+"unlinked")
        return -999
    else : return 1

def pop_calculate (sec):
    for _ in range(len(sec)):
        pop_sum = pop_sum + population[sec[_]-1]
    return pop_sum

#input
n = int(input())
population = list(map(int, input().split()))
for _ in range(n) :
    graph.append(list(map(int, input().split())))
    idx.append(_+1)

dfs_linking()
"""
for i in range(1, int(n/2+1)):
    sec_A = combination(idx, i)
    if(dfs_linking(sec_A)<0) :
        continue
    sec_B = idx - set(sec_A)  
"""




