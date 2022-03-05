#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,fma")
#include <bits/stdc++.h>
#include <x86intrin.h>
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

const int u = 48; // all block coordinates must be a multiple of lcm(6, 16) = 48

const int n = 20 * u; // = 1920 (also try 240, 480, 960)
alignas(64) float a[n * n], b[n * n], c[n * n];

const int B = 8;
typedef float vec __attribute__ (( vector_size(4 * B) ));

// "100x faster than for loops" (but compared against i,j,k order)
// https://gist.github.com/sslotin/fae39ea49a812732ae45db7b72f6a7ff
// 6x16 micro-kernel
void kernel(int x, int y, int l, int r) {
    vec t[6][2] = {0};

    for (int k = l; k < r; k++)
        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 2; j++)
                t[i][j] += (vec{} + a[x * n + i * n + k]) * ((vec*) b)[n / 8 * k + y / 8 + j];

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 2; j++)
            ((vec*) c)[x * n / 8 + i * n / 8 + y / 8 + j] += t[i][j];
}

void matmul() {
    const int s3 = 2 * u;
    const int s2 = 4 * u;
    const int s1 = 8 * u;
    
    for (int i3 = 0; i3 < n; i3 += s3)
        for (int i2 = 0; i2 < n; i2 += s2)
            for (int i1 = 0; i1 < n; i1 += s1)
                for (int x = i2; x < std::min(i2 + s2, n); x += 6)
                    for (int y = i3; y < std::min(i3 + s3, n); y += 16)
                        kernel(x, y, i1, std::min(i1 + s1, n));
}

constexpr ll m = 101;
ll mat[101][101];
ll jmat[101][101];
// mat equal to jmat at beginning (1st degree)

// Algorytm	ijk	    ikj	    bikj(16)	bikj(32)	DGEMM	ATLAS DGEMM
// Czas (s)	320.49	24.28	8.68    	30.45	    25.72	2.58
// Mflop/s	10.06	132.67	371.11  	105.79	    125.24	1248.53

void numertkimul(){
    ll nmat[101][101];
    memset(nmat,0,sizeof nmat);
    /* bikj(16) */
    for (int i = 0; i < m; i+=16)
        for (int k = 0; k < m; k+=16)
            for (int j = 0; j < m; j+=16)
                for (int ii = i; ii < i+15; ii++)
                    for (int kk = k; kk < k+15; kk++)
                        for (int jj = j; jj < j+15; jj++){
                            /* C[ii*N+jj] += A[ii*N+kk]*B[kk*N+jj]; */
                            nmat[ii][jj] += mat[ii][kk] * jmat[kk][jj];
                            nmat[i][j] %= N;
                        }
    memcpy(mat,nmat,sizeof mat);
}

void mul2(){
    ll nmat[101][101];
    memset(nmat,0,sizeof nmat);
    FOR(i,0,m){
        FOR(k,0,m){ // better cache optimization
            FOR(j,0,m){
                nmat[i][j] += mat[i][k] * mat[k][j];
                nmat[i][j] %= N;
            }
        }
    }
    memcpy(mat,nmat,sizeof mat);
}

void mul1(){
    ll nmat[101][101];
    // chg memset value if getting min
    // avoid any ifs cause that prevent vectorization
    memset(nmat,0,sizeof nmat);
    FOR(i,0,m){
        FOR(k,0,m){
            FOR(j,0,m){
                nmat[i][j] += mat[i][k] * jmat[k][j];
                nmat[i][j] %= N;
            }
        }
    }
    memcpy(mat,nmat,sizeof mat);
}


void poww(ll k){
    if(k <= 1) return;
    if(k&1){
        poww(k-1);
        mul1();
    }
    else{
        poww(k/2);
        mul2();
    }
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    mat[0][0] = 1;
    mat[1][1] = 10;
    mat[0][1] = 1;
    mat[1][2] = 1;
    mat[2][2] = 1;
    /* mat[0][1] = mat[1][0] = mat[1][1] = 1; */
    memcpy(jmat,mat,sizeof mat);
    poww(3);
    /* cout << mat[0][0] << '\n'; */
    cout << mat[0][1] << '\n';
    cout << mat[0][2] << '\n';
    /* cout << mat[1][1] << '\n'; */
}
