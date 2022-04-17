#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("inline-all-stringops,bmi,bmi2,popcnt,lzcnt")
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

// static inline?
// __restrict i jakaś tam pragma btw.
/* void buf_cpy(void * __restrict dest, const void * __restrict src, size_t sz) { */
void buf_cpy(void *dest, const void *src, size_t sz) {
    static char buf[1 << 20];
    memcpy(buf, src, sz);
    memcpy(dest, buf, sz);
}

template <class T>
int lifting_find_first_false_unrolled(int l, int r, T val, T *vec) { // [l;r)
    int p = 31 - __builtin_clz(r - l);
    int w = 1 << p;
    --l;
    if (l + w < r && vec[l + w] < val) l = r - w;
    switch (p) {
        case 31:
            if (vec[l + (1 << 30)] < val) l += 1 << 30;
        case 30:
            if (vec[l + (1 << 29)] < val) l += 1 << 29;
        case 29:
            if (vec[l + (1 << 28)] < val) l += 1 << 28;
        case 28:
            if (vec[l + (1 << 27)] < val) l += 1 << 27;
        case 27:
            if (vec[l + (1 << 26)] < val) l += 1 << 26;
        case 26:
            if (vec[l + (1 << 25)] < val) l += 1 << 25;
        case 25:
            if (vec[l + (1 << 24)] < val) l += 1 << 24;
        case 24:
            if (vec[l + (1 << 23)] < val) l += 1 << 23;
        case 23:
            if (vec[l + (1 << 22)] < val) l += 1 << 22;
        case 22:
            if (vec[l + (1 << 21)] < val) l += 1 << 21;
        case 21:
            if (vec[l + (1 << 20)] < val) l += 1 << 20;
        case 20:
            if (vec[l + (1 << 19)] < val) l += 1 << 19;
        case 19:
            if (vec[l + (1 << 18)] < val) l += 1 << 18;
        case 18:
            if (vec[l + (1 << 17)] < val) l += 1 << 17;
        case 17:
            if (vec[l + (1 << 16)] < val) l += 1 << 16;
        case 16:
            if (vec[l + (1 << 15)] < val) l += 1 << 15;
        case 15:
            if (vec[l + (1 << 14)] < val) l += 1 << 14;
        case 14:
            if (vec[l + (1 << 13)] < val) l += 1 << 13;
        case 13:
            if (vec[l + (1 << 12)] < val) l += 1 << 12;
        case 12:
            if (vec[l + (1 << 11)] < val) l += 1 << 11;
        case 11:
            if (vec[l + (1 << 10)] < val) l += 1 << 10;
        case 10:
            if (vec[l + (1 << 9)] < val) l += 1 << 9;
        case 9:
            if (vec[l + (1 << 8)] < val) l += 1 << 8;
        case 8:
            if (vec[l + (1 << 7)] < val) l += 1 << 7;
        case 7:
            if (vec[l + (1 << 6)] < val) l += 1 << 6;
        case 6:
            if (vec[l + (1 << 5)] < val) l += 1 << 5;
        case 5:
            if (vec[l + (1 << 4)] < val) l += 1 << 4;
        case 4:
            if (vec[l + (1 << 3)] < val) l += 1 << 3;
        case 3:
            if (vec[l + (1 << 2)] < val) l += 1 << 2;
        case 2:
            if (vec[l + (1 << 1)] < val) l += 1 << 1;
        case 1:
            if (vec[l + (1 << 0)] < val) l += 1 << 0;
        default:
            break;
    }
    return l + 1;
}

// Don't try this at your OI.
template<typename T>
class fastset {
public:
    T *begin() {
        return arr;
    }
    T *end() {
        return arr + sz;
    }
    T *lower_bound(const T &key) {
        /* return ::lower_bound(arr, arr + sz, key); */
        return arr + lifting_find_first_false_unrolled(0, sz, key, arr);
    }
    bool insert(const T &val) {
        T *it = lower_bound(val);
        if (it == arr + sz) {
            arr[sz++] = val;
            return 1;
        }
        else if (*it == val) {
            return 0;
        }
        else {
            buf_cpy(it + 1, it, ((arr + sz) - it) * sizeof(T));
            ++sz;
            *it = val;
            return 1;
        }
    }
    T pop_largest() {
        return arr[--sz];
    }
    bool erase(T *it) {
        buf_cpy(it, it + 1, ((arr + sz) - it - 1) * sizeof(T));
        --sz;
        return 1;
    }
    bool erase(const T &val) {
        T *it = lower_bound(val);
        if (it == arr + sz || *it != val) {
            return 0;
        }
        else {
            // might only need one memcpy here btw.
            buf_cpy(it, it + 1, ((arr + sz) - it - 1) * sizeof(T));
            --sz;
            return 1;
        }
    }
    ssize_t size() const {
        return sz;
    }
    bool empty() const {
        return !sz;
    }
    void clear() {
        sz = 0;
    }
    // should be const niby.
    T &operator [](size_t pos) {
        return arr[pos];
    }
private:
    static constexpr int cap = 1 << 20;
    T arr[cap];
    int sz = 0;
    /* array<T, cap> arr; */
};

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    /* set<int> st; */
    fastset<int> st;
    int a[N];
    iota(a,a+N,0);
    random_shuffle(a,a+N);
    FORR(i,a)
        st.insert(i);
    cout << *st.begin() << ' ' << st.size() << '\n';
}

