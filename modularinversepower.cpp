#include <stdio.h>
#include <algorithm>
#include <vector>
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
#define whatis(x) cerr << #x << " is " << x << endl;
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

#ifdef _WIN32
#define getchar_unlocked() _getchar_nolock()
#define _CRT_DISABLE_PERFCRIT_LOCKS
#endif
template<class L, class R> ostream& operator<<(ostream &os, map<L, R> P) { for(auto const &vv: P)os<<"("<<vv.first<<","<<vv.second<<")"; return os; }
template<class T> ostream& operator<<(ostream &os, set<T> V) { os<<"[";for(auto const &vv:V)os<<vv<<","; os<<"]"; return os; }
template<class T> ostream& operator<<(ostream &os, vector<T> V) { os<<"[";for(auto const &vv:V)os<<vv<<","; os<<"]"; return os; }
template<class L, class R> ostream& operator<<(ostream &os, pair<L, R> P) { os<<"("<<P.first<<","<<P.second<<")"; return os; }
inline int fstoi(const string &str){auto it=str.begin();bool neg=0;int num=0;if(*it=='-')neg=1;else num=*it-'0';++it;while(it<str.end()) num=num*10+(*it++-'0');if(neg)num*=-1;return num;}
inline void getch(char &x){while(x = getchar_unlocked(), x < 33){;}}
inline void getstr(string &str){str.clear(); char cur;while(cur=getchar_unlocked(),cur<33){;}while(cur>32){str+=cur;cur=getchar_unlocked();}}
template<typename T> inline bool sc(T &num){ bool neg=0; int c; num=0; while(c=getchar_unlocked(),c<33){if(c == EOF) return false;} if(c=='-'){ neg=1; c=getchar_unlocked(); } for(;c>47;c=getchar_unlocked()) num=num*10+c-48; if(neg) num*=-1; return true;}template<typename T, typename ...Args> inline void sc(T &num, Args &...args){ bool neg=0; int c; num=0; while(c=getchar_unlocked(),c<33){;} if(c=='-'){ neg=1; c=getchar_unlocked(); } for(;c>47;c=getchar_unlocked()) num=num*10+c-48; if(neg) num*=-1; sc(args...); }
#define N 1000001
/* #define N 2000001 */

inline uint64_t mulmod(uint64_t a, uint64_t b, uint64_t mod){
    if(b == 1) return a;
    if(b&1){
        return (a+mulmod(a,b^1,mod))%mod;
    }
    return mulmod(a,b >> 1,mod)*2%mod;
}

/* constexpr int64_t mod = 1000000007; */
constexpr int64_t mod = 998244353;
inline int64_t fastpow(int64_t a, int64_t b){
    if(b == 0)
        return 1;
    if(b&1){
        return (a * fastpow(a,b^1)) % mod;
    }
    a = fastpow(a,b >> 1);
    return (a*a)%mod;
}

int gcdExtended(int a, int b, int *x, int *y){
    if (a == 0){
        *x = 0, *y = 1;
        return b;
    }
    int x1, y1;
    int gcd = gcdExtended(b%a, a, &x1, &y1);
    *x = y1 - (b/a) * x1;
    *y = x1;
    return gcd;
}

//dzielnik i modulo musza byc wzglednie pierwsze
//jesli oba sa PIERWSZE, mozna tez uzyskac invb=fastpow(b,mod-2) % mod
int modInverse(int a, int m) {
    int x, y;
    gcdExtended(a, m, &x, &y);
    return (x%m + m) % m;
}

ll fac[N];
ll facinv[N];

// constexpr btw?
// -> operation limit that can't be changed by a pragma is too low. (agc051a.cpp tried on pc)
void pre(){
    fac[0] = 1;
    FOR(i,1,N)
        fac[i] = fac[i - 1] * i % mod;
    if constexpr (mod == 1000000007 && N == 1000001)
        facinv[N - 1] = 397802501;
    else if constexpr (mod == 998244353 && N == 1000001)
        facinv[N - 1] = 490058372;
    else
        facinv[N - 1] = fastpow(fac[N - 1], mod - 2);
    for(int i = N - 2; i >= 0; --i)
        facinv[i] = facinv[i + 1] * (i + 1) % mod;
    // Also i^-1 = facinv[i] * fac[i - 1] (i in 1..n)
    // Similary idea can be used to get invs of any n numbers in O(n + logp).
    // -> zamiast *1, *2, *3... do *a[0], *a[1], *a[2]...
}

ll binom(ll n, ll k){
    if(n < k || n < 0)
        return 0;
    return fac[n] * facinv[k] % mod * facinv[n - k] % mod;
}

ll stirling2(ll n, ll k){
    // S2(n,k) = (sum_{j=0}^{k}(-1)^{j}*binom(k,j)*(k-j)^n)/k!
    // Jeśli chcę wyliczyć wszystkie stirlingi z danym n, a tylko rosnące k, to
    // mogę fft użyć, i przemnożyć wielomiany [((-1)^i)/(i!)...], [(i^n)/(i!)]
    // S2(n+k+1,k) = sum_{j=0}^{k}S2(n+j,j)*j
    ll res = 0;
    FORE(i,0,k){
        ll cr = binom(k, i) * fastpow(k - i, n) % mod;
        if(i&1)
            res -= cr;
        else
            res += cr;
        res %= mod;
    }
    res *= facinv[k];
    return res % mod;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    pre();
    int a = 5, b = 2;
    int invb = modInverse(b,mod);
    int adivbmodmod = a*invb%mod;
    cout << adivbmodmod << '\n';
}

