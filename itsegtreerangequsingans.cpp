#include <bits/stdc++.h>
using namespace std;
#define N 100000
int t[N<<1];
int n;
//Range increment, val of element

void modify(int l, int r, int inc){ //[l,r)
    l += n, r += n;
    while(l < r){
        if(l&1)
            t[l++] += inc;
        if(r&1)
            t[--r] += inc;
        l >>= 1, r >>= 1;
    }
}

int query(int pos){
    pos += n;
    int ret = 0;
    while(pos){
        ret += t[pos];
        pos >>= 1;
    }
    return ret;
}

int main(){
    ios_base::sync_with_stdio(0);
    int q;
    cin >> n;
    int arr[n];
    for(auto &i: arr)
        cin >> i;
    for(int i = n; i < n<<1; ++i)
        t[i] = arr[i-n];
    int type, l, r,val;
    cin >> q;
    while(q--){
        cin >> type >> l;
        if(type == 2){
            cin >> r >> val;
            modify(l,r+1,val);
        }
        else{
            cout << query(l) << endl;
        }
    }
}
