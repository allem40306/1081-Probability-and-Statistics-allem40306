#include <iostream>
#include <vector>
#include <queue>
#include <bitset>
#include <string.h>
using namespace std;
const int N = 1000;
class Edge{
public:
    int from, to, w;
};
class State{
public:
    int d, w;
    State(int _d, int _w): d(_d), w(_w){}
};

int n, S;
int d[N], p[N];
vector<Edge>E;
vector<int>v[N];
bitset<N> vis;

void init(){
    E.clear();
    for(int i = 0; i < N; ++i){
        v[i].clear();
    }
}

void addEdge(int from, int to, int w){
    v[from].push_back(E.size());
    E.push_back(Edge{from, to, w});
}

void dfs(int i){
    if(i == -1)return;
    dfs(p[i]);
    cout << i << "->";
    return;
}

void dijkstra(int s){// set d[] INF && set p[] -1
    memset(d, 0x3f, sizeof(d));
    memset(p, -1, sizeof(p));
    d[s] = 0;
    auto cmp =[](State &lhs, State &rhs){
        if(lhs.w != rhs.w)return lhs.w > rhs.w;
        return lhs.d < rhs.d;
    };
    priority_queue<State,vector<State>, decltype(cmp)>pq(cmp);
    vis.reset();
    pq.push(State(s, d[s]));
    while(!pq.empty()){
        auto k = pq.top(); pq.pop();
        if(vis[k.d])continue;
        if(k.d != S){
            dfs(p[k.d]);
            cout << k.d << ' ' << k.w << '\n';
        }        
        vis[k.d] = true;
        for(auto it: v[k.d]){
            Edge e = E[it];
            if(d[e.to] > d[e.from] + e.w){
                d[e.to] = d[e.from] + e.w;
                p[e.to] = e.from;
                pq.push(State(e.to, d[e.to]));
            }
        }
    }
}

int main(){
    while(cin >> n >> S){
        init();
        int x, y, z;
        while(cin >> x >> y >> z){
            addEdge(x, y, z);
        }
        dijkstra(S);
    }
}