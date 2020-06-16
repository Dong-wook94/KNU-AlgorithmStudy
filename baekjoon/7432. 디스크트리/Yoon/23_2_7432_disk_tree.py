import string
class Node :
    def __init__(self, data):
        self.data = data
        self.children = []
    def add_child(self, obj):
        self.children.append(obj)

def tree_sort_print(root,buffer):
    if root == None :
        return
    root.children =  sorted(root.children, key=lambda x: x.data)
    if root.data is not None :
        print(buffer + root.data)
        buffer += " "
    for _ in root.children :
        tree_sort_print(_,buffer)


input_num = int(input())
root = Node(None)
for _ in range(input_num) : #한줄씩 받아옴
    cur_path = input()
    cur_path = cur_path.split('\\')
    idx = 0
    cur_node = root
    next_node = Node(cur_path[idx])

    # \하나씩 떼서 트리에 집어넣음
    while True :
        #종료조건 : 패스길이만큼 돈다
        if idx >= len(cur_path):
            break
        next_node = Node(cur_path[idx])
        # checking for existing node with next_node: 새로들어올 노드가 이미 있는지 체크를 위함
        flag = 0
        for i in cur_node.children :
            if next_node.data == i.data :
                flag = 1
                break
        #자식에 next 노드가 있으면
        if flag == 1 :
            cur_node = i
        #자식에 next_node가 없으면
        if flag == 0:
            cur_node.add_child(next_node)
            cur_node = next_node
        idx += 1
tree_sort_print(root,'')