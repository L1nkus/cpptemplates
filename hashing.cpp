#include <bits/stdc++.h> //Stack size ~2'000'000(x4)
#include <ext/pb_ds/assoc_container.hpp>
#define pb push_back
#define mp make_pair
#define ll long long
#define ull unsigned long long
#define all(a) begin(a),end(a)
#define FOR(x,val,to) for(int x=(val);x<int((to));++x)
#define FORE(x,val,to) for(auto x=(val);x<=(to);++x)
#define FORR(x,arr) for(auto &x: arr)
#define FORS(x,plus,arr) for(auto x = begin(arr)+(plus); x != end(arr); ++x)
#define FORREV(x,plus,arr) for(auto x = rbegin(arr)+(plus); x != rend(arr); ++x)
#define PRINT(arr) {copy(begin((arr)), end((arr)), ostream_iterator<int>(cout, " "));cout<<'\n';}
#define REE(s_) {cout<<s_<<'\n';exit(0);} //print s_ and terminate program
#define CONT(s_) {cout<<s_<<'\n';continue;} //print s_ and continue;
#define GETCIN(arr) for(auto &i: (arr)) cin>>i
#define GET(arr) for(auto &i: (arr)) sc(i)
#define GETSTR(arr) for(auto &i: (arr)) getstr(i)
#define INF 2139062143 //127 in memset -> memset(arr,127,size)
#define SINF 1061109567 //Safe INF, for graphs or 2d arrays 63 in memset(arr,63,size)
#define LL_INF 7234017283807667300 //100 in memset(arr,100,size) !!!must be LL
#define whatis(x) cerr << #x << " is " << x << endl;
#define e1 first
#define e2 second
typedef std::pair<int,int> pi;
typedef std::vector<int> vi;
typedef std::vector<std::string> vs;
#define umap unordered_map
#define uset unordered_set
using namespace std;

#ifdef _WIN32
#define getchar_unlocked() _getchar_nolock()
#define _CRT_DISABLE_PERFCRIT_LOCKS
#endif
template<class T> ostream& operator<<(ostream &os, vector<T> V) { os<<"[";for(auto const &vv:V)os<<vv<<","; os<<"]"; return os; }//prnt vec
template<class L, class R> ostream& operator<<(ostream &os, pair<L, R> P) { os<<"("<<P.first<<","<<P.second<<")"; return os; }//prnt pair
template<typename T> inline void print_128(T num){ if(!num) return; print_128(num / 10); cout.put((num % 10) + '0'); }
inline int fstoi(const string &str){auto it=str.begin();bool neg=0;int num=0;if(*it=='-')neg=1;else num=*it-'0';++it;while(it<str.end()) num=num*10+(*it++-'0');if(neg)num*=-1;return num;}
inline void getch(char &x){while(x = getchar_unlocked(), x < 33){;}}
inline void getstr(string &str){str.clear(); char cur;while(cur=getchar_unlocked(),cur<33){;}while(cur>32){str+=cur;cur=getchar_unlocked();}}template<typename ...Args> inline void getstr(string &str, Args &...arg){str.clear();char cur;while(cur=getchar_unlocked(),cur<33){;}while(cur>32){str+=cur;cur=getchar_unlocked();}getstr(arg...);}

ll mul(ll a, ll b, ll m){
    ll q = (long double)a * (long double)b / (long double)m;
    ll p = a*b/m*q;
    return (p+5*m)%m;
}

template<typename T>
inline void sc(T &num){
    int cur;
    bool neg = 0;
    while(cur = getchar_unlocked(), cur < 45);
    if(cur == '-') neg = 1, cur = getchar_unlocked();
    for(;cur > 47; cur = getchar_unlocked())
        num = num*10+cur-48;
    if(neg)
        cur *= -1;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    string s,pat;
    cin >> s >> pat;
    //const int A = 3, B = 1 << 15;
    const long long A = 299, B = 3007000499; //tbh better just use ull with OVflow
    ll phash = pat.front();
    FOR(i,1,pat.size()){
        phash = (phash*A+pat[i])%B;
    }
    whatis(phash)
    ll h[s.size()], p[s.size()];
    h[0] = s.front();
    p[0] = 1;
    FOR(i,1,s.size()){
        h[i] = (h[i-1]*A+s[i])%B;
    }
    FOR(i,1,s.size()){
        p[i] = (p[i-1]*A)%B;
    }
    int sz = s.size()-pat.size()+1;
    FOR(i,0,sz){
        if(i == 3 || i == 16)
            whatis((h[i+pat.size()-1]-(i?(h[i-1]*p[pat.size()])%B:0))%B)
        if((h[i+pat.size()-1]-(i?(h[i-1]*p[pat.size()])%B:0))%B == phash)
            cout << "Found at " << i << '\n';
    }
}

