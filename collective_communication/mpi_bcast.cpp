// practice MPI_boradcast
#include <mpi.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

    int rank, size;

    // MPI 초기화
    MPI_Init(&argc, &argv);
    
    // 현재 프로세스의 랭크와 전체 프로세스 수 얻기
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int buff[size];

    // rank == 0인 프로세스(ROOT)에게만 [1,2,3 .. n] 나머지는 [0,0,0 .. 0]
    if (rank == 0) {
        for(int i = 0; i < size; i++) buff[i] = i+1;
    } else {
        for(int i = 0; i < size; i++) buff[i] = 0;
    }

    // Broadcast 전 buffer 출력
    cout << "[BEFORE] RANK: " << rank << " BUFFER = ";
    for(int i = 0; i < size; i++) cout << buff[i] << " ";
    cout << endl;

    // MPI_Bcast(버퍼 시작 주소, 버퍼 원소 갯수, 버퍼 원소의 MPI 데이터 타입, 루트 프로세스의 랭크, 커뮤니케이터)
    MPI_Bcast(buff, size, MPI_INT, 0, MPI_COMM_WORLD);
    sleep(1);

    // Broadcast 후 buffer 출력
    cout << "[AFTER] RANK: " << rank << " BUFFER = ";
    for(int i = 0; i < size; i++) cout << buff[i] << " ";
    cout << endl;

    // MPI 종료
    MPI_Finalize();

    return 0;
}