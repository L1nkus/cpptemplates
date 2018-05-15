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
//various geometric functions

//Czy sa w jednej fukcji liniowej, bez floatow, bez dzielenia, bez edge casow!
bool isInLine(const std::pair<int, int>& p1, const std::pair<int, int>& p2, const std::pair<int, int>& p3) {
    int64_t d1x = p2.first - p1.first;
    int64_t d1y = p2.second - p1.second;
    int64_t d2x = p3.first - p1.first;
    int64_t d2y = p3.second - p1.second;
    return d1x * d2y == d1y * d2x;
}

double dist(pair<int,int> a, pair<int,int> b){
    int d1 = a.e1-b.e1, d2 = a.e2-b.e2;
    return sqrt(d1*d1+d2*d2);
}

pair<int,int> vec(pair<int,int> a, pair<int,int> b){
    return mp(a.e1-b.e1,a.e2-b.e2);
}

int dotproduct(pair<int,int> a, pair<int,int> b){ //vectory
    return a.e1*b.e1+a.e2*b.e2; //to samo co |A|*|B|*cos(kat a,b)
    //wiec cos(a,b) to jest
    //dotproduct(a,b)/(|A|*|B|)
    //z tego, (najkrotszy, czyli (0,180 [stopni]) kat miedzy vectorami to
    //acos(cos(a,b))
}

int crossproduct(pair<int,int> a, pair<int,int> b){ //vectory
    return a.e1*b.e2 - a.e2*b.e1;
    //|A|*|B|*sin(a,b)
    //pole trójkąta ABC to crossproduct(AB,BC)/2.0
}

double disttoline(pair<int,int> p, pair<int,int> a, pair<int,int> b){ //dystans punktu p do lini AB
    int cross = crossproduct(vec(a,b),vec(a,p));
    return abs(cross/dist(a,b));
}

double disttosegment(pair<int,int> p, pair<int,int> a, pair<int,int> b){ //dystans punktu p do odcinka AB
    int dst = crossproduct(vec(a,b),vec(p,a))/dist(a,b);
    int dot1 = dotproduct(vec(b,a),vec(p,b));
    whatis(dot1)
    if(dot1 > 0) return dist(b,p);
    int dot2 = dotproduct(vec(a,b),vec(p,a));
    whatis(dot2)
    if(dot2 > 0) return dist(a,p);
    return abs(dst);
}

double polygonarea(vector<pair<int,int>> &v){ //sum of areas of triangles from first vertex, with every 2 adjacent vertexes. Works for non and yes convex, because areas are signed.
    int n = v.size();
    double res = 0;
    for(int i = 1; i+1 < n; ++i){
        res += crossproduct(vec(v[0],v[i]),vec(v[0],v[i+1]));
    }
    return abs(res/2.0);
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    cout << disttosegment({3,8},{4,0},{8,0});
}

