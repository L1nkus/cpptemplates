#include <bits/stdc++.h>
#define ll long long
#define FOR(x,val,to) for(int x=(val);x<int((to));++x)
using namespace std;

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,fma")
// Mo's.
const int S = n/sqrt(t)+1;
sort(qu,qu+t,[&](const query &f, const query &s){return f.L/S != s.L/S ? f.L/S<s.L/S : (f.R==s.R ? 0 : (f.R>s.R)^(f.L/S%2));});

// Simdmin "Argmin at the speed of memory (~3⋅1010 integer / float elements per second)".
#include <x86intrin.h>
const int B = 8;
typedef int vec __attribute__ (( vector_size(4 * B) ));
vec min(vec x, vec y) {
    return (x < y ? x : y);
}
const int n = (1<<16);
alignas(64) int a[n];
int argmin() {
    vec *v = (vec*) a;
    int m = INT_MAX, k = 0;
    vec t0, t1, p;
    t0 = t1 = p = m + vec{};
    for (int i = 0; i < n / B; i += 2) {
        t0 = min(t0, v[i]);
        t1 = min(t1, v[i + 1]);
        vec t = min(t0, t1);
        int mask = _mm256_movemask_epi8((__m256i) (p == t));
        if (mask != -1) { [[unlikely]]
            for (int j = B * i; j < B * i + 2 * B; j++)
                if (a[j] < m)
                    m = a[k = j];
            t0 = t1 = p = m + vec{};
        }
    }
    return k;
}

// Fast sort.
// about 2-3 times faster than std::sort() for N >= 1e6
template<typename T>
void fast_sort(vector<T> & t) {
    const int n = t.size(), k = 1 << 16; // t[i] < k * k
    auto tmp = t; // if array: static int/unsigned tmp[nax];
    FOR(turn, 0, 2) {
    #define val(x) (turn ? x >> 16 : x & 65535)
    int cnt[k+1];
    memset(cnt, 0, sizeof cnt);
    // change t[i] to t[i].first / t[i][0] etc. if needed
    FOR(i, 0, n) cnt[val(t[i]) + 1]++;
    FOR(i, 0, k) cnt[i+1] += cnt[i];
    FOR(i, 0, n) tmp[ cnt[val(t[i])]++ ] = t[i];
    memcpy(&t[0], &tmp[0], n * sizeof t[0]);
    #undef val
    }
}

// Fenwick range updates.
// 0.202s vs 0.739s on n = 1000000, m = 1000000 vs classic recursive lazy prop
// 1-indexed musi być, wiec dodaj offset jak co.
int n;
ll B1[N], B2[N];
void add(ll *b, int idx, int x){
    while(idx <= n){
        b[idx] += x;
        idx += idx & -idx;
    }
}
void range_add(int l, int r, int x){
    add(B1, l, x);
    add(B1, r+1, -x);
    add(B2, l, 1ll*x*(l-1));
    add(B2, r+1, 1ll*-x*r);
}
ll sum(ll *b, int idx){
    ll res = 0;
    while(idx){
        res += b[idx];
        idx -= idx & -idx;
    }
    return res;
}
ll pre_sum(int idx){
    return sum(B1, idx) * idx - sum(B2,idx);
}
ll range_sum(int l, int r){
    return pre_sum(r) - (l > 1 ? pre_sum(l-1) : 0);
}

// Xorbasis

const int LOG_A = 20;

int basis[LOG_A];
int sz;
void insertvec(int mask){
	/* for(int i = 0; i < LOG_A; i++){ */
	for(int i = LOG_A - 1; i >= 0; --i){
		if((mask & 1 << i) == 0)
            continue;
		if(!basis[i]){
			basis[i] = mask;
			++sz;
			return;
		}
        mask ^= basis[i];
	}
}
int getminxored(int num){
	/* for(int i = 0; i < LOG_A; i++){ */
	for(int i = LOG_A - 1; i >= 0; --i){
		if((num & 1 << i) == 0)
            continue;
		/* if(!basis[i]){ */
		/* 	basis[i] = mask; */
		/* 	++sz; */
		/* 	return; */
		/* } */
        // jak 0 to cokolwiek
        num ^= basis[i];
	}
    return num;
}
 
// Cacheeff_tree_path_queries.
// Also, thanks to this op implementation, not only are hld path ids
// contigious, but also subtree ones, so can also use this for subtree queries.
// If there's some change, that only affects the result contribution of
// ancestors of the current node, or the descendents, try to just iterate over
// all ancestors, or over all descdenents.
// Very imporant to keep the core function as simple as possible.
// The lower separate arrays the better.
// If simple, 1e10 ops under 2s.
vi adj[N];
int k[N]; // task-specific
ll b[N]; // task-specific
int n,q;

int in[N], out[N], sz[N], nxt[N], p[N], d[N], in_to_orig[N];
void dfs_sz(int v) {
    sz[v] = 1;
    for(auto &u: adj[v]) {
        if(u == p[v])
            continue;
        p[u] = v;
        d[u] = d[v] + 1;
        dfs_sz(u);
        sz[v] += sz[u];
        if(sz[u] > sz[adj[v][0]]) {
            swap(u, adj[v][0]);
        }
    }
}
int hld_it;
void dfs_hld(int v) {
    in[v] = hld_it++;
    in_to_orig[in[v]] = v;
    for(auto u: adj[v]) {
        if(u == p[v])
            continue;
        nxt[u] = (u == adj[v][0] ? nxt[v] : u);
        dfs_hld(u);
    }
    out[v] = hld_it;
}
// I don't have to care about any adj, p, in etc. here, just the value arrays
// used in query / update funs.
void relabel(){
    int nwk[n];
    ll nwb[n];
    for(int i = 0; i < n; ++i){
        nwk[in[i]] = k[i];
        nwb[in[i]] = b[i];
    }
    memcpy(k, nwk, sizeof nwk);
    memcpy(b, nwb, sizeof nwb);
}

int target; // <task specific
ll crtype;
ll res;
int crinck, crincb; // task specific>

// https://www.codechef.com/submit/SONGIF
void query(int l, int r){
    for(int v = l; v <= r; ++v){
        res = max(res, k[v] * crtype + b[v]);
    }
}
void inc(int l, int r){
    for(int v = l; v <= r; ++v){
        k[v] += crinck;
        b[v] += crincb;
    }
}
void d1(int v, int u){
    while(nxt[v] != nxt[u]){
        if(d[nxt[v]] < d[nxt[u]]) swap(v, u);
        query(in[nxt[v]], in[v]);
        v = p[nxt[v]];
    }
    if(d[v] < d[u])
        swap(v, u);
    query(in[u], in[v]);
}
void d2(int v, int u){
    while(nxt[v] != nxt[u]){
        if(d[nxt[v]] < d[nxt[u]]) swap(v, u);
        inc(in[nxt[v]], in[v]);
        v = p[nxt[v]];
    }
    if(d[v] < d[u])
        swap(v, u);
    inc(in[u], in[v]);
}
dfs_sz(0);
dfs_hld(0);
relabel();

// Linear_sieve_eratosthenes
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    vector<int> primes;
    bool is_composite[N]{};
    int wh_pr_ind[N];
    static int func[N], cnt[N]; // If wanna wyliczyć multiplicative function.
    // Mobius function calc by default.
    func[1] = 1;
    FOR(i,2,N){
        // without checking divisibility:
        if(!is_composite[i]){
            wh_pr_ind[i] = primes.size();
            primes.push_back(i);
            func[i] = -1; cnt[i] = 1; // If wanna wyliczyć multiplicative function.
        }
        for(int j = 0; j <= wh_pr_ind[i] && i * primes[j] < N; ++j){
            is_composite[i * primes[j]] = 1;
            wh_pr_ind[i * primes[j]] = j;
            // If wanna wyliczyć multiplicative function.
            if(j + 1 == wh_pr_ind[i]){
                /* func[i * primes[j]] = func[i] / cnt[i] * (cnt[i] + 1); */
                func[i * primes[j]] = 0;
                cnt[i * primes[j]] = cnt[i] + 1;
            }
            else{
                func[i * primes[j]] = func[i] * func[primes[j]];
                cnt[i * primes[j]] = 1;
            }
        }
    }
    auto gen_pr_facts = [&](int n){
        vi res;
        while(n != 1){
            int cr = primes[wh_pr_ind[n]];
            n /= cr;
            if(res.empty() || res.back() != cr)
                res.push_back(cr);
        }
        return res;
    };
    whatis(primes.size())
    whatis(func[2])
    whatis(func[4])
    whatis(func[6])
    whatis(gen_pr_facts(84))
}

/*
 * Opis: FWHT; n musi byc potega dwojki.
 *   fwht_or(a)[i] = suma(j będące podmaską i) a[j].
 *   ifwht_or(fwht_or(a)) == a.
 *   convolution_or(a, b)[i] = suma(j | k == i) a[j] * b[k].
 *   fwht_and(a)[i] = suma(j będące nadmaską i) a[j].
 *   ifwht_and(fwht_and(a)) == a.
 *   convolution_and(a, b)[i] = suma(j \& k == i) a[j] * b[k].
 *   fwht_xor(a)[i] = suma(j oraz i parzyscie razem zapalonych bitow) a[j] - suma(j oraz i maja nieparzyscie) a[j].
 *   ifwht_xor(fwht_xor(a)) == a.
 *   convolution_xor(a, b)[i] = suma(j ^ k == i) a[j] * b[k].
 */

#define ssize(x) (x).size()
vector<int> fwht_or(vector<int> a) {
	int n = ssize(a);
	assert((n & (n - 1)) == 0);
	for(int s = 1; 2 * s <= n; s *= 2)
		for(int l = 0; l < n; l += 2 * s)
			for(int i = l; i < l + s; ++i)
				a[i + s] += a[i];
	return a;
}
vector<int> ifwht_or(vector<int> a) {
	int n = ssize(a);
	assert((n & (n - 1)) == 0);
	for(int s = n / 2; s >= 1; s /= 2)
		for(int l = 0; l < n; l += 2 * s)
			for(int i = l; i < l + s; ++i)
				a[i + s] -= a[i];
	return a;
}
vector<int> convolution_or(vector<int> a, vector<int> b) {
	int n = ssize(a);
	assert((n & (n - 1)) == 0 and ssize(b) == n);
	a = fwht_or(a);
	b = fwht_or(b);
    FOR(i,0,n)
		a[i] *= b[i];
	return ifwht_or(a);
}

vector<int> fwht_and(vector<int> a) {
	int n = ssize(a);
	assert((n & (n - 1)) == 0);
	for(int s = 1; 2 * s <= n; s *= 2)
		for(int l = 0; l < n; l += 2 * s)
			for(int i = l; i < l + s; ++i)
				a[i] += a[i + s];
	return a;
}
vector<int> ifwht_and(vector<int> a) {
	int n = ssize(a);
	assert((n & (n - 1)) == 0);
	for(int s = n / 2; s >= 1; s /= 2)
		for(int l = 0; l < n; l += 2 * s)
			for(int i = l; i < l + s; ++i)
				a[i] -= a[i + s];
	return a;
}
vector<int> convolution_and(vector<int> a, vector<int> b) {
	int n = ssize(a);
	assert((n & (n - 1)) == 0 and ssize(b) == n);
	a = fwht_and(a);
	b = fwht_and(b);
    FOR(i,0,n)
		a[i] *= b[i];
	return ifwht_and(a);
}
vector<int> fwht_xor(vector<int> a) {
	int n = ssize(a);
	assert((n & (n - 1)) == 0);
	for(int s = 1; 2 * s <= n; s *= 2)
		for(int l = 0; l < n; l += 2 * s)
			for(int i = l; i < l + s; ++i) {
				int t = a[i + s];
				a[i + s] = a[i] - t;
				a[i] += t;
			}
	return a;
}
vector<int> ifwht_xor(vector<int> a) {
	int n = ssize(a);
	assert((n & (n - 1)) == 0);
	for(int s = n / 2; s >= 1; s /= 2)
		for(int l = 0; l < n; l += 2 * s)
			for(int i = l; i < l + s; ++i) {
				int t = a[i + s];
				a[i + s] = (a[i] - t) / 2;
				a[i] = (a[i] + t) / 2;
			}
	return a;
}
vector<int> convolution_xor(vector<int> a, vector<int> b) {
	int n = ssize(a);
	assert((n & (n - 1)) == 0 and ssize(b) == n);
	a = fwht_xor(a);
	b = fwht_xor(b);
	REP(i, n)
		a[i] *= b[i];
	return ifwht_xor(a);
}

// Multidimensional xor fwht with powering.
const int mod = 998244353;
int POW(long long n, long long k) {
  int ans = 1 % mod; n %= mod; if (n < 0) n += mod;
  while (k) {
      if (k & 1) ans = (long long) ans * n % mod;
      n = (long long) n * n % mod;
      k >>= 1;
  }
  return ans;
}
namespace FWHT {
  const int MXK = 10; //(mod - 1) should be divisible by each base
  struct Matrix {
    int a[MXK][MXK], n, m;
    Matrix(int n, int m) : n(n), m(m) { }
  };
  Matrix operator * (Matrix& p, Matrix& q) {
    Matrix result(p.n, q.m);
    for (int i = 0; i < p.n; i++)
      for (int j = 0; j < q.m; j++) {
        long long val = 0;
        for (int k = 0; k < p.m; k++) val += 1LL * p.a[i][k] * q.a[k][j];
        result.a[i][j] = val % mod;
      }
    return result;
  }
  Matrix constructMatrix(int k, bool invert) {
    vector<int> divs;
    int x = mod - 1;
    for (int i = 2; i * i <= x; i++) if (x % i == 0) {
      divs.push_back((mod - 1) / i);
      while (x % i == 0) x /= i;
    }
    if (x > 1) divs.push_back((mod - 1) / x);
    int g = 2;
    while (true) {
      bool ok = true;
      for (int d : divs) if (POW(g, d) == 1) ok = false;
      if (ok) break;
      g++;
    }
    int root = POW(g, (mod - 1) / k);
    Matrix result(k, k);
    for (int i = 0; i < k; i++) {
      int x = POW(root, invert ? k - i : i);
      for (int j = 0; j < k; j++) result.a[i][j] = POW(x, j);
    }
    return result;
  }
  void transform(vector<int> &a, int n, int k, bool invert) {
    Matrix M = constructMatrix(k, invert);
    for (int len = 1; len < n; len *= k)
      for (int i = 0; i < n; i += k * len)
        for (int j = 0; j < len; j++) {
          Matrix V(1, k);
          for (int p = 0; p < k; p++) V.a[0][p] = a[i + j + p * len];
          V = V * M;
          for (int p = 0; p < k; p++) a[i + j + p * len] = V.a[0][p];
        }
    if (invert) {
      long long d = POW(n, mod - 2);
      for (int i = 0; i < n; i++) a[i] = a[i] * d % mod;
    }
  }
  //O(k^d * k * d) where d = log_k(MAX VALUE)
  vector<int> multiply(vector<int> a, vector<int> b, int k) {
    int n = 1;
    int nw = max((int)a.size() - 1, (int)b.size() - 1);
    while (n <= nw) n *= k;
    a.resize(n); b.resize(n);
    transform(a, n, k, false);
    transform(b, n, k, false);
    for (int i = 0; i < n; i++) a[i] = 1LL * a[i] * b[i] % mod;
    transform(a, n, k, true);
    return a;
  }
  vector<int> pow(vector<int> a, long long p, int k) {
    int n = 1;
    int nw = (int)a.size() - 1;
    while (n <= nw) n *= k;
    a.resize(n);
    transform(a, n, k, false);
    for (int i = 0; i < n; i++) a[i] = POW(a[i], p);
    transform(a, n, k, true);
    return a;
  }
}
void solve() {
    int n;
    ll k;
    cin >> n >> k;
    vector<int> vec(823543);
    FOR(i, 0, n) {
        int a, pos = 0, mul = 1;
        cin >> a;
        while(a) {
            if(a & 1) pos += mul;
            a /= 2;
            mul *= 7;
        }
        vec[pos]++;
    }
    vec = FWHT::pow(vec, k, 7);
    cout << vec[0] << '\n';
}

// TODO op persistent treaps with hashes for cool unions / some simd op set.
