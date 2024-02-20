#include <iostream>
#include <mpi.h>
#include <algorithm>

using namespace std;

int ROOT = 0;

int buff1[3] = {68, 37, 69};
void func1(int rank, int size) {
    int sender = 1;
    int data1 = 75;

    if (rank == ROOT) {
        // MPI_Recv(수신할 데이터를 저장할 버퍼의 시작 주소, 수신할 데이터의 개수, 수신할 데이터의 타입, 
        //          송신자 프로세스의 랭크, 송신자가 메시지에 부여한 태그, 커뮤니케이터,
        //          메세지의 상태를 나타내는 MPI_Status 구조체에 대한 포인터, 필요하지 않을 시 MPI_STATUS_IGNORE를 사용할 수 있음)
        MPI_Recv(buff1+1, 1, MPI_INT, sender, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else if(rank == sender) {
        cout << "";
        // MPI_Send(전송할 데이터의 시작 주소, 전송할 데이터의 갯수, 전송할 데이터 타입, 목적지 프로세서 랭크, 메세지를 식별하는 태그, 커뮤니케이터)
        MPI_Send(&data1, 1, MPI_INT, ROOT, 0, MPI_COMM_WORLD);
    }
}

int buff2[3];
void func2(int rank, int size) {
    int data2[3] = {70, 73, 71};

    // MPI_Gather(송신 버퍼의 시작 주소, 송신 버퍼의 원소 갯수, 송신 버퍼 원소의 데이터 타입, 
    //            수신 버퍼의 주소, 수신할 원소의 갯수, 수신 버퍼 원소의 데이터 타입, 수신(루트)프로세스의 랭크, 커뮤니케이터)
    MPI_Gather(data2+rank, 1, MPI_INT, buff2, 1, MPI_INT, ROOT, MPI_COMM_WORLD);
}

int buff3[6];
void func3(int rank, int size) {
    int data3[6] = {72, 84, 73, 78, 71, 33};
    // MPI_Allgather(송신 버퍼의 시작 주소, 송신 버퍼의 원소 개수, 송신 버퍼의 데이터 타입, 
    //               수신 버퍼의 주소, 각 프로세스로부터 수신된 데이터 갯수, 수신버퍼 데이터 타입, 커뮤니케이터)
    MPI_Allgather(data3+rank*2, 2, MPI_INT, buff3, 2, MPI_INT, MPI_COMM_WORLD);
}

void print_result(int rank, int size) {
    int result[12] = {0,};

    if(rank == ROOT) {
        copy(buff1, buff1+3, result);
        copy(buff2, buff2+3, result+3);
        copy(buff3, buff3+6, result+6);

        for (int i = 0; i < 12; i++) {
            if (i == 3) cout << " ";
            printf("%c", result[i]);
        }
        cout << endl;
    }
}

int main(int argc, char *argv[]) {

    int size, rank;
    
    // MPI 초기화
    MPI_Init(&argc, &argv);
    
    // 현재 프로세스의 랭크와 전체 프로세스 수 얻기
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    func1(rank, size);
    func2(rank, size);
    func3(rank, size);

    MPI_Barrier(MPI_COMM_WORLD);
    print_result(rank, size);

    // MPI 종료
    MPI_Finalize();

    return 0;
}