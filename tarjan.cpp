#include <bits/stdc++.h>
using namespace std;
#define MX 50001
vector<int> adj[MX];
int dfs_num[MX], dfs_min[MX];
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
        if(!dfs_num[i])
            tarjan(i);
    }
}
