#include <stdio.h>

typedef struct Wheel{
    int tooth[8];
    int dir;
    int score;
}Wheel;

int n_turn;
Wheel wheel[4];

void changeAllDir(int num,int dir){
    //톱니바퀴 오른쪽방향설정
    for (int i = num;i<3; i++) {
        if (wheel[i].tooth[2] == wheel[i + 1].tooth[6]) //같은극일때
            break;
        else {//다른극일때
            wheel[i + 1].dir = -1 * wheel[i].dir;
        }
    }
    //톱니바퀴 왼쪽방향설정
    for (int i = num; i>0; i--) {
        if (wheel[i].tooth[6] == wheel[i - 1].tooth[2]) //같은극일때
            break;
        else {//다른극일때
            wheel[i - 1].dir = -1 * wheel[i].dir;
        }
    }
}

void turnWheel(int num,int dir){
    for(int i=0;i<4;i++){
        wheel[i].dir=0;
    }
    wheel[num].dir = dir;
    changeAllDir(num,dir);
    
    for (int i = 0; i < 4; i++) {
        if (wheel[i].dir == 1) {
            int temp = wheel[i].tooth[7];
            for (int j = 6; j >= 0; j--) {
                wheel[i].tooth[j + 1] = wheel[i].tooth[j];
            }
            wheel[i].tooth[0] = temp;
        }
        else if(wheel[i].dir==-1){
            int temp = wheel[i].tooth[0];
            for (int j = 0; j <=6; j++) {
                wheel[i].tooth[j] = wheel[i].tooth[j+1];
            }
            wheel[i].tooth[7] = temp;
        }
        else {//dir==0
            continue;
        }
    }
    
}

int main() {
    int score=1;
    for(int i=0;i<4;i++){
        for(int j=0;j<8;j++){
            scanf("%1d",&wheel[i].tooth[j]);
        }
        wheel[i].score=score;
        score*=2;
    }
    scanf("%d",&n_turn);
    for(int i=0;i<n_turn;i++){
        int wheel_num;
        int wheel_dir;
        scanf("%d %d",&wheel_num,&wheel_dir);
        turnWheel(wheel_num-1, wheel_dir);
//        printf("\n톱니바퀴\n");
//         for(int i=0;i<4;i++){
//               for(int j=0;j<8;j++){
//                   printf("%d",wheel[i].tooth[j]);
//               }
//             printf("\n");
//           }
    }
    
    int sum=0;
    for(int i = 0; i < 4; i++) {
        if (wheel[i].tooth[0] == 1)
            sum += wheel[i].score;
    }
    printf("%d\n",sum);

    
    return 0;
}
