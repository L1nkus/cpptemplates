// By UW2: Markadiusz, staniewzki, tnowak#, contest: The 2021 CCPC Weihai Onsite, problem: (M) 810975
#include<bits/stdc++.h>
using namespace std;
using LL=long long;
#define FOR(i,l,r) for(int i=(l);i<=(r);++i)
#define REP(i,n) FOR(i,0,(n)-1)
#define ssize(x) int(x.size())
template<class A,class B>auto&operator<<(ostream&o,pair<A,B>p){return o<<'('<<p.first<<", "<<p.second<<')';}
template<class T>auto operator<<(ostream&o,T x)->decltype(x.end(),o){o<<'{';int i=0;for(auto e:x)o<<(", ")+2*!i++<<e;return o<<'}';}
#ifdef DEBUG
#define debug(x...) cerr<<"["#x"]: ",[](auto...$){((cerr<<$<<"; "),...)<<'\n';}(x)
#else
#define debug(...) {}
#endif

template<unsigned Mod> struct ModularInt {
	using M = ModularInt;
	unsigned v;
	ModularInt(LL a = 0) : v((unsigned)((a %= Mod) < 0 ? a + Mod : a)) {}
	M operator-() const { return M() -= *this; }
	M& operator*=(M r) { v = (unsigned)((uint64_t)v * r.v % Mod); return *this; }
	M& operator/=(M r) { return *this *= r.inv(); }
	M& operator+=(M r) { if ((v += r.v) >= Mod) v -= Mod; return *this; }
	M& operator-=(M r) { if ((v += Mod - r.v) >= Mod) v -= Mod; return *this; }
	friend M operator*(M l, M r) { return l *= r; }
	friend M operator/(M l, M r) { return l /= r; }
	friend M operator+(M l, M r) { return l += r; }
	friend M operator-(M l, M r) { return l -= r; }
	M pow(LL n) const {
		assert(n >= 0);
		M res = 1;
		for (M t = *this; n; t *= t, n >>= 1) if (n & 1) res *= t;
		return res;
	}
	M inv() const { assert(v != 0); return pow(Mod - 2); }
	friend string to_string(M a) { return to_string(a.v); }
	friend ostream&operator<<(ostream&o,M m){return o<<m.v;}
};
constexpr int mod = 998244353, M = mod;
using Mint = ModularInt<mod>;

const Mint root = [] {
	for (Mint r = 2;; ++r.v) if(r.pow((mod - 1) / 2).v != 1) return r;
}();
void ntt(vector<Mint>&a,bool inverse = false) {
	int n = ssize(a);
	assert(__builtin_popcount(n) == 1);
	static vector<Mint> dt(30), idt(30);
	if(dt[0].v == 0) for(int i = 0; i < 30; ++i)
		dt[i] = -root.pow((mod - 1) >> (i + 2)), idt[i] = dt[i].inv();
	if(not inverse) {
		for(int w = n; w >>= 1; ) {
			Mint t=1;
			for(int s = 0, k = 0; s < n; s += 2 * w) {
				for(int i = s, j = s + w; i < s + w; ++i, ++j) {
					Mint x = a[i], y = a[j] * t;
					a[i] = x + y, a[j] = x - y;
				}
				t *= dt[__builtin_ctz(++k)];
			}
		}
	} else {
		for(int w = 1; w < n; w *= 2) {
			Mint t=1;
			for(int s = 0, k = 0; s < n; s += 2 * w) {
				for(int i = s, j = s + w; i < s + w; ++i, ++j) {
					Mint x = a[i], y = a[j];
					a[i] = x + y, a[j] = (x - y) * t;
				}
				t *= idt[__builtin_ctz(++k)];
			}
		}
	}
}
vector<Mint> multiply(vector<Mint> a, vector<Mint> b) {
	if(a.empty() or b.empty()) return {};
	int n = ssize(a), m = ssize(b), l = n + m - 1, sz = 1 << __lg(2 * l - 1);
	a.resize(sz), ntt(a);
	b.resize(sz), ntt(b);
	REP(i, sz) a[i] *= b[i];
	ntt(a, true), a.resize(l);
	Mint inv = Mint(sz).inv();
	for (auto &&e : a) e *= inv;
	return a;
}


void trim(vector<Mint>& a) {
	while (not a.empty() and a.back().v == 0) {
		a.pop_back();
	}
}

vector<Mint> conv_mod(vector<Mint> a, vector<Mint> b) {
	return multiply(a, b);
}

vector<Mint> poly_odj(vector<Mint> a, vector<Mint> b) {
	debug(a, b);
	if(ssize(b) > ssize(a)) a.resize(ssize(b));
	REP(i,ssize(b)) {
		a[i] -= b[i];
	}
	debug(a);
	trim(a);
	return a;
}

vector<Mint> poly_inv(vector<Mint> a, int n) {
	assert(not a.empty() and a[0].v != 0);
	trim(a);
	int deg = 1;
	vector<Mint> b = {Mint(a[0]).inv()};
	while (deg <= n) {
		deg *= 2;
		debug(b);
		vector<Mint> ca(min(deg, ssize(a)));
		REP(i,min(ssize(ca), ssize(a))) {
			ca[i] = a[i];
		}
		auto temp = conv_mod(ca, b);
		if (ssize(temp) > deg) {
			temp.resize(deg);
		}
		b = conv_mod(poly_odj({2}, temp), b);
		if (ssize(b) > deg) {
			b.resize(deg);
		}
	}
	b.resize(n);
	debug(a, n, b);
	debug(conv_mod(a, b));
	return b;
}

vector<Mint> poly_div(vector<Mint> a, vector<Mint> b) {
	trim(a);
	trim(b);
	auto c = conv_mod(a, poly_inv(b, ssize(a)));
	c.resize(ssize(a) - ssize(b) + 1);
	//auto ddd = poly_inv(b, ssize(a));
	//debug(a, b, ddd, c);
	return c;
}

struct Binom {
	vector<Mint> fac, rev;
	Binom(int n) {
		fac = rev = vector<Mint>(n + 1, 1);
		FOR(i, 1, n) fac[i] = fac[i - 1] * i;
		rev[n] = Mint(fac[n]).inv();
		for(int i = n; i >= 1; i--)
			rev[i - 1] = rev[i] * i;
	}
	Mint operator()(int n, int k) {
		return fac[n] * rev[n - k] * rev[k];
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);

	debug(conv_mod({1, 1}, {1, 2, 1}));

	debug(poly_div({1, 3, 3, 1}, {1, 2, 1}));

	//return 0;

	int n, m, k;
	cin >> n >> m >> k;

	if(n == 0) {
		cout << "1\n";
		return 0;
	}
	else if(k == 0) {
		if(m == 0) cout << "1\n";
		else cout << "0\n";
		return 0;
	}
	else if(k > m) {
		cout << "0\n";
		return 0;
	} if(n < m) {
		cout << "0\n";
		return 0;	
	}

	debug(poly_div({1, 3, 3, 1}, {1, 2, 1}));

	int z = n + 1 - m;
	n++;

	Binom b(z);

	auto get = [&](int x) {
		vector<Mint> res(2 * n + 1);
		for(int i = 0; i * x <= 2 * n && i <= z; i++) {
			res[i * x] = b(z, i) * ((z - i) % 2 == 0 ? 1 : -1);
			// if(res[i * x] < 0) res[i * x] += M;
		}
		trim(res);
		return res;
	};

	debug(get(k+1));
	debug(get(k));
	debug(get(1));
	auto p1 = poly_div(get(k+1), get(1));
	auto p2 = poly_div(get(k), get(1));
	debug(p1);
	debug(p2);
	auto ans = poly_odj(p1, p2);
	debug(ans);
	ans.resize(n+1-z);
	cout << ans[n-z] << '\n';
	debug(ans);

	debug(get(2));
}
