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

struct Segtree {
    int mx[N << 2];
    int ilemx[N << 2];
    // w sumie "other" zamiast mx2
    /* int mx2[N << 2]; */
    /* int mn[N << 2]; */
    // both mx for mn for both minowanie and maxowanie
    int mn[N << 2];
    int ilemn[N << 2];
    /* int t[N << 2]; // suma all innych liczb (nie mx / nie mn) */
    int t[N << 2]; // suma all liczb
    int mx2[N << 2]; // największy w innych (poza mx / mn)
    int mn2[N << 2]; // najmniejszy w innych (poza mx / mn)
    /* vector<function<void(void)>> lazyvec[N << 2]; */
    // Work in progress.
    // Due to vectors, needed to support nested operations of multitude of
    // times, this present code is somehow slower than a quadratic solution.
    /* vector<pair<void (Segtree::*)(int,int,int,int),int>> lazyvec[N << 2]; */
    // Also, pointers to functions are way too slow, it's better to place a
    // bunch of if's.
    // Right now, it's actually sliightly faster than quadratic for 1e6 n.
    /* vector<pair<int,int>> lazyvec[N << 2]; */
    int mxelazy[N << 2];
    int mnelazy[N << 2];
    /* bool mxelastest[N << 2]; */
    // Z niewektorowym lazy jest już szybko, ale z ograniczoną funkcjonalnością.
    // ^^ mxe, mne modifies, sum queries implemented.
    /* function<void(void)> lazy[N << 2]; */
    /* bool haslazy[N << 2]; */
    /* function<void(void)> voidf = []{}; */
    void updatecr(int v){
        t[v] = t[v << 1] + t[v << 1 | 1];
        // O epsilon szybsze z ifami.
        if(mx[v << 1] > mx[v << 1 | 1]){
            mx[v] = mx[v << 1];
            mx2[v] = max(mx[v << 1 | 1] != mx[v] ? mx[v << 1 | 1] : mx2[v << 1 | 1], mx2[v << 1]);
            ilemx[v] = ilemx[v << 1] + (mx[v << 1 | 1] == mx[v] ? ilemx[v << 1 | 1] : 0);
        }
        else{
            mx[v] = mx[v << 1 | 1];
            mx2[v] = max(mx[v << 1] != mx[v] ? mx[v << 1] : mx2[v << 1], mx2[v << 1 | 1]);
            ilemx[v] = ilemx[v << 1 | 1] + (mx[v << 1] == mx[v] ? ilemx[v << 1] : 0);
        }
        if(mn[v << 1] < mn[v << 1 | 1]){
            mn[v] = mn[v << 1];
            mn2[v] = min(mn[v << 1 | 1] != mn[v] ? mn[v << 1 | 1] : mn2[v << 1 | 1], mn2[v << 1]);
            ilemn[v] = ilemn[v << 1] + (mn[v << 1 | 1] == mn[v] ? ilemn[v << 1 | 1] : 0);
        }
        else{
            mn[v] = mn[v << 1 | 1];
            mn2[v] = min(mn[v << 1] != mn[v] ? mn[v << 1] : mn2[v << 1], mn2[v << 1 | 1]);
            ilemn[v] = ilemn[v << 1 | 1] + (mn[v << 1] == mn[v] ? ilemn[v << 1] : 0);
        }
        /* mx[v] = max(mx[v << 1], mx[v << 1 | 1]); */
        /* mn[v] = min(mn[v << 1], mn[v << 1 | 1]); */
        /* ilemx[v] = (mx[v << 1] == mx[v] ? ilemx[v << 1] : 0) + (mx[v << 1 | 1] == mx[v] ? ilemx[v << 1 | 1] : 0); */
        /* ilemn[v] = (mn[v << 1] == mn[v] ? ilemn[v << 1] : 0) + (mn[v << 1 | 1] == mn[v] ? ilemn[v << 1 | 1] : 0); */
        /* mx2[v] = -INF; */
        /* // miny też w uwadze? */
        /* // Jeśli mx2 / mn2 mają już pod uwagą przeciwne miny / maxy, to tu nie muszę. */
        /* for(auto const &i: {mx[v << 1], mx[v << 1 | 1], mx2[v << 1], mx2[v << 1 | 1]}){ */
        /*     if(i != mx[v]){ */
        /*         mx2[v] = max(mx2[v], i); */
        /*     } */
        /* } */
        /* mn2[v] = INF; */
        /* for(auto const &i: {mn[v << 1], mn[v << 1 | 1], mn2[v << 1], mn2[v << 1 | 1]}){ */
        /*     if(i != mn[v]){ */
        /*         mn2[v] = min(mn2[v], i); */
        /*     } */
        /* } */
    }
    void build(int v, int tl, int tr, int a[]){
        if(tl == tr){
            t[v] = a[tl];
            mx[v] = mn[v] = a[tl];
            ilemx[v] = ilemn[v] = 1;
            mx2[v] = -INF;
            mn2[v] = INF;
            return;
        }
        int tm = (tl + tr) / 2;
        build(v << 1, tl, tm, a);
        build(v << 1 | 1, tm + 1, tr, a);
        updatecr(v);
        mxelazy[v] = -INF;
        mnelazy[v] = INF;
    }
    // vectors, pointers to functions could be stonks
    void push(int v, int tl, int tr){
        /* if(haslazy[v]){ */
        /*     haslazy[v] = 0; */
        /*     lazy[v](); */
        /*     assert(!haslazy[v]); */
        /*     /1* haslazy[v] = 0; *1/ */
        /* } */
        /* for_each(lazyvec[v].begin(), lazyvec[v].end(), [](auto const &i){i();}); */
        int tm = (tl + tr) / 2;
            /* push(v << 1, tl, tm); */
            /* push(v << 1 | 1, tm + 1, tr); */
        /* for(auto const &i: lazyvec[v]){ */
        /*     /1* whatis("lazy") *1/ */
        /*     /1* whatis(v) *1/ */
        /*     /1* i(); *1/ */
        /*     /1* i.e1(v<<1,tl,tm,i.e2); *1/ */
        /*     /1* i.e1(v<<1|1,tm+1,tr,i.e2); *1/ */
        /*     /1* (this->*(i.e1))(v<<1,tl,tm,i.e2); *1/ */
        /*     /1* (this->*(i.e1))(v<<1|1,tm+1,tr,i.e2); *1/ */
        /*     if(i.e1 == 2){ */
        /*         mnenodeupd(v<<1,tl,tm,i.e2); */
        /*         mnenodeupd(v<<1|1,tm+1,tr,i.e2); */
        /*     } */
        /*     else if(i.e1 == 3){ */
        /*         mxenodeupd(v<<1,tl,tm,i.e2); */
        /*         mxenodeupd(v<<1|1,tm+1,tr,i.e2); */
        /*     } */
        /* } */
        /* lazyvec[v].clear(); */
        if(mnelazy[v] != INF){
            mnenodeupd(v<<1,tl,tm,mnelazy[v]);
            mnenodeupd(v<<1|1,tm+1,tr,mnelazy[v]);
            mnelazy[v] = INF;
        }
        if(mxelazy[v] != -INF){
            mxenodeupd(v<<1,tl,tm,mxelazy[v]);
            mxenodeupd(v<<1|1,tm+1,tr,mxelazy[v]);
            mxelazy[v] = -INF;
        }
        /* if(!mxelastest[v]){ */
        /*     if(mnelazy[v] != INF){ */
        /*         mnenodeupd(v<<1,tl,tm,mnelazy[v]); */
        /*         mnenodeupd(v<<1|1,tm+1,tr,mnelazy[v]); */
        /*         mnelazy[v] = INF; */
        /*     } */
        /*     if(mxelazy[v] != -INF){ */
        /*         mxenodeupd(v<<1,tl,tm,mxelazy[v]); */
        /*         mxenodeupd(v<<1|1,tm+1,tr,mxelazy[v]); */
        /*         mxelazy[v] = -INF; */
        /*     } */
        /* } */
        /* else{ */
        /*     if(mxelazy[v] != -INF){ */
        /*         mxenodeupd(v<<1,tl,tm,mxelazy[v]); */
        /*         mxenodeupd(v<<1|1,tm+1,tr,mxelazy[v]); */
        /*         mxelazy[v] = -INF; */
        /*     } */
        /*     if(mnelazy[v] != INF){ */
        /*         mnenodeupd(v<<1,tl,tm,mnelazy[v]); */
        /*         mnenodeupd(v<<1|1,tm+1,tr,mnelazy[v]); */
        /*         mnelazy[v] = INF; */
        /*     } */
        /* } */
    }
    int query(int v, int tl, int tr, int l, int r){
        if(l > r)
            return 0;
        /* push(v, tl, tr); */
        if(l == tl && r == tr){
            return t[v];
        }
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        return query(v << 1, tl, tm, l, min(tm, r)) + query(v << 1 | 1, tm + 1, tr, max(l, tm + 1), r);
    }
    void mnenodeupd(int v, int tl, int tr, int val){
        if(mx[v] <= val || mx2[v] >= val)
            return;
        /* whatis("mnenodeupd") */
        /* whatis(v) */
        t[v] += ilemx[v] * (val - mx[v]);
        mx[v] = val;
        if(val < mn[v]){
            mn[v] = val;
            ilemn[v] = ilemx[v];
        }
        /* mn2[v] = min(mn2[v], val); */
        if(mn[v] != val)
            mn2[v] = min(mn2[v], val);
        if(tl != tr){
            int tm = (tl + tr) / 2;
            /* push(v << 1, tl, tm); */
            /* push(v << 1 | 1, tm + 1, tr); */
            /* mnenodeupd(v << 1, tl, tm, val); */
            /* mnenodeupd(v << 1 | 1, tm + 1, tr, val); */
            /* lazy[v << 1] = [=]{mnenodeupd(v << 1, tl, tm, val);}; */
            /* lazy[v << 1 | 1] = [=]{mnenodeupd(v << 1 | 1, tm + 1, tr, val);}; */
            /* haslazy[v << 1] = 1; */
            /* haslazy[v << 1 | 1] = 1; */
            // Z tym było źle, bo updatecr() wymaga aktualnego info dla synów?
            // Nie no, nie czaję wsm.
            // Actually, got it, miałem push wciąż przed aktualizacją warunku
            // na premature return.
            /* lazyvec[v << 1].push_back([=]{return mnenodeupd(v << 1, tl, tm, val);}); */
            /* lazyvec[v << 1 | 1].push_back([=]{return mnenodeupd(v << 1 | 1, tm + 1, tr, val);}); */
            /* lazyvec[v].push_back([=]{return mnenodeupd(v << 1, tl, tm, val);}); */
            /* lazyvec[v].push_back([=]{return mnenodeupd(v << 1 | 1, tm + 1, tr, val);}); */
            // Nvm, nie da się bez w < O(n) bez użycia bufora
            /* push(v, tl, tr); */
            /* lazy[v] = [=]{mnenodeupd(v << 1, tl, tm, val);mnenodeupd(v << 1 | 1, tm + 1, tr, val);}; */
            /* haslazy[v] = 1; */
            /* lazyvec[v].push_back([=]{mnenodeupd(v << 1, tl, tm, val);mnenodeupd(v << 1 | 1, tm + 1, tr, val);}); */
            /* lazyvec[v].push_back({mnenodeupd, val}); */
            /* lazyvec[v].push_back(mp(mnenodeupd, val)); */
            /* lazyvec[v].push_back({&Segtree::mnenodeupd, val}); */
            /* lazyvec[v].push_back({2, val}); */
            /* mxelazy[v] = val; */
            /* mxelazy[v] = min(mnelazy[v],max(mxelazy[v], val)); */

            /* mnelazy[v] = max(mxelazy[v],min(mnelazy[v], val)); */

            mnelazy[v] = min(mnelazy[v], val);
            // mne jest późniejszy od mxe
            if(mxelazy[v] > mnelazy[v]){
                mxelazy[v] = mnelazy[v];
            }
            // wsm, do I actually need that?
        }
    }
    void modifymne(int v, int tl, int tr, int l, int r, int val){
        if(l > r || mx[v] <= val)
            return;
        /* if(l > r) */
        /*     return; */
        /* push(v, tl, tr); */
        /* if(mx[v] <= val) */
        /*     return; */
        if(l == tl && r == tr && mx2[v] < val){
            mnenodeupd(v, tl, tr, val);
            return;
        }
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        modifymne(v << 1, tl, tm, l, min(tm, r), val);
        modifymne(v << 1 | 1, tm + 1, tr, max(l, tm + 1), r, val);
        updatecr(v);
    }
    void mxenodeupd(int v, int tl, int tr, int val){
        if(mn[v] >= val || mn2[v] <= val)
            return;
        /* whatis("mxenodeupd") */
        /* whatis(v) */
        t[v] += ilemn[v] * (val - mn[v]);
        mn[v] = val;
        if(val > mx[v]){
            mx[v] = val;
            ilemx[v] = ilemn[v];
        }
        /* mx2[v] = max(mx2[v], val); */
        if(mx[v] != val)
            mx2[v] = max(mx2[v], val);
        if(tl != tr){
            int tm = (tl + tr) / 2;
            /* push(v << 1, tl, tm); */
            /* push(v << 1 | 1, tm + 1, tr); */
            /* mxenodeupd(v << 1, tl, tm, val); */
            /* mxenodeupd(v << 1 | 1, tm + 1, tr, val); */
            /* lazy[v << 1] = [=]{mxenodeupd(v << 1, tl, tm, val);}; */
            /* lazy[v << 1 | 1] = [=]{mxenodeupd(v << 1 | 1, tm + 1, tr, val);}; */
            /* haslazy[v << 1] = 1; */
            /* haslazy[v << 1 | 1] = 1; */
            /* lazyvec[v << 1].push_back([=]{return mxenodeupd(v << 1, tl, tm, val);}); */
            /* lazyvec[v << 1 | 1].push_back([=]{return mxenodeupd(v << 1 | 1, tm + 1, tr, val);}); */
            /* lazyvec[v].push_back([=]{return mxenodeupd(v << 1, tl, tm, val);}); */
            /* lazyvec[v].push_back([=]{return mxenodeupd(v << 1 | 1, tm + 1, tr, val);}); */
            /* push(v, tl, tr); */
            /* lazy[v] = [=]{mxenodeupd(v << 1, tl, tm, val);mxenodeupd(v << 1 | 1, tm + 1, tr, val);}; */
            /* haslazy[v] = 1; */
            /* lazyvec[v].push_back([=]{mxenodeupd(v << 1, tl, tm, val);mxenodeupd(v << 1 | 1, tm + 1, tr, val);}); */
            /* lazyvec[v].push_back({&Segtree::mxenodeupd, val}); */
            /* lazyvec[v].push_back({3, val}); */
            /* mxelazy[v] = min(mnelazy[v],max(mxelazy[v], val)); */
            mxelazy[v] = max(mxelazy[v], val);

            if(mnelazy[v] < mxelazy[v])
                // hmmmmm
                /* mxelazy[v] = mxelazy[v]; */
                mnelazy[v] = mxelazy[v];
                // -> najss, działa mne + mxe
        }
    }
    void modifymxe(int v, int tl, int tr, int l, int r, int val){
        if(l > r || mn[v] >= val)
            return;
        /* if(l > r) */
        /*     return; */
        /* push(v, tl, tr); */
        /* if(mn[v] >= val) */
        /*     return; */
        if(l == tl && r == tr && mn2[v] > val){
            mxenodeupd(v, tl, tr, val);
            return;
        }
        push(v, tl, tr);
        // wait, jak tl == tr, to mn2[v] zawsze powinno być INF anyway, czyli
        // to powinno być redundant.
        /* if(tl == tr) */
        /*     return; */
        int tm = (tl + tr) / 2;
        modifymxe(v << 1, tl, tm, l, min(tm, r), val);
        modifymxe(v << 1 | 1, tm + 1, tr, max(l, tm + 1), r, val);
        updatecr(v);
    }
    /* void setnodeupd(int v, int tl, int tr, int val){ */
    /*     t[v] = (tr - tl + 1) * val; */
    /*     ilemx[v] = ilemn[v] = tr - tl + 1; */
    /*     mn[v] = mx[v] = val; */
    /*     mx2[v] = -INF; */
    /*     mn2[v] = INF; */
    /*     if(tl != tr){ */
    /*         int tm = (tl + tr) / 2; */
    /*         lazyvec[v].push_back([=]{return setnodeupd(v << 1, tl, tm, val);}); */
    /*         lazyvec[v].push_back([=]{return setnodeupd(v << 1 | 1, tm + 1, tr, val);}); */
    /*     } */
    /* } */
    /* void modifyset(int v, int tl, int tr, int l, int r, int val){ */
    /*     if(l > r) */
    /*         return; */
    /*     if(l == tl && r == tr){ */
    /*         setnodeupd(v, tl, tr, val); */
    /*         return; */
    /*     } */
    /*     push(v, tl, tr); */
    /*     int tm = (tl + tr) / 2; */
    /*     modifyset(v << 1, tl, tm, l, min(tm, r), val); */
    /*     modifyset(v << 1 | 1, tm + 1, tr, max(l, tm + 1), r, val); */
    /*     updatecr(v); */
    /* } */
    /* void addnodeupd(int v, int tl, int tr, int val){ */
    /*     t[v] += (tr - tl + 1) * val; */
    /*     mn[v] += val; */
    /*     mx[v] += val; */
    /*     if(mx2[v] != -INF) */
    /*         mx2[v] += val; */
    /*     if(mn2[v] != INF) */
    /*         mn2[v] += val; */
    /*     if(tl != tr){ */
    /*         int tm = (tl + tr) / 2; */
    /*         lazyvec[v].push_back([=]{return addnodeupd(v << 1, tl, tm, val);}); */
    /*         lazyvec[v].push_back([=]{return addnodeupd(v << 1 | 1, tm + 1, tr, val);}); */
    /*     } */
    /* } */
    /* void modifyadd(int v, int tl, int tr, int l, int r, int val){ */
    /*     if(l > r) */
    /*         return; */
    /*     if(l == tl && r == tr){ */
    /*         addnodeupd(v, tl, tr, val); */
    /*         return; */
    /*     } */
    /*     push(v, tl, tr); */
    /*     int tm = (tl + tr) / 2; */
    /*     modifyadd(v << 1, tl, tm, l, min(tm, r), val); */
    /*     modifyadd(v << 1 | 1, tm + 1, tr, max(l, tm + 1), r, val); */
    /*     updatecr(v); */
    /* } */
    /* void modnodeupd(int v, int tl, int tr, int val){ */
    /*     if(mx[v] < val || mx[v] != mn[v]) */
    /*         return; */
    /*     int wh = mx[v] % val; */
    /*     t[v] = (tr - tl + 1) * wh; */
    /*     ilemx[v] = ilemn[v] = tr - tl + 1; */
    /*     mn[v] = mx[v] = wh; */
    /*     mx2[v] = -INF; */
    /*     mn2[v] = INF; */
    /*     if(tl != tr){ */
    /*         int tm = (tl + tr) / 2; */
    /*         lazyvec[v].push_back([=]{return modnodeupd(v << 1, tl, tm, val);}); */
    /*         lazyvec[v].push_back([=]{return modnodeupd(v << 1 | 1, tm + 1, tr, val);}); */
    /*     } */
    /* } */
    /* void modifymod(int v, int tl, int tr, int l, int r, int val){ */
    /*     if(l > r || mx[v] < val) */
    /*         return; */
    /*     if(l == tl && r == tr && mn[v] == mx[v]){ */
    /*         modnodeupd(v, tl, tr, val); */
    /*         return; */
    /*     } */
    /*     push(v, tl, tr); */
    /*     int tm = (tl + tr) / 2; */
    /*     modifymod(v << 1, tl, tm, l, min(tm, r), val); */
    /*     modifymod(v << 1 | 1, tm + 1, tr, max(l, tm + 1), r, val); */
    /*     updatecr(v); */
    /* } */
};

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    /* int arr[] = {5,-1,32,-6,31,42,3,41,0,-4,44,8}; */
    /* int n = sizeof arr / sizeof *arr; */
    int n;
    sc(n);
    int arr[n];
    GET(arr);
    /* Segtree t; */
    static Segtree t;
    t.build(1,0,n-1,arr);
    int q,f,s,val,mode;
    sc(q);
    while(q--){
        sc(mode,f,s);
        if(mode == 1){ //query
            /* cout << t.query(1,0,n-1,f,s) << endl; */
            cout << t.query(1,0,n-1,f,s) << '\n';
        }
        /* else{ */
        /*     sc(val); */
        /*     t.modifymne(1,0,n-1,f,s,val); */
        /* } */
        else if(mode == 2){
            sc(val);
            t.modifymne(1,0,n-1,f,s,val);
        }
        else if(mode == 3){
            sc(val);
            t.modifymxe(1,0,n-1,f,s,val);
        }
        /* else if(mode == 4){ */
        /*     sc(val); */
        /*     t.modifyset(1,0,n-1,f,s,val); */
        /* } */
        /* else if(mode == 5){ */
        /*     sc(val); */
        /*     t.modifyadd(1,0,n-1,f,s,val); */
        /* } */
        /* else if(mode == 6){ */
        /*     sc(val); */
        /*     t.modifymod(1,0,n-1,f,s,val); */
        /* } */
    }
}

