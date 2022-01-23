#include <iostream>
#include <regex>
#include <string>
#include <algorithm>
using namespace std;

int main(){
    string s;
    regex reg("\\+\\(\\d{3}\\)-(\\d)-(\\1)(\\d{3})-(\\d{4})");
    while(getline(cin, s)){
        cout << regex_replace(s, reg, "+(XXX)-X-XXXX-$4") << '\n';
    }
}