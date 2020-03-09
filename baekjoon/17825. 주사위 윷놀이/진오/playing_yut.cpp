#include <iostream>
using namespace std;
#define endl '\n' 

struct dice {
	int dice_num;
	int horse_num;
};
dice arr[10];
//이동 규칙이 복잡할 수 있으므로 Look-up 테이블을 만들어서 사용한다.
//jump[index][0] = 해당 판 점수 //jump[index][1~5] => 주사위 해당 수가 나오면 이동하는 양 
int jump[33][6] = { {0,1,2,3,4,5},//0번자리
{2,2,3,4,5,9}, //1번자리
{4,3,4,5,9,10},//2번자리
{6,4,5,9,10,11}, //3번자리
{8,5,9,10,11,12},//4번자리
{10,6,7,8,20,29},//5번자리 
{13,7,8,20,29,30}, //6번자리 
{16,8,20,29,30,31}, //7번자리
{19,20,29,30,31,32}, //8번자리 
{12,10,11,12,13,14}, //9번자리
{14,11,12,13,14,15}, //10번자리 
{16,12,13,14,15,16}, //11번자리
{18,13,14,15,16,17}, //12번자리
{20,18,19,20,29,30}, //13번자리
{22,15,16,17,24,25}, //14번자리 
{24,16,17,24,25,26}, //15번자리 
{26,17,24,25,26,27}, //16번자리 
{28,24,25,26,27,28}, //17번자리
{22,19,20,29,30,31}, //18번자리
{24,20,29,30,31,32}, //19번자리
{25,29,30,31,32,32}, //20번자리 
{26,20,29,30,31,32}, //21번자리
{27,21,20,29,30,31}, //22번자리 
{28,22,21,20,29,30}, //23번자리 
{30,23,22,21,20,29}, //24번자리 
{32,26,27,28,31,32}, //25번자리 
{34,27,28,31,32,32}, //26번자리
{36,28,31,32,32,32}, //27번자리 
{38,31,32,32,32,32}, //28번자리 
{30,30,31,32,32,32}, //29번자리
{35,31,32,32,32,32}, //30번자리
{40,32,32,32,32,32}, //31번자리
{0,32,32,32,32,32} //32번자리 
}; 
int move();
int simul();


int main() {
	for (int i = 0; i < 10; i++) {
		cin >> arr[i].dice_num;
	}
	cout << simul();
}
int simul() {
	int count = 0;
	int temp;
	for (int i0 = 1; i0 <= 4; i0++) {
		arr[0].horse_num = i0;
		for (int i1 = 1; i1 <= 4; i1++) {
			arr[1].horse_num = i1;
			for (int i2 = 1; i2 <= 4; i2++) {
				arr[2].horse_num = i2;
				for (int i3 = 1; i3 <= 4; i3++) {
					arr[3].horse_num = i3;
					for (int i4 = 1; i4 <= 4; i4++) {
						arr[4].horse_num = i4;
						for (int i5 = 1; i5 <= 4; i5++) {
							arr[5].horse_num = i5;
							for (int i6 = 1; i6 <= 4; i6++) {
								arr[6].horse_num = i6;
								for (int i7 = 1; i7 <= 4; i7++) {
									arr[7].horse_num = i7;
									for (int i8 = 1; i8 <= 4; i8++) {
										arr[8].horse_num = i8;
										for (int i9 = 1; i9 <= 4; i9++) {
											arr[9].horse_num = i9;
											temp = move();
											if (temp > count) {
												count = temp;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return count;
}
int move() {
	int visit[33] = { 0, };
	int end[5] = { 0, };// 1~4번 끝났는지
	int num = 0;
	int sum = 0;
	int temp;
	int i;
	while (1) {
		if (num >= 10) {
			break;
		}
		for (i = 1; i < 32; i++) {
			if (arr[num].horse_num == visit[i]) {
				temp = i + jump[i][arr[num].dice_num];
				if (temp< 33) {
					visit[temp] = arr[num].horse_num;
					visit[i] = 0;
					sum = sum + jump[temp][0];
					break;
				}
				else if(visit[temp]!=0){
					return -1;
				}
				else {
					visit[i] = 0;
					end[arr[num].horse_num] = 1;
				}
			}
		}
		if (i == 32 && end[arr[num].horse_num] != 1) { //
			visit[jump[0][arr[num].dice_num]] = arr[num].horse_num;
			sum = sum + jump[0][arr[num].dice_num];
		}
		num++;

	}
	return sum;
}