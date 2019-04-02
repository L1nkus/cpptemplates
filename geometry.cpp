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
//various geometric functions (2D)

typedef long long ftype;
//typ (int, ll, double)?

struct point{
    ftype x,y;
    point(): x(0), y(0){};
    point(ftype x, ftype y): x(x), y(y){};
    point& operator+=(const point &t){
        x += t.x;
        y += t.y;
        return *this;
    }
    point& operator-=(const point &t){
        x -= t.x;
        y -= t.y;
        return *this;
    }
    point& operator*=(ftype t){
        x *= t;
        y *= t;
        return *this;
    }
    point& operator/=(ftype t){
        x /= t;
        y /= t;
        return *this;
    }
    point operator+(const point &t) const {
        return point(*this) += t;
    }
    point operator-(const point &t) const {
        return point(*this) -= t;
    }
    point operator*(ftype t) const {
        return point(*this) *= t;
    }
    point operator/(ftype t) const {
        return point(*this) /= t;
    }
    bool operator==(point t) const {
        return x == t.x && y == t.y;
    }
};
point operator*(ftype a, point b) { return b*a; }
ostream& operator<<(ostream &os, point v) { os<<"[";os<<v.x<<' '<<v.y<<"]"; return os; }
istream& operator>>(istream &is, point v) { is >> v.x >> v.y; return is; }

//Czy sa w jednej fukcji liniowej, bez floatow, bez dzielenia, bez edge casow
bool isInLine(const point& p1, const point& p2, const point& p3) {
    ftype d1x = p2.x - p1.x;
    ftype d1y = p2.y - p1.y;
    ftype d2x = p3.x - p1.x;
    ftype d2y = p3.y - p1.y;
    return d1x * d2y == d1y * d2x;
}

double dist(point a, point b){
    double d1 = a.x-b.x, d2 = a.y-b.y;
    return sqrt(d1*d1+d2*d2);
}

ftype dot(point a, point b){ //vectory
    return a.x*b.x+a.y*b.y; //to samo co |A|*|B|*cos(kat a,b)
    //wiec cos(a,b) to jest
    //dotproduct(a,b)/(|A|*|B|)
    //z tego, (najkrotszy, czyli (0,180 [stopni]) kat miedzy vectorami to
    //acos(cos(a,b))
    //0 -> prostopadłe
    //>0 -> skierowane w tę samą stronę (<180 deg)
    //<0 -> skierowane w przeciwną stronę
}

ftype cross(point a, point b){ //vectory
    return a.x*b.y - a.y*b.x;
    //|A|*|B|*sin(a,b)
    //pole trójkąta ABC to crossproduct(AB,BC)/2.0
    //0 -> na tej samej prostej
    //>0 -> na lewo od a (najkrócej ofc)
    //<0 -> na prawo od b
}
ftype operator*(point a, point b) { return cross(a,b); }

double disttoline(point p, point a, point b){ //dystans punktu p do lini AB
    ftype crss = cross(b-a,p-a);
    return abs(crss/dist(a,b));
}

double disttosegment(point p, point a, point b){ //dystans punktu p do odcinka AB
    int dst = cross(b-a,a-p)/dist(a,b);
    int dot1 = dot(a-b,b-p);
    if(dot1 > 0) return dist(b,p);
    int dot2 = dot(b-a,a-p);
    if(dot2 > 0) return dist(a,p);
    return abs(dst);
}

double polygonarea(vector<point> &v){
    int n = v.size();
    double res = 0;
    for(int i = 0; i < n; ++i){
        /* res += cross(v[i]-v[0],v[i+1]-v[0]); */
        res += cross(v[i],v[(i+1)%n]); //works interestingly
    }
    return abs(res/2.0);
}

point intersect(point a1, point a2, point b1, point b2){ //intersection of 2 lines
    ftype c1 = cross(a2-a1,b2);
    ftype c2 = cross(b1,b2);
    if(!c2) return {-INF,INF}; //parallel
    return a1+c1/c2*b1;
}

bool cmp(const point &f, const point &s){
    return f.x<s.x || (f.x==s.x && f.y<s.y);
}

vector<point> convex_hull(vector<point> a){
    sort(all(a),cmp);
    a.erase(unique(all(a)),a.end());
    if(a.size() == 1) return a;
    vector<point> up,down;
    up = down = {a[0]};
    FORR(i,a){
        while(up.size() > 1 && (
    }
    return hull;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    int n;
    while(sc(n),n){
        vector<point> a(n);
        FOR(i,0,n){
            sc(a[i].x);
            sc(a[i].y);
        }
        a = convex_hull(a);
        cout << a.size() << '\n';
        FORR(i,a)
            cout << i.x << ' ' << i.y << '\n';
    }
}

