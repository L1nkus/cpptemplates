#include <bits/stdc++.h>
using namespace std;
//Non decreasing, can be easily modified to any
//However, this implementation relies on value indexation, and as such
//if values can be too large, compression is needed.

//Supports printing out the sequence itself with some complications

#define N 1000001
int n = N-1;
int t[N];
int w[N];
int p[N];

void upd(int pos, int v, int ind){
    for(;pos <= n; pos += pos & -pos){
        if(v > t[pos]){
            t[pos] = v;
            w[pos] = ind;
        }
    }
}

int qu(int pos, int ind){
    int ret = 0;
    p[ind] = -1;
    for(;pos > 0; pos -= pos & -pos){
        if(t[pos] > ret){
            ret = t[pos];
            p[ind] = w[pos];
        }
    }
    return ret;
}

int main() {
	int n;
	cin >> n;
    int in[n];
    int ans = 0;
    int aen;
    for(int i = 0; i < n; ++i){
        cin >> in[i];
        int nv = qu(in[i]+1,i)+1; //+1, because there must be no zeroes (fenwick)
        if(nv > ans){
            ans = nv;
            aen = i; //ending points, needed for sequence backtrace
        }
        upd(in[i]+1,nv,i);
    }
    //Backtrace
    vector<int> vec;
    int i = aen;
    do{
        vec.push_back(i);
        i = p[i];
    }while(~i);
    reverse(vec.begin(),vec.end());
    cout << ans << '\n';
    for(auto &i: vec)
        cout << in[i] << ' ';
}

