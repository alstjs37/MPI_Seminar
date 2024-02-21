#include <iostream>
#include <unistd.h>
#include <mpi.h>

using namespace std;

int ROOT = 0;

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
/*  [ func1 설명 ]
    MPI 함수 중 Collective Communication 함수를 사용합니다.

    ROOT process (rank = 0)가 자신이 가지고 있는 arr 배열을 원소 3개씩 모든 프로세스에게 나눠줍니다.
    ex) rank = 0 -> 1, 2, 3
        rank = 1 -> 4, 5, 6 
        ...
        rank = N -> 3N-2, 3N-1, 3N

    즉, 하나의 배열을 원소 3개씩 나누어서 모든 프로세스에게 나눠주는 함수를 사용하면 됩니다.

    buff로 보내야된다는거 작성해야함
*/
int buff[3] = {0, };
void func1(int rank, int size, int arr[]) {
    // MPI_Scatter(송신 버퍼의 주소, 각 프로세스로 보내지는 원소 개수, 송신 버퍼 데이터 타입, 
    //             수신 버퍼 주소, 수신 버퍼 원소 갯수, 수신 버퍼의 데이터 타입, 송신 프로세스 랭크, 커뮤니케이터)
    MPI_Scatter(arr+rank*3, 3, MPI_INT, buff, 3, MPI_INT, ROOT, MPI_COMM_WORLD);
    
    cout << "[FUNC1] RANK: " << rank << "'s ARRAY: ";
    for (int i = 0; i <= 2; i++) cout << buff[i] << " ";
    cout << endl;
}

int operation(int rank, int size, int sum) {
    // 각 프로세스에서 따로 sum 계산
    cout << "[OPERATION] RANK: " << rank << " AND I CALCULATE ( ";
    for (int i = 0; i <= 2; i++) {
        sum *= buff[i];

        cout << buff[i];
        if (i != 2) cout << " * ";
    }
    cout << " = " << sum << " )" << endl;

    return sum;
}

void func2(int rank, int size, int sum){
    int result;

    // 각 프로세스로부터 데이터를 모아 하나의 값으로 환산, 그 결과를 모든 프로세스에 저장
    // MPI_Allreduce(송신 버퍼의 시작 주소, 수신 버퍼의 시작 주소, 송신 버퍼의 원소 갯수, 송신 버퍼의 데이터 타입, 환산 연산자, 커뮤니케이터)
    MPI_Allreduce(&sum, &result, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    cout << "[RESULT] RANK: " << rank << " [FUNC2] with PRODUCT operation! RESULT = " << result << endl;

}

int main(int argc, char *argv[]) {

    int size, rank;

    // MPI 초기화
    MPI_Init(&argc, &argv);
    
    // 현재 프로세스의 랭크와 전체 프로세스 수 얻기
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int arr[size*3], sum = 1;

    generateArray(rank, size, arr);

    func1(rank, size, arr);

    MPI_Barrier(MPI_COMM_WORLD);
    sum = operation(rank, size, sum);
    MPI_Barrier(MPI_COMM_WORLD);

    func2(rank, size, sum);

    // MPI 종료
    MPI_Finalize();

    return 0;
}