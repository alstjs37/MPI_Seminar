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

    // 각 프로세스에서 root에게 보낼 값: 본인의 rank 값 + 1
    send_msg = rank + 1;
    
    if (rank == 0) {
        cout << "[BEFORE] RANK: " << rank << " AND I RECV (GATHER) : ";
        for(int i = 0; i < size; i++) cout << buff[i] << " ";
        cout << endl;
    }

    sleep(1);
    cout << "[SEND] RANK : " << rank << " AND I WILL SEND ( " << send_msg << " ) TO ROOT (0)" << endl;
    sleep(1);

    // MPI_Gather(송신버퍼의 시작 주소, 송신버퍼의 원소 갯수, 송신 버퍼 원소의 데이터 타입, 
    //            수신 버퍼의 주소, 수신할 원소의 갯수, 수신 버퍼 원소의 데이터 타입, 수신(루트)프로세스의 랭크, 커뮤니케이터)
    /* 코드를 작성해 주세요 (1줄) */
    


    // 0을 루트로 사용, 0에서 각 프로세스가 보낸 정보 취합
    // 모든 프로세스(루트 포함)가 송신한 데이터를 취합하여 랭크 순서대로 저장
    if (rank == 0) {
        cout << "[AFTER] RANK: " << rank << " AND I RECV (GATHER) : ";
        for(int i = 0; i < size; i++) cout << buff[i] << " ";
        cout << endl;
    }
    
    // MPI 종료
    MPI_Finalize();

    return 0;
}