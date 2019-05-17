#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
map<string, int> tb;

struct Cmp{
    int val;
    Cmp(int _val = 0):val(_val){};
    void SetVal(int _val){
        val = _val;
    }
    bool operator()(int i){
        return i >= val;
    }
};


int main(){
    int n, m, q;
    string s;
    cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> s;
        tb.insert({s, 0});
    }
    cin >> m;
    for(int i = 0, p; i < m; ++i){
        cin >> s >> p;
        tb[s] += p;
    }
    cout << "Scoreboard:\n";
    for(auto it: tb){
        cout << it.first << ':' << it.second << '\n';
    }
    vector<int> v;
    for(auto it: tb){
        v.push_back(it.second);
    }
    cout << "Query Result:\n";
    cin >> q;
    Cmp cmp;
    for(int i = 0, qp, p; i < q; ++i){
        cin >> qp;
        cmp.SetVal(qp);
        cout << count_if(v.begin(), v.end(), cmp) << " people greater or equal to " << qp << " scores\n";
    }

}