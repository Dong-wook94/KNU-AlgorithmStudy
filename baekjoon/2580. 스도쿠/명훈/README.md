# 2580 스도쿠

## 문제해결 사진

![image](https://user-images.githubusercontent.com/42582516/81520841-5f2b6d80-9380-11ea-9ca2-0a660f549b73.png)



## 문제 알고리즘

- dfs
- 백트래킹



## 풀이방법

1. 넣을 수 있는 빈칸을 체크한다
2. 해당 빈칸에 수 하나씩 넣으면서 가능한지 확인하고, 가능 한 경우 다음 빈칸을 확인한다
   * 불가능인 경우 해당 수를 다른 수로 바꾼다.



- 핵심 코드

~~~java
import java.util.*;

class pos{
	int y;
	int x;
	public pos(int y, int x) {
		this.y = y;
		this.x = x;
	}
}

public class Main {
	static final int MAX = 9;
	static int board[][] = new int[MAX][MAX];
	static ArrayList<pos> blankList = new ArrayList<>();	// 빈칸 위치
	
	static void dfs(ArrayList<pos> arr, int idx) {
		if(idx == blankList.size()) {
			for(int i=0; i<MAX; i++) {
				for(int j=0; j<MAX; j++) {
					System.out.print(board[i][j] + " ");
				}
				System.out.println("");
			}
			System.exit(0);
		}
		
		// 1~9까지 적합한지 가능성 확인
		for(int i=1; i<=MAX; i++) {
			if(isValidPos(arr, idx, i)) {
				board[arr.get(idx).y][arr.get(idx).x] = i;
				dfs(arr, idx + 1);
			}
			if(i == MAX)
				board[arr.get(idx).y][arr.get(idx).x] = 0;
		}
	}
	
	static boolean isValidPos(ArrayList<pos> arr, int idx, int num) {
		for(int j=0; j<MAX; j++) {		// 가로
			if(arr.get(idx).x == j)	
				continue;
			if(board[arr.get(idx).y][j] == num)	
				return false;
		}
		for(int i=0; i<MAX; i++) {		// 세로
			if(arr.get(idx).y == i)	
				continue;
			if(board[i][arr.get(idx).x] == num)	
				return false;
		}
		int y = (arr.get(idx).y/3) * 3;
		int x = (arr.get(idx).x/3) * 3;
		for(int i=y; i<y+3; i++) {
			for(int j=x; j<x+3; j++) {
				if(i == arr.get(idx).y && j == arr.get(idx).x)	
					continue;
				if(board[i][j] != 0 && board[i][j] == num)	
					return false;
			}
		}
		return true;
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		// 스도쿠 board 채우기
		for(int i=0; i<MAX; i++)
			for(int j=0; j<MAX; j++)
				board[i][j] = sc.nextInt();
		
		// 스도쿠 빈칸을 Array List에 저장
		for(int i=0; i<MAX; i++)
			for(int j=0; j<MAX; j++)
				if(board[i][j] == 0)
					blankList.add(new pos(i, j));
		
		//for(int i=0; i<MAX; i++)
		//	System.out.print(blankList.get(i).y + ", " + blankList.get(i).x + "  ");
		//System.out.println("");
		
		// dfs, 0번째 인덱스부터 스도쿠 판을 채워간다.
		dfs(blankList, 0);
		
	}

}

~~~



## 문제 후 느낀점

- 오랜만에 java로 코딩

