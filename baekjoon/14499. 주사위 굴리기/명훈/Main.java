import java.util.*;

class pos{
	int x;
	int y;
	public pos() {
		this.x = 0;
		this.y = 0;
	}
	public pos(int x, int y) {
		this.x = x;
		this.y = y;
	}
}

class dice{
	int up;
	int down;
	int left;
	int right;
	int front;
	int back;
}

public class Main {
	static final int MAX = 20;
	static final int EAST = 1;
	static final int WEST = 2;
	static final int NORTH = 3;
	static final int SOUTH = 4;
	static final int dx[] = {1, -1, 0, 0};
	static final int dy[] = {0, 0, -1, 1};
	
	static int N, M, K;
	static int board[][] = new int[MAX][MAX];
	static dice Dice = new dice();
	static pos startPos = new pos();
	static ArrayList<Integer> dirList = new ArrayList<>();
	
	// 입력 및 초기화 
	public static void init() {
		Scanner sc = new Scanner(System.in);
		
		// input
		N = sc.nextInt();	M = sc.nextInt();
		startPos.y = sc.nextInt();	startPos.x = sc.nextInt();
		K = sc.nextInt();
		
		for(int i=0; i<N; i++)
			for(int j=0; j<M; j++)
				board[i][j] = sc.nextInt();
		for(int i=0; i<K; i++)
			dirList.add(sc.nextInt());
		
	}
	
	// 문제 해결
	public static void solution() {
		for(int i=0; i<dirList.size(); i++) {
			// 다음 방향 
			int nextDir= dirList.get(i);
			int nextY = startPos.y + dy[nextDir - 1];
			int nextX = startPos.x + dx[nextDir - 1];
			
			// 다음 위치가 밖이 아닌 경우에만 진행 
			if(isInBoard(nextY, nextX)) {
				// 다음 위치로 주사위를 굴
				moveDice(nextY, nextX, nextDir);
				
				// move position to next position
				startPos.y = nextY;
				startPos.x = nextX;
			}
		}
	}
	
	// move dice
	public static void moveDice(int nextY, int nextX, int nextDir) {
		int tmp;
		// move
		switch(nextDir) {
		case EAST:
			tmp = Dice.left;
			Dice.left = Dice.back;
			Dice.back = Dice.right;
			Dice.right = Dice.front;
			Dice.front = tmp;
			break;
		case WEST:
			tmp = Dice.right;
			Dice.right = Dice.back;
			Dice.back = Dice.left;
			Dice.left = Dice.front;
			Dice.front = tmp;
			break;
		case NORTH:
			tmp = Dice.down;
			Dice.down = Dice.back;
			Dice.back = Dice.up;
			Dice.up = Dice.front;
			Dice.front = tmp;
			break;
		case SOUTH:
			tmp = Dice.up;
			Dice.up = Dice.back;
			Dice.back = Dice.down;
			Dice.down = Dice.front;
			Dice.front = tmp;
			break;
		default:
			System.err.println("False Dir");
			System.exit(1);
		}
		
		// change Dice back 
		if(board[nextY][nextX] > 0) {
			Dice.back = board[nextY][nextX];
			board[nextY][nextX] = 0;
		}
		else {
			board[nextY][nextX] = Dice.back;
		}
		
		// print Dice front
		System.out.println(Dice.front);
		
	}
	
	
	// (y, x) => (bool), 해당 위치가 맵 안에 있는지 여부 확인 
	public static boolean isInBoard(int y, int x) {
		if(y < 0 || y >= N || x < 0 || x >= M)
			return false;
		return true;
	}
	
	public static void main(String[] args) {
		// input
		init();
		
		// solution
		solution();
		
		// output
	}

}
