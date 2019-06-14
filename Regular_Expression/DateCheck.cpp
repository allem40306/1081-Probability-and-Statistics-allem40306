#include <bits/stdc++.h>
using namespace std;
regex reg ("\\d{2}\\/\\d{2}\\/\\d{4}");
regex reg2 ("\\d+");
int DaysOfMonths[15] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
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

bool isDate(string s){
    if(!regex_match(s, reg))
        return false;
    sregex_iterator pos(s.begin(), s.end(), reg2);
    sregex_iterator end;
    vector<int> v;
    for(auto it = pos; it != end; ++it){
        string s = it->str();
        v.push_back(StringToInt(s));
    }
    swap(v[0], v[1]);
    if(isLeap(v[2]) && v[1] == 2 && v[0] > 0 && v[0] <= 29)
        return true;
    if(v[0] <= 0 || v[0] > DaysOfMonths[v[1]])
        return false;
    return true;
}


int main(){
    string s;
    while(cin >> s){
        if(isDate(s)){
            cout << "TRUE\n";
        }else{
            cout << "FALSE\n";
        }
    }
    
}