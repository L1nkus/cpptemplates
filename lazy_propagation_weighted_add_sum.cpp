/* #pragma GCC optimize("O3,unroll-loops") */
/* #pragma GCC optimize("Ofast,unroll-loops") */
/* #pragma GCC target("avx2,popcnt") */
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
#define debug(x...) cerr << "[" #x "]: ", [](auto... $) {((cerr << $ << "; "), ...); }(x), cerr << '\n'
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
#define debug(x...) ;
#endif
#ifdef _WIN32
#define getchar_unlocked() _getchar_nolock()
#define _CRT_DISABLE_PERFCRIT_LOCKS
#endif
template<class A, class B> auto& operator<<(ostream &o, pair<A, B> p) { return o << '(' << p.first << ", " << p.second << ')'; }
template<class T, enable_if_t<!is_same<T, string>::value, bool> = true> auto operator<<(ostream &o, T x) -> decltype(x.end(), o) { o << '{'; int i = 0; for(auto e : x) o << (", ")+2*!i++ << e; return o << '}'; }
inline void getch(char &x){while(x = getchar_unlocked(), x < 33){;}}
inline void getstr(string &str){str.clear(); char cur;while(cur=getchar_unlocked(),cur<33){;}while(cur>32){str+=cur;cur=getchar_unlocked();}}
template<typename T> inline bool sc(T &num){ bool neg=0; int c; num=0; while(c=getchar_unlocked(),c<33){if(c == EOF) return false;} if(c=='-'){ neg=1; c=getchar_unlocked(); } for(;c>47;c=getchar_unlocked()) num=num*10+c-48; if(neg) num*=-1; return true;}template<typename T, typename ...Args> inline void sc(T &num, Args &...args){ bool neg=0; int c; num=0; while(c=getchar_unlocked(),c<33){;} if(c=='-'){ neg=1; c=getchar_unlocked(); } for(;c>47;c=getchar_unlocked()) num=num*10+c-48; if(neg) num*=-1; sc(args...); }
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; //s.find_by_order(), s.order_of_key() <- works like lower_bound
template<typename T> using ordered_map = tree<T, int, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define N 1000001

// weight constant.
struct weightedaddseg{
    int t[N << 2];
    int weight[N << 2];
    int lazy[N << 2];

    // init sums 0.
    void build(int v, int tl, int tr, int arr[]){
        if(tl == tr){
            weight[v] = arr[tl];
            return;
        }
        int tm = (tl+tr)>>1;
        build(v<<1,tl,tm,arr);
        build(v<<1|1,tm+1,tr,arr);
        weight[v] = weight[v<<1] + weight[v<<1|1];
    }

    void push(int v, int tl, int tr){
        if(lazy[v]){
            int tm = (tl+tr)>>1;
            t[v<<1] += lazy[v]*weight[v<<1];
            t[v<<1|1] += lazy[v]*weight[v<<1|1];
            lazy[v<<1] += lazy[v];
            lazy[v<<1|1] += lazy[v];
            lazy[v] = 0;
        }
    }

    void modify(int v, int tl, int tr, int l, int r, int val){
        if(l > r) return;
        if(tl == l && tr == r){
            lazy[v] += val;
            t[v] += val*weight[v];
            return;
        }
        push(v,tl,tr);
        int tm = (tl+tr)>>1;
        modify(v << 1,tl,tm,l,min(tm,r),val);
        modify(v << 1 | 1,tm+1,tr,max(l,tm+1),r,val);
        t[v] = t[v<<1] + t[v<<1|1];
    }

    int query(int v, int tl, int tr, int l, int r){
        if(l > r) return 0;
        if(tl == l && tr == r){
            return t[v];
        }
        push(v,tl,tr);
        int tm = (tl+tr)>>1;
        return query(v<<1,tl,tm,l,min(tm,r)) + query(v<<1|1,tm+1,tr,max(l,tm+1),r);
    }
};
 
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
}

