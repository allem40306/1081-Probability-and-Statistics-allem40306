#include <iostream>
#include <string>
#include <cctype>
#include <set>
#include <vector>
#include <ctime>
using namespace std;

void String_generate(string &s, int sz){
    s = "";
    for(int i = 0; i < sz; ++i){
        s += char('a' + rand() % 26);
    }
    s[0] = toupper(s[0]);
    return;
}

int main(int argc, char const *argv[]){
    int n = atoi(argv[1]), m = atoi(argv[2]), q = atoi(argv[3]);
    set<string> stringSet;
    vector<string> v;
    srand(time(NULL));
    cout << n << '\n';
    for(int i = 0, sz; i < n; ++i){
        static string s;
        sz = rand() % 100 + 1;
        do{
            String_generate(s, sz);
        }while(stringSet.find(s) != stringSet.end());
        stringSet.insert(s);
        v.push_back(s);
        cout << s << '\n';
    }
    cout << m << '\n';
    for(int i = 0, idx, p; i < m; ++i){
        idx = rand() % v.size();
        p = rand() % 100 + 1;
        cout << v[idx] << ' ' << p << '\n';
    }
    cout << q << '\n';
    long long qp;
    for(int i = 0; i < q; ++i){
        qp = rand() * rand() % 10000000 + 1;
        cout << qp << '\n';
    }
}
