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

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    srand(time(0));
    int ch = 0;
    vs ts; //edge cases to always check for at start
    FORR(i,ts){
        ofstream f("in.in");
        f << i << '\n';
        f.close();
        system("./1130A.o < in.in > o1");
        system("./1130Ahack.o < in.in > o2");
        system("diff -w o1 o2 > df");
        ifstream of("df");
        string ss;
        if(of >> ss){
            cout << "DIFF!\n";
            cout << ch << '\n';
            exit(0);
        }
    }
    for(;;){
        ++ch;
        if(ch%10 == 0) whatis(ch)
        /* ll a,b,k; */
        /* a = rand()%1000+1; */
        /* b = rand()%1000+1; */
        /* k = rand()%1000+1; */
        /* int n,m; */
        /* /1* n = rand()%8+1; *1/ */
        /* /1* n = rand()%300+1; *1/ */
        /* n = rand()%5+1; */
        /* /1* m = rand()%10+1; *1/ */
        /* m = rand()%100+1; */
        /* /1* m = rand()%3+1; *1/ */
        /* ofstream f("in.in"); */
        /* f << n << ' ' << m <<  '\n'; */
        /* FOR(i,0,n){ */
        /*     f << (rand()%2 ? rand()%4 : 65535-rand()%4)  << ' '; */
        /* } */
        /* f << '\n'; */
        /* FOR(i,0,m){ */
        /*     int t = rand()%2; */
        /*     int l,r; */
        /*     if(t){ */
        /*         f << "1 "; */
        /*         l = rand()%n; */
        /*         r = rand()%(n-l)+l; */
        /*         f << l+1 << ' ' << r+1 << '\n'; */
        /*     } */
        /*     else{ */
        /*         f << "2 "; */
        /*         int len = rand()%n+1; */
        /*         l = rand()%(n-len+1); */
        /*         r = rand()%(n-len+1); */
        /*         f << l+1 << ' ' << r+1 << ' ' << len << '\n'; */
        /*     } */
        /* } */
        /* f.close(); */
        system("./test.o > in.in");
        system("./chinese_segtree_test.o < in.in > ou1");
        system("./chinese_segment_tree_beats.o < in.in > ou2");
        /* system("python tmpp.py < in.in > o2"); */
        /* system("head -n 1 o1 > o11"); */
        /* system("head -n 1 o2 > o22"); */
        /* system("diff -w o11 o22 > df"); */
        /* system("diff -w o1 o2 > df"); */
        system("diff -w ou1 ou2 > df");
        ifstream of("df");
        string ss;
        if(of >> ss){
            cout << "DIFF!\n";
            cout << ch << '\n';
            exit(0);
        }
    }
}

