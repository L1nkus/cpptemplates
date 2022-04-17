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

struct MinCost {
	struct kra {
		int cel, *prze1, *prze2;
		ll koszt;
	};
	int n=0, zr, uj;
	const ll inf=1e9;
	vector<vector<kra>> graf;
	vector<int> bylo, aktu;
	vector<ll> odl, pamodl;
	void vert(int v) {
		if (v>n) {
			n=v;
			graf.resize(n);
			bylo.resize(n);
			aktu.resize(n);
			odl.resize(n);
			pamodl.resize(n);
		}
	}
	void add_edge(int v, int u, int prze, ll koszt) {
		vert(v+1); vert(u+1);
		kra ret1{u, new int(prze), new int(0), koszt};
		kra ret2{v, ret1.prze2, ret1.prze1, -koszt};
		graf[v].push_back(ret1);
		graf[u].push_back(ret2);
	}
	void spfa() {
		for (int i=0; i<n; i++) {
			aktu[i]=1;
			pamodl[i]=inf;
		}
		aktu[zr]=pamodl[zr]=0;
		queue<int> kol;
		kol.push(zr);
		while(!kol.empty()) {
			int v=kol.front();
			kol.pop();
			if (aktu[v])
				continue;
			aktu[v]=1;
			for (kra i : graf[v]) {
				if (*i.prze1 && pamodl[v]+i.koszt<pamodl[i.cel]) {
					pamodl[i.cel]=pamodl[v]+i.koszt;
					aktu[i.cel]=0;
					kol.push(i.cel);
				}
			}
		}
	}
	void dij() {
		for (int i=0; i<n; i++)
			odl[i]=inf;
		priority_queue < pair <ll,int> > dijks;
		dijks.push({0, zr});
		while(!dijks.empty()) {
			ll dis=-dijks.top().first;
			int v=dijks.top().second;
			dijks.pop();
			if (odl[v]!=inf)
				continue;
			odl[v]=pamodl[v]+dis;
			for (auto j : graf[v])
				if ((*j.prze1) && odl[j.cel]==inf)
					dijks.push({-(dis+pamodl[v]-pamodl[j.cel]+j.koszt), j.cel});
		}
	}
	int dfs(int v) {
		if (v==uj)
			return 1;
		bylo[v]=1;
		for (int i=0; i<(int)graf[v].size(); i++) {
			if (!bylo[graf[v][i].cel] && (*graf[v][i].prze1) &&
			odl[v]+graf[v][i].koszt==odl[graf[v][i].cel] && dfs(graf[v][i].cel)) {
				(*graf[v][i].prze1)--;
				(*graf[v][i].prze2)++;
				return 1;
			}
		}
		return 0;
	}
	pair<int,ll> flow(int zrzr, int ujuj) {
		zr=zrzr; uj=ujuj;
		vert(zr+1); vert(uj+1);
		spfa();
		pair<int,ll> ret{0, 0};
		while(1) {
			dij();
			for (int i=0; i<n; i++)
				bylo[i]=0;
			if (!dfs(zr))
				break;
			ret.first++;
			ret.second+=odl[uj];
		}
		return ret;
	}
};

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
}

