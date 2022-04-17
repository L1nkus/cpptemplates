#pragma GCC target("bmi,bmi2,popcnt,lzcnt")
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
using namespace __gnu_pbds;

#ifdef _WIN32
#define getchar_unlocked() _getchar_nolock()
#define _CRT_DISABLE_PERFCRIT_LOCKS
#endif
template<class T> ostream& operator<<(ostream &os, vector<T> V) { os<<"[";for(auto const &vv:V)os<<vv<<","; os<<"]"; return os; }
template<class L, class R> ostream& operator<<(ostream &os, pair<L, R> P) { os<<"("<<P.first<<","<<P.second<<")"; return os; }
inline int fstoi(const string &str){auto it=str.begin();bool neg=0;int num=0;if(*it=='-')neg=1;else num=*it-'0';++it;while(it<str.end()) num=num*10+(*it++-'0');if(neg)num*=-1;return num;}
inline void getch(char &x){while(x = getchar_unlocked(), x < 33){;}}
inline void getstr(string &str){str.clear(); char cur;while(cur=getchar_unlocked(),cur<33){;}while(cur>32){str+=cur;cur=getchar_unlocked();}}
template<typename T> inline bool sc(T &num){ bool neg=0; int c; num=0; while(c=getchar_unlocked(),c<33){if(c == EOF) return false;} if(c=='-'){ neg=1; c=getchar_unlocked(); } for(;c>47;c=getchar_unlocked()) num=num*10+c-48; if(neg) num*=-1; return true;}template<typename T, typename ...Args> inline void sc(T &num, Args &...args){ bool neg=0; int c; num=0; while(c=getchar_unlocked(),c<33){;} if(c=='-'){ neg=1; c=getchar_unlocked(); } for(;c>47;c=getchar_unlocked()) num=num*10+c-48; if(neg) num*=-1; sc(args...); }
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; //s.find_by_order(), s.order_of_key() <- works like lower_bound
template<typename T> using ordered_map = tree<T, int, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

//Range Sum Query, Single element incrementaion update (only possibility pretty much, unless no re-modifications)
int n;
#define N 100000 //The same as array size is the need
int t[N];

//1 INDEXED, increment in function if needed

inline void upd(int pos, int val){ //val is delta
    // todo unrolled opt na podstawie popcountu xdddd
    // w przypadku upd, jeżeli n jest potęgą dwójki, which it should, ilość
    // iteracji to __log(N) - popcnt(pos) - ffs(pos)
    // całe pos -= pos & (-pos) translates into 1 instruction blsr, much better than some 1 << ffs
    // But, only z #pragma GCC target("bmi")
    // ; pos & (-pos) translated into blsi alone, gdy trzema += zamiast -=.
    for(;pos <= n;pos += pos & (-pos))
            //simply for(;posy <= m;posy += posy & (-posy)) for 2nd dimension
        t[pos] += val;
}

inline int query(int r){ //[0,r]
    // tutaj po prostu ilość iteracji to popcnt
    int ret = 0;
    for(;r > 0;r -= r & (-r))
        ret += t[r];
    return ret;
}

inline int query2(int r){ //[0,r]
    int ret = 0;
    int ile = __builtin_popcount(r);
    switch(ile){
        default:
            __builtin_unreachable(); // to mega pomaga, inaczej jeszcze musi caseować < 0 albo > maxval tutaj. (potężne 2 instructions saved)
        case 4:
            ret += t[r];
            r -= r & (-r);
        case 3:
            ret += t[r];
            r -= r & (-r);
        case 2:
            ret += t[r];
            r -= r & (-r);
        case 1:
            ret += t[r];
            r -= r & (-r);
    }
    return ret;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    int a[] = {1,9,-4,0,32,1,8};
    n = sizeof a >> 2;
    for(int i = 1; i <= n; ++i){
        cout << a[i-1] << ' ';
        upd(i,a[i-1]);
    }
    cout << endl;
    int q,f,s;
    cin >> q;
    while(q--){
        cin >> f >> s;
        cout << query(s+1) - (f?query(f):0) << endl;
    }
}

