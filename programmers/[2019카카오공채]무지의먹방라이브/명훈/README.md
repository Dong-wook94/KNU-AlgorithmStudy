# [2019카카오공채] 무지의 먹방 라이브

## 문제 풀이 사진

![image](https://user-images.githubusercontent.com/42582516/81668741-0e9b3980-9480-11ea-8df5-747930ff26f7.png)



## 문제 알고리즘

- 문제 구현 문제



## 풀이방법

1. 해당 값들을 받아서 Food class 배열에 넣는다.
2. Food 의 먹는 시간을 기준으로 오름차순으로 정렬한다
   * 그 이유는 해당 `index의 크기 * 전체 크기` 만큼 먹으면 해당 음식을 다먹을 동안 계속 전체 음식을 여러번 먹은 것이기 때문에
3. 먹는 시간을 기준으로 돌면서 언제까지 전체 길이 만큼 먹을 수 있는지 체크한다.
4. 한바퀴씩 먹을 수 있는 만큼 먹은 이후에 찾은 index를 찾는다
5. Food 의 번호 순으로 재정렬하고 난 뒤에 index를 가지고 해당 위치를 찾는다.

* 해당 설명이 이해가 안되면 코드로 이해하는 것이 도움이 될 것 같다.



- 핵심 코드

```java
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

```

## 문제 후 느낀점

- 다른사람 코드 참고