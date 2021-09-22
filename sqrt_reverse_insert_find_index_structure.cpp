// Ofast with avx2 -> 2807ms ; O3 with avx2 -> 2059ms
// Lone Ofast -> 2276ms ; Lone O3 -> 1996ms
/* #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math") */
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <array>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <stdlib.h>
#include <ctime>
#include <climits>
#include <cmath>
#include <complex>
#include <iostream>
#include <cctype>
#include <cstring>
#include <numeric>
#include <bitset>
#include <stack>
#include <functional>
#include <cassert>
#include <tuple>
#include <iomanip>
#define pb push_back
#define mp make_pair
#define all(a) begin(a),end(a)
#define FOR(x,val,to) for(int x=(val);x<int((to));++x)
#define FORE(x,val,to) for(auto x=(val);x<=(to);++x)
#define FORR(x,arr) for(auto &x: arr)
#define FORS(x,plus,arr) for(auto x = begin(arr)+(plus); x != end(arr); ++x)
#define FORREV(x,plus,arr) for(auto x = (arr).rbegin()+(plus); x !=(arr).rend(); ++x)
#define REE(s_) {cout<<s_<<'\n';exit(0);}
#define GET(arr) for(auto &i: (arr)) sc(i)
#define whatis(x) cerr << #x << " is " << (x) << endl;
#define e1 first
#define e2 second
#define INF 0x7f7f7f7f
typedef std::pair<int,int> pi;
typedef std::vector<int> vi;
typedef std::vector<std::string> vs;
typedef int64_t ll;
typedef uint64_t ull;
#define umap unordered_map
#define uset unordered_set
using namespace std;

#ifdef ONLINE_JUDGE
#define whatis(x) ;
#endif
#ifdef _WIN32
#define getchar_unlocked() _getchar_nolock()
#define _CRT_DISABLE_PERFCRIT_LOCKS
#endif
template<class L, class R> ostream& operator<<(ostream &os, pair<L, R> P) { os<<"("<<P.first<<","<<P.second<<")"; return os; }
template<class L, class R> ostream& operator<<(ostream &os, map<L, R> P) { for(auto const &vv: P)os<<"("<<vv.first<<","<<vv.second<<")"; return os; }
template<class T> ostream& operator<<(ostream &os, set<T> V) { os<<"[";for(auto const &vv:V)os<<vv<<","; os<<"]"; return os; }
template<class T> ostream& operator<<(ostream &os, vector<T> V) { os<<"[";for(auto const &vv:V)os<<vv<<","; os<<"]"; return os; }
inline int fstoi(const string &str){auto it=str.begin();bool neg=0;int num=0;if(*it=='-')neg=1;else num=*it-'0';++it;while(it<str.end()) num=num*10+(*it++-'0');if(neg)num*=-1;return num;}
inline void getch(char &x){while(x = getchar_unlocked(), x < 33){;}}
inline void getstr(string &str){str.clear(); char cur;while(cur=getchar_unlocked(),cur<33){;}while(cur>32){str+=cur;cur=getchar_unlocked();}}
template<typename T> inline bool sc(T &num){ bool neg=0; int c; num=0; while(c=getchar_unlocked(),c<33){if(c == EOF) return false;} if(c=='-'){ neg=1; c=getchar_unlocked(); } for(;c>47;c=getchar_unlocked()) num=num*10+c-48; if(neg) num*=-1; return true;}template<typename T, typename ...Args> inline void sc(T &num, Args &...args){ bool neg=0; int c; num=0; while(c=getchar_unlocked(),c<33){;} if(c=='-'){ neg=1; c=getchar_unlocked(); } for(;c>47;c=getchar_unlocked()) num=num*10+c-48; if(neg) num*=-1; sc(args...); }
#define N 1000001

#define assert(x) ;

// Very cool TODO -> constexpr block size, e.g. 256 or 512 (higher może
// bardziej pylić dla lepszych efektów). -> array o stałym sizie, though wtedy
// uwaga aby to tak zrobić, żeby swap() wciąż był efektywny -- może std::array
// hmm, std::array swap is linear though.

struct block{
    /* auto operator=(const block &) & -> block& = delete; // to assure std::swap will move stuff in O(1). */
    /* auto operator=(block &&) & noexcept -> block&{ // is it needed for std::swap? */
    /*     return *this; */
    /* } */
    int l, r;
    int origid;
    bool shouldrev;
    vector<int> arr;
    void propagate(){
        if(shouldrev){
            reverse(all(arr));
            shouldrev = 0;
        }
    }
    void revrng(int whl, int whr){
        assert(!shouldrev);
        assert(l <= whl && whr <= r);
        whl -= l, whr -= l;
        reverse(arr.begin() + whl, arr.begin() + whr + 1);
    }
    template<bool shouldreverse>
    vector<int> cutoutarr(int whl, int whr){
        assert(!shouldrev);
        assert(l <= whl && whr <= r);
        whl -= l, whr -= l;
        assert(whl == 0 || whr == r - l);
        assert(whl >= 0 && whl <= r - l && whr >= 0 && whr <= r - l && whl <= whr);
        vector<int> ret(arr.begin() + whl, arr.begin() + whr + 1);
        if(shouldreverse)
            reverse(all(ret));
        arr.erase(arr.begin() + whl, arr.begin() + whr + 1);
        return ret;
    }
    bool operator<(const block &oth) const{
        return l < oth.l;
    }
};

struct revsqrt{
    revsqrt(int *a, int n){
        // Could be tuned.
        /* blksz = sqrt(n) + 1; */ // 2292ms
        /* blksz = 2 * sqrt(n) + 1; // 1668ms */
        for(int i = 0, l = 0, r = blksz - 1; l < n; l += blksz, r += blksz, ++i){
            blvec.push_back({l, min(r, n - 1), i, 0});
        }
        int it = 0;
        // In the task where this was originally used, values were 1..n, so
        // this could be used.
        // If values can be arbirtrarly large, either compress firstly, or use
        // a map here.
        inwhorigblk.resize(n + 1, 0);
        for(auto &i: blvec){
            i.arr = vector<int>(a + i.l, a + i.r + 1);
            FOR(x,0,i.r - i.l + 1)
                inwhorigblk[i.arr[x]] = it;
            ++it;
        }
        nit = blvec.size();
    }
    /* int blksz; */
    static constexpr int blksz = 1024; // 1590ms
    vector<block> blvec;
    vector<int> inwhorigblk;
    int nit;
    int opit;
    void reverse(int l, int r){
        vector<block> nwblocks;
        int it1 = -1, it2 = -1;
        for(int x = 0; x < (int)blvec.size(); ++x){
            if(blvec[x].l >= l && blvec[x].r <= r){
                int nwl = r + l - blvec[x].r;
                int nwr = r + l - blvec[x].l;
                blvec[x].l = nwl;
                blvec[x].r = nwr;
                blvec[x].shouldrev ^= 1;
                if(it1 == -1)
                    it1 = x;
                it2 = x;
            }
            else if(blvec[x].l <= l && blvec[x].r >= r){
                blvec[x].propagate();
                blvec[x].revrng(l, r);
            }
            else if(blvec[x].l <= l && blvec[x].r <= r && blvec[x].r >= l){
                blvec[x].propagate();
                block nwblock{r + l - blvec[x].r, r, nit, 0};
                nwblock.arr = blvec[x].cutoutarr<true>(l, blvec[x].r);
                FORR(i,nwblock.arr)
                    inwhorigblk[i] = nit;
                nwblocks.push_back(nwblock);
                blvec[x].r = l - 1;
                assert(blvec[x].r >= blvec[x].l);
                ++nit;
                assert(it1 == -1);
                it1 = x + 1;
                it2 = x + 1;
            }
            else if(blvec[x].l >= l && blvec[x].r >= r && blvec[x].l <= r){
                blvec[x].propagate();
                block nwblock{l, r + l - blvec[x].l, nit, 0};
                nwblock.arr = blvec[x].cutoutarr<true>(blvec[x].l, r);
                FORR(i,nwblock.arr)
                    inwhorigblk[i] = nit;
                nwblocks.push_back(nwblock);
                blvec[x].l = r + 1;
                assert(blvec[x].r >= blvec[x].l);
                ++nit;
            }
        }
        if(it1 != -1){
            std::reverse(blvec.begin() + it1, blvec.begin() + it2 + 1);
            FORR(i, nwblocks){
                if(i.l < blvec[it1].l){
                    assert(i.r == blvec[it1].l - 1);
                    blvec.insert(blvec.begin() + it1, std::move(i));
                    ++it2;
                }
                else{
                    assert(i.l == blvec[it2].r + 1);
                    blvec.insert(blvec.begin() + it2 + 1, std::move(i));
                }
            }
        }
        // Potentially to be tuned.
        if(++opit == 10){
            opit = 0;
            mergeloop();
        }
    }
    void insert(int pos, int val){
        for(int x = 0; x < (int)blvec.size(); ++x){
            if(blvec[x].l <= pos && blvec[x].r >= pos){
                blvec[x].propagate();
                blvec[x].arr.insert(blvec[x].arr.begin() + (pos - blvec[x].l), val);
                // TODO local, here newly inserted element was n + 1 always.
                inwhorigblk.push_back(blvec[x].origid);
                ++blvec[x].r;
                for(int j = x + 1; j < (int)blvec.size(); ++j){
                    ++blvec[j].l;
                    ++blvec[j].r;
                }
                // Split, potentially tune.
                if(blvec[x].r - blvec[x].l + 1 >= 2 * blksz){
                    int mid = blvec[x].l + blksz / 2;
                    blvec.insert(blvec.begin() + x + 1, {mid + 1, blvec[x].r, nit++, 0});
                    blvec[x + 1].arr = blvec[x].cutoutarr<false>(mid + 1, blvec[x].r);
                    blvec[x].r = mid;
                    FORR(i, blvec[x + 1].arr)
                        inwhorigblk[i] = blvec[x + 1].origid;
                }
                return;
            }
        }
        assert(pos == blvec.back().r + 1); // I hate edge cases.
        blvec.back().propagate();
        blvec.back().arr.push_back(val);
        inwhorigblk.push_back(blvec.back().origid);
        ++blvec.back().r;
    }
    int printval(int pos){
        // Can binsearch overkill this potentially.
        for(auto &i: blvec){
            if(i.l <= pos && pos <= i.r){
                i.propagate();
                return i.arr[pos - i.l];
            }
        }
        assert(false);
    }
    int printpos(int val){
        // Can potentially map origblk to curindex to eliminate this traversal.
        for(auto &i: blvec){
            if(i.origid == inwhorigblk[val]){
                i.propagate();
                auto it = find(all(i.arr), val);
                assert(it != i.arr.end());
                return (it - i.arr.begin()) + i.l;
            }
        }
        assert(false);
    }
    // Custom multiple vec iter erase?
    void mergeloop(){
        // Do i also wanna handle splits here?
        for(int x = 0; x < (int)blvec.size(); ++x){
            // Stuff to be tuned.
            if(blvec[x].r - blvec[x].l + 1 <= blksz / 2){
                blvec[x].propagate();
                if(x + 1 < (int)blvec.size() && blvec[x + 1].r - blvec[x + 1].l + 1 + blvec[x].r - blvec[x].l + 1 >= blksz * 3 / 2){
                    blvec[x + 1].propagate();
                    int szf = (blvec[x + 1].r - blvec[x + 1].l + 1 + blvec[x].r - blvec[x].l + 1) / 2;
                    /* assert(szf > blvec[x].r - blvec[x].l + 1); */
                    int ilemore = szf - (blvec[x].r - blvec[x].l + 1);
                    assert(ilemore < blvec[x+1].r - blvec[x+1].l + 1); // -> that failed, hmm.
                    vi nwarr = blvec[x + 1].cutoutarr<false>(blvec[x + 1].l, blvec[x + 1].l + ilemore - 1);
                    blvec[x].arr.insert(blvec[x].arr.end(), all(nwarr));
                    blvec[x].r += ilemore;
                    blvec[x + 1].l += ilemore;
                    FORR(i, nwarr)
                        inwhorigblk[i] = blvec[x].origid;
                }
                else if(x + 1 < (int)blvec.size()){
                    FORR(i, blvec[x].arr)
                        inwhorigblk[i] = blvec[x + 1].origid;
                    blvec[x + 1].propagate();
                    blvec[x + 1].arr.insert(blvec[x + 1].arr.begin(), all(blvec[x].arr));
                    blvec[x + 1].l = blvec[x].l;
                    blvec.erase(blvec.begin() + x);
                }
            }
        }
    }
};

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    int t;
    sc(t);
    while(t--){
        int n,m;
        sc(n,m);
        int a[n];
        int crn = n;
        GET(a);
        /* vi a(n); */
        /* iota(a,a+n,1); */
        /* iota(all(a),1); */
        revsqrt sth(a, n);
        /* revsqrt indmap(a, n); */
        // ^^ diff input indeed.
        int b[n];
        iota(b,b+n,1);
        revsqrt indmap(b, n);
        // -> nc, no more wa. no let's go back to opts.
        while(m--){
            int typ;
            int l,r,val,pos;
            sc(typ);
            if(typ == 1){
                sc(l,r);
                --l, --r;
                /* reverse(a+l,a+r+1); */
                /* reverse(a.begin()+l,a.begin()+r+1); */
                sth.reverse(l, r);
            }
            else if(typ == 2){
                sc(l,r);
                --l, --r;
                /* assert(0); */
                indmap.reverse(l, r);
            }
            else if(typ == 3){
                sc(pos, val);
                --pos;
                /* assert(0); */
                /* sth.insert(pos, val); */
                sth.insert(pos, crn + 1);
                indmap.insert(val - 1, crn + 1);
                ++crn;
            }
            else if(typ == 4){
                sc(pos);
                --pos;
                int res = sth.printval(pos);
                /* cout << res << '\n'; */
                int res2 = indmap.printpos(res);
                cout << res2 + 1 << '\n';
            }
            else if(typ == 5){
                sc(val);
                /* assert(0); */
                /* auto it = find(all(a), val); */
                /* assert(it != a.end()); */
                /* cout << it - a.begin() + 1 << '\n'; */
                /* int res = sth.printpos(val); */
                int res = sth.printpos(indmap.printval(val - 1));
                cout << res + 1 << '\n';
            }
        }
    }
}
