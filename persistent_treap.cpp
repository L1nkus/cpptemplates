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
#define N 1000001

constexpr uint32_t C = int(5e8 * M_PI) + 69;
constexpr uint32_t RANDOM = 235713604;
uint32_t hash(uint32_t x){
    return __builtin_bswap32((x^RANDOM) * C);
}

// then found https://www.cs.cmu.edu/~scandal/papers/treaps-spaa98.pdf
// Also, TODO, to rem memory usage, mogę trzymać hashset wszystkich
// istniejących nodów. Wtedy, jeżeli mamy obecnie o danym hashu node, zamiast
// new, po prostu set pointer na tamten.
// I jeżeli chciałbym też freeować, to mógłbym trzymać counter i go incować /
// decować, ale ponieważ tutaj dopiero pod koniec chciałbym całość freeować, a
// po drodze raczej nie, no to chyba nie miałoby to tu sensu.
// -> shared_ptr w takim razie pewnie też nie ma zbytniego sensu.
// Może miałby przy większym degu, bo możemy nie chcieć przetrzymywać wyników
// pośrednich.
struct item {
    int key, prior, cnt;
    unsigned int hash;
#ifdef __sharedptr
    shared_ptr<item> l, r;
#else
    item *l, *r;
#endif
    item () {}
#ifdef __sharedptr
    item (item *node) : key(node->key), prior(node->prior), l(node->l), r(node->r), cnt(node->cnt), hash(node->hash) {}
#else
    item (item *node) : key(node->key), prior(node->prior), l(node->l), r(node->r), cnt(node->cnt), hash(node->hash) {}
#endif
    item (int key) : key(key), prior(::hash(key)), l(NULL), r(NULL), cnt(1) {
        hash = prior;
    }
	void combine ();
};
typedef item* pitem;

int count (pitem t) {
    return t ? t->cnt : 0;
}

uint32_t gethash (pitem t) {
    return t ? t->hash : 0;
}

void item::combine () {
    cnt = 1 + count(this->l) + count(this->r);
    hash = ::hash(gethash(this->l) ^ gethash(this->r) ^ prior);
}

unordered_map<uint32_t, pitem> node_map;

pitem newitem(int val) {
    return new item(val);
    /* uint32_t prior = ::hash(val); */
    /* pitem &sth = node_map[prior]; */
    /* if (!sth) */
    /*     sth = new item(val); */
    /* return sth; */
}

pitem newitem(pitem val) {
    // -> hmm. guess tutaj chcę robić jakieś modyfikacje jeszcze na tym, temu
    // jest new in the first place?
    // -> Surely.
    return new item(val);
}

pitem newitem() {
    return new item();
}

void split (pitem t, int key, pitem & l, pitem & r) {
    if (!t)
        return void(l = r = NULL);
    if(t->key < key){
        pitem root = newitem(t);
        l = root;
        split(t->r, key, l->r, r);
        l->combine();
    }
    else if(t->key > key){
        pitem root = newitem(t);
        r = root;
        split(t->l, key, l, r->l);
        r->combine();
    }
    else{
        l = t->l;
        r = t->r;
        // can return duplicate here, with return t.
    }
}

/* void insert (pitem & t, pitem it) { */
/*     if (!t) */
/*         t = it; */
/*     else if (it->prior > t->prior) */
/*         split (t, it->key, it->l, it->r),  t = it; */
/*     else */
/*         insert (t->key <= it->key ? t->r : t->l, it); */
/* } */

/* pitem merge (pitem & t, pitem l, pitem r) { */
/*     if (!l || !r) */
/*         return l ? new item(l) : new item(r); */
/*     pitem res; */
/*     if (l->prior > r->prior) */
/*         merge (l->r, l->r, r),  t = l; */
/*     else */
/*         merge (r->l, l, r->l),  t = r; */
/*     return res; */
/* } */

/* void erase (pitem & t, int key) { */
/*     if (t->key == key) { */
/*         pitem th = t; */
/*         merge (t, t->l, t->r); */
/*         delete th; */
/*     } */
/*     else */
/*         erase (key < t->key ? t->l : t->r, key); */
/* } */

// O(m log(n / m)) where |m| <= |n|.
// With hashes, O(k log(n/k)), where k = min(|m|, |t1 ∆ t2|)
// https://arxiv.org/pdf/1301.3388.pdf
pitem unite (pitem l, pitem r) {
    if (!l || !r)  return l ? l : r;
    if (l->hash == r->hash)  return l;
    // może z tą wersją, nie muszę w splicie mieć czeka o eq key?
    pitem ret = newitem();
    if (l->prior < r->prior)  swap (l, r);
    ret->key = l->key;
    ret->prior = l->prior;
    pitem lt, rt;
    split (r, l->key, lt, rt);
    ret->l = unite (l->l, lt);
    ret->r = unite (l->r, rt);
    ret->combine();
    return ret;
}

// Version without hashes.
/* pitem unite (pitem l, pitem r) { */
/*     if (!l || !r)  return l ? l : r; */
/*     pitem ret = new item(); */
/*     if (l->prior < r->prior)  swap (l, r); */
/*     ret->key = l->key; */
/*     ret->prior = l->prior; */
/*     pitem lt, rt; */
/*     split (r, l->key, lt, rt); */
/*     ret->l = unite (l->l, lt); */
/*     ret->r = unite (l->r, rt); */
/*     ret->combine(); */
/*     return ret; */
/* } */

// untested.
void insert (pitem & t, pitem it) {
    if (!t)
        t = it;
    else if (it->prior > t->prior)
        split (t, it->key, it->l, it->r),  t = it;
    else
        insert (t->key <= it->key ? t->r : t->l, it);
}

bool count (pitem v, int key) {
    if(!v)
        return false;
    if(v->key == key)
        return true;
    return count(key < v->key ? v->l : v->r, key);
}

void wypisz (pitem v) {
    if(!v)
        return;
    wypisz(v->l);
    cout << v->key << ' ';
    wypisz(v->r);
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
}

