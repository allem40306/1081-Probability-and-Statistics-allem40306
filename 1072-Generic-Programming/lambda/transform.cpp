#include <bits/stdc++.h>
using namespace std;

int main(){
    bool o = false;
    vector<int> v, v2, v3, v4;
    int n;
    while(cin >> n){
        v.resize(n);
        v2.clear();
        v3.clear();
        v4.clear();
        for(int i = 0; i < n; ++i){
            cin >> v[i];
        }
        auto it = v.begin();
        transform(v.begin(), v.end() - 1, back_inserter(v2), [&it](int i){
            ++it;
            return *it - i;
        });
        auto output = [](int i){
            cout << ' ' << i;
        };
        if(o)cout << '\n';
        o = true;
        cout << *v.begin();
        for_each(v.begin() + 1, v.end(), output); 
        cout << '\n';
        cout << *v2.begin();
        for_each(v2.begin() + 1, v2.end(), output); 
        cout << '\n';
        int sum = 0;
        transform(v2.begin(), v2.end(), back_inserter(v3), [&](int i){
            sum += i;
            return sum;
        });
        cout << *v3.begin();
        for_each(v3.begin() + 1, v3.end(), output); 
        cout << '\n';

        int min_point = 0, max_profit = 0, now_index = 1;
        pair<int, int> pos = {0, 0};
        transform(v.begin() + 1, v.end(), back_inserter(v4), [&](int item){
            if(v[min_point] > v[now_index - 1])min_point = now_index - 1;
            min_point = min(min_point, v[now_index - 1]);
            if(max_profit < item - v[min_point]){
                max_profit = item - v[min_point];
                pos = make_pair(min_point, now_index);
            }
            ++now_index;
            return item - v[min_point];
        });
        cout << *v4.begin();
        for_each(v4.begin() + 1, v4.end(), output); 
        cout << '\n';
        cout << max_profit << '\n';
        cout << *(v.begin() + pos.first);
        for_each(v.begin() + pos.first + 1, v.begin() + pos.second + 1, output); 
        cout << '\n';
    }
}