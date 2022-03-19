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

//fast fft

// Radewoosh ma ciekawe z jakimiś anti-precision error tricks:
// https://codeforces.com/contest/1548/submission/124596600
// ^^ więc no NTT needed even with modulos.

// new tnowak's.
using C = complex<double>;
void fft(vector<C>& a) {
    int n = a.size(), L = 31 - __builtin_clz(n);
    static vector<C> R(2, 1);
    static vector<C> rt(2, 1);  // (^ 10% faster if double)
    for (static int k = 2; k < n; k *= 2) {
        R.resize(n), rt.resize(n);
        auto x = polar(1.0, acos(-1.0) / k);
        FOR(i, k, 2 * k - 1) rt[i] = R[i] = i & 1 ? R[i >> 1] * x : R[i >> 1];
    } 
    vector<int> rev(n);
    FOR(i, 0, n) rev[i] = (rev[i >> 1] | (i & 1) << L) >> 1;
    FOR(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2) for (int i = 0; i < n; i += 2 * k) FOR(j, 0, k) {
        auto x = (double*)&rt[j + k], y = (double*)&a[i + j + k];
        C z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);
        a[i + j + k] = a[i + j] - z, a[i + j] += z;
    }
}
 
#define ssize(x) int(x.size())
vector<ll> conv(vector<ll> a, vector<ll> b) {
	if (a.empty() || b.empty()) return {};
	vector<ll> res(ssize(a) + ssize(b) - 1);
	int L = 32 - __builtin_clz(ssize(res)), n = (1 << L);
	vector<C> in(n), out(n);
	FOR(i, 0, ssize(a)) in[i].real(a[i]);
	// copy(a.begin(), a.end(), in.begin());
	FOR(i, 0, ssize(b)) in[i].imag(b[i]);
	fft(in);
	for (auto &x : in) x *= x;
	FOR(i, 0, n) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out);
	FOR(i, 0, ssize(res)) res[i] = imag(out[i]) / (4 * n) + 0.5;
	return res;
}

// Also, atcoder implementation seems cool (but has internal dependencies):
// https://github.com/atcoder/ac-library/blob/master/atcoder/convolution.hpp

typedef complex<double> cd;
// nie lepiej jakby constexpr było?
/* const double PI = 4*atan(1.); */
constexpr double PI = M_PI;
// TODO, jeśli WA, define double long double sprobuj
// e.g. 200000 x2 jest +1 przy +0.5 i doublach, inaczej gitr

void fft(vector<cd> &a, bool invert){
    int n = a.size();
	for (int i=1, j=0; i<n; ++i) {
		int bit = n >> 1;
		for (; j>=bit; bit>>=1)
			j -= bit;
		j += bit;
		if (i < j)
			swap (a[i], a[j]);
	}
    for(int len = 2; len <= n; len <<= 1){
		double ang = 2*PI/len * (invert ? -1 : 1);
        cd wn(cos(ang),sin(ang));
        for(int i = 0; i < n; i += len){
            cd w(1);
            for(int j = 0; j < len/2; ++j){
				cd u = a[i+j],  v = a[i+j+len/2] * w;
				a[i+j] = u + v;
				a[i+j+len/2] = u - v;
                w *= wn;
            }
        }
    }
    if(invert)
        FOR(i,0,n) a[i] /= n;
}

vector<int> multiply(const vector<int> a, const vector<int> b){
    vector<cd> fa(a.begin(),a.end()), fb(b.begin(),b.end());
    int k = 0;
    while((1 << k) < (int)(a.size()+b.size()-1)) ++k;
    int n = 1 << k;
    fa.resize(n,0), fb.resize(n,0);
    fft(fa,0);
    fft(fb,0);
    for(int i = 0; i < n; ++i){
        fa[i] *= fb[i];
    }
    fft(fa,1);
    vector<int> res(n);
    for(int i = 0; i < n; ++i){
        res[i] = int(fa[i].real()+0.5);
        // TODO, jeśli WA, zmień + 0.5 na mniejsze.
        // e.g. 200000 x2 jest +1 przy +0.5 i doublach
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    vector<int> a = {3,1,0};
    vector<int> b = {0,1,0,0};
    auto ret = multiply(a,b);
    FORR(i,ret) cout << i << ' ';
    cout << '\n';
}

