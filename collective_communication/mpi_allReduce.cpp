#include <iostream>
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

    int start, end;
    double arr[size*3], sum = 0.0, result;

    start = rank * 3;
    end = start + 2;
    
    // arr 배열 생성 [1, 2, 3, ... , N*3]
    for (int i = start; i <= end; i++) arr[i] = i+1;

    cout << "[BEFORE] RANK: " << rank << "'s ARRAY: ";
    for (int i = start; i <= end; i++) cout << arr[i] << " ";
    cout << endl;

    MPI_Barrier(MPI_COMM_WORLD);

    // 각 프로세스에서 따로 sum 계산
    cout << "[OPERATION] RANK: " << rank << " AND I CALCULATE ( ";
    for (int i = start; i <= end; i++) {
        sum += arr[i];

        cout << arr[i];
        if (i != end) cout << " + ";
    }
    cout << " = " << sum << " )" << endl;

    MPI_Barrier(MPI_COMM_WORLD);

    // 각 프로세스로부터 데이터를 모아 하나의 값으로 환산, 그 결과를 모든 프로세스에 저장
    // MPI_Allreduce(송신 버퍼의 시작 주소, 수신 버퍼의 시작 주소, 송신 버퍼의 원소 갯수, 송신 버퍼의 데이터 타입, 환산 연산자, 커뮤니케이터)
    /* 코드를 작성해 주세요 (1줄) */
    

    cout << "[RESULT] RANK: " << rank << " ALL REDUCE with SUM operation! RESULT = " << result << endl;

    // MPI 종료
    MPI_Finalize();

    return 0;
}