// https://judge.yosupo.jp/problem/predecessor_problem
// library checker so cool for getting the fastest stuff
// op for potyczki
// std::set is 2498ms
// https://judge.yosupo.jp/submission/76471 (o 1ms faster; bardziej rozbudowany/ bitset)
// https://judge.yosupo.jp/submission/76543 (this one here)
// 55ms
/* #pragma GCC optimize("O3,unroll-loops") */
/* #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt") */
/* #include <immintrin.h> // for _addcarry_u64 and _subborrow_u64 */
/* #include <bits/stdc++.h> */
/* #include <unistd.h> */
/* using namespace std; */
/* using ull = unsigned long long; */
/* using uint = unsigned int; */

/* // Thanks to nor for finding out how much a custom bitset speeds this up */
/* // NOT INITIALISED BY DEFAULT! call .clear to zero all bits */
/* template<uint N> */
/* class Bitset { */
/* 	private: */
/* 		constexpr static ull LM = (1ull<<32) - 1; */
/* 		constexpr static ull FM = ~0ull; */
/* 		constexpr static uint H = (N + 63) >> 6; */
/* 		array<ull, H> bits; */

/* 		void clearHighBits() { */
/* 			if constexpr (N & 63) bits[H-1] &= ~(FM << (N & 63)); */
/* 		} */
/* 	public: */
/* 		Bitset() {} */

/* 		void clear() { for (ull& v : bits) v = 0; } */
/* 		void set() { */
/* 			for (ull& v : bits) v = FM; */
/* 			clearHighBits(); */
/* 		} */
/* 		void flip() { */
/* 			for (ull& v : bits) v = ~v; */
/* 			clearHighBits(); */
/* 		} */
/* 		bool get(uint i) const { return bits[i>>6] & (1ull << (i & 63)); } */
/* 		void set(uint i, ull v) { bits[i>>6] = (bits[i>>6] & ~(1ull << (i & 63))) | (v << (i & 63)); } */
/* 		void setZero(uint i) { bits[i>>6] &= ~(1ull << (i & 63)); } */
/* 		void setOne(uint i) { bits[i>>6] |= 1ull << (i & 63); } */

/* 		// Sets bit[a + i] = v[i] for i \in [0, b-a]. Must have 0 <= a <= b < min(a + 64, N) */
/* 		void setRange(uint a, uint b, ull v) { */
/* 			uint j = (a >> 6), r = (a & 63), len = b-a+1; */
/* 			ull mask = FM >> (64 - len); */
/* 			bits[j] = (bits[j] & ~(mask << r)) | (v << r); */
/* 			if ((b >> 6) > j) bits[j + 1] = (bits[j + 1] & ~(mask >> (64 - r))) | (v >> (64 - r)); */
/* 		} */

/* 		// Returns v s.t. v[i] = bit[a + i] for i \in [0, b-a]. Must have 0 <= a <= b < min(a + 64, N) */
/* 		ull getRange(uint a, uint b) const { */
/* 			uint j = (a >> 6), r = (a & 63), len = b-a+1; */
/* 			ull mask = FM >> (64 - len); */
/* 			if ((b >> 6) <= j) return (bits[j] >> r) & mask; */
/* 			return ((bits[j] >> r) | (bits[j+1] << (64 - r))) & mask; */
/* 		} */

/* 		// Returns minimum i \in [a, b] such that bits[i] = 1, or b + 1 if none exist */
/* 		int findNext(uint a, uint b = N-1) const { */
/* 			if (a > b) return b + 1; */

/* 			uint j = (a >> 6); */
/* 			ull tmp = bits[j] >> (a & 63); */
/* 			if (tmp != 0) return min(b + 1, a + __builtin_ctzll(tmp)); */
/* 			for (++j; (j << 6) <= b; ++j) { */
/* 				if (bits[j]) return min(b + 1, (j << 6) + __builtin_ctzll(bits[j])); */
/* 			} */
/* 			return b + 1; */
/* 		} */

/* 		// Returns maximum i \in [a, b] such that bits[i] = 1, or a - 1 if none exist */
/* 		int findPrev(uint b, uint a = 0) const { */
/* 			if (b < a) return a - 1; */

/* 			uint j = (b >> 6); */
/* 			ull tmp = bits[j] << (63 - (b & 63)); */
/* 			if (tmp != 0) return (int)max(a, b+1 - __builtin_clzll(tmp)) - 1; */
/* 			for (--j; ((j + 1) << 6) > a; --j) { */
/* 				if (bits[j]) return (int)max(a, ((j + 1) << 6) - __builtin_clzll(bits[j])) - 1; */
/* 			} */
/* 			return (int)a - 1; */
/* 		} */
		
/* 		// Counts set bits in range [a, b] */
/* 		uint count(uint a = 0, uint b = N-1) const { */
/* 			uint res = 0; */
/* 			if (a & 63) res -= __builtin_popcountll(bits[a >> 6] << (64 - (a & 63))); */
/* 			if ((b + 1) & 63) res -= __builtin_popcountll(bits[b >> 6] >> ((b + 1) & 63)); */
/* 			for (uint j = (a >> 6); j <= (b >> 6); ++j) res += __builtin_popcountll(bits[j]); */
/* 			return res; */
/* 		} */

/* 		bool operator==(const Bitset<N>& rhs) const { */
/* 			for (uint i = 0; i < H; ++i) { */
/* 				if (bits[i] != rhs.bits[i]) return false; */
/* 			} */
/* 			return true; */
/* 		} */
/* 		bool operator<(const Bitset<N>& rhs) const { */
/* 			for (uint i = 0; i < H; ++i) { */
/* 				if (bits[i] != rhs.bits[i]) return bits[i] < rhs.bits[i]; */
/* 			} */
/* 			return false; */
/* 		} */
/* 		Bitset<N> operator~() const { */
/* 			Bitset<N> res; */
/* 			for (uint i = 0; i < H; ++i) res.bits[i] = ~bits[i]; */
/* 			res.clearHighBits(); */
/* 			return res; */
/* 		} */
/* 		Bitset<N> operator<<(uint d) const { */
/* 			Bitset<N> res; */
/* 			uint s = min(d >> 6, H); */
/* 			uint r = d & 63; */
/* 			for (uint i = 0; i < s; ++i) res.bits[i] = 0; */
/* 			if (r == 0) for (uint i = s; i < H; ++i) res.bits[i] = bits[i - s]; */
/* 			else { */
/* 				if (s < H) res.bits[s] = bits[0] << r; */
/* 				for (uint i = s + 1; i < H; ++i) res.bits[i] = (bits[i - s] << r) | (bits[i-1 - s] >> (64 - r)); */
/* 			} */
/* 			res.clearHighBits(); */
/* 			return res; */
/* 		} */
/* 		Bitset<N> operator>>(uint d) const { */
/* 			Bitset<N> res; */
/* 			uint s = min(d >> 6, H); */
/* 			uint r = d & 63; */
/* 			for (uint i = H-1; i >= H-s; ++i) res.bits[i] = 0; */
/* 			if (r == 0) for (int i = H-1-s; i >= 0; --i) res.bits[i] = bits[i + s]; */
/* 			else { */
/* 				if (s < H) res.bits[H-1-s] = bits[H-1] >> r; */
/* 				for (uint i = H-2-s; i >= 0; --i) res.bits[i] = (bits[i + s] >> r) | (bits[i+1 + s] << (64 - r)); */
/* 			} */
/* 			return res; */
/* 		} */
/* 		Bitset<N> operator|(const Bitset& rhs) const { */
/* 			Bitset<N> res; */
/* 			for (uint i = 0; i < H; ++i) res.bits[i] = bits[i] | rhs.bits[i]; */
/* 			return res; */
/* 		} */
/* 		Bitset<N> operator&(const Bitset& rhs) const { */
/* 			Bitset<N> res; */
/* 			for (uint i = 0; i < H; ++i) res.bits[i] = bits[i] & rhs.bits[i]; */
/* 			return res; */
/* 		} */
/* 		Bitset<N> operator^(const Bitset& rhs) const { */
/* 			Bitset<N> res; */
/* 			for (uint i = 0; i < H; ++i) res.bits[i] = bits[i] ^ rhs.bits[i]; */
/* 			return res; */
/* 		} */
/* 		Bitset operator+(const Bitset& rhs) const { */
/* 			Bitset<N> res; */
/* 			uint8_t carry = 0; */
/* 			for (uint i = H-1; i >= 0; --i) carry = _addcarry_u64(carry, bits[i], rhs.bits[i], res.bits[i]); */
/* 			return res; */
/* 		} */
/* 		Bitset operator-(const Bitset& rhs) const { */
/* 			Bitset<N> res; */
/* 			uint8_t borrow = 0; */
/* 			for (uint i = H-1; i >= 0; --i) borrow = _subborrow_u64(borrow, bits[i], rhs.bits[i], res.bits[i]); */
/* 			return res; */
/* 		} */
/* }; */

/* // van Emde Boas tree. Maintains a set of integers in range [0, 2^B) and supports operations */
/* //	findNext(i): returns minimum j >= i in set, or 2^B if none exist */
/* // 	findPrev(i): returns maximum j <= i in set, or -1 if none exist */
/* //	insert(i), erase(i): insert/erase i into the set */
/* //	empty(): returns TRUE if the set is empty */
/* //	clear(): empties the set */
/* //	init(bts): inits the set, after the call i will be in the set if bts[i] = 1. bts should be a bitset, but can be a vector of 0/1 */
/* // All operations except empty, clear and init are O(log B) = O(log log 2^B) with good constants */
/* template<int B, typename ENABLE = void> */
/* class VEBTree { */
/* 	private: */
/* 		const static int K = B / 2, R = (B + 1) / 2, M = (1 << B); */
/* 		const static int S = 1 << K, MASK = (1 << R) - 1; */
/* 		array<VEBTree<R>, S> ch; */
/* 		VEBTree<K> act; */
/* 		int mi, ma; */
/* 	public: */
/* 		bool empty() const { return ma < mi; } */
		
/* 		int findNext(int i) const { */
/* 			if (i <= mi) return mi; */
/* 			if (i > ma) return M; */
			
/* 			int j = i >> R, x = i & MASK; */
/* 			int res = ch[j].findNext(x); */
/* 			if (res <= MASK) return (j << R) + res; */
			
/* 			j = act.findNext(j + 1); */
/* 			return (j >= S) ? ma : ((j << R) + ch[j].findNext(0)); */
/* 		} */
/* 		int findPrev(int i) const { */
/* 			if (i >= ma) return ma; */
/* 			if (i < mi) return -1; */
			
/* 			int j = i >> R, x = i & MASK; */
/* 			int res = ch[j].findPrev(x); */
/* 			if (res >= 0) return (j << R) + res; */
			
/* 			j = act.findPrev(j - 1); */
/* 			return (j < 0) ? mi : ((j << R) + ch[j].findPrev(MASK)); */
/* 		} */
/* 		void insert(int i) { */
/* 			if (i <= mi) { */
/* 				if (i == mi) return; */
/* 				swap(mi, i); */
/* 				if (i == M) ma = mi; // we were empty */
/* 				if (i >= ma) return; // we had mi == ma */
/* 			} else if (i >= ma) { */
/* 				if (i == ma) return; */
/* 				swap(ma, i); */
/* 				if (i <= mi) return; // we had mi == ma */
/* 			} */
/* 			int j = i >> R; */
/* 			if (ch[j].empty()) act.insert(j); */
/* 			ch[j].insert(i & MASK); */
/* 		} */
/* 		void erase(int i) { */
/* 			if (i <= mi) { */
/* 				if (i < mi) return; */
/* 				i = mi = findNext(mi + 1); */
/* 				if (i >= ma) { */
/* 					if (i > ma) ma = -1; // we had mi == ma */
/* 					return; // after erase we have mi == ma */
/* 				} */
/* 			} else if (i >= ma) { */
/* 				if (i > ma) return; */
/* 				i = ma = findPrev(ma - 1); */
/* 				if (i <= mi) return; // after erase we have mi == ma */
/* 			} */
/* 			int j = i >> R; */
/* 			ch[j].erase(i & MASK); */
/* 			if (ch[j].empty()) act.erase(j); */
/* 		} */

/* 		void clear() { */
/* 			mi = M, ma = -1; */
/* 			act.clear(); */
/* 			for (int i = 0; i < S; ++i) ch[i].clear(); */
/* 		} */
/* 		template<class T> */
/* 		void init(const T& bts, int shift = 0, int s0 = 0, int s1 = 0) { */
/* 			s0 = -shift + bts.findNext(shift + s0, shift + M-1 - s1); */
/* 			s1 = M-1 - (-shift + bts.findPrev(shift + M-1-s1, shift + s0)); */
/* 			if (s0 + s1 >= M) clear(); */
/* 			else { */
/* 				act.clear(); */
/* 				mi = s0, ma = M-1 - s1; */
/* 				++s0; ++s1; */
/* 				for (int j = 0; j < S; ++j) { */
/* 					ch[j].init(bts, shift + (j << R), max(0, s0 - (j << R)), max(0, s1 - ((S-1-j) << R))); */
/* 					if (! ch[j].empty()) act.insert(j); */
/* 				} */
/* 			} */
/* 		} */
/* }; */

/* template<int B> */
/* class VEBTree<B, enable_if_t<(B <= 6)>> { */
/* 	private: */
/* 		const static int M = (1 << B); */
/* 		ull act; */
/* 	public: */
/* 		bool empty() const { return !act; } */
/* 		void clear() { act = 0; } */

/* 		int findNext(int i) const { */
/* 			return ((i < M) && (act >> i)) ? i + __builtin_ctzll(act >> i) : M; */
/* 		} */
/* 		int findPrev(int i) const { */
/* 			return ((i != -1) && (act << (63 - i))) ? i - __builtin_clzll(act << (63 - i)) : -1; */
/* 		} */
/* 		void insert(int i) { act |= 1ull << i; } */
/* 		void erase(int i) { act &= ~(1ull << i); } */
		
/* 		template<class T> */
/* 		void init(const T& bts, int shift = 0, int s0 = 0, int s1 = 0) { */
/* 			if (s0 + s1 >= M) act = 0; */
/* 			else act = bts.getRange(shift + s0, shift + M-1-s1) << s0; */
/* 		} */
/* }; */

/* struct FastIO { */
/* 	private: */
/* 		const static int K = 1 << 15; */
/* 		array<array<char, 4>, 10000> num_strs; */
/* 		array<int, 10000> skip_chs; */
/* 		array<char, K> in_buf, out_buf; */
/* 		int in_fd, out_fd, in_x = K, out_x = 0; */

/* 		void refillBuffer() { */
/* 			if (in_x < K) { */
/* 				memmove(in_buf.data(), in_buf.data() + in_x, K - in_x); */
/* 				in_x = K - in_x; */
/* 			} else in_x = 0; */
/* 			read(in_fd, in_buf.data() + in_x, K - in_x); */
/* 			in_x = 0; */
/* 		} */
/* 		void flush() { */
/* 			if (out_x) write(out_fd, out_buf.data(), out_x); */
/* 			out_x = 0; */
/* 		} */
/* 	public: */
/* 		FastIO(FILE* in = stdin, FILE* out = stdout) : in_fd(fileno(in)), out_fd(fileno(out)) { */
/* 			for (int x = 0; x < num_strs.size(); ++x) { */
/* 				skip_chs[x] = 0; */
/* 				for (int i = 0, tmp = x; i < 4; ++i, tmp /= 10) { */
/* 					if (tmp == 0 && (x > 0 || i > 0)) skip_chs[x] = max(skip_chs[x], 4-i); */
/* 					num_strs[x][3-i] = ('0' + (tmp % 10)); */
/* 				} */
/* 			} */
/* 		} */
/* 		~FastIO() { flush(); close(out_fd); } */

/* 		int readInt() { */
/* 			if (in_x >= K / 2) refillBuffer(); */
/* 			while(in_buf[in_x] < '-') ++in_x; */

/* 			int res = 0, sg = 1; */
/* 			if (in_buf[in_x] == '-') sg = -1, ++in_x; */
/* 			for (; in_buf[in_x] > '-'; ++in_x) res = (10 * res + (in_buf[in_x] - '0')); */
/* 			return sg * res; */
/* 		} */
/* 		template<int N> */
/* 		Bitset<N> readBinaryString() { */
/* 			if (in_x >= K / 2) refillBuffer(); */
/* 			while(in_buf[in_x] < '0' || in_buf[in_x] > '1') ++in_x; */

/* 			int j = 0; */
/* 			Bitset<N> res; */
/* 			while('0' <= in_buf[in_x] && in_buf[in_x] <= '1') { */
/* 				res.set(j, in_buf[in_x] == '1'); */
/* 				++in_x, ++j; */
/* 				if (in_x >= K / 2) refillBuffer(); */
/* 			} */
/* 			return res; */
/* 		} */
/* 		void printChar(char c) { */
/* 			out_buf[out_x] = c; */
/* 			++out_x; */
/* 			if (out_x >= K / 2) flush(); */
/* 		} */
/* 		// Works for |num| < 1e8. Add additional ifs for larger |num| */
/* 		void printInt(int num) { */
/* 			if (num < 0) { */
/* 				out_buf[out_x] = '-'; */
/* 				++out_x; */
/* 				num *= -1; */
/* 			} */
/* 			if (num >= 10000) { */
/* 				int hi = num / 10000; */
/* 				int lo = num % 10000; */
/* 				for (int i = skip_chs[hi]; i < 4; ++i, ++out_x) out_buf[out_x] = num_strs[hi][i]; */
/* 				for (int i = 0; i < 4; ++i, ++out_x) out_buf[out_x] = num_strs[lo][i]; */
/* 			} else { */
/* 				for (int i = skip_chs[num]; i < 4; ++i, ++out_x) out_buf[out_x] = num_strs[num][i]; */
/* 			} */
/* 			if (out_x >= K / 2) flush(); */
/* 		} */
/* }; */

/* int main() { */
/* 	FastIO io; */
/* 	int n = io.readInt(); */
/* 	int q = io.readInt(); */
/* 	auto ini = io.readBinaryString<(1 << 24)>(); */
	
/* 	VEBTree<24> veb; */
/* 	veb.init(ini); */

/* 	vector<int> res; */
/* 	for (int qi = 0; qi < q; ++qi) { */
/* 		int c = io.readInt(); */
/* 		int i = io.readInt(); */

/* 		if (c == 0) veb.insert(i); */
/* 		else if (c == 1) veb.erase(i); */
/* 		else { */
/* 			int r; */
/* 			if (c == 2) { */
/* 				r = (veb.findNext(i) == i); */
/* 			} else if (c == 3) { */
/* 				r = veb.findNext(i); */
/* 				if (r >= n) r = -1; */
/* 			} else if (c == 4) { */
/* 				r = veb.findPrev(i); */
/* 			} */
/* 			io.printInt(r); */
/* 			io.printChar('\n'); */
/* 		} */
/* 	} */
/* } */

// 235ms
// https://judge.yosupo.jp/submission/53379
/* #include <assert.h> */

/* #include <stdint.h> */

/* #include <stdio.h> */

/* #include <vector> */



/* using std::vector; */



/* // [0, n), 1 <= n <= 2^(6D) */

/* template <int D> struct Set { */

/*   int n; */

/*   vector<uint64_t> a[D]; */

/*   Set() {} */

/*   Set(int n_) : n(n_) { */

/*     static_assert(1 <= D && D <= 6, "Set: 1 <= D <= 6 must hold"); */

/*     assert(1 <= n_ && n_ <= 1LL << (6 * D)); */

/*     for (int d = 0; d < D; ++d) { */

/*       n_ = (n_ + 63) >> 6; */

/*       a[d].assign(n_, 0); */

/*     } */

/*   } */

/*   bool empty() const { */

/*     return !a[D - 1][0]; */

/*   } */

/*   bool contains(int x) const { */

/*     return (a[0][x >> 6] >> (x & 63)) & 1; */

/*   } */

/*   void insert(int x) { */

/*     for (int d = 0; d < D; ++d) { */

/*       const int q = x >> 6, r = x & 63; */

/*       a[d][q] |= 1ULL << r; */

/*       x = q; */

/*     } */

/*   } */

/*   void erase(int x) { */

/*     for (int d = 0; d < D; ++d) { */

/*       const int q = x >> 6, r = x & 63; */

/*       if ((a[d][q] &= ~(1ULL << r))) break; */

/*       x = q; */

/*     } */

/*   } */

/*   // min s.t. >= x */

/*   int next(int x) const { */

/*     for (int d = 0; d < D; ++d) { */

/*       const int q = x >> 6, r = x & 63; */

/*       if (static_cast<size_t>(q) >= a[d].size()) break; */

/*       const uint64_t upper = a[d][q] >> r; */

/*       if (upper) { */

/*         x += __builtin_ctzll(upper); */

/*         for (int e = d - 1; e >= 0; --e) x = x << 6 | __builtin_ctzll(a[e][x]); */

/*         return x; */

/*       } */

/*       x = q + 1; */

/*     } */

/*     return n; */

/*   } */

/*   // max s.t. <= x */

/*   int prev(int x) const { */

/*     for (int d = 0; d < D; ++d) { */

/*       if (x < 0) break; */

/*       const int q = x >> 6, r = x & 63; */

/*       const uint64_t lower = a[d][q] << (63 - r); */

/*       if (lower) { */

/*         x -= __builtin_clzll(lower); */

/*         for (int e = d - 1; e >= 0; --e) x = x << 6 | (63 - __builtin_clzll(a[e][x])); */

/*         return x; */

/*       } */

/*       x = q - 1; */

/*     } */

/*     return -1; */

/*   } */

/* }; */



/* void unittest() { */

/*   Set<5> s(123456789); */

/*   assert(s.empty()); */

/*   s.insert(314159); */

/*   s.insert(141592); */

/*   assert(!s.empty()); */

/*   s.erase(314159); */

/*   s.erase(141592); */

/*   assert(s.empty()); */

/*   s.insert(653589); */

/*   s.insert(793238); */

/*   s.insert(462643); */

/*   s.erase(653589); */

/*   s.insert(383279); */

/*   s.insert(502884); */

/*   s.erase(502884); */

/*   s.insert(383289); */

/*   s.insert(462743); */

/*   s.insert(794238); */

/*   s.erase(462643); */

/*   // {383279, 383289, 462743, 793238, 794238} */

/*   assert(s.next(400000) == 462743); */

/*   assert(s.next(462743) == 462743); */

/*   assert(s.next(462744) == 793238); */

/*   assert(s.next(800000) == 123456789); */

/*   assert(s.next(123456788) == 123456789); */

/*   assert(s.prev(800000) == 794238); */

/*   assert(s.prev(383289) == 383289); */

/*   assert(s.prev(383288) == 383279); */

/*   assert(s.prev(300000) == -1); */

/*   assert(s.prev(0) == -1); */

/* } */





/* // https://old.yosupo.jp/problem/predecessor_problem */

/* char T[10'000'010]; */



/* int main() { */

/*   // unittest(); */

  

/*   int N, Q; */

/*   for (; ~scanf("%d%d", &N, &Q); ) { */

/*     scanf("%s", T); */

/*     Set<4> s(N); */

/*     for (int i = 0; i < N; ++i) { */

/*       if (T[i] == '1') { */

/*         s.insert(i); */

/*       } */

/*     } */

/*     for (; Q--; ) { */

/*       int typ, k; */

/*       scanf("%d%d", &typ, &k); */

/*       switch (typ) { */

/*         case 0: { */

/*           s.insert(k); */

/*         } break; */

/*         case 1: { */

/*           s.erase(k); */

/*         } break; */

/*         case 2: { */

/*           const bool ans = s.contains(k); */

/*           puts(ans ? "1" : "0"); */

/*         } break; */

/*         case 3: { */

/*           const int ans = s.next(k); */

/*           printf("%d\n", (ans >= N) ? -1 : ans); */

/*         } break; */

/*         case 4: { */

/*           const int ans = s.prev(k); */

/*           printf("%d\n", ans); */

/*         } break; */

/*         default: assert(false); */

/*       } */

/*     } */

/*   } */

/*   return 0; */

/* } */



// 210ms
// https://judge.yosupo.jp/submission/86005
// short as hell.

// ESSENTIALLY Nachia's EXCELLENT CODE

/* #include <iostream> */

/* #include <vector> */

/* #include <cassert> */

/* using namespace std; */



/* class  WordsizeTree */

/* { */

/*   private: */

/*     using  u64 = uint64_t; */

/*     using  V64 = vector<u64>; */



/*     vector<V64>  A; */



/*   public: */

/*     WordsizeTree( const string &binStr = "" )  { */

/*         int  n = binStr.size(); */



/*         V64  a( n/64 + 1 ); */

/*         for( int i=0 ; i<n ; ++i ) */

/*             if( binStr[i] == '1' ) */

/*                 a[i/64] |= (u64)1 << ( i % 64 ); */



/*         A.push_back( a ); */

/*         n /= 64; */



/*         while( n )  { */

/*             V64  a( n/64 + 1, 0 ); */

/*             for( int i=0 ; i<=n ; ++i ) */

/*                 if( A.back()[i] ) */

/*                     a[i/64] |= (u64)1 << ( i % 64 ); */



/*             A.push_back( a ); */

/*             n /= 64; */

/*         } */

/*     } */

	

/*     void  insert( int x )  { */

/*         for( auto &a : A )  { */

/*             a[x/64] |= (u64)1 << ( x % 64 ); */

/*             x /= 64; */

/*         } */

/*     } */

	

/*     void  erase( int x )  { */

/*         for( auto &a : A )  { */

/*            if( a[x/64] &= ~( (u64)1 << ( x % 64 ) ) )  return; */

/*            x /= 64; */

/*         } */

/*     } */

	

/*     int  count( int x ) const  { */

/*         return  (int)( ( A[0][x/64] >> ( x % 64 ) ) & 1 ); */

/*     } */

	

/*     int  atLeast( int x ) const  { */

/*         int  d = 0,  i = x; */

/*         while( true )  { */

/*             if( d >= A.size() )  return  -1; */

/*             u64  m = A[d][i/64] & ( ( ~(u64)0 ) <<  ( i % 64 ) ); */

/*             if( !m )  { ++d;  i /= 64;  ++i; } */

/*             else  { */

/*                 i = i/64 * 64 + lowBit( m ); */

/*                 if( d-- == 0 )  break; */

/*                 i *= 64; */

/*             } */

/*         } */

/*         return  i; */

/*     } */

	

/*     int  atMost( int x ) const  { */

/*         int  d = 0,  i = x; */

/*         while( true )  { */

/*             if( i < 0  ||  d >= A.size() )   return  -1; */

/*             u64  m = A[d][i/64] & ~( ( ~(u64)1 ) << ( i % 64 ) ); */

/*             if( !m )  { ++d;  i /= 64;  --i; } */

/*             else  { */

/*                 i = i/64 * 64 + highBit( m ); */

/*                 if( d-- == 0 )  break; */

/*                 i *= 64; */

/*                 i += 63; */

/*             } */

/*         } */

/*         return  i; */

/*     } */



/*   private: */

/*     static int  highBit( u64 x )  { */

/*         if( x == 0 )  return  0; */

/*         return  63 - __builtin_clzll( x ); */

/*     } */

	

/*     static int  lowBit( u64 x )  { */

/*         if( x == 0 )  return  64; */

/*         return  __builtin_ctzll( x ); */

/*     } */

/* }; */





/* int  main() */

/* { */

/*     ios::sync_with_stdio( false ); */

/*     cin.tie( nullptr ); */

    

/*     int     N, Q; */

/*     string  A; */

/*     cin >> N >> Q >> A; */



/*     WordsizeTree  G( A ); */



/*     enum  opTypes { INSERT, ERASE, COUNT, ATLEAST, ATMOST }; */



/*     while( Q-- ) */

/*     { */

/*         int  c, k; */

/*         cin >> c >> k; */



/*         switch( c ) */

/*         { */

/*           case  INSERT: */

/*             G.insert( k );  break; */



/*           case  ERASE: */

/*             G.erase( k );   break; */



/*           case  COUNT: */

/*             cout << G.count( k ) << '\n';    break; */



/*           case  ATLEAST: */

/*             cout << G.atLeast( k ) << '\n';  break; */



/*           case  ATMOST: */

/*             cout << G.atMost( k ) << '\n';   break; */

            

/*           default: */

/*             assert( false ); */

/*         } */

/*     } */

	

/*     return  0; */

/* } */



// 118ms
/* https://judge.yosupo.jp/submission/73350 */
/* #line 1 "test/library_checker/datastructure/predecessor_problem.test.cpp" */

/* #define PROBLEM "https://judge.yosupo.jp/problem/predecessor_problem" */

/* #line 1 "my_template.hpp" */

/* #include <bits/stdc++.h> */

/* #include <unistd.h> */



/* using namespace std; */



/* using ll = long long; */

/* using ll8 = __int128; */

/* using pi = pair<ll, ll>; */

/* using vi = vector<ll>; */

/* using uint = unsigned int; */

/* using ull = unsigned long long; */



/* template <class T> */

/* using vc = vector<T>; */

/* template <class T> */

/* using vvc = vector<vc<T>>; */

/* template <class T> */

/* using vvvc = vector<vvc<T>>; */

/* template <class T> */

/* using vvvvc = vector<vvvc<T>>; */

/* template <class T> */

/* using vvvvvc = vector<vvvvc<T>>; */

/* template <class T> */

/* using pq = priority_queue<T>; */

/* template <class T> */

/* using pqg = priority_queue<T, vector<T>, greater<T>>; */



/* #define vec(type, name, ...) vector<type> name(__VA_ARGS__) */

/* #define VEC(type, name, size) \ */

/*   vector<type> name(size);    \ */

/*   IN(name) */

/* #define vv(type, name, h, ...) \ */

/*   vector<vector<type>> name(h, vector<type>(__VA_ARGS__)) */

/* #define VV(type, name, h, w)                     \ */

/*   vector<vector<type>> name(h, vector<type>(w)); \ */

/*   IN(name) */

/* #define vvv(type, name, h, w, ...)   \ */

/*   vector<vector<vector<type>>> name( \ */

/*       h, vector<vector<type>>(w, vector<type>(__VA_ARGS__))) */

/* #define vvvv(type, name, a, b, c, ...)       \ */

/*   vector<vector<vector<vector<type>>>> name( \ */

/*       a, vector<vector<vector<type>>>(       \ */

/*              b, vector<vector<type>>(c, vector<type>(__VA_ARGS__)))) */



/* #define FOR_(n) for (ll _ = 0; (_) < (ll)(n); ++(_)) */

/* #define FOR(i, n) for (ll i = 0; (i) < (ll)(n); ++(i)) */

/* #define FOR3(i, m, n) for (ll i = (m); (i) < (ll)(n); ++(i)) */

/* #define FOR_R(i, n) for (ll i = (ll)(n)-1; (i) >= 0; --(i)) */

/* #define FOR3_R(i, m, n) for (ll i = (ll)(n)-1; (i) >= (ll)(m); --(i)) */

/* #define FOR_subset(t, s) for (ll t = s; t >= 0; t = (t == 0 ? -1 : (t - 1) & s)) */

/* #define all(x) x.begin(), x.end() */

/* #define len(x) ll(x.size()) */

/* #define elif else if */



/* #define eb emplace_back */

/* #define mp make_pair */

/* #define mt make_tuple */

/* #define fi first */

/* #define se second */



/* int popcnt(int x) { return __builtin_popcount(x); } */

/* int popcnt(uint x) { return __builtin_popcount(x); } */

/* int popcnt(ll x) { return __builtin_popcountll(x); } */

/* int popcnt(ull x) { return __builtin_popcountll(x); } */

/* // (0, 1, 2, 3, 4) -> (-1, 0, 1, 1, 2) */

/* int topbit(int x) { return 31 - __builtin_clz(x); } */

/* int topbit(uint x) { return 31 - __builtin_clz(x); } */

/* int topbit(ll x) { return 63 - __builtin_clzll(x); } */

/* int topbit(ull x) { return 63 - __builtin_clzll(x); } */

/* // (0, 1, 2, 3, 4) -> (32 or 64, 0, 1, 0, 2) */

/* int lowbit(int x) { return 31 - __builtin_clz(x); } */

/* int lowbit(uint x) { return 31 - __builtin_clz(x); } */

/* int lowbit(ll x) { return 63 - __builtin_clzll(x); } */

/* int lowbit(ull x) { return 63 - __builtin_clzll(x); } */



/* ll ceil(ll x, ll y) { return (x > 0 ? (x + y - 1) / y : x / y); } */

/* ll floor(ll x, ll y) { return (x > 0 ? x / y : (x - y + 1) / y); } */

/* pi divmod(ll x, ll y) { */

/*   ll q = floor(x, y); */

/*   return {q, x - q * y}; */

/* } */



/* namespace yosupo_IO { */



/* template <class T> */

/* using is_signed_int128 = */

/*     typename std::conditional<is_same<T, __int128_t>::value */

/*                                   || is_same<T, __int128>::value, */

/*                               true_type, false_type>::type; */



/* template <class T> */

/* using is_unsigned_int128 = */

/*     typename std::conditional<is_same<T, __uint128_t>::value */

/*                                   || is_same<T, unsigned __int128>::value, */

/*                               true_type, false_type>::type; */



/* template <class T> */

/* using make_unsigned_int128 = */

/*     typename std::conditional<is_same<T, __int128_t>::value, __uint128_t, */

/*                               unsigned __int128>; */



/* template <class T> */

/* using is_integral = */

/*     typename std::conditional<std::is_integral<T>::value */

/*                                   || is_signed_int128<T>::value */

/*                                   || is_unsigned_int128<T>::value, */

/*                               true_type, false_type>::type; */



/* template <class T> */

/* using is_signed_int = */

/*     typename std::conditional<(is_integral<T>::value */

/*                                && std::is_signed<T>::value) */

/*                                   || is_signed_int128<T>::value, */

/*                               true_type, false_type>::type; */



/* template <class T> */

/* using is_unsigned_int = */

/*     typename std::conditional<(is_integral<T>::value */

/*                                && std::is_unsigned<T>::value) */

/*                                   || is_unsigned_int128<T>::value, */

/*                               true_type, false_type>::type; */



/* template <class T> */

/* using to_unsigned = typename std::conditional< */

/*     is_signed_int128<T>::value, make_unsigned_int128<T>, */

/*     typename std::conditional<std::is_signed<T>::value, std::make_unsigned<T>, */

/*                               std::common_type<T>>::type>::type; */



/* template <class T> */

/* using is_integral_t = enable_if_t<is_integral<T>::value>; */



/* template <class T> */

/* using is_signed_int_t = enable_if_t<is_signed_int<T>::value>; */



/* template <class T> */

/* using is_unsigned_int_t = enable_if_t<is_unsigned_int<T>::value>; */



/* namespace detail { */

/* template <typename T, decltype(&T::is_modint) = &T::is_modint> */

/* std::true_type check_value(int); */

/* template <typename T> */

/* std::false_type check_value(long); */

/* } // namespace detail */



/* template <typename T> */

/* struct is_modint : decltype(detail::check_value<T>(0)) {}; */



/* template <typename T> */

/* using is_modint_t = enable_if_t<is_modint<T>::value>; */



/* template <class T> */

/* using to_unsigned_t = typename to_unsigned<T>::type; */



/* struct Scanner { */

/* public: */

/*   Scanner(const Scanner &) = delete; */

/*   Scanner &operator=(const Scanner &) = delete; */



/*   Scanner(FILE *fp) : fd(fileno(fp)) { line[0] = 127; } */



/*   void read() {} */

/*   template <class H, class... T> */

/*   void read(H &h, T &... t) { */

/*     bool f = read_single(h); */

/*     assert(f); */

/*     read(t...); */

/*   } */



/*   int read_unsafe() { return 0; } */

/*   template <class H, class... T> */

/*   int read_unsafe(H &h, T &... t) { */

/*     bool f = read_single(h); */

/*     if (!f) return 0; */

/*     return 1 + read_unsafe(t...); */

/*   } */



/*   int close() { return ::close(fd); } */



/* private: */

/*   static constexpr int SIZE = 1 << 15; */



/*   int fd = -1; */

/*   array<char, SIZE + 1> line; */

/*   int st = 0, ed = 0; */

/*   bool eof = false; */



/*   bool read_single(string &ref) { */

/*     if (!skip_space()) return false; */

/*     ref = ""; */

/*     while (true) { */

/*       char c = top(); */

/*       if (c <= ' ') break; */

/*       ref += c; */

/*       st++; */

/*     } */

/*     return true; */

/*   } */

/*   bool read_single(double &ref) { */

/*     string s; */

/*     if (!read_single(s)) return false; */

/*     ref = std::stod(s); */

/*     return true; */

/*   } */



/*   template <class T, enable_if_t<is_same<T, char>::value> * = nullptr> */

/*   bool read_single(T &ref) { */

/*     if (!skip_space<50>()) return false; */

/*     ref = top(); */

/*     st++; */

/*     return true; */

/*   } */



/*   template <class T, is_signed_int_t<T> * = nullptr, */

/*             enable_if_t<!is_same<T, char>::value> * = nullptr> */

/*   bool read_single(T &sref) { */

/*     using U = to_unsigned_t<T>; */

/*     if (!skip_space<50>()) return false; */

/*     bool neg = false; */

/*     if (line[st] == '-') { */

/*       neg = true; */

/*       st++; */

/*     } */

/*     U ref = 0; */

/*     do { ref = 10 * ref + (line[st++] & 0x0f); } while (line[st] >= '0'); */

/*     sref = neg ? -ref : ref; */

/*     return true; */

/*   } */

/*   template <class U, is_unsigned_int_t<U> * = nullptr, */

/*             enable_if_t<!is_same<U, char>::value> * = nullptr> */

/*   bool read_single(U &ref) { */

/*     if (!skip_space<50>()) return false; */

/*     ref = 0; */

/*     do { ref = 10 * ref + (line[st++] & 0x0f); } while (line[st] >= '0'); */

/*     return true; */

/*   } */



/*   bool reread() { */

/*     if (ed - st >= 50) return true; */

/*     if (st > SIZE / 2) { */

/*       std::memmove(line.data(), line.data() + st, ed - st); */

/*       ed -= st; */

/*       st = 0; */

/*     } */

/*     if (eof) return false; */

/*     auto u = ::read(fd, line.data() + ed, SIZE - ed); */

/*     if (u == 0) { */

/*       eof = true; */

/*       line[ed] = '\0'; */

/*       u = 1; */

/*     } */

/*     ed += int(u); */

/*     line[ed] = char(127); */

/*     return true; */

/*   } */



/*   char top() { */

/*     if (st == ed) { */

/*       bool f = reread(); */

/*       assert(f); */

/*     } */

/*     return line[st]; */

/*   } */



/*   template <int TOKEN_LEN = 0> */

/*   bool skip_space() { */

/*     while (true) { */

/*       while (line[st] <= ' ') st++; */

/*       if (ed - st > TOKEN_LEN) return true; */

/*       if (st > ed) st = ed; */

/*       for (auto i = st; i < ed; i++) { */

/*         if (line[i] <= ' ') return true; */

/*       } */

/*       if (!reread()) return false; */

/*     } */

/*   } */

/* }; */



/* struct Printer { */

/* public: */

/*   template <char sep = ' ', bool F = false> */

/*   void write() {} */

/*   template <char sep = ' ', bool F = false, class H, class... T> */

/*   void write(const H &h, const T &... t) { */

/*     if (F) write_single(sep); */

/*     write_single(h); */

/*     write<true>(t...); */

/*   } */

/*   template <char sep = ' ', class... T> */

/*   void writeln(const T &... t) { */

/*     write<sep>(t...); */

/*     write_single('\n'); */

/*   } */



/*   Printer(FILE *_fp) : fd(fileno(_fp)) {} */

/*   ~Printer() { flush(); } */



/*   int close() { */

/*     flush(); */

/*     return ::close(fd); */

/*   } */



/*   void flush() { */

/*     if (pos) { */

/*       auto res = ::write(fd, line.data(), pos); */

/*       assert(res != -1); */

/*       pos = 0; */

/*     } */

/*   } */



/* private: */

/*   static array<array<char, 2>, 100> small; */

/*   static array<unsigned long long, 20> tens; */



/*   static constexpr size_t SIZE = 1 << 15; */

/*   int fd; */

/*   array<char, SIZE> line; */

/*   size_t pos = 0; */

/*   std::stringstream ss; */



/*   template <class T, enable_if_t<is_same<char, T>::value> * = nullptr> */

/*   void write_single(const T &val) { */

/*     if (pos == SIZE) flush(); */

/*     line[pos++] = val; */

/*   } */



/*   template <class T, is_signed_int_t<T> * = nullptr, */

/*             enable_if_t<!is_same<char, T>::value> * = nullptr> */

/*   void write_single(const T &val) { */

/*     using U = to_unsigned_t<T>; */

/*     if (val == 0) { */

/*       write_single('0'); */

/*       return; */

/*     } */

/*     if (pos > SIZE - 50) flush(); */

/*     U uval = val; */

/*     if (val < 0) { */

/*       write_single('-'); */

/*       uval = -uval; */

/*     } */

/*     write_unsigned(uval); */

/*   } */



/*   template <class T, is_modint_t<T> * = nullptr> */

/*   void write_single(const T &val) { */

/*     write_single(val.val); */

/*   } */



/*   static int bsr(unsigned int n) { */

/*     return 8 * (int)sizeof(unsigned int) - 1 - __builtin_clz(n); */

/*   } */

/*   static int bsr(unsigned long n) { */

/*     return 8 * (int)sizeof(unsigned long) - 1 - __builtin_clzl(n); */

/*   } */

/*   static int bsr(unsigned long long n) { */

/*     return 8 * (int)sizeof(unsigned long long) - 1 - __builtin_clzll(n); */

/*   } */



/*   template <class U, is_unsigned_int_t<U> * = nullptr> */

/*   void write_single(U uval) { */

/*     if (uval == 0) { */

/*       write_single('0'); */

/*       return; */

/*     } */

/*     if (pos > SIZE - 50) flush(); */



/*     write_unsigned(uval); */

/*   } */



/*   template <class U, is_unsigned_int_t<U> * = nullptr> */

/*   static int calc_len(U x) { */

/*     int i = (bsr(1ULL * x) * 3 + 3) / 10; */

/*     if (x < tens[i]) */

/*       return i; */

/*     else */

/*       return i + 1; */

/*   } */



/*   template <class U, is_unsigned_int_t<U> * = nullptr, */

/*             enable_if_t<2 >= sizeof(U)> * = nullptr> */

/*   void write_unsigned(U uval) { */

/*     size_t len = calc_len(uval); */

/*     pos += len; */



/*     char *ptr = line.data() + pos; */

/*     while (uval >= 100) { */

/*       ptr -= 2; */

/*       memcpy(ptr, small[uval % 100].data(), 2); */

/*       uval /= 100; */

/*     } */

/*     if (uval >= 10) { */

/*       memcpy(ptr - 2, small[uval].data(), 2); */

/*     } else { */

/*       *(ptr - 1) = char('0' + uval); */

/*     } */

/*   } */



/*   template <class U, is_unsigned_int_t<U> * = nullptr, */

/*             enable_if_t<4 == sizeof(U)> * = nullptr> */

/*   void write_unsigned(U uval) { */

/*     array<char, 8> buf; */

/*     memcpy(buf.data() + 6, small[uval % 100].data(), 2); */

/*     memcpy(buf.data() + 4, small[uval / 100 % 100].data(), 2); */

/*     memcpy(buf.data() + 2, small[uval / 10000 % 100].data(), 2); */

/*     memcpy(buf.data() + 0, small[uval / 1000000 % 100].data(), 2); */



/*     if (uval >= 100000000) { */

/*       if (uval >= 1000000000) { */

/*         memcpy(line.data() + pos, small[uval / 100000000 % 100].data(), 2); */

/*         pos += 2; */

/*       } else { */

/*         line[pos] = char('0' + uval / 100000000); */

/*         pos++; */

/*       } */

/*       memcpy(line.data() + pos, buf.data(), 8); */

/*       pos += 8; */

/*     } else { */

/*       size_t len = calc_len(uval); */

/*       memcpy(line.data() + pos, buf.data() + (8 - len), len); */

/*       pos += len; */

/*     } */

/*   } */



/*   template <class U, is_unsigned_int_t<U> * = nullptr, */

/*             enable_if_t<8 == sizeof(U)> * = nullptr> */

/*   void write_unsigned(U uval) { */

/*     size_t len = calc_len(uval); */

/*     pos += len; */



/*     char *ptr = line.data() + pos; */

/*     while (uval >= 100) { */

/*       ptr -= 2; */

/*       memcpy(ptr, small[uval % 100].data(), 2); */

/*       uval /= 100; */

/*     } */

/*     if (uval >= 10) { */

/*       memcpy(ptr - 2, small[uval].data(), 2); */

/*     } else { */

/*       *(ptr - 1) = char('0' + uval); */

/*     } */

/*   } */



/*   template <class U, enable_if_t<is_unsigned_int128<U>::value> * = nullptr> */

/*   void write_unsigned(U uval) { */

/*     static array<char, 50> buf; */

/*     size_t len = 0; */

/*     while (uval > 0) { */

/*       buf[len++] = char((uval % 10) + '0'); */

/*       uval /= 10; */

/*     } */

/*     std::reverse(buf.begin(), buf.begin() + len); */

/*     memcpy(line.data() + pos, buf.data(), len); */

/*     pos += len; */

/*   } */



/*   void write_single(const std::string &s) { */

/*     for (char c: s) write_single(c); */

/*   } */

/*   void write_single(const char *s) { */

/*     size_t len = strlen(s); */

/*     for (size_t i = 0; i < len; i++) write_single(s[i]); */

/*   } */

/*   template <class T> */

/*   void write_single(const std::vector<T> &val) { */

/*     auto n = val.size(); */

/*     for (size_t i = 0; i < n; i++) { */

/*       if (i) write_single(' '); */

/*       write_single(val[i]); */

/*     } */

/*   } */

/* }; */



/* array<array<char, 2>, 100> Printer::small = [] { */

/*   array<array<char, 2>, 100> table; */

/*   for (int i = 0; i <= 99; i++) { */

/*     table[i][1] = char('0' + (i % 10)); */

/*     table[i][0] = char('0' + (i / 10 % 10)); */

/*   } */

/*   return table; */

/* }(); */

/* array<ull, 20> Printer::tens = [] { */

/*   array<ull, 20> table; */

/*   for (int i = 0; i < 20; i++) { */

/*     table[i] = 1; */

/*     for (int j = 0; j < i; j++) { table[i] *= 10; } */

/*   } */

/*   return table; */

/* }(); */



/* } // namespace yosupo_IO */



/* using namespace yosupo_IO; */

/* Scanner scanner = Scanner(stdin); */

/* Printer printer = Printer(stdout); */



/* #define INT(...)   \ */

/*   int __VA_ARGS__; \ */

/*   IN(__VA_ARGS__) */

/* #define LL(...)   \ */

/*   ll __VA_ARGS__; \ */

/*   IN(__VA_ARGS__) */

/* #define STR(...)      \ */

/*   string __VA_ARGS__; \ */

/*   IN(__VA_ARGS__) */

/* #define CHR(...)    \ */

/*   char __VA_ARGS__; \ */

/*   IN(__VA_ARGS__) */

/* #define DBL(...)           \ */

/*   long double __VA_ARGS__; \ */

/*   IN(__VA_ARGS__) */

/* void scan(int &a) { scanner.read(a); } */

/* void scan(ll &a) { scanner.read(a); } */

/* void scan(ull &a) { scanner.read(a); } */

/* void scan(char &a) { scanner.read(a); } */

/* void scan(double &a) { scanner.read(a); } */

/* // void scan(long double &a) { scanner.read(a); } */

/* void scan(string &a) { scanner.read(a); } */

/* template <class T> */

/* void scan(pair<T, T> &p) { */

/*   scan(p.first), scan(p.second); */

/* } */

/* template <class T> */

/* void scan(tuple<T, T, T> &p) { */

/*   scan(get<0>(p)), scan(get<1>(p)), scan(get<2>(p)); */

/* } */

/* template <class T> */

/* void scan(tuple<T, T, T, T> &p) { */

/*   scan(get<0>(p)), scan(get<1>(p)), scan(get<2>(p)), scan(get<3>(p)); */

/* } */

/* template <class T> */

/* void scan(vector<T> &a) { */

/*   for (auto &&i: a) scan(i); */

/* } */

/* template <class T> // modint */

/* void scan(T &a) { */

/*   ll x; */

/*   scanner.read(x); */

/*   a = x; */

/* } */

/* void IN() {} */

/* template <class Head, class... Tail> */

/* void IN(Head &head, Tail &... tail) { */

/*   scan(head); */

/*   IN(tail...); */

/* } */



/* vi s_to_vi(string S, char first_char = 'a') { */

/*   vi A(S.size()); */

/*   FOR(i, S.size()) { A[i] = S[i] - first_char; } */

/*   return A; */

/* } */



/* void print() { printer.writeln(); } */

/* template <class Head, class... Tail> */

/* void print(Head &&head, Tail &&... tail) { */

/*   printer.write(head); */

/*   if (sizeof...(Tail)) printer.write(' '); */

/*   print(forward<Tail>(tail)...); */

/* } */



/* void YES(bool t = 1) { print(t ? "YES" : "NO"); } */

/* void NO(bool t = 1) { YES(!t); } */

/* void Yes(bool t = 1) { print(t ? "Yes" : "No"); } */

/* void No(bool t = 1) { Yes(!t); } */

/* void yes(bool t = 1) { print(t ? "yes" : "no"); } */

/* void no(bool t = 1) { yes(!t); } */



/* template <typename T> */

/* vector<T> cumsum(vector<T> &A) { */

/*   int N = A.size(); */

/*   vector<T> B(N + 1); */

/*   B[0] = T(0); */

/*   FOR(i, N) { B[i + 1] = B[i] + A[i]; } */

/*   return B; */

/* } */



/* vc<int> bin_count(vi &A, int size) { */

/*   vc<int> C(size); */

/*   for (auto &x: A) { ++C[x]; } */

/*   return C; */

/* } */



/* template <typename T> */

/* vector<int> argsort(vector<T> &A) { */

/*   vector<int> ids(A.size()); */

/*   iota(all(ids), 0); */

/*   sort(all(ids), */

/*        [&](int i, int j) { return A[i] < A[j] || (A[i] == A[j] && i < j); }); */

/*   return ids; */

/* } */



/* ll binary_search(function<bool(ll)> check, ll ok, ll ng) { */

/*   assert(check(ok)); */

/*   while (abs(ok - ng) > 1) { */

/*     auto x = (ng + ok) / 2; */

/*     if (check(x)) */

/*       ok = x; */

/*     else */

/*       ng = x; */

/*   } */

/*   return ok; */

/* } */



/* template <class T, class S> */

/* inline bool chmax(T &a, const S &b) { */

/*   return (a < b ? a = b, 1 : 0); */

/* } */

/* template <class T, class S> */

/* inline bool chmin(T &a, const S &b) { */

/*   return (a > b ? a = b, 1 : 0); */

/* } */



/* #define SUM(v) accumulate(all(v), 0LL) */

/* #define MIN(v) *min_element(all(v)) */

/* #define MAX(v) *max_element(all(v)) */

/* #define LB(c, x) distance((c).begin(), lower_bound(all(c), (x))) */

/* #define UB(c, x) distance((c).begin(), upper_bound(all(c), (x))) */

/* #define UNIQUE(x) sort(all(x)), x.erase(unique(all(x)), x.end()) */

/* #line 1 "ds/fastset.hpp" */

/* struct FastSet { */

/*   using uint = unsigned; */

/*   using ull = unsigned long long; */



/*   int bsr(ull x) { return 63 - __builtin_clzll(x); } */

/*   int bsf(ull x) { return __builtin_ctzll(x); } */



/*   static constexpr uint B = 64; */

/*   int n, lg; */

/*   vc<vc<ull>> seg; */

/*   FastSet(int _n) : n(_n) { */

/*     do { */

/*       seg.push_back(vc<ull>((_n + B - 1) / B)); */

/*       _n = (_n + B - 1) / B; */

/*     } while (_n > 1); */

/*     lg = int(seg.size()); */

/*   } */

/*   bool operator[](int i) const { return (seg[0][i / B] >> (i % B) & 1) != 0; } */

/*   void insert(int i) { */

/*     for (int h = 0; h < lg; h++) { */

/*       seg[h][i / B] |= 1ULL << (i % B); */

/*       i /= B; */

/*     } */

/*   } */

/*   void erase(int i) { */

/*     for (int h = 0; h < lg; h++) { */

/*       seg[h][i / B] &= ~(1ULL << (i % B)); */

/*       if (seg[h][i / B]) */

/*         break; */

/*       i /= B; */

/*     } */

/*   } */

/*   // x以上最小の要素 */



/*   int next(int i) { */

/*     for (int h = 0; h < lg; h++) { */

/*       if (i / B == seg[h].size()) */

/*         break; */

/*       ull d = seg[h][i / B] >> (i % B); */

/*       if (!d) { */

/*         i = i / B + 1; */

/*         continue; */

/*       } */

/*       // find */



/*       i += bsf(d); */

/*       for (int g = h - 1; g >= 0; g--) { */

/*         i *= B; */

/*         i += bsf(seg[g][i / B]); */

/*       } */

/*       return i; */

/*     } */

/*     return n; */

/*   } */

/*   // x以下最大の要素 */



/*   int prev(int i) { */

/*     if(i < 0) return -1; */

/*     chmin(i, n - 1); */

/*     for (int h = 0; h < lg; h++) { */

/*       if (i == -1) */

/*         break; */

/*       ull d = seg[h][i / B] << (63 - i % 64); */

/*       if (!d) { */

/*         i = i / B - 1; */

/*         continue; */

/*       } */

/*       // find */



/*       i += bsr(d) - (B - 1); */

/*       for (int g = h - 1; g >= 0; g--) { */

/*         i *= B; */

/*         i += bsr(seg[g][i / B]); */

/*       } */

/*       return i; */

/*     } */

/*     return -1; */

/*   } */

/*   void debug(){ */

/*     for(int i=0;i<n;++i) cout << (*this)[i]; */

/*     cout << endl; */

/*   } */

/* }; */

/* #line 4 "test/library_checker/datastructure/predecessor_problem.test.cpp" */



/* void solve() { */

/*   LL(N, Q); */

/*   FastSet ss(N); */

/*   STR(S); */

/*   FOR(x, N) { */

/*     if (S[x] == '1') ss.insert(x); */

/*   } */



/*   FOR(_, Q) { */

/*     LL(t, k); */

/*     if (t == 0) { ss.insert(k); } */

/*     elif (t == 1) { ss.erase(k); } */

/*     elif (t == 2) { print(ss[k]); } */

/*     elif (t == 3) { */

/*       ll x = ss.next(k); */

/*       if (x == N) x = -1; */

/*       print(x); */

/*     } */

/*     elif (t == 4) { print(ss.prev(k)); } */

/*   } */

/* } */



/* signed main() { */

/*   cin.tie(nullptr); */

/*   ios::sync_with_stdio(false); */

/*   cout << setprecision(15); */



/*   solve(); */



/*   return 0; */

/* } */
