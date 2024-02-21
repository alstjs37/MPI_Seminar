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

    int send_msg[size], buff;

    if (rank == ROOT) {
        for (int i = 0; i < size; i++) send_msg[i] = i + 1;

        cout << "[BEFORE] RANK: " << rank << "'s SEND_MSG: ";
        for (int i = 0; i < size; i++) cout << send_msg[i] << " ";
        cout << endl;

        for (int i = 0; i < size; i++) cout << "[SEND] RANK: " << rank << " AND I WILL SEND ( " << send_msg[i] << " ) TO RANK " << send_msg[i]-1 << endl;
    }

    // MPI_Scatter(송신 버퍼의 주소, 각 프로세스로 보내지는 원소 개수, 송신 버퍼 데이터 타입, 
    //             수신 버퍼 주소, 수신 버퍼 원소 갯수, 수신 버퍼의 데이터 타입, 송신 프로세스 랭크, 커뮤니케이터)
    // ROOT 프로세스는 데이터를 같은 크기로 나누어 각 프로세스에 랭크 순서대로 하나씩 전송
    /* 코드를 작성해 주세요 (1줄) */
    

    cout << "[AFTER] RANK: " << rank << " AND I RECV (SCATTER): " << buff << endl;

    // MPI 종료
    MPI_Finalize();

    return 0;
}