#include <iostream>
#include <ctime>
using namespace std;

int main(int argc, char *argv[])
{
	
    srand(time(NULL));   //預防數字跑出一樣
    int N = atoi(argv[1]), M = atoi(argv[2]), tmp=0;
    for(int i =0;i <N; i++){
        tmp= rand()% M;   //個數隨機
        for(int i = 0; i <tmp;i++){
            cout<<char((rand()%26)+'a');  //字串產生
        }
        cout<<'\n';
    }
    return 0;
}
