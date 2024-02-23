#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char* argv[]) {
    // MPI 초기화
    /* 코드를 작성해 주세요 (1줄) */
    MPI_Init(&argc, &argv);

    // 현재 프로세스의 랭크와 전체 프로세스 수 얻기
    int rank, world_size;
    /* 코드를 작성해 주세요 (2줄) */
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // 각 프로세스에서 출력
    cout << "Hello from process " << rank << " of " << world_size << endl;

    // MPI 종료
    MPI_Finalize();

    return 0;
}

