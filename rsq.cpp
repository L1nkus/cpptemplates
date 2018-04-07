#include <bits/stdc++.h> //Stack size ~2'000'000(x4)
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
template<typename T> inline bool sc(T &num){ bool neg=0; int c; num=0; while(c=getchar_unlocked(),c<33){if(c == EOF) return false;} if(c=='-'){ neg=1; c=getchar_unlocked(); } for(;c>47;c=getchar_unlocked()) num=num*10+c-48; if(neg) num*=-1; return true;}template<typename T, typename ...Args> inline void sc(T &num, Args &...args){ bool neg=0; int c; num=0; while(c=getchar_unlocked(),c<33){;} if(c=='-'){ neg=1; c=getchar_unlocked(); } for(;c>47;c=getchar_unlocked()) num=num*10+c-48; if(neg) num*=-1; sc(args...); }

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    int arr[] = {1, 1, 2, 1, 3, 4, 5, 2, 8};
    const int N = sizeof arr >> 2;
        //MO's Algorithm
    struct qu{
        int l;
        int r;
        int n;
    };
    /* pi querys[] = {{0,4},{1,3},{2,4}}; */
    qu querys[] = {{0,4,0},{1,3,1},{2,4,2}};
    /* const int block = sqrt(N); */
    const int block = sqrt(N) - (sqrt(N) == (int)sqrt(N));
    /* sort(all(querys), [&](auto &f, auto &s){if(f.e1/block == s.e1/block) return f.e2 < s.e2; return f.e1/block < s.e1/block;}); */
    sort(all(querys), [&](auto &f, auto &s){if(f.l/block == s.l/block) return f.r < s.r; return f.l/block < s.l/block;});
    int answer[3];

    /* FORR(i,querys) */
    /*     cout << i << ' '; */
    int lastl = 0, lastr = 0;
    int cur = 0;
    FORR(i,querys){
        int curl = i.l , curr = i.r + 1;
        int tmp = lastl;
        while(lastl < curl){
            if(lastl == lastr)
                break;
            cur -= arr[lastl];
            ++lastl;
        }
        lastl = tmp;
        tmp = lastr;
        --lastr;
        while(lastr >= curr){
            cur -= arr[lastr];
            if(lastr == lastl)
                break;
            --lastr;
        }
        lastr = tmp;
        tmp = curl;
        while(curl < lastl){
            if(curl == curr)
                break;
            cur += arr[curl];
            ++curl;
        }
        curl = tmp;
        tmp = curr;
        --curr;
        while(curr >= lastr){
            cur += arr[curr];
            if(curr == curl)
                break;
            --curr;
        }
        curr = tmp;
        answer[i.n] = cur;
        lastl = i.l;
        lastr = i.r+1;
        /* cout << cur << endl; */
    }
    FORR(i,answer)
        cout << i << '\n';































        //Segment Tree
    /* int t[N << 1]; */
    /* FOR(i,0,N) */
    /*     t[i+N] = arr[i]; */
    /* for(int i = N-1; i > 0; --i){ */
    /*     t[i] = t[i << 1] + t[i << 1 | 1]; */
    /* } */
    /* int n = 3; */
    /* int l,r; */
    /* while(n--){ */
    /*     sc(l,r); */
    /*     ++r; */
    /*     int sum = 0; */
    /*     l += N, r += N; */
    /*     while(l < r){ */
    /*         if(l&1){ */
    /*             sum += t[l++]; */
    /*         } */
    /*         if(r&1){ */
    /*             sum += t[--r]; */
    /*         } */
    /*         l >>= 1; r >>= 1; */
    /*     } */
    /*     cout << sum << '\n'; */
    /* } */
        //Simple RSQ
    /* int ans[sizeof arr >> 2]; */
    /* ans[0] = 1; */
    /* FOR(i,1,sizeof arr >> 2){ */
    /*     ans[i] = ans[i-1] + arr[i]; */
    /* } */
    /* int n = 3; */
    /* int l,r; */
    /* while(n--){ */
    /*     sc(l,r); */
    /*     if(!l) */
    /*         cout << ans[r]; */
    /*     else */
    /*         cout << ans[r] - ans[l-1]; */
    /*     cout << '\n'; */
    /* } */
}

