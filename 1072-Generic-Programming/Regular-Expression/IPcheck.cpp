#include <bits/stdc++.h>
using namespace std;

int main(){
    string s;
    regex reg ("((2([0-4]\\d|5[0-5]))|(1\\d{2})|([1-9]?\\d)).((2([0-4]\\d|5[0-5]))|(1\\d{2})|([1-9]?\\d)).((2([0-4]\\d|5[0-5]))|(1\\d{2})|([1-9]?\\d)).((2([0-4]\\d|5[0-5]))|(1\\d{2})|([1-9]?\\d))");
    while(cin >> s){
        if(regex_match(s, reg)){
            cout << "TRUE\n";
        }else{
            cout << "FALSE\n";
        }
    }
    
}