#include <iostream>
#include <unistd.h>
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[]) {

    int size, rank;
    int ROOT = 0;
    
    // MPI 초기화
    MPI_Init(&argc, &argv);
    
    // 현재 프로세스의 랭크와 전체 프로세스 수 얻기
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int start = 0, end = 2;
    int buff[3] = {0, };
    int arr[size*3], sum = 1, result;

    // arr 배열 생성 [1, 2, 3, ... , N*3]
    if(rank == ROOT) {
        for (int i = 0; i < size*3; i++) arr[i] = i+1;
    
        cout << "[BEFORE] ROOT's ARRAY: ";
        for (int i = 0; i < size*3; i++) cout << arr[i] << " ";
        cout << endl << endl;
    }


    sleep(1);

    // MPI_Scatter(송신 버퍼의 주소, 각 프로세스로 보내지는 원소 개수, 송신 버퍼 데이터 타입, 
    //             수신 버퍼 주소, 수신 버퍼 원소 갯수, 수신 버퍼의 데이터 타입, 송신 프로세스 랭크, 커뮤니케이터)
    MPI_Scatter(arr+rank*3, 3, MPI_INT, buff, 3, MPI_INT, ROOT, MPI_COMM_WORLD);



    cout << "[SCATTER] RANK: " << rank << "'s ARRAY: ";
    for (int i = start; i <= end; i++) cout << buff[i] << " ";
    cout << endl;

    MPI_Barrier(MPI_COMM_WORLD);

    // 각 프로세스에서 따로 sum 계산
    cout << "[OPERATION] RANK: " << rank << " AND I CALCULATE ( ";
    for (int i = start; i <= end; i++) {
        sum *= buff[i];

        cout << buff[i];
        if (i != end) cout << " * ";
    }
    cout << " = " << sum << " )" << endl;

    MPI_Barrier(MPI_COMM_WORLD);

    // 각 프로세스로부터 데이터를 모아 하나의 값으로 환산, 그 결과를 모든 프로세스에 저장
    // MPI_Allreduce(송신 버퍼의 시작 주소, 수신 버퍼의 시작 주소, 송신 버퍼의 원소 갯수, 송신 버퍼의 데이터 타입, 환산 연산자, 커뮤니케이터)
    MPI_Allreduce(&sum, &result, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    cout << "[RESULT] RANK: " << rank << " ALL REDUCE with PRODUCT operation! RESULT = " << result << endl;

    // MPI 종료
    MPI_Finalize();

    return 0;
}