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

const ll is_qu = -(1ll << 61);

struct Line{
    ll m,b;
    //pamiętać trzeba mutable i <const Line*()>
    mutable function<const Line*()> succ; //aby w comparatorze mieć dostęp do nexta Linii
    bool operator < (const Line &rhs) const{
        if(rhs.b != is_qu){ //hackish - gdy porównujemy przy insercie liczy się tylko m
            return m < rhs.m;
        }
        //przy lower boundzie - porównujemy z nextem dla danego iksa
        const Line *nx = succ();
        if(!nx) return 0;
        ll x = rhs.m;
        return x*m+b < x*nx->m+nx->b;
    }
};

struct hull : public multiset<Line>{
    bool bad(iterator y){
        auto nx = next(y);
        if(y == begin()){
            if(nx == end()) return 0;
            return y->m == nx->m && y->b <= nx->b;
        }
        auto pr = prev(y);
        if(nx == end()){
            return y->m == pr->m && y->b <= pr->b;
        }
        //to cza pamiętać, zawsze najpierw m i b, w 1. najpierw nx potem pr,
        //potem na odwrót i na odwrót kolejność z y
        return (nx->m-y->m)*(pr->b-y->b) >= (y->m-pr->m)*(y->b-nx->b);
    }
    void insert_line(ll m, ll b){
        auto y = insert({m,b});
        // [=]
        y->succ = [=]{return next(y) == end() ? 0 : &*next(y);}; //referencja nie iterator
        if(bad(y)){
            erase(y);
            return;
        }
        while(y != begin() && bad(prev(y))){
            erase(prev(y));
        }
        while(next(y) != end() && bad(next(y))){
            erase(next(y));
        }
    }
    ll eval(ll x){
        auto l = *lower_bound((Line){x,is_qu});
        return l.m*x+l.b;
    }
};

//eval(x) -> Get maximum value of ax+b on all inserted lines
//min = -eval(x) on -a -b

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
}

