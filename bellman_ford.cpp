#include<bits/stdc++.h>
using namespace std;

vector<vector<pair<int,int>>> adj;

vector<int> bellman_ford(int start, int n){
    vector<int> dist(n,1e9);
    dist[start] = 0;
    bool cont = true;
    for(int i=0;i<n-1;++i){
        if(!cont) break;
        cont = false;
        for(int j=0;j<n;++j){
            for(auto const &e: adj[j]){
                if(dist[j] + e.second < dist[e.first]){
                    cont = true;
                    dist[e.first] = dist[j] + e.second;
                }
            }
        }
    }
    cont = false;
    for(int j=0;j<n;++j){
        for(auto const &e: adj[j]){
            if(dist[j] + e.second < dist[e.first]){
                cont = true;
                dist[e.first] = dist[j] + e.second;
            }
        }
    }
    if(cont)
        cout << "NEGATIVE WEIGHT CYCLE DETECTED!!!!!111111\n";


    return dist;
}

int main(){
    int n,m;
    n = 9;
    m = 8;
    adj.resize(n);
    adj[0].emplace_back(1,2);
    adj[0].emplace_back(5,2);
    adj[1].emplace_back(0,2);
    adj[1].emplace_back(2,2);
    adj[1].emplace_back(3,2);
    adj[2].emplace_back(1,2);
    adj[2].emplace_back(6,3);
    adj[3].emplace_back(1,2);
    adj[3].emplace_back(4,1);
    adj[3].emplace_back(5,2);
    adj[4].emplace_back(3,1);
    adj[4].emplace_back(6,1);
    adj[5].emplace_back(0,2);
    adj[5].emplace_back(3,2);
    adj[6].emplace_back(4,1);
    adj[6].emplace_back(2,3);
    adj[7].emplace_back(8,2);
    adj[8].emplace_back(7,2);
    int start = 0;
    vector<int> ret = bellman_ford(start,n);
    for(int i=0;i!=(int)ret.size();++i){
        ret[i] == 1e9 ? cout << "Not accessible\n" : cout << "Dist for " << i << ": " << ret[i] << '\n';
    }
}
