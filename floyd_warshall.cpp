#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,m;
    n = 9;
    m = 8;
    vector<pair<int,int>> adj[n];
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
    int dist[n][n];
    memset(dist,63,sizeof dist);
    for(int i = 0; i < n; ++i){
        dist[i][i] = 0;
        for(auto &x: adj[i])
            dist[i][x.first] = x.second;
    }
    for(int k=0;k<n;k++)
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    int start = 0;
    for(int i=0;i!=n;++i){
        dist[start][i] == 1061109567 ? cout << "Not accessible\n" : cout << "Dist for " << i << ": " << dist[start][i] << '\n';
    }
}
