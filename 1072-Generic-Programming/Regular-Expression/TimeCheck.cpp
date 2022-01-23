#include <bits/stdc++.h>
using namespace std;
regex reg ("\\d{2}:\\d{2}:\\d{2}");
regex reg2 ("\\d+");

int StringToInt(string s){
    int ret = 0;
    for(auto it: s){
        ret *= 10;
        ret += (it - '0');
    }
    return ret;
}

bool isLeap(int y){
    return (y % 400 == 0 || (y % 4 == 0 && y % 100));
}

bool isTime(string s){
    if(!regex_match(s, reg))
        return false;
    sregex_iterator pos(s.begin(), s.end(), reg2);
    sregex_iterator end;
    vector<int> v;
    for(auto it = pos; it != end; ++it){
        string s = it->str();
        v.push_back(StringToInt(s));
    }
    if(v[0] < 24 && v[1] < 60 && v[2] < 60)
        return true;
    return false;
}


int main(){
    string s;
    while(cin >> s){
        if(isTime(s)){
            cout << "TRUE\n";
        }else{
            cout << "FALSE\n";
        }
    }
    
}