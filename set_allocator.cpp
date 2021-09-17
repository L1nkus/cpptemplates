/* #pragma GCC optimize("O3") */
#include <random>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <array>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <stdlib.h>
#include <ctime>
#include <climits>
#include <cmath>
#include <complex>
#include <iostream>
#include <cctype>
#include <cstring>
#include <numeric>
#include <bitset>
#include <stack>
#include <functional>
#include <cassert>
#include <tuple>
#include <iomanip>
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
typedef std::pair<int,int> pi;
typedef std::vector<int> vi;
typedef std::vector<std::string> vs;
typedef int64_t ll;
typedef uint64_t ull;
#define umap unordered_map
#define uset unordered_set
using namespace std;

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
#define N 1000001

namespace btree {
    #include <x86intrin.h>
    typedef __m256i reg;

    const int n = (1<<20), B = 16;
    const int nblocks = (n + B - 1) / B;
    const int INF = numeric_limits<int>::max();

    alignas(64) int btree[nblocks][B];

    int go(int k, int i) { return k * (B + 1) + i + 1; }

    void build(int k = 0) {
        static int t = 0;
        if (k < nblocks) {
            for (int i = 0; i < B; i++) {
                build(go(k, i));
                btree[k][i] = (t < n ? a[t++] : INF);
            }
            build(go(k, B));
        }
    }

    // what of insert, erase?

    int cmp(reg x_vec, int* y_ptr) {
        reg y_vec = _mm256_load_si256((reg*) y_ptr);
        reg mask = _mm256_cmpgt_epi32(x_vec, y_vec);
        return _mm256_movemask_ps((__m256) mask);
    }

    int search(int x) {
        int k = 0, res = INF;
        reg x_vec = _mm256_set1_epi32(x);
        while (k < nblocks) {
            int mask = ~(
                cmp(x_vec, &btree[k][0]) +
                (cmp(x_vec, &btree[k][8]) << 8)
            );
            int i = __builtin_ffs(mask) - 1;
            if (i < B)
                res = btree[k][i];
            k = go(k, i);
        }
        return res;
    }
}

// static all try.
// inline btw?
// static with template -> different static address var for each other template.
/* char arr[(1 << 20) * 100]; */
/* int it; */
/* bool freed[(1 << 20) * 100]; */
/* char arr[(1 << 20)]; */
/* int it; */
// no dif static vs non-static.
/* bool freed[(1 << 20)]; */
char arr[(1 << 26)];
int it;
/* bool freed[(1 << 26)]; */
// guess globals work also.
template<typename T>
class cacheeff_alloc {
    /* static T arr[1 << 20]; */
    /* static int it; */
    /* T arr[1 << 20]; */
    /* T arr[4]; */
    // 1.4s not static, bcs every new set -> this much stack stuff i guess.
    /* char arr[1 << 26]; */
    /* bool freed[1 << 26]; */
    /* vector<char> arr = vector<char>(1 << 26); // -> basically the same speed as global bss one. */
    int it = 0;
    /* static char arr[1 << 20]; */
    /* static int it; */
public:
    /* cacheeff_alloc () = default; */
    /* template <class U> constexpr cacheeff_alloc (const cacheeff_alloc <U>&) noexcept {} */
    typedef T value_type;
    /* T *allocate(std::size_t n) { */
    // become WAY slowe with inline xd (0.25s -> 1.3s)
    // or nvm, just one unlucky one, still no speed improvement,
    /* static inline T *allocate(std::size_t n) { */
    T *allocate(std::size_t n) {
        /* return (T *) new char[n * sizeof(T)]; */
        /* return (T *) malloc(n * sizeof(T)); */
        // ^^ -> basically as fast as std::set in the 2nd case (malloc troche slower vs new).
        it += n * sizeof(T);
        return (T *)&arr[it - n * sizeof(T)];
    }
    static void deallocate(T *, std::size_t) noexcept {
    }
    /* void deallocate(T *p, std::size_t n) noexcept { */
    /*     /1* cout << "dealloc"; *1/ */
    /*     memset(freed + ((char *)p - arr), 1, n * sizeof(T)); */
    /*     while(it >= 0 && freed[it - 1]){ */
    /*         freed[--it] = 0; */
    /*     } */
    /* } */
    // -> 0.277, sometimes 0.35 with this dealloc.
    // ^^b4 fixing bug, after fixing bug, 0.26 consistently.
    // -> if have the mem, seems pretty worthwhile.
    // 0.266 with empty dealloc, but consistently without spikes.
};

#define blocksz 1 << 7
template<typename T>
class cacheeff_alloc_block {
    int it = blocksz;
    char *block;
public:
    typedef T value_type;
    cacheeff_alloc_block() {
        static_assert(sizeof(T) <= blocksz, "Too small blocksz.");
    }
    T *allocate(std::size_t n) {
        it += n * sizeof(T);
        if(it > blocksz){
            block = new char[blocksz];
            it = n * sizeof(T);
        }
        return (T *)&block[it - n * sizeof(T)];
    }
    static void deallocate(T *, std::size_t) noexcept {
    }
};

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    /* std::set<int, std::less<int>, cacheeff_alloc<int>> st1; */
    /* std::set<int, std::less<int>, Mallocator<int>> st1; */
    std::set<int> st2;
    int res = 0;
    // 100 -> 0.25s on both global and 1 << 20 non-global.
    // 0.36s on default allocator.
    /* FOR(x,0,100){ */
    /*     std::set<int, std::less<int>, cacheeff_alloc<int>> st1; */
    /*     /1* std::set<int> st1; *1/ */
    /*     FOR(i,0,10000){ */
    /*         st1.insert(i); */
    /*     } */
    /*     FOR(i,0,10000){ */
    /*         res += st1.count(i); */
    /*     } */
    /*     FOR(i,0,10000){ */
    /*         st1.erase(i); */
    /*     } */
    /* } */
    {
        /* std::set<int, std::less<int>, cacheeff_alloc<int>> st1; */
        // 0.17
        /* std::set<int> st1; */
        std::set<int, std::less<int>, cacheeff_alloc_block<int>> st1;
        /* std::set<int, std::less<int>, bestAlloc<int>> st1; // worse than mine o eps xd. */
        // 0.17 also, hmm.
        /* FOR(i,0,10000){ */
        /*     st1.insert(i); */
        /* } */
        /* FOR(x,0,100){ */
        /*     /1* std::set<int> st1; *1/ */
        /*     FOR(i,0,10000){ */
        /*         res += st1.count(i); */
        /*     } */
        /* } */
        // custom 1.6s
        // noncustom 1.1s XD?
        // how the heck.
        // hmm, na ideone somehow mine is just a bit faster.
        // on cf custom invocation 0.9s normal vs 1.3s mine though. on stack
        // not faster at all.
        FOR(i,0,1000000){
            st1.insert(i);
        }
        // insert time similar at 0.33s
        // but yeah, counts somehow worse than original, not what I expected xd.
        static int a[1000000];
        iota(a,a+1000000,0);
        std::random_device rd;
        std::mt19937 g(rd());
        shuffle(a,a+1000000,g);
        FOR(x,0,10){
            /* std::set<int> st1; */
            /* FOR(i,0,1000000){ */
            FORR(i,a){ // 7.5s cacheoff -O2 ; 4.4s normal -O2.
                // block 1024 6.247s. ; block 1 << 26 7.5s
                // 1 << 5 4.5s
                res += st1.count(i);
            }
        }
        cout << res << '\n';
        // exit here -> no deallocs -> 1.4s custom / 0.8s normal, damn.
        exit(0);
    }
    cout << res << '\n';
}

