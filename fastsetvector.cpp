#include <algorithm>
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
/* #define N 10001 */
/* #define N 100001 */
#define N 1000001

// def todo własny lower_bound obv xd.
// potrzebuję własny iterator also pod ++, --.
template<typename T>
class fastset {
public:
    T lower_bound(const T &key) {
        auto it1 = ::lower_bound(large.begin(), lrgbnd, key);
        /* auto it2 = small.lower_bound(key); */
        auto it2 = ::lower_bound(lrgbnd, large.end(), key);
        return it1 != large.end() && (it2 == large.end() || *it1 <= *it2) ? *it1 : it2 == large.end() ? INF : *it2;
    }
    bool insert(const T &val){
        auto it = ::lower_bound(large.begin(), lrgbnd, val);
        if (it != lrgbnd && *it == val)
            return 0;
        /* bool inserted = small.insert(val).second; */
        /* if (!inserted) */
        /*     return 0; */
        auto it2 = ::lower_bound(lrgbnd, large.end(), val);
        if (it2 != large.end() && *it2 == val)
            return 0;
        int cr_off = lrgbnd - large.begin();
        large.insert(it2, val);
        lrgbnd = large.begin() + cr_off;
        if (large.end() - lrgbnd >= small_bound) {
            /* int origlgsz = large.size(); */
            /* int newn = large.size() + small.size(); */
            /* large.resize(newn); */
            // Reverse iterator can be slower.
            /* auto it1 = small.end(); */
            /* auto it2 = large.begin() + origlgsz; */
            // Hmmm, unless I wanna to inplace_merge, which I probably don't
            // bcs that's slow and allocated extra tmp memory anyway, guess I
            // need to either have blank space between large and small of same
            // size as smallprog, or shift the vec (prob worse);
            /* for (int i = newn - 1; i >= 0; --i) { */
            /*     if (it2 != large.begin() && (it1 == small.begin() || *prev(it2) >= *prev(it1))){ */
            /*         large[i] = *--it2; */
            /*     } */
            /*     else{ */
            /*         large[i] = *--it1; */
            /*     } */
            /* } */
            inplace_merge(large.begin(), lrgbnd, large.end());
            lrgbnd = large.end(); // iterator safety no ta.
        }
        return 1;
    }
    // erase jednak nie da się, jakieś zastąpianie wartości jest nierobialne,
    // bo co jak potem zerasuję wartość na którą zastąpiłem?
    // ewentualnie mógłbym też amortyzować erasy i przy lower_boundach robić
    // dodatkowe checki / skippnięcia tego co usunięte, ale to już przechodzi w
    // syf.
    // W sumie może nie aż tak potężny, po prostu w lower_boundzie while *midit == -1
    // ++midit, ale musiałbym własny lower_bound naklepać (wsm to nie jest zbyt
    // długie // prefetching od razu kappa) + jeszcze musiałbym mieć własny merge albo dać komparator do
    // inplace_mergea który by te -1 ignorował -> wsm nontrivial taki
    // komparator raczej.
    // No i obv zaimplementowanie iteratora też byłoby czymś, aczkolwiek może
    // nawet czymś łatwiejszym.

    // -> Nvm, erase actually would not be syfem. Po prostu przy erasowaniu
    // ustawianie elementu na -1 jeśli na prawo nie jest erased, inaczej na
    // to na prawo -1, i na lewo spropaguj to dla all co śą zerasowane, tak aby
    // na erase wartość wynosiła zawsze -ile miejsc w prawo do next non-erased.

    // XXX 170422 also, pomysł z użyciem DSU do tego. Wtedy bardzo szybkie logn/alpha n, aby otrzymać najbliższe nonerased (CERC14C technique).
    // (po prostu trzymaj closest nonerased na pałe, i wtedy reku funkcja find()), a unite() jak coś usuwam.
    // Also, tą dsu-korekcję jedynie musiałbym robić po ::lower_boundzie. Bo
    // git jak ::lower_bound zwróci nawiązanie do erased elementu, no bo wtedy
    // po prostu jak do dsu użyję to mam correct wynik ez. -> No overhead basically <3
    // No i wtedy też insert bez zmiany właściwie, bo tak jak wcześniej robię
    // lower_bound i tyle. (ewentualnie could check czy mogę zastąpić erased
    // elem zamiast robić vector::insert, jako opt)
    // -> w sumie, mógłbym sb ten erase z łatwością naklepać. def to
    // kiedyś zrobię, pytanie czy teraz, given jak spory hype na mm i inne
    // fajny rzeczy mam xd

    // -> W lower_boundzie tylko if jeden trzeba dodać wtedy.
    // Jedynie jest syfniej, jeżeli to nie ma być set od typu liczbowego, bo
    // albo trzeba jeszcze w jakiejś parze trzymać tą wartość pod erasowania,
    // albo jakimś hackowańskiem castować wartość na typ intowy i sprawdzać czy
    // jest ujemne, zakładając że normalnie nie jest bo e.g. to wskaźnik.
    // But come on, jak chcesz robić erasy na secie, to nie powinienem mieć go
    // od jakiegoś stringa xd.
    // -> Jedynie warto aby handlować też wtedy jakieś pary, i ew. arraye.
    // -> Możnaby templateowo zdefiniować inline funkcję zwracającą referencję
    // do tego elementu co normalnie jest nieujemny, a ma być użyty do
    // trzymania erasowości.
    // (or rather -dsu link to nonerased tera)
    ssize_t size() const {
        /* return large.size() + small.size(); */
        return large.size();
    }
    bool empty() const {
        return !size();
    }
    void clear() {
        /* small.clear(); */
        large.clear();
    }
private:
    /* static constexpr int small_bound = 50000; */
    /* static constexpr int small_bound = 30000; */
    /* static constexpr int small_bound = 1024; */
    static constexpr int small_bound = 4096;
    // giga taktyk -> trzymanie unsorted części vectora również w large (na
    // końcu); wtedy lepszy cacheeff, i np. można inplace_merge użyć.
    // inplace_merge does try to get_temporary_buffer though.
    // -> wtedy tylko mały bound mógłby być. let's try.
    // -> 0.021s z 1024bnd, better than std::set, pog. Chyba to jest meta.
    vector<T> large;
    typename vector<T>::iterator lrgbnd = large.begin();
    /* set<T> small; */
    /* vector<T> small; */
};

// 0.023 std::set vs 0.275s fastset setbnd64 1e5 inserts + 2 lower_bounds -> terrible.
// Im mniejszy small_bound tym gorzej. W sumie rzeczywiście znacznie za mały wziąłem, powinien być pokroju tego sqrt.
// 1024 -> 0.038
// 8024 -> 0.028
// 20k, 30l -> 0.03s
// 0.023 nowa wersja z implace_mergem na 4096 small_boundzie.

// 1M inserts std::set 0.533s ; 0.509s 1024bnd2xvec | 0.332s 4096; | 10096 0.369s; | 0.332 5096 | 0.377s 2048
// 1M z vecxsetem dla 30000 0.487s najlepiej. -> 2 vecs def more worthwhile.
// Singular vec, inplace_sort 4096 0.309s nc. Def better and more worthwhile.
// Fastest na O2 czystym btw.
// 170422
// z 1M lower_bounds jeszcze.
// std::set -> 0.964
// fastset 4096 implace_merge without erase -> 0.487s. Czyli 400ms vs 150ms lb cost, i to bez własnego zoptowanego lower_bounda z constexpr i prefetchingiem. pog.
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    fastset<int> st;
    /* set<int> st; */
    int a[N];
    iota(a,a+N,0);
    random_shuffle(a,a+N);
    FORR(i,a)
        st.insert(i);
    /* cout << st.lower_bound(-4) << ' ' << st.lower_bound(2137) << '\n'; */
    int sth = 0;
    /* FOR(x,0,N){ */
    FORR(x,a){
        /* sth += *st.lower_bound(x); */
        sth += st.lower_bound(x);
    }
    cout << sth << '\n';
    /* cout << *st.lower_bound(-4) << ' ' << *st.lower_bound(2137) << '\n'; */
}

