#include <iostream>
#include <ctime>
using namespace std;

int main(int argc, char *argv[])
{
	
    srand(time(NULL));   //�w���Ʀr�]�X�@��
    int N = atoi(argv[1]), M = atoi(argv[2]), tmp=0;
    for(int i =0;i <N; i++){
        tmp= rand()% M;   //�Ӽ��H��
        for(int i = 0; i <tmp;i++){
            cout<<char((rand()%26)+'a');  //�r�겣��
        }
        cout<<'\n';
    }
    return 0;
}
