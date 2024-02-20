// practice MPI_Reduce
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

    // 각 프로세스에서 계산한 sum 값 한 프로세스로 합치기
    // MPI_Reduce(송신 버퍼의 시작 주소, 수신버퍼의 시작 주소, 송신 버퍼의 원소 갯수, 송신 버퍼의 데이터 타입, 환산 연산자, 루트 프로세스 랭크, 커뮤니케이터)
    MPI_Reduce(&sum, &result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    cout << "[RESULT] RANK: " << rank << " REDUCE with SUM operation! RESULT = " << result << endl;

    // MPI 종료
    MPI_Finalize();

    return 0;
}