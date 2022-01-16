#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,popcnt,fma")
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, l, r) for(int i = (l); i <= (r); ++i)
#define REP(i, n) FOR(i, 0, (n) - 1)
#define ssize(x) int(x.size())
template<class A, class B> auto& operator<<(ostream &o, pair<A, B> p) {
    return o << '(' << p.first << ", " << p.second << ')';
}
template<class T> auto operator<<(ostream &o, T x) -> decltype(x.end(), o) {
    o << '{'; int i = 0; for(auto e : x) o << (", ")+2*!i++ << e; return o << '}';
}
ostream& operator<<(ostream &o, string &s) {
    return o << s.data();
}
#ifdef DEBUG
/* #ifdef LOCAL */
#define debug(x...) cerr << "[" #x "]: ", [](auto... $) {((cerr << $ << "; "), ...); }(x), cerr << '\n'
#else
#define debug(...) {}
#endif
// https://codeforces.com/gym/102835/problem/D

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    if(n == 2){
        cout << "1\n";
        return 0;
    }
    /* set<int> adj[n]; */
    /* set<int> adj[31000]; */
    /* set<int> adj[31000]; */
    vector<int> adj[31000];
    REP(i,m){
        int f,s;
        cin >> f >> s;
        /* adj[f].insert(s); */
        /* adj[s].insert(f); */
        adj[f].push_back(s);
        adj[s].push_back(f);
    }
    REP(i,n)
        sort(adj[i].begin(), adj[i].end());
    constexpr int origk = 28;
    int k = 28;
    bool erasd[n];
    memset(erasd,0,n);
    /* // na pałę liniowo this part, though could smarter. */
    /* // Part 1. Wywalenie all z deg > k. */
    bool cont = 1;
    for(;cont;){
        cont = 0;
        for(int i = 0; i < n; ++i){
            if(erasd[i])
                continue;
            if(adj[i].size() > k){
                if(k <= 0){
                    cout << "-1\n";
                    return 0;
                }
                for(auto &x: adj[i])
                    /* adj[x].erase(i); */
                    adj[x].erase(lower_bound(adj[x].begin(), adj[x].end(), i));
                erasd[i] = 1;
                --k;
                cont = 1;
                break;
            }
        }
    }
    /* // Reguła 2. |E| > k^2 -> -1. */
    vector<int> rem;
    int edgecnt = 0;
    for(int i = 0; i < n; ++i){
        if(!erasd[i] && adj[i].size()){
            rem.push_back(i);
            edgecnt += adj[i].size();
        }
    }
    // wait, podwójnie policzony miałem xd.
    edgecnt >>= 1;
    if(edgecnt > k * k){
        cout << "-1\n";
        return 0;
    }
    static bool vis[31000];
    /* bool vis[n]; */
    /* memset(vis, 0, n); */
    /* auto bt = [&](vector<int> rem, int k){ */
    debug(rem);
    auto bt = [&](auto self, int depth){
        int mxdeg = 0;
        int whnode = -1;
        for(auto &i: rem){
            int crdeg = 0;
            for(auto &x: adj[i]){ // way slower with adj as a set here obv.
                // (202ms without a set, even though this still is quite dumb)
                // Radeoosh has same, but without kernelization. Ja mem TLE bez
                // kernelization
                crdeg += binary_search(rem.begin(), rem.end(), x);
            }
            if(crdeg > mxdeg){
                mxdeg = crdeg;
                whnode = i;
            }
        }
        if(!~whnode)
            return 0;
        if(depth >= k)
            return 1; // 1 + depth > k, czyli i tak zle by wychodziło. Very important. That's the difference between tle and not tle. Gotta limit the depth as far as is needed.
        // Or just do not wyifowańsko tego xd.
        // XD, it's actually faster without this.
        /* if(mxdeg <= 2){ */
        /*     // Łatwo rozwiązać. Chainy (m == n - 1) -> n / 2 floor; Cykle (m == n) -> n / 2 ceil. -> m / 2 ceil. */
        /*     int add = 0; */
        /*     vector<int> cleanupvec; */
        /*     for(auto &i: rem){ */
        /*         int ilem = 0; */
        /*         auto d1 = [&](auto self, int v) -> void{ */
        /*             cleanupvec.push_back(v); */
        /*             /1* debug(v); *1/ */
        /*             vis[v] = 1; */
        /*             for(auto &i: adj[v]){ */
        /*                 if(!binary_search(rem.begin(), rem.end(), i)) */
        /*                     continue; */
        /*                 ++ilem; // can't be pod !vis[i], no bo moze byc cycle; lepiej tak, i >>= 1 potem simply. */
        /*                 if(!vis[i]){ */
        /*                     /1* debug(v, i); *1/ */
        /*                     /1* ++ilem; *1/ */
        /*                     self(self, i); */
        /*                 } */
        /*             } */
        /*         }; */
        /*         if(!vis[i]){ */
        /*             d1(d1, i); */
        /*             debug(i, ilem); */
        /*             ilem >>= 1; */
        /*             add += (ilem + 1) >> 1; */
        /*         } */
        /*     } */
        /*     for(auto &i: cleanupvec) */
        /*         vis[i] ^= 1; */
        /*     /1* for(auto &i: rem){ *1/ */
        /*     /1*     auto d2 = [&](auto self, int v) -> void{ *1/ */
        /*     /1*         vis[v] = 0; *1/ */
        /*     /1*         for(auto &i: adj[v]){ *1/ */
        /*     /1*             if(!binary_search(rem.begin(), rem.end(), i)) *1/ */
        /*     /1*                 continue; *1/ */
        /*     /1*             if(vis[i]){ *1/ */
        /*     /1*                 self(self, i); *1/ */
        /*     /1*             } *1/ */
        /*     /1*         } *1/ */
        /*     /1*     }; *1/ */
        /*     /1*     if(vis[i]){ *1/ */
        /*     /1*         d2(d2, i); *1/ */
        /*     /1*     } *1/ */
        /*     /1* } *1/ */
        /*     debug(rem, add); */
        /*     return add; */
        /* } */
        vector<int> origrem = rem;
        rem.erase(lower_bound(rem.begin(), rem.end(), whnode));
        int wh = 1 + self(self, depth + 1); // dodajemy whnode do vertex cover.
        /* rem.insert(lower_bound(rem.begin(), rem.end(), whnode), whnode); */
        // don't have to reinsert this one actually.
        for(auto &i: adj[whnode]){
            if(binary_search(rem.begin(), rem.end(), i)){
                rem.erase(lower_bound(rem.begin(), rem.end(), i));
            }
        }
        wh = min(wh, mxdeg + self(self, depth + mxdeg)); // dodajemy adj(whnode) do vertex cover.
        rem = origrem;
        return wh;
    };
    int ret = bt(bt, 0);
    if(ret <= k){
        k -= ret;
        // max dopełnienie vertex coveru.
        cout << n - (origk - k) << '\n';
    }
    else{
        cout << "-1\n";
    }
}

