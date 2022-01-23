//
//  main.cpp
//  STL hw04_01
//
//  Created by Mark Mac on 2019/5/25.
//  Copyright © 2019 Mark Mac. All rights reserved.
//

#include <iostream>
#include <regex>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, const char * argv[]) {
    string s;
    string str[1000];
    smatch result;
    bool o = false;
    while(getline(cin,s)){
        if(o)cout << '\n'; o = true;
        vector<string>ans;
        smatch match;
        regex sp("\\w+");//just character
        while(regex_search(s, match, sp)==true){
            for(auto i=match.begin();i!=match.end();i++){
                ans.push_back(i->str());
            }
            s=match.suffix().str();
        }
        sort(ans.begin(),ans.end());
        reverse(ans.begin(),ans.end());
        for(auto i=0;i!=ans.size();i++){
            cout<<ans[i]<<endl;
        }
    }
    return 0;
}
