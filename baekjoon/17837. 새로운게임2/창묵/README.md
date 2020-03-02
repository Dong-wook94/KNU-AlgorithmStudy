# 새로운게임2

# 풀이방법

시뮬레이션 문제에서 조건이 복잡하다보니 이를 잘 정리하고 풀어야겠다는 생각이 들었다.

move()라는 함수를 두어서, 색깔이 blue일때와 red,white 일때 움직이는 좌표의 변수를 각각 blueX,blueY newX,newY라고 두었다.

if ( blueX < 0 || blueX >= N || blueY < 0 || blueY >= N ) ==> 파란색칸의 움직임으로 인해 새로 움직이는 곳의 좌표가 막혀있다면, 그냥 방향만 바꿔주면 된다.



        cur.x = changeX;
        cur.y = changeY;
        move_chess_arr.add(cur); -> cur(현재 말)을 move_arr에 넣고
        cur_stacked_arr.remove(cur_chess_index); -> cur stacked_arr은 map의 각 index마다 있는 배열을 의미하는데, 각 맵에 어떠한 말들이 쌓여있는지 확인하기 위해 선언한 배열이다. 현재말을 옮겨야되기때문에 map[]의 배열에 있는 말을 제거해주어야한다.

        for (int i = cur_chess_index; i < cur_stacked_arr.size(); ) { // cur말고 나머지 체스말들을 같이 옮기기기위해 for문을 사용하였다.
            cur = cur_stacked_arr.get(cur_chess_index);
            cur.x = changeX;
            cur.y = changeY;
            move_chess_arr.add(cur);
            cur_stacked_arr.remove(cur_chess_index); // 마찬가지로 제거해주어야한다.
        }

         if (map[changeX][changeY].color == red) { 빨강이면 move_arr에 들어있는 말들을 역순으로 배치해주어야한다.
            Collections.reverse(move_chess_arr);
        }

        map[changeX][changeY].stacked_chess.addAll(move_chess_arr); // 흰색이면 그냥 merge.

        if(map[changeX][changeY].stacked_chess.size()>=4) // 4개 이상 쌓였으면? 바로 return.
            return true;


# 느낀점

일단 문제를 한번 잘못 이해하니깐, 코드를 그에 맞게 고치는데 애먹었다. 한줄을 추가안해서 두시간이라는 시간이 소비했다.
이 문제로 인해서 많이 부족하다는 것을 깨달았다.
