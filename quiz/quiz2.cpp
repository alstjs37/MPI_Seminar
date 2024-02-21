#include <iostream>
#include <unistd.h>
#include <mpi.h>

using namespace std;

int ROOT = 0;

/*
    [Collective Communication 함수 모음]
    1. MPI_Bcast(버퍼 시작 주소, 버퍼 원소 갯수, 버퍼 원소의 MPI 데이터 타입, 루트 프로세스의 랭크, 커뮤니케이터)

    2. MPI_Gather(송신 버퍼의 시작 주소, 송신 버퍼의 원소 갯수, 송신 버퍼 원소의 데이터 타입, 
                  수신 버퍼의 주소, 수신 할 원소의 갯수, 수신 버퍼 원소의 데이터 타입, 수신(루트)프로세스의 랭크, 커뮤니케이터)

    3. MPI_Allgather(송신 버퍼의 시작 주소, 송신 버퍼의 원소 개수, 송신 버퍼의 데이터 타입, 
                     수신 버퍼의 주소, 각 프로세스로부터 수신된 데이터 갯수, 수신버퍼 데이터 타입, 커뮤니케이터)

    4. MPI_Scatter(송신 버퍼의 주소, 각 프로세스로 보내지는 원소 개수, 송신 버퍼 데이터 타입, 
                    수신 버퍼 주소, 수신 버퍼 원소 갯수, 수신 버퍼의 데이터 타입, 송신 프로세스 랭크, 커뮤니케이터)

    5. MPI_ Reduce(송신 버퍼의 시작 주소, 수신 버퍼의 시작 주소, 송신 버퍼의 원소 갯수, 송신 버퍼의 데이터 타입, MPI 연산자, 루트 프로세스 랭크, 커뮤니케이터)
    
    6. MPI_Allreduce(송신 버퍼의 시작 주소, 수신 버퍼의 시작 주소, 송신 버퍼의 원소 갯수, 송신 버퍼의 데이터 타입, 환산 연산자, 커뮤니케이터)
*/

/*
    배열을 생성해주는 함수 입니다. 
    (N = 사용하는 프로세스 수)
    
    ROOT process (rank = 0)에서 arr 배열 생성 -> [1, 2, 3, ... , N*3] 
*/
void generateArray(int rank, int size, int arr[]) {
    if(rank == ROOT) {
        for (int i = 0; i < size*3; i++) arr[i] = i+1;
    
        cout << "[BEFORE] ROOT's ARRAY: ";
        for (int i = 0; i < size*3; i++) cout << arr[i] << " ";
        cout << endl << endl;
    }
}

/*  
    [ func1 설명 ]
    MPI 함수 중 Collective Communication 함수를 사용합니다.

    ROOT process (rank = 0)가 자신이 가지고 있는 arr 배열을 원소 3개씩 모든 프로세스에게 나눠줍니다.
    ex) rank = 0 -> 1, 2, 3
        rank = 1 -> 4, 5, 6 
        ...
        rank = N -> 3N-2, 3N-1, 3N

    이렇게 배열을 3개씩 나누어서 각 프로세스에 있는 buff 배열에 저장합니다.

    즉, 하나의 배열을 원소 3개씩 나누어서 모든 프로세스에게 나눠주는 함수를 사용하면 됩니다.

*/
int buff[3] = {0, };
void func1(int rank, int size, int arr[]) {
    /* 코드를 작성해 주세요 (1줄) */
    

    cout << "[FUNC1] RANK: " << rank << "'s ARRAY: ";
    for (int i = 0; i <= 2; i++) cout << buff[i] << " ";
    cout << endl;
}

/* 
    각 프로세스에서 자신이 가지고 있는 각 원소의 곱을 계산하여 반환해주는 함수
    ex) rank = 0 -> 1, 2, 3 -> 6
        rank = 1 -> 4, 5, 6 -> 120
        ...
        rank = N -> 3N-2, 3N-1, 3N 
*/
int operation(int rank, int size, int sum) {
    cout << "[OPERATION] RANK: " << rank << " AND I CALCULATE ( ";
    for (int i = 0; i <= 2; i++) {
        sum *= buff[i];

        // 식 출력
        cout << buff[i];
        if (i != 2) cout << " * ";
    }
    cout << " = " << sum << " )" << endl;

    return sum;
}

/*  
    [ func2 설명 ]
    MPI 함수 중 Collective Communication 함수를 사용합니다.

    각 프로세스에서 각각 계산한 값 (sum)을 모두 모아서 하나의 값으로 환산합니다.
    이때, 하나의 값으로 환산할 때는 각 프로세스에서 계산한 값 (sum)을 모두 더합니다.

    더한 값을 모든 process (rank = 0, 1, ... , N)의 특정 변수 (result)에 저장합니다.

    즉, 각 프로세스로부터 데이터를 모아서 하나의 값으로 환산하고, 그 결과를 모든 프로세스에 저장하는 함수를 사용하면 됩니다.
*/
void func2(int rank, int size, int sum){
    int result = 1;

    /* 코드를 작성해 주세요 (1줄) */


    cout << "[RESULT] RANK: " << rank << " [FUNC2] with SUM operation! RESULT = " << result << endl;

}

int main(int argc, char *argv[]) {

    int size, rank;

    // MPI 초기화
    MPI_Init(&argc, &argv);
    
    // 현재 프로세스의 랭크와 전체 프로세스 수 얻기
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int arr[size*3], sum = 1;

    // 프로세스의 수에 따라 배열 초기화
    generateArray(rank, size, arr);
    sleep(1);
    // 각 프로세스에게 데이터를 나눠주기
    func1(rank, size, arr);

    MPI_Barrier(MPI_COMM_WORLD);
    sleep(1);
    // 각 프로세스에서 특정 계산을 진행
    sum = operation(rank, size, sum);
    MPI_Barrier(MPI_COMM_WORLD);
    sleep(1);

    // 계산한 결과 값을 하나의 값으로 만들어 모든 프로세스에 저장
    func2(rank, size, sum);

    // MPI 종료
    MPI_Finalize();

    return 0;
}