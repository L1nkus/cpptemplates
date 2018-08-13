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
//CHANGE TO LL ON MOST PROBLEMS

typedef complex<double> cd;
const double PI = 4*atan(1.);

const int N = 1000000; //max limit
int rev[N];
cd wlen_pw[N];

void fft (cd a[], int n, bool invert) {
	for (int i=0; i<n; ++i)
		if (i < rev[i])
			swap (a[i], a[rev[i]]);

	for (int len=2; len<=n; len<<=1) {
		double ang = 2*PI/len * (invert?-1:+1);
		int len2 = len>>1;

		cd wlen (cos(ang), sin(ang));
		wlen_pw[0] = cd (1, 0);
		for (int i=1; i<len2; ++i)
			wlen_pw[i] = wlen_pw[i-1] * wlen;

		for (int i=0; i<n; i+=len) {
			cd t,
				*pu = a+i,
				*pv = a+i+len2,
				*pu_end = a+i+len2,
				*pw = wlen_pw;
			for (; pu!=pu_end; ++pu, ++pv, ++pw) {
				t = *pv * *pw;
				*pv = *pu - t;
				*pu += t;
			}
		}
	}

	if (invert)
		for (int i=0; i<n; ++i)
			a[i] /= n;
}

void calc_rev (int n, int log_n) { //only needs to be cainted once for each same size usage of FFT
	for (int i=0; i<n; ++i) {
		rev[i] = 0;
		for (int j=0; j<log_n; ++j)
			if (i & (1<<j))
				rev[i] |= 1<<(log_n-1-j);
    }
}

    //once to get endsize and use init function for each size
    /* while((1 << k) < (int)(a.size()+b.size()-1)) ++k; */
    /* int nn = 1 << k; */
    /* calc_rev(nn,k); */
vector<int> multiply(vector<int> a, vector<int> b, int n){
    cd fa[n],fb[n];
    fill(copy(a.begin(),a.end(),fa),fa+n,0);
    fill(copy(b.begin(),b.end(),fb),fb+n,0);
    fft(fa,n,0);
    fft(fb,n,0);
    for(int i = 0; i < n; ++i){
        fa[i] *= fb[i];
    }
    fft(fa,n,1);
    vector<int> res(n);
    for(int i = 0; i < n; ++i){
        res[i] = int(fa[i].real()+0.5);
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    vector<int> a = {3,1,0};
    vector<int> b = {0,1,0,0};
    int k = 1;
    while((1 << k) < (int)(a.size()+b.size()-1)) ++k;
    int nn = 1 << k;
    calc_rev(nn,k);
    auto ret = multiply(a,b,nn);
    FORR(i,ret) cout << i << ' ';
    cout << '\n';
}

