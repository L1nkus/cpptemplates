#pragma GCC optimize("Ofast,unroll-loops")
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

template<const int md>
struct ntt{
	inline void add(int &a, int b) { a += b; if(a >= md) a -= md; }
	inline void sub(int &a, int b) { a -= b; if(a < 0) a += md; }
	inline int add2(int a, int b) { a += b; if(a >= md) a -= md; return a;}
	inline int sub2(int a, int b) { a -= b; if(a < 0) a += md; return a;}
	inline int mul(int a, int b) { return (int)((ll)a*b%md); }
	inline int power(int a, long long b) {
		int res = 1;
		while (b > 0) {
			if (b & 1) res = mul(res, a);
	    	a = mul(a, a);
			b >>= 1;
		}
		return res;
	}
	inline int inv(int a) {
		a %= md;
		if (a < 0) a += md;
		int b = md, u = 0, v = 1;
		while (a) {
			int t = b / a;
			b -= t * a; swap(a, b);
			u -= t * v; swap(u, v);
		}
		assert(b == 1);
		if (u < 0) u += md;
		return u;
	}

 	int max_base, root;
	vector<int> dw, idw;
	ntt() {
		int tmp = md - 1;
		max_base = 0;
		while (tmp % 2 == 0) {
			tmp /= 2;
			max_base++;
		}
		root = 2;
		while (power(root, (md-1)>>1) == 1) root++;
		dw.resize(max_base); idw.resize(max_base);
		FOR(i, 0, max_base){
			sub(dw[i], power(root, (md-1) >> (i+2)));
			idw[i] = inv(dw[i]);
		}
	}
	void fft(vector<int> &a, bool inv) {
		const int n = a.size();
		assert((n & (n - 1)) == 0);
		assert(__builtin_ctz(n) <= max_base);
		if(!inv){
			for(int m=n;m>>=1;){
				int w = 1;
				for(int s=0,k=0; s<n; s += 2*m){
					for(int i=s, j=s+m ; i < s+m; ++i, ++j) {
						int x = a[i], y = mul(a[j], w);
						a[j] = (x>=y?x-y:x+md-y);
						a[i] = (x+y>=md?x+y-md:x+y);
					}
					w = mul(w, dw[__builtin_ctz(++k)]);
				}
			}
		}
		else{
			for(int m=1;m<n;m*=2){
				int w = 1;
				for(int s=0,k=0; s<n; s += 2*m){
					for(int i=s, j=s+m ; i < s+m; ++i, ++j) {
						int x = a[i], y = a[j];
						a[j] = (x>=y?x-y:x+md-y);
						a[j] = mul(a[j], w);
						a[i] = (x+y>=md?x+y-md:x+y);
					}
					w = mul(w, idw[__builtin_ctz(++k)]);
				}
			}
		}
	}
    // XXX muszą być nieujemne elementy. i.e. do += mod %= mod. Had WA bcs of this.
	vector<int> multiply(vector<int> a, vector<int> b, int eq = 0) {
        for(auto &i: a)
            assert(i >= 0);
        for(auto &i: b)
            assert(i >= 0);
		int need = a.size() + b.size() - 1;
		int nbase = 0;
		while ((1 << nbase) < need) nbase++;
		int sz = 1 << nbase;
		a.resize(sz);
		b.resize(sz);
		fft(a, 0);
		if (eq) b = a; else fft(b, 0);
		int inv_sz = inv(sz);
		for (int i = 0; i < sz; i++) {
			a[i] = mul(mul(a[i], b[i]), inv_sz);
		}
		fft(a, 1);
		a.resize(need);
		return a;
	}
	vector<int> square(vector<int> a) {
		return multiply(a, a, 1);
	}
};
int n, k, aa;
ntt<998244353>nt;

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
}

