import java.util.*;

public class Main {
	static final int MAX = 10;
	static final int SPECIAL_POS = 4;

	static int N;
	static int[][] playerScore; // player score board in 1 inning
	static boolean[] isPlayed; // is player played in before?
	static int[] player; // player number index
	static int answer; // answer

	public static void main(String[] args) {
		init(); // init input

		dfs(1); // solution

		System.out.println(answer);
	}

	// init
	public static void init() {
		Scanner sc = new Scanner(System.in);

		N = sc.nextInt();
		playerScore = new int[N][MAX];
		for (int i = 0; i < N; i++) {
			for (int j = 1; j < MAX; j++)
				playerScore[i][j] = sc.nextInt();
		}

		isPlayed = new boolean[MAX];
		player = new int[MAX];

		Arrays.fill(isPlayed, false);
		player[SPECIAL_POS] = 1;
		answer = -1;
	}

	// arrange player in list
	public static void dfs(int idx) {
		// end state
		if (idx == MAX) {
			int score = getBaseballScore();
			answer = (answer < score) ? score : answer;
			return;
		}
		
		// check 4th player
		// 4번 타자는 넘어가기 
		if (idx == SPECIAL_POS) {
			dfs(idx + 1);
			return;
		}

		// check general case
		// 1번 타자는 4번에 서므로, 2번부터 9번 타자까지만 세우면 된다 
		for (int i = 2; i < MAX; i++) {
			if (isPlayed[i])
				continue;
			player[idx] = i;
			isPlayed[i] = true;
			dfs(idx + 1);
			isPlayed[i] = false;
		}
	}

	// get score
	public static int getBaseballScore() {
		int score = 0; // score
		int outCount = 0; // out coumt, If this is 3, go next inning
		boolean[] baseballBase = new boolean[4]; // check baseball base
		int hitter = 1;

		for (int inning = 0; inning < N; inning++) {
			outCount = 0;
			boolean flag = true;
			Arrays.fill(baseballBase, false); // init
			
			while (flag) {
				int curPlayerScore = playerScore[inning][player[hitter]];

				// loop hitter 1 to 9 before 3 out
				if (hitter == 9)
					hitter = 1;
				else
					hitter++;

				// check 1, 2, 3, home base
				switch (curPlayerScore) {
				case 1: // single-base stroke
					if (baseballBase[3])
						score++;
					for (int i = 2; i >= 1; i--) {
						baseballBase[i + 1] = baseballBase[i];
					}
					baseballBase[1] = true;
					break;
				case 2: // double-base stroke
					if (baseballBase[3]) {
						score++;
						baseballBase[3] = false;
					}
					if (baseballBase[2]) {
						score++;
						baseballBase[2] = false;
					}
					if (baseballBase[1]) {
						baseballBase[3] = true;
						baseballBase[1] = false;
					}
					baseballBase[2] = true;
					break;
				case 3: // three-base stroke
					for (int i = 3; i >= 1; i--) {
						if (baseballBase[i])
							score++;
						baseballBase[i] = false;
					}
					baseballBase[3] = true;
					break;
				case 4: // home run
					for (int i = 3; i >= 1; i--) {
						if (baseballBase[i])
							score++;
						baseballBase[i] = false;
					}
					score++;
					break;
				case 0: // out
					outCount++;
					if (outCount == 3)
						flag = false;
					break;
				}
			}
		}
		return score;
	}

}
