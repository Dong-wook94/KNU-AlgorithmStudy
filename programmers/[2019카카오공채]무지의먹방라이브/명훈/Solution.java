import java.util.*;

class Food implements Comparable<Food> {
	int idx;
	int time;

	Food(int idx, int time) {
		this.idx = idx;
		this.time = time;
	}

	public int compareIdx(Food other) {
		return idx - other.idx;
	}

	@Override
	public int compareTo(Food other) {
		return time - other.time;
	}
}

class Solution {
	static Food[] FoodList;

	public static int solution(int[] food_times, long k) {
		// init
		FoodList = new Food[food_times.length];
		for (int i = 0; i < food_times.length; i++)
			FoodList[i] = new Food(i + 1, food_times[i]);

		// sorting by times
		Arrays.sort(FoodList);

		// eat food
		long sum = 0;					// eaten food
		long leftoverFood = 0;			// leftover food
		int size = FoodList.length;		// food size
		int idx = 0; 					// next index
		boolean flag = false;			// flag that check eating all food

		for (int i = 0; i < size; i++) {
			long prev = sum;

			if (i == 0) {
				sum += (long)FoodList[i].time * size;
			} else {
				sum += (long)(FoodList[i].time - FoodList[i - 1].time) * (size - i);
			}

			if (sum > k) {
				leftoverFood = k - prev;
				idx = i;
				flag = true;
				break;
			}
			FoodList[i].idx = -1;
		}

		// 섭취할 경우가 없는 경우
		if (!flag)
			return -1;

		// sorting by idx
		Arrays.sort(FoodList, Food::compareIdx);

		// get answer
		int len = size - idx;		// find index
		int curIdx = 0;
		int ansIdx = 0;
		long findIdx = leftoverFood % (long) len;

		for (int i = 0; i < size; i++) {
			if (FoodList[i].idx == -1)
				continue;
			if (curIdx == findIdx) {
				ansIdx = i;
				break;
			}
			curIdx++;
		}
		return FoodList[ansIdx].idx;
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int food_times[] = { 3, 1, 2 };
		int ansResult = solution(food_times, 5);
		System.out.println(ansResult);
	}

}
