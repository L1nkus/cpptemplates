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
#define N 1000000
//range-range lazy propagation with arithmetic progression based updates
//(sum query)

struct el{ //arithmetic progrestion
    int fir;
    int dif;
};

int t[N << 2]; //sum
el lazy[N << 2]; //value to propagate

void init(int v, int l, int r, int a[]){
    if(l == r){
        t[v] = a[l];
        return;
    }
    int m = (l+r)>>1;
    init(v<<1,l,m,a);
    init(v<<1|1,m+1,r,a);
    t[v] = t[v<<1]+t[v<<1|1];
}

void prop(int v, int tl, int tr){
    if(!(lazy[v].fir | lazy[v].dif))
        return;
    int tm = (tl+tr) >> 1;
    int ll =  (tm-tr+1)*(lazy[v].fir*2+lazy[v].dif*(tm-tr))/2;
    t[v<<1] += ll;
    t[v<<1|1] += (tr-tl+1)*(lazy[v].fir*2+lazy[v].dif*(tr-tl))/2 - ll;
    lazy[v<<1].fir += lazy[v].fir;
    lazy[v<<1].dif += lazy[v].dif;
    lazy[v<<1|1].fir += lazy[v].fir+lazy[v].dif*(tm+1-tl);
    lazy[v<<1|1].dif += lazy[v].dif;
    lazy[v] = {0,0};
}

void update(int v, int tl, int tr, int l, int r, el cel){
    if(l > r) return;
    if(tl == l && tr == r){
        t[v] += (tr-tl+1)*(cel.fir*2+cel.dif*(tr-tl))/2;
        lazy[v].fir += cel.fir;
        lazy[v].dif += cel.dif;
        return;
    }
    prop(v,tl,tr);
    int tm = (tl+tr)>>1;
    update(v<<1,tl,tm,l,min(tm,r),cel);
    update(v<<1|1,tm+1,tr,max(l,tm+1),r,{cel.fir+cel.dif*(max(l,tm+1)-l),cel.dif});
    t[v] = t[v<<1]+t[v<<1|1];
}

int query(int v, int tl, int tr, int l, int r){
    if(l > r) return 0;
    if(tl == l && tr == r){
        return t[v];
    }
    prop(v,tl,tr);
    int tm = (tl+tr)>>1;
    return query(v<<1,tl,tm,l,min(tm,r)) +
    query(v<<1|1,tm+1,tr,max(l,tm+1),r);
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    int n;
    sc(n);
    int a[n];
    /* GET(a); */
    FOR(i,0,n)
        a[i] = 0;
    init(1,0,n-1,a);
    int q,t,l,r,fir,dif;
    sc(q);
    while(q--){
        sc(t,l,r);
        if(t == 1){ //update
            sc(fir,dif);
            update(1,0,n-1,l,r,{fir,dif});
        }
        else{
            cout << query(1,0,n-1,l,r) << endl;
        }
    }
}

