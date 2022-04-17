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
// 1 << 19 if segtree where merges matter.
#define N 1000001

// Tomasz Nowak
// lcp[i] to lcp suffixu sa[i - 1] i sa[i]
// Dla s = "aabaaab" sa = {7, 3, 4, 0, 5, 1, 6, 2}, lcp = {0, 0, 2, 3, 1, 2, 0, 1}
struct SuffixArray{
	vector<int> sa, lcp;
	SuffixArray(string& s, int lim = 256){ // >= 1 xd.
		int n = s.size() + 1, k = 0, a, b;
		vector<int> x(s.begin(), s.end() + 1);
		vector<int> y(n), ws(max(n, lim)), rank(n);
		sa = lcp = y;
		iota(sa.begin(), sa.end(), 0);
		for(int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j;
			iota(y.begin(), y.end(), n - j);
			FOR(i, 0, n)
                if(sa[i] >= j)
                    y[p++] = sa[i] - j;
			fill(ws.begin(), ws.end(), 0);
			FOR(i, 0, n) ws[x[i]]++;
			FOR(i, 1, lim) ws[i] += ws[i - 1];
			for(int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y);
			p = 1, x[sa[0]] = 0;
			FOR(i, 1, n) a = sa[i - 1], b = sa[i], x[b] =
				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
		}
		FOR(i, 1, n) rank[sa[i]] = i;
		for(int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
			for(k && k--, j = sa[rank[i]-1];
				s[i + k] == s[j + k]; k++);
        // RMQ na lcp[i+1..j], to lcp między sa[i] oraz sa[j]
        /* if(sa[i] == 0) */
        /*     lcp[i] = 0; */
        lcp[find(all(sa), 0) - sa.begin()] = 0; // untested.
	}
};

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    string s;
    cin >> s;
    for(auto &i: s)
        i -= 'a' - 1;
    auto xd = SuffixArray(s, 30);
    auto sa = xd.sa;
    auto lcp = xd.lcp;
    /* sa.erase(sa.begin()); */
    /* lcp.erase(lcp.begin()); */
    /* reverse(sa.begin(), sa.end()); */
    /* reverse(lcp.begin(), lcp.end()); */
    /* cout << lcp.size(); */
    int n = s.size();
    /* cout << sa.size() << ' ' << lcp.size() << endl; */
    /* FOR(i,0,n+1){ */
    /*     cout << sa[i] << ' '; */
    /* } */
    /* cout << '\n'; */
    /* FOR(i,0,n+1){ */
    /*     cout << lcp[i] << ' '; */
    /* } */
    /* cout << '\n'; */
    vector<array<int,3>> vec2; // {i, sa, lcp}
    FOR(i,1,n+1){
        if(sa[i] == 0)
            lcp[i] = 0;
        while(vec2.size() && vec2.back()[1] > sa[i]){
            lcp[i] = min(lcp[i], vec2.back()[2]);
            vec2.pop_back();
        }
        vec2.emplace_back(array<int,3>{i, sa[i], lcp[i]});
        /* if(vec2.back()[1] == 0) */
        /*     vec2.back()[2] = 0; */
    }
    vector<array<int,3>> vec;
    /* FOR(i,1,n+1){ */
    /*     /1* vec.emplace_back(sa[i], i == 1 ? 0 : lcp[i]); *1/ */
    /*     /1* vec.emplace_back(array<int,3>{(i == 1 ? 0 : lcp[i]) + sa[i], sa[i], i}); *1/ */
    /*     vec.emplace_back(array<int,3>{(sa[i] == 0 ? 0 : lcp[i]) + sa[i], sa[i], i}); */
    /*     /1* vec.emplace_back(array<int,3>{lcp[i] + sa[i], sa[i], i}); *1/ */
    /* } */
    for(auto &i: vec2){
        vec.emplace_back(array<int,3>{i[1] + i[2], i[1], i[0]});
    }
    sort(vec.begin(), vec.end());
    int it = 0;
    /* int sth = 0; */
    pair<int,int> sth = {-1,-1};
    FOR(i,0,n){
        /* while(it < vec.size() && vec[it].first + vec[it].second <= i) */
        while(it < vec.size() && vec[it][0] <= i){
            /* sth = max(sth, vec[it].second); */
            sth = max(sth, pair<int,int>{vec[it][2], vec[it][1]});
            ++it;
        }
        cout << sth.second + 1 << ' ' << i + 1 << '\n';
    }
}
