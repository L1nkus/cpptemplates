#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
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
using namespace __gnu_pbds;

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
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; //s.find_by_order(), s.order_of_key() <- works like lower_bound
template<typename T> using ordered_map = tree<T, int, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define N 1000001

/*
    Algo:   Pollar Rho
    Task:   Prime Factorization of an Integer
    Author: Chandan Mittal
*/

const int MAX = 100000000;
const int LMT = 10000;
//
//if needed, replace operator with this
inline int64_t mulmod(int64_t a, int64_t b, int64_t mod){
    return (__int128_t(a))*b%mod;
    /* if(b == 1) return a; */
    /* if(b&1){ */
    /*     return (a+mulmod(a,b^1,mod))%mod; */
    /* } */
    /* return mulmod(a,b >> 1,mod)*2%mod; */
}

inline int64_t fastpow(int64_t a, int64_t b, int64_t mod){
    if(b == 1)
        return a;
    if(b&1){
        /* return (a * fastpow(a,b^1,mod)) % mod; */
        return mulmod(a,fastpow(a,b^1,mod),mod);
    }
    a = fastpow(a,b >> 1,mod);
    /* return (a*a)%mod; */
    return mulmod(a,a,mod);
}

//Miller-Rabin
inline bool isprime(ll n){
    if(n == 1) return 0;
    if(n == 2) return 1;
    if(n%2 == 0) return 0;
    /* ll magic[] = {2,3,5,7}; //enough for <= 1 << 32 */
    ll magic[] = {2,3,5,7,11,13,17,19,23,29,31,37}; //enough for <= 1 << 64
    /* ll magic[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37,41}; //enough for <= 1 << 64 */
    ll d = n;
    --d;
    ll r = 0;
    while(d%2)
        d /= 2, ++r;
    bool pr = 1;
    FORR(k,magic){
        if(k >= n) break;
        ll x = fastpow(k,d,n);
        if(x == 1 || x == n-1) continue;
        bool kk = 1;
        FOR(i,0,r-1){
            /* x = x*x%n; */
            x = mulmod(x,x,n);
            if(x == n-1){
                k = 0;
                break;
            }
        }
        if(kk){
            pr = 0;
            break;
        }
    }
    return pr;
}


/* ll abso(ll a)     //fn to return absolute value */
/* { */
/*     return a>0?a:-a; */
/* } */
/* ll gcd(ll a,ll b)    //Euclidean GCD recursive fn */
/* { */
/*     if(b==0) */
/*         return a; */
/*     else */
/*         return gcd(b,a%b); */
/* } */

ll pollard_rho(ll n){
    if(n%2==0)
        return 2;
    /* ll x = rand()%n+1; */
    /* ll c = rand()%n+1; */
    ll x = rand()%min(n,(ll)1e9)+1;
    ll c = rand()%min(n,(ll)1e9)+1;
    ll y = x;
    ll g = 1;
    //(x) = x*x + c
    while(g==1)
    {
        x = (mulmod(x,x,n) + c)%n;
        y = (mulmod(y,y,n) + c)%n;
        y = (mulmod(y,y,n) + c)%n;
        g = __gcd(abs(x-y),n);
    }
    assert(g != n);
    return g;
}

vector<ll> factors;

void factorize(ll n){
    if(n == 1)
        return;
    /* whatis(n) */
    /* whatis(isprime(n)) */
    if(isprime(n)){
        factors.push_back(n);
        return;
    }
    ll divisor = pollard_rho(n);
    factorize(divisor);
    factorize(n/divisor);
}

int main()  //Driver Program
{
    srand(time(0));
	ll n;
    cin >> n;
    factorize(n);
    FORR(i,factors)
        cout << i << ' ';
    printf("\n");
	return 0;
}


