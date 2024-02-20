// practice mpi_gather
#include <iostream>
#include <unistd.h>
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[]) {
    
    int size, rank;
    
    // MPI 초기화
    MPI_Init(&argc, &argv);
    
    // 현재 프로세스의 랭크와 전체 프로세스 수 얻기
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int send_msg, buff[size] = {0, };

    // 각 프로세스에서 allGather할 값: 본인의 rank 값 + 1
    send_msg = rank + 1;
    
    cout << "[BEFORE] RANK: " << rank << " AND I RECV (ALLGATHER): ";
    for (int i = 0; i < size; i++) cout << buff[i] << " ";
    cout << endl;

    sleep(1);
    cout << "[SEND] RANK : " << rank << " AND I WILL SEND ( " << send_msg << " )" << endl;
    sleep(1);

    // MPI_Allgather(송신 버퍼의 시작 주소, 송신 버퍼의 원소 개수, 송신 버퍼의 데이터 타입, 
    //               수신 버퍼의 주소, 각 프로세스로부터 수신된 데이터 갯수, 수신버퍼 데이터 타입, 커뮤니케이터)
    MPI_Allgather(&send_msg, 1, MPI_INT, buff, 1, MPI_INT, MPI_COMM_WORLD);

    // 프로세스 j의 데이터 -> 모든 수신 버퍼 j 번째 블록에 저장
    cout << "[AFTER] RANK: " << rank << " AND I RECV (ALLGATHER): ";
    for (int i = 0; i < size; i++) cout << buff[i] << " ";
    cout << endl;
    
    // MPI 종료
    MPI_Finalize();

    return 0;
}