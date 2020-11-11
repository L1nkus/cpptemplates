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

//pożyczone z https://github.com/mareksom/acmlib/blob/master/code/kamil/halfplanes.cpp

// halfplanes_online
#define X real()
#define Y imag()
typedef long long LL;
typedef long double LD;
typedef complex<LL> P;
#define SZ(x) (int)x.size()

struct line {
    LL a,b,c;
    line(LL a_ = 0, LL b_ = 0, LL c_ = 0): a(a_), b(b_), c(c_) {} // <= 10^9
    line (P const &A, P const &B): a(A.Y-B.Y), b(B.X-A.X), c(A.X*B.Y-A.Y*B.X) {} //pts <= 10^6

    line operator - () const {return line(-a, -b, -c); }
    bool up() const { return a?(a<0):(b>0);}
};

inline LL wek(line const &a, line const &b) {return a.a*b.b-a.b*b.a;}
inline bool rown(line a, line b) {return wek(a,b) == 0;}
inline bool pokr(line a, line b) {return rown(a,b) && a.a*b.c == b.a*a.c && a.b*b.c == b.b*a.c;}
inline bool podobne(line a, line b) {return rown(a,b) && a.up() == b.up();}

inline complex<LD> prosta_prosta(line a, line b) {
    LL det = wek(a,b);
    LL x =  -a.c*b.b+b.c*a.b;
    LL y =  -a.a*b.c+a.c*b.a;
    return complex<LD>(x,y)/(LD)det;
}

inline LL weaker (line a, line b) { // czy a jest slabsze niz b
    assert(rown(a,b));
    if (abs(a.a) > abs(a.b)) return a.c*abs(b.a) -  b.c*abs(a.a);
    else return a.c*abs(b.b) -  b.c*abs(a.b);
}

struct Comp {
    bool operator()(const line& a, const line& b) const {
        if (a.up() != b.up()) return a.up() > b.up();
        return wek(a,b) > 0;
    }
};

const LD EPS = 1e-12;

struct przeciecie_polplaszczyzn {
    bool empty, pek;
    set<line, Comp> S;
    typedef set<line, Comp>::iterator iter;

    przeciecie_polplaszczyzn() : empty(false), pek(false) {};

    iter next(iter it){return (++it == S.end() ? S.begin() : it);}
    iter prev(iter it){return (it == S.begin() ? --S.end() : --it);}

    bool hide(line a, line b, line c) {
        if (rown(a,b)) {
            if (weaker(a, -b) < 0) empty = true;
            return false;
        }
        if (wek(a,b) < 0) swap(a,b);
        complex<LD> r = prosta_prosta(a,b);
        LD v = r.X * c.a + r.Y * c.b + c.c;
        if (wek(a,c) >=0  && wek(c,b) >=0 && v > -EPS) return true;
        if (wek(a,c) < 0  && wek(c,b) < 0) {
            if (v < -EPS) empty = true;
            else if (v < EPS) pek = true;
        }
        return false;
    }

    void add(line l) {
        if (empty) return;
        if (l.a == 0 && l.b == 0) {
            if (l.c < 0) empty = true;
            return;
        }
        iter it = S.lower_bound(l);
        //rownolegle
        if(it != S.end() && podobne(*it, l)) {
            if (weaker(l, *it)>=0) return;
            iter del = it;
            it = next(it);
            S.erase(del);
        }
        //*it>p
        if(SZ(S) >= 2 && it == S.end()) it = S.begin();
        while(SZ(S) >= 2 && hide(l, *next(it), *it)) {
            iter del = it;
            it = next(it);
            S.erase(del);
        }
        //*it<p
        if(SZ(S) >= 2) it = prev(it);
        while(SZ(S) >= 2 && hide(l, *prev(it), *it)) {
            iter del = it;
            it = prev(it);
            S.erase(del);
        }
        if(S.size() < 2 || !hide(*it, *next(it), l)) S.insert(l);
    }
    /*	 0 - puste	 1 - punkt	 2 - odcinek	 3 - półprosta	 4 - prosta
         5 - dodatnie (może nieskończone) pole (S.size() daje wowczas liczbę boków) */
    int type() {
        if(empty) return 0;
        if(SZ(S) <= 4){
            vector<line> res(all(S));
            if (SZ(res) == 2 && rown(res[0], res[1]) && weaker(res[0], -res[1])<0) return 0;
            FOR(i, 0, SZ(res)) FOR(j, 0, i) if(pokr(res[i], res[j])) {
                if(SZ(res) == 2) return 4;
                if(SZ(res) == 3) return 3;
                if(SZ(res) == 4 && pokr(res[0], res[2]) && pokr(res[1], res[3])) return 1;
                return 2;
            }
            if(SZ(res) == 3 && pek) return 1;
        }
        return 5;
    }
};

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
}

