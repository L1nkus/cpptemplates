#include <bits/stdc++.h>
using namespace std;
//Non decreasing, can be easily modified to any
//However, this implementation relies on value indexation, and as such
//if values can be too large, compression is needed.

#define N 1000001
int n = N-1;
int t[N];

void upd(int pos, int v){
    for(;pos <= n; pos += pos & -pos){
        if(v > t[pos]){
            t[pos] = v;
        }
    }
}

int qu(int pos){
    int ret = 0;
    for(;pos > 0; pos -= pos & -pos){
        if(t[pos] > ret){
            ret = t[pos];
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
	int n;
	cin >> n;
    int in[n];
    for(auto &i: in) cin >> i;
    vector<int> vec(in,in+n);
    sort(vec.begin(),vec.end());
    vec.erase(unique(vec.begin(),vec.end()),vec.end());
    for(auto &i: in){
        i = lower_bound(vec.begin(),vec.end(),i)-vec.begin()+1;
    }
    int ans = 0;
    for(int i = 0; i < n; ++i){
        int nv = qu(in[i])+1; //there must be no zeroes (fenwick)
        if(nv > ans){
            ans = nv;
        }
        upd(in[i],nv);
    }
    cout << ans << '\n';
}

