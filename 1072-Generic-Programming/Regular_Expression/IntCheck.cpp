#include <bits/stdc++.h>
using namespace std;

int main(){
    string s;
    regex reg("([+-]?0[0-7]+[uUlLiI]?)|([+-]?[1-9]\\d+[uUlLiI]?)|(0[xX]([0-9]|[a-f]|[A-F])+[uUlLiI]?)");
    while(cin >> s){
        smatch m;
        if(regex_match(s, m, reg)){
            stringstream ss(s);
            int val;
            for(int i = 1; i <= 3; ++i){
                if(m[i] == "")continue;
                if(i == 1){
                    ss >> oct >> val;
                }else if(i == 2){
                    ss >> dec >> val;
                }else{
                    ss >> hex >> val;
                }
                if(i == 2){
                    cout << "TRUE\n";
                }else if(val > 0 && s[s.size() - 1] != 'U' && s[s.size() - 1] != 'u'){
                    cout << "TRUE +" << val << '\n';
                }
                else{
                    cout << "TRUE " << val << '\n';
                }
                break;
            }
        }else{
            cout << "FALSE\n";
        }
    }
}