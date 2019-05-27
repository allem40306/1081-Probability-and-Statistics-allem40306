//
//  main.cpp
//  STL hw04_02
//
//  Created by Mark Mac on 2019/5/25.
//  Copyright © 2019 Mark Mac. All rights reserved.
//
#include <iostream>
#include <regex>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, const char * argv[]) {
    string s;
    regex reg("^\\d{4}-\\d{4}-\\d{4}-\\d{4}$");
    regex reg2("^[0-9]{4}");
    while(getline(cin,s)){
        int total=0, a=0;
        if(regex_match(s,reg)){
            cout<<"TRUE ";
            string t="-";
            auto f=s.begin();
            auto b=s.end();
            for(int i=0;i<4;i++){
                sregex_token_iterator pos(f, b,reg2);
                sregex_token_iterator end;
                f+=5;
                a=stoi(pos->str());
                total+=a;
            }
            cout<<total<<"\n\n";
        }else{
            cout<<"FALSE\n\n";
        }
    }
    return 0;
}
