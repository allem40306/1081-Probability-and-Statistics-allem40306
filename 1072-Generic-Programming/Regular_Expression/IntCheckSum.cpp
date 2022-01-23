#include <bits/stdc++.h>
using namespace std;

int main(){
    string s;
    bool CaseDelimiter = false;
    regex reg("([+-]?0[0-7]+[uUlLiI]?\\b)|([+-]?[1-9]\\d+[uUlLiI]?\\b)|(0[xX]([0-9]|[a-f]|[A-F])+[uUlLiI]?\\b)");
    while(getline(cin, s)){
        vector<int> v;
        smatch m;
        if(CaseDelimiter)cout << '\n';
        CaseDelimiter = true;
        while(regex_search(s, m, reg)){
            int val;
            stringstream ss(m.str());
            for(int i = 1; i <= 3; ++i){
                if(m[i] == "")continue;
                if(i == 1){
                    ss >> oct >> val;
                }else if(i == 2){
                    ss >> dec >> val;
                }else{
                    ss >> hex >> val;
                }
                v.push_back(val);
                break;
            }
            s = m.suffix().str();
        }
        int sum = 0;
        sort(v.begin(), v.end(), greater<int>());
        for(int i = 0; i != (int)v.size(); ++i){
            if(i)cout << ' ';
            cout << v[i];
            sum += v[i];
        }
        cout << '\n' << sum << '\n';
    }
}