#input

BLANK = -999
maps = [] #리스트 생성 - wleh
orders = [] #명령
m,n,x,y,o_num = map (int, input().split())

for i in range(m) :
    maps.append( list(map(int, input().split())))
orders = list(map(int, input().split()))

#dice_index initialization
class dice_index:
    def __init__(self):
        self.east = 3
        self.west = 4
        self.south = 2
        self.north = 5
        self.bottom = 1
        self. top = 6

dice_index = dice_index()
dice = list()
for i in range(0, 7, 1) :
    if i==0 :
        dice.append(BLANK)
    dice.append(0)


#process
for i in range(0, o_num, 1) :
    #east
    if orders[i]==1 :
        y = y + 1
        if y>=n :
            y=y-1
            continue
        dice_index.bottom, dice_index.east, dice_index.top, dice_index.west = dice_index.east, dice_index.top, dice_index.west, dice_index.bottom
        if maps[x][y] == 0 :
            maps[x][y] = dice[dice_index.bottom]
        else :
            dice[dice_index.bottom] = maps[x][y]
            maps[x][y] = 0
        print(dice[dice_index.top])
    #west
    elif orders[i] == 2 :
        y = y - 1
        if y<0 :
            y=y+1
            continue
        dice_index.bottom, dice_index.east, dice_index.top, dice_index.west = dice_index.west, dice_index.bottom,dice_index.east , dice_index.top

        if maps[x][y] == 0:
            maps[x][y] = dice[dice_index.bottom]
        else:
            dice[dice_index.bottom] = maps[x][y]
            maps[x][y] = 0
        print(dice[dice_index.top])
    #north
    elif orders[i] == 3 :
        x = x -1
        if x<0 :
            x = x + 1
            continue
        dice_index.bottom, dice_index.south, dice_index.top, dice_index.north = dice_index.north, dice_index.bottom, dice_index.south, dice_index.top
        if maps[x][y] == 0:
            maps[x][y] = dice[dice_index.bottom]
        else:
            dice[dice_index.bottom] = maps[x][y]
            maps[x][y] = 0
        print(dice[dice_index.top])
    #south
    elif orders[i] == 4 :
        x = x + 1
        if x >= m :
            x = x - 1
            continue
        dice_index.bottom, dice_index.south, dice_index.top, dice_index.north = dice_index.south, dice_index.top, dice_index.north, dice_index.bottom
        if maps[x][y] == 0 :
            maps[x][y] = dice[dice_index.bottom]
        else :
            dice[dice_index.bottom] = maps[x][y]
            maps[x][y] = 0
        print(dice[dice_index.top])