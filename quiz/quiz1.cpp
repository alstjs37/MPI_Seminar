#include <iostream>
#include <mpi.h>
#include <algorithm>

using namespace std;

int ROOT = 0;

/*  [ func1 설명 ]
    MPI 함수 중 point to point 함수를 사용합니다.
    
    sender process (rank = 1)이 ROOT process (rank = 0)에게 data1을 전달합니다.
    ROOT process (rank = 0)은 sender process (rank = 1)으로 부터 data1을 전달받아 그 값을 buff1[1]에 작성합니다.
    즉, ROOT process (rank = 0)의 buff[3] = {68, 37, 69}를 buff[3] = {68, data1, 69} 으로 변경합니다.
    
    [ HINT ]
    배열의 이름은 배열의 시작주소를 담고 있습니다.
    배열의 n번째 인덱스는 (배열주소 + n) 형식으로 접근 가능합니다.
*/
int buff1[3] = {68, 37, 69};
void func1(int rank, int size) {
    int sender = 1;
    int data1 = 75;

    if (rank == ROOT) {
        /* 코드를 작성해 주세요 (1줄) */

    } else if(rank == sender) {
        /* 코드를 작성해 주세요 (1줄) */

    }
}

/*  [ func2 설명 ]
    MPI 함수 중 Collective Communication 함수를 사용합니다.

    함수를 사용하여,
    process rank: 0은 data2[0]을 ROOT process (rank = 0)의 buff[0]에,
    process rank: 1은 data2[1]을 ROOT process (rank = 0)의 buff[1]에,
    process rank: 2은 data2[2]을 ROOT process (rank = 0)의 buff[2]에 보냅니다.

    즉, 각 프로세스가 가지고 있는 값을 ROOT 프로세스에 하나의 값 (buff)에 모으는 함수를 사용합니다.

    [ HINT ]
    배열의 이름은 배열의 시작주소를 담고 있습니다.
    배열의 n번째 인덱스는 (배열주소 + n) 형식으로 접근 가능합니다.
*/
int buff2[3];
void func2(int rank, int size) {
    int data2[3] = {70, 73, 71};

    /* 코드를 작성해 주세요 (1줄) */

}

/*  [ func3 설명 ]
    MPI 함수 중 Collective Communication 함수를 사용합니다.

    함수를 사용하여,
    process rank: 0은 ( data2[0], data2[1] )을 모든 process (rank = 0, 1, 2)의 buff[0], buff[1]에,
    process rank: 1은 ( data2[2], data2[3] )을 모든 process (rank = 0, 1, 2)의 buff[2], buff[3]에,
    process rank: 2은 ( data2[4], data2[5] )을 모든 process (rank = 0, 1, 2)의 buff[4], buff[5]에 보냅니다.

    즉, 각 프로세스가 가지고 있는 값을 모든 프로세스에 하나의 값 (buff)에 모으는 함수를 사용합니다.

    [ HINT ]
    배열의 이름은 배열의 시작주소를 담고 있습니다.
    배열의 n번째 인덱스는 (배열주소 + n) 형식으로 접근 가능합니다.
*/
int buff3[6];
void func3(int rank, int size) {
    int data3[6] = {72, 84, 73, 78, 71, 33};
    
    /* 코드를 작성해 주세요 (1줄) */

}

/* 결과를 출력해주는 함수 입니다. */
void printResult(int rank, int size) {
    int result[12] = {0,};

    if(rank == ROOT) {
        copy(buff1, buff1+3, result);
        copy(buff2, buff2+3, result+3);
        copy(buff3, buff3+6, result+6);

        if (result[1] == 37) { cout << "[ERROR] 코드를 모두 작성하고 실행시켜 주세요 ^^" << endl; exit(1); }

        cout << "[SUCCESS] ";
        for (int i = 0; i < 12; i++) {
            if (i == 3) cout << " ";
            printf("%c", result[i]);
        }
        cout << endl;
    }
}

int main(int argc, char *argv[]) {

    int size, rank;
    
    // MPI 초기화
    MPI_Init(&argc, &argv);
    
    // 현재 프로세스의 랭크와 전체 프로세스 수 얻기
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // 프로세스는 3개를 사용해 주세요
    if (size != 3) {cout << "[ERROR] INCORRECT NUMBER OF PROCESS " << endl; return 0;}

    // func1, func2, func3을 작성해 주세요.
    func1(rank, size);
    func2(rank, size);
    func3(rank, size);

    // 결과를 출력해주는 함수 입니다.
    printResult(rank, size);

    // MPI 종료
    MPI_Finalize();

    return 0;
}