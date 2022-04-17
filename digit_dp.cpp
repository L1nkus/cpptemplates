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
template<class T> ostream& operator<<(ostream &os, vector<T> V) { os<<"[";for(auto const &vv:V)os<<vv<<","; os<<"]"; return os; }
template<class L, class R> ostream& operator<<(ostream &os, pair<L, R> P) { os<<"("<<P.first<<","<<P.second<<")"; return os; }
inline int fstoi(const string &str){auto it=str.begin();bool neg=0;int num=0;if(*it=='-')neg=1;else num=*it-'0';++it;while(it<str.end()) num=num*10+(*it++-'0');if(neg)num*=-1;return num;}
inline void getch(char &x){while(x = getchar_unlocked(), x < 33){;}}
inline void getstr(string &str){str.clear(); char cur;while(cur=getchar_unlocked(),cur<33){;}while(cur>32){str+=cur;cur=getchar_unlocked();}}
template<typename T> inline bool sc(T &num){ bool neg=0; int c; num=0; while(c=getchar_unlocked(),c<33){if(c == EOF) return false;} if(c=='-'){ neg=1; c=getchar_unlocked(); } for(;c>47;c=getchar_unlocked()) num=num*10+c-48; if(neg) num*=-1; return true;}template<typename T, typename ...Args> inline void sc(T &num, Args &...args){ bool neg=0; int c; num=0; while(c=getchar_unlocked(),c<33){;} if(c=='-'){ neg=1; c=getchar_unlocked(); } for(;c>47;c=getchar_unlocked()) num=num*10+c-48; if(neg) num*=-1; sc(args...); }
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; //s.find_by_order(), s.order_of_key() <- works like lower_bound
template<typename T> using ordered_map = tree<T, int, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// Suma cyfr liczb od 0 do n
ll dp[20][155][2]; //{index, suma, czy bez limitu} -> ilosc spelniajacych warunki state-a

ll qu(string n){
    for(auto &i: n){
        i -= '0';
    }
    memset(dp,0,sizeof dp);
    dp[0][0][0] = 1;
    int len = n.size();
    // Gdyz tutaj liczby o mniejszej ilosci cyfr tak naprawde skladaja sie z
    // leading zeros przed nimi, jesli one wplywaja na statey, trzeba dolozyc
    // dodatkowy case - czy byla juz jakas zaczeta liczba, oraz dodatkowo
    // rozwazyc '0'
    for(int i = 0; i < len; ++i){
        for(int t = 0; t < 2; ++t){ //t == 1 -> brak limitu
            for(int s = 0; s < 155; ++s){
                // if(!dp[i][s][t]) continue might speed it up a lot
                for(int d = 0; d < 10; ++d){
                    if(!t && n[i] < d) break;
                    int nt = (t | (d < n[i]));
                    /* int nz = (z | (d != 0)); */
                    dp[i+1][s+d][nt] += dp[i][s][t];
                }
            }
        }
    }
    ll ans = 0;
    FOR(i,0,155){
        ans += dp[len][i][1]*i;
        ans += dp[len][i][0]*i;
    }
    return ans;
}

ll dppre[21][155];

// constexpr można ez
void pre(){
    // Traktując pos == 0 jako końcowy state -> jaki ma wkład w odpowiedź
    // Jeśli tylko 1 dobry state, to tylko jedno = 1 na początku
    FOR(i,0,155){
        dppre[0][i] = i;
    }
    for(int i = 1; i <= 20; ++i){
        for(int s = 0; s < 155; ++s){
            for(int d = 0; d < 10; ++d){
                // next state wyliczany dokładnie tak samo jak normalnie,
                // ale aplikowany do poprzednika
                dppre[i][s] += dppre[i-1][s + d];
            }
        }
    }
}

// Liniowe od długości liczby, bo zawsze jest tylko n statów z t == 0 (limitem)
ll qupostpre(string n){
    ll res = 0;
    for(auto &i: n){
        i -= '0';
    }
    int len = n.size();
    int suma = 0;
    for(int i = 0; i < len; ++i){
        for(int d = 0; d < n[i]; ++d){
            int nsuma = suma + d;
            res += dppre[len - i - 1][nsuma];
        }
        // Next state dla d == n[i], czyli jedynego dalszego z t == 0
        suma = suma + n[i];
    }
    // W pętli wyliczane jest exclusive samo n, więc na końcu trzeba dodać
    // wynik dla całej liczby, a mamy zapisany state końcowy w zmiennych
    res += suma;
    return res;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    int t;
    cin >> t;
    string a,b;
    pre();
    while(t--){
        cin >> a >> b;
        ll res = qu(b);
        if(a.size() > 1 || a[0] != '0'){
            if(a == "1"){
                a = "0";
            }
            else{
                auto it = --a.end();
                while(it != a.begin() && *it == '0'){
                    *it = '9';
                    --it;
                }
                if(it == a.begin() && *it == '1')
                    a.erase(a.begin());
                else
                    --*it;
            }
            res -= qu(a); // IF MODUOLING, DON'T FORGET TO CORRECT IN CASE RES GOES NEGATIVE
        }
        cout << res << '\n';
        ll res2 = qupostpre(b) - qupostpre(a);
        cout << res2 << '\n';
    }
}
