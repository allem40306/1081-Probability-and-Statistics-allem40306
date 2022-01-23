#include <iostream>
#include <regex>
#include <string>
#include <algorithm>
using namespace std;

int main(){
    bool o = false;
    string s;
    regex reg("((\\d+\\.\\d*|\\d*\\.\\d+)((e|E)[+-]?\\d+)?|\\d+((e|E)[+-]?\\d+))(F|f|L|l)?");
    while(getline(cin, s)){
        if(o)cout << '\n';
        o = true;
        if(regex_match(s,reg)){
            cout << "TRUE\n";
        }else{
            cout << "FALSE\n";
            sregex_token_iterator pos(s.cbegin(), s.cend(), reg);
            sregex_token_iterator end;
            for(;pos != end; ++pos){
                cout << pos->first - s.begin() << ' ' << pos->str() << '\n';
            }
        }
    }
}