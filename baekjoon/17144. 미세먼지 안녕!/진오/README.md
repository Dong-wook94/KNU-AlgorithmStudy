# 미세먼지 안녕!


**확산**

> 현재 배열에서만 확산이 진행된다고 가정하면, 하나의 확산이 다른 원소들에도 영향을 끼치기 때문에, spread 라는 배열을 만들어 확산된 값을 따로 구해준 후, 1sec 가 끝난후 arr 에 전부 더해주는 방식으로 구현하였음.

~~~c++
void spread_dust(int row, int col) {
	int dust;
	int count = 0;

	dust = arr[row][col] / 5;

	if (row - 1 >= 1 && arr[row - 1][col]>-1) {
		spread[row - 1][col] += dust;
		count++;
	}
	if (col - 1 >= 1 && arr[row][col - 1]>-1) {
		spread[row][col - 1] += dust;
		count++;
	}
	if (row + 1 <= row_num && arr[row + 1][col]>-1) {
		spread[row + 1][col] += dust;
		count++;
	}
	if (col + 1 <= col_num && arr[row][col + 1]>-1) {
		spread[row][col + 1] += dust;
		count++;
	}
	arr[row][col] = arr[row][col] - count * dust;
}
~~~

