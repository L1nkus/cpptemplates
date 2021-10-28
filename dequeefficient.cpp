/* #pragma GCC optimize("O3,unroll-loops") */
/* #pragma GCC optimize("Ofast,unroll-loops") */
/* #pragma GCC target("avx2,popcnt") */
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <type_traits>
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
template<class L, class R> ostream& operator<<(ostream &os, pair<L, R> P) { os<<"("<<P.first<<","<<P.second<<")"; return os; }
template<class L, class R> ostream& operator<<(ostream &os, map<L, R> P) { for(auto const &vv: P)os<<"("<<vv.first<<","<<vv.second<<")"; return os; }
template<class T> ostream& operator<<(ostream &os, set<T> V) { os<<"[";for(auto const &vv:V)os<<vv<<","; os<<"]"; return os; }
template<class T> ostream& operator<<(ostream &os, vector<T> V) { os<<"[";for(auto const &vv:V)os<<vv<<","; os<<"]"; return os; }
inline int fstoi(const string &str){auto it=str.begin();bool neg=0;int num=0;if(*it=='-')neg=1;else num=*it-'0';++it;while(it<str.end()) num=num*10+(*it++-'0');if(neg)num*=-1;return num;}
inline void getch(char &x){while(x = getchar_unlocked(), x < 33){;}}
inline void getstr(string &str){str.clear(); char cur;while(cur=getchar_unlocked(),cur<33){;}while(cur>32){str+=cur;cur=getchar_unlocked();}}
template<typename T> inline bool sc(T &num){ bool neg=0; int c; num=0; while(c=getchar_unlocked(),c<33){if(c == EOF) return false;} if(c=='-'){ neg=1; c=getchar_unlocked(); } for(;c>47;c=getchar_unlocked()) num=num*10+c-48; if(neg) num*=-1; return true;}template<typename T, typename ...Args> inline void sc(T &num, Args &...args){ bool neg=0; int c; num=0; while(c=getchar_unlocked(),c<33){;} if(c=='-'){ neg=1; c=getchar_unlocked(); } for(;c>47;c=getchar_unlocked()) num=num*10+c-48; if(neg) num*=-1; sc(args...); }
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; //s.find_by_order(), s.order_of_key() <- works like lower_bound
template<typename T> using ordered_map = tree<T, int, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define N 1000001

// sz 0 -> unknown at compile time, dynamically allocated based on constructor.
template<typename T, size_t sz = 1000000, bool push_front_only = true, bool push_back_only = false>
struct fastdeque {
    T _a[sz];
    T *a = _a;
    /* template<std::enable_if_t<sz, int> = -1> */
    /* fastdeque(size_t dyn_sz) { */
    /*     a = new T[dyn_sz]; */
    /* } */
    /* template<std::enable_if_t<sz, int> = -1> */
    /* fastdeque() = delete; */
    int initpos = push_front_only ? sz : push_back_only ? 0 : sz >> 1;
    /* T *l = a + initpos, *r = a + initpos; */
    int l = initpos, r = initpos;
    void resize(size_t dyn_sz) {
        static_assert(sz == 0, "resize on nonzero init size");
        a = new T[dyn_sz];
        l = r = initpos = push_front_only ? dyn_sz : push_back_only ? 0 : dyn_sz >> 1;
    }
    /* template<std::enable_if_t<push_front_only, bool> = false> */
    void push_back(const T& value) {
        static_assert(!push_front_only, "push_back on push_front_only");
        a[r++] = value;
    }
    void pop_back() {
        --r;
    }
    /* template<std::enable_if_t<push_back_only, bool> = false> */
    void push_front(const T& value) {
        static_assert(!push_back_only, "push_front on push_back_only");
        a[--l] = value;
    }
    void pop_front() {
        ++l;
    }
    T &front() {
        return a[l];
    }
    T &back() {
        return a[r - 1];
    }
    T *begin() {
        return &a[l];
    }
    T *end() {
        return &a[r];
    }
    ssize_t size() {
        return r - l;
    }
    bool empty() {
        return l == r;
    }
    void clear() {
        /* r = l = initpos; */
        r = l = (r + l) >> 1;
    }
    T &operator [](size_t pos) {
        return a[l + pos];
    }
};
 
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
}

