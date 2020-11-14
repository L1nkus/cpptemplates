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

#ifdef ONLINE_JUDGE
#define whatis(x) ;
#endif
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

ll t[N << 2];
pair<ll,ll> lazy[N << 2];
bool lazyclr[N << 2];

void prop(int v, int tl, int tr){
    if(!(lazyclr[v] | lazy[v].e1 | lazy[v].e2))
        return;
    if(tl != tr){
        if(lazyclr[v]){
            lazy[v << 1] = {0,0};
            lazy[v << 1 | 1] = {0,0};
            lazyclr[v << 1] = 1;
            lazyclr[v << 1 | 1] = 1;
            t[v << 1] = 0;
            t[v << 1 | 1] = 0;
        }
        int tm = (tl + tr) / 2;
        lazy[v << 1].e1 += lazy[v].e1;
        lazy[v << 1].e2 += lazy[v].e2;
        ll rfir = lazy[v].e1 + (tm + 1 + 1 - tl - 1) * lazy[v].e2;
        lazy[v << 1 | 1].e1 += rfir;
        lazy[v << 1 | 1].e2 += lazy[v].e2;
        int len1 = tm - tl + 1;
        int len2 = tr - (tm + 1) + 1;
        t[v << 1] += (lazy[v].e1 + lazy[v].e1 + (len1 - 1) * lazy[v].e2) * len1 / 2;
        t[v << 1 | 1] += (rfir + rfir + (len2 - 1) * lazy[v].e2) * len2 / 2;
    }
    lazyclr[v] = 0;
    lazy[v].e1 = 0;
    lazy[v].e2 = 0;
}

// seq musi być zgodny wględem [l,r];
// ważne żeby l >= 0 i r <= n - 1 tu
void update(int v, int tl, int tr, int l, int r, pair<ll,ll> seq){
    if(l > r)
        return;
    if(tl == l && tr == r){
        int len = tr - tl + 1;
        t[v] += (seq.e1 + seq.e1 + (len - 1) * seq.e2) * len / 2;
        lazy[v].e1 += seq.e1;
        lazy[v].e2 += seq.e2;
        return;
    }
    prop(v, tl, tr);
    int tm = (tl + tr) / 2;
    update(v << 1, tl, tm, l, min(r,tm), seq);
    int ldif = max(0, tm + 1 - l);
    update(v << 1 | 1, tm + 1, tr, max(l,tm + 1), r, {seq.e1 + ldif * seq.e2, seq.e2});
    t[v] = t[v << 1] + t[v << 1 | 1];
}

// zawsze 0 .. N - 1
void updateclr(int v, int tl, int tr){
    // override lazy always
    lazyclr[v] = 1;
    lazy[v] = {0,0};
    t[v] = 0;
    return;
}

ll query(int v, int tl, int tr, int l, int r){
    if(l > r)
        return 0;
    if(tl == l && tr == r){
        return t[v];
    }
    prop(v, tl, tr);
    int tm = (tl + tr) / 2;
    return query(v << 1, tl, tm, l, min(r,tm)) +
    query(v << 1 | 1, tm + 1, tr, max(l,tm + 1), r);
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
}

