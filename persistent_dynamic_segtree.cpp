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

struct Vertex {
    Vertex *l, *r;
    int sum;

    Vertex() : l(nullptr), r(nullptr), sum(0) {}
    Vertex(int val) : l(nullptr), r(nullptr), sum(val) {}
    Vertex(Vertex *l, Vertex *r) : l(l), r(r), sum(0) {
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    }
};

Vertex vs[2000000]; //Increase accordingly!!!
vi freee; //freed nodes if required
int it;

inline Vertex* neww(){
    Vertex *vn;
    if(freee.empty())
        vn = &vs[it++];
    else{
        vn = &vs[freee.back()];
        freee.pop_back();
    }
    return vn;
}

//If not dynamic and initialization is required
Vertex* build(int a[], int tl, int tr) {
    Vertex *vn = neww();
    if (tl == tr){
        vn->sum = a[tl];
        return vn;
    }
    int tm = (tl + tr) / 2;
    *vn = Vertex(build(a, tl, tm), build(a, tm+1, tr));
    return vn;
}

Vertex* update(Vertex* v, int tl, int tr, int pos, int new_val) { //persistent
    Vertex *vn = neww();
    if (tl == tr){
        vn->sum = new_val;
        return vn;
    }
    int tm = (tl + tr) / 2;
    if (pos <= tm){
        *vn = Vertex(update((v->l?v->l:neww()), tl, tm, pos, new_val), v->r);
    }
    else{
        *vn = Vertex(v->l, update((v->r?v->r:neww()), tm+1, tr, pos, new_val));
    }
    return vn;
}

void update2(Vertex* v, int tl, int tr, int pos, int new_val) { //not persistent
    if (tl == tr){
        v->sum = new_val;
        return;
    }
    int tm = (tl + tr) / 2;
    if (pos <= tm){
        if(!v->l)
            v->l = neww();
        update2(v->l, tl, tm, pos, new_val);
    }
    else{
        if(!v->r)
            v->r = neww();
        update2(v->r, tm+1, tr, pos, new_val);
    }
    v->sum = (v->l?v->l->sum:0)+(v->r?v->r->sum:0);
}

int query(Vertex* v, int tl, int tr, int l, int r) {
    if (l > r)
        return 0;
    if (l == tl && tr == r)
        return v->sum;
    int tm = (tl + tr) / 2;
    return (v->l?query(v->l, tl, tm, l, min(r, tm)):0)
         + (v->r?query(v->r, tm+1, tr, max(l, tm+1), r):0);
}

/* void free(Vertex* v) { */
/*     /1* whatis(v->l) *1/ */
/*     if(v->l) free(v->l); */
/*     if(v->r) free(v->r); */
/*     freee.pb(v-vs); */
/*     *v = Vertex(); */
/* } */

void merge(Vertex *v1, Vertex *v2){ //z v1 do v2
    v1->sum += v2->sum;
    if(v2->l){
        if(!v1->l)
            v1->l = v2->l;
        else
            merge(v1->l,v2->l);
    }
    if(v2->r){
        if(!v1->r)
            v1->r = v2->r;
        else
            merge(v1->r,v2->r);
    }
    freee.pb(v2-vs);
    *v2 = Vertex();
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    int n = 1000000;
    Vertex v(0);
    update2(&v,0,n-1,18,1);
    cout << query(&v,0,n-1,0,n-1);
}

