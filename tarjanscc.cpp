#include <bits/stdc++.h>
using namespace std;
#define N 50001
vector<int> adj[N];
int dfs_num[N], dfs_min[N];
int wh[N];
vector<int> adj2[N];
vector<vector<int>> scc;
stack<int> st;
int it;

void tarjan(int cur){
    dfs_num[cur] = dfs_min[cur] = ++it;
    st.push(cur);
    for(auto &i: adj[cur]){
        if(!dfs_num[i])
            tarjan(i);
        dfs_min[cur] = min(dfs_min[cur], dfs_min[i]);
    }
    if(dfs_num[cur] == dfs_min[cur]){
        scc.push_back({});
        int cr;
        do{
            //elements of the scc
            cr = st.top(); st.pop();
            dfs_min[cr] = 0x7f7f7f7f;
            wh[cr] = scc.size()-1;
            scc.back().push_back(cr);
        }while(cr != cur);
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n,m,f,s;
    cin >> n >> m;
    while(m--){
        cin >> f >> s;
        adj[f].push_back(s);
    }
    for(int i = 1; i <= n; ++i){
        if(!dfs_num[i]){
            tarjan(i);
        }
    }
    int nn = scc.size();
    bool was[n];
    memset(was,0,n);
    int qu[n+1];
    int *quit = qu;
    for(int i = 0; i < nn; ++i){
        wh[i] = 1;
        for(auto &x: scc[i]){
            for(auto &j: adj[x]){
                if(!was[wh[j]]){
                    was[wh[j]] = 1;
                    adj2[i].push_back(wh[j]);
                    *++quit = wh[j];
                }
            }
        }
        wh[i] = 0;
        while(quit != qu){
            wh[*quit--] = 0;
        }
    }
}
