#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define all(a) begin(a),end(a)
#define FOR(x,val,to) for(int x=(val);x<int((to));++x)
#define FORE(x,val,to) for(auto x=(val);x<=(to);++x)
#define FORR(x,arr) for(auto &x: arr)
#define FORS(x,plus,arr) for(auto x = begin(arr)+(plus); x != end(arr); ++x)
#define FORREV(x,plus,arr) for(auto x = (arr).rbegin()+(plus); x !=(arr).rend(); ++x)
#define REE(s_) {cout<<s_<<'\n';exit(0);}
#define GETCIN(arr) for(auto &i: (arr)) cin>>i
#define GET(arr) for(auto &i: (arr)) sc(i)
#define GETSTR(arr) for(auto &i: (arr)) getstr(i)
#define INF 0x7F7F7F7F //2139062143 | 127 in memset -> memset(arr,127,size)
#define SINF 1061109567 //Safe INF, for graphs or 2d arrays 63 in memset(arr,63,size)
#define LL_INF 7234017283807667300 //100 in memset(arr,100,size) !!!must be LL
#define whatis(x) cerr << #x << " is " << x << endl;
#define e1 first
#define e2 second
typedef std::pair<int,int> pi;
typedef std::vector<int> vi;
typedef std::vector<std::string> vs;
typedef int64_t ll;
#define umap unordered_map
#define uset unordered_set
using namespace std;

#ifdef _WIN32
#define getchar_unlocked() _getchar_nolock()
#define _CRT_DISABLE_PERFCRIT_LOCKS
#endif
template<class T> ostream& operator<<(ostream &os, vector<T> V) { os<<"[";for(auto const &vv:V)os<<vv<<","; os<<"]"; return os; }
template<class L, class R> ostream& operator<<(ostream &os, pair<L, R> P) { os<<"("<<P.first<<","<<P.second<<")"; return os; }
template<typename T> inline void print_128(T num){ if(!num) return; print_128(num / 10); cout.put((num % 10) + '0'); }
inline int fstoi(const string &str){auto it=str.begin();bool neg=0;int num=0;if(*it=='-')neg=1;else num=*it-'0';++it;while(it<str.end()) num=num*10+(*it++-'0');if(neg)num*=-1;return num;}
inline void getch(char &x){while(x = getchar_unlocked(), x < 33){;}}
inline void getstr(string &str){str.clear(); char cur;while(cur=getchar_unlocked(),cur<33){;}while(cur>32){str+=cur;cur=getchar_unlocked();}}
template<typename T> inline bool sc(T &num){ bool neg=0; int c; num=0; while(c=getchar_unlocked(),c<33){if(c == EOF) return false;} if(c=='-'){ neg=1; c=getchar_unlocked(); } for(;c>47;c=getchar_unlocked()) num=num*10+c-48; if(neg) num*=-1; return true;}template<typename T, typename ...Args> inline void sc(T &num, Args &...args){ bool neg=0; int c; num=0; while(c=getchar_unlocked(),c<33){;} if(c=='-'){ neg=1; c=getchar_unlocked(); } for(;c>47;c=getchar_unlocked()) num=num*10+c-48; if(neg) num*=-1; sc(args...); }

ll ans;
ll in[200000];
ll cnt[1000001];

inline void dec(int num){
    ans -= num * (cnt[num]*2-1);
    --cnt[num];
}

inline void inc(int num){
    ans += num * (++cnt[num]*2-1);
}

/* inline int64_t hilbertOrder(int x, int y, int pow, int rotate = 0){ */
/* 	if (pow == 0){ */
/* 		return 0; */
/* 	} */
/* 	int hpow = 1 << (pow-1); */
/* 	int seg = (x < hpow) ? ( */
/* 		(y < hpow) ? 0 : 3 */
/* 	) : ( */
/* 		(y < hpow) ? 1 : 2 */
/* 	); */
/* 	seg = (seg + rotate) & 3; */
/* 	const int rotateDelta[4] = {3, 0, 0, 1}; */
/* 	int nx = x & (x ^ hpow), ny = y & (y ^ hpow); */
/* 	int nrot = (rotate + rotateDelta[seg]) & 3; */
/* 	int64_t subSquareSize = int64_t(1) << (2*pow - 2); */
/* 	int64_t ans = seg * subSquareSize; */
/* 	int64_t add = hilbertOrder(nx, ny, pow-1, nrot); */
/* 	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1); */
/* 	return ans; */
/* } */

// supposively simpler and slightly faster
// pls do not change logn... (got penalty bcs of that)
constexpr int logn = 20;
constexpr int maxn = 1 << logn;

long long hilbertorder(int x, int y)
{
	long long d = 0;
	for (int s = 1 << (logn - 1); s; s >>= 1)
	{
		bool rx = x & s, ry = y & s;
		d = d << 2 | (rx * 3 ^ static_cast<int>(ry));
		if (!ry)
		{
			if (rx)
			{
				x = maxn - x;
				y = maxn - y;
			}
			swap(x, y);
		}
	}
	return d;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    int n,t;
    sc(n,t);
    FOR(i,0,n)
        sc(in[i]);
    struct query{
        int L,R,id,ord;
    };
    query qu[t];
    int k = 1;
    while(1 << k < n) ++k;
    FOR(i,0,t){
        sc(qu[i].L,qu[i].R);
        --qu[i].L, --qu[i].R;
        qu[i].id = i;
        /* qu[i].ord = hilbertOrder(qu[i].L,qu[i].R,k); */
        qu[i].ord = hilbertorder(qu[i].L,qu[i].R);
    }
    /* const int S = sqrt(n)+1; //THAT'S SLOWER */
    const int S = n/sqrt(t)+1; //THAT'S MUCH BETTER
    /* sort(qu,qu+t,[&](const query &f, const query &s){return f.L/S != s.L/S ? f.L/S<s.L/S : (f.R>s.R)^(f.L/S%2);}); */ // can rte cause not strictly ordered
    /* sort(qu,qu+t,[&](const query &f, const query &s){return f.L/S != s.L/S ? f.L/S<s.L/S : (f.R==s.R ? 0 : (f.R>s.R)^(f.L/S%2));}); */
    sort(qu,qu+t,[](const query &f, const query &s){return f.ord<s.ord;}); //A bit faster
    int curl = 0, curr = 0;
    cnt[in[0]] = 1;
    ans = in[0];
    ll answer[t];
    FORR(i,qu){
        while(curl < i.L){
            dec(in[curl++]);
        }
        while(i.L < curl){
            inc(in[--curl]);
        }
        while(curr > i.R){
            dec(in[curr--]);
        }
        while(i.R > curr){
            inc(in[++curr]);
        }
        answer[i.id] = ans;
    }
    FORR(i,answer)
        cout << i << '\n';
}
