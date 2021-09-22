#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, l, r) for(int i = (l); i <= (r); ++i)
#define REP(i, n) FOR(i, 0, (n) - 1)
#define ssize(x) int(x.size())
template<class A, class B> auto& operator<<(ostream &o, pair<A, B> p) {
	return o << '(' << p.first << ", " << p.second << ')';
}
template<class T> auto operator<<(ostream &o, T x) -> decltype(x.end(), o) {
	o << '{'; int i = 0; for(auto e : x) o << (", ")+2*!i++ << e; return o << '}';
}
#ifdef DEBUG
#define debug(x...) cerr << "[" #x "]: ", [](auto... $) {((cerr << $ << "; "), ...); }(x), cerr << '\n'
#else
#define debug(...) {}
#endif
 
/*
 * Status: Przetestowane na zadankach
 * Opis: Implict Treap
 * Czas: wszystko w O(\log n)
 * Użycie:
 *   wszystko indexowane od 0
 *   insert(key, val) insertuję na pozycję key
 *   treap[i] zwraca i-tą wartość
 */
// Tomasz Nowak, Michał Staniewski
// https://codeforces.com/group/NHALkPSUcR/contest/103145/problem/F

mt19937 rng_key(0);	
 
template<class T>
struct Treap {
	struct Node {
		int prio, cnt, lazy = 0;
		T val;
		Node *l = nullptr, *r = nullptr, *p = nullptr;
		Node(T _val) : prio((int) rng_key()), val(_val) {}
		~Node() {
			if(l) delete l;
			if(r) delete r;
		}
	};
	~Treap() { if(root) delete root; }
	using pNode = Node*;
	pNode root = nullptr;
 
	void add_lazy(pNode t) {
		if(t) t->lazy ^= 1;
	}
	void propagate(pNode t) {
		if(t && t->lazy) {
			swap(t->l, t->r);
			add_lazy(t->l);
			add_lazy(t->r);
			t->lazy = 0;
		}
	}
 
	int cnt(pNode t) { return t ? t->cnt : 0; }
	void update(pNode t) {
		if(!t) return;
		t->cnt = cnt(t->l) + cnt(t->r) + 1;
		if(t->l) t->l->p = t;
		if(t->r) t->r->p = t;
	}
 
	void split(pNode t, int key, pNode &l, pNode &r) {
		propagate(t);
		if(!t) l = r = nullptr;
		else if(key <= cnt(t->l)) 
			split(t->l, key, l, t->l), r = t;
		else
			split(t->r, key - cnt(t->l) - 1, t->r, r), l = t;
		update(t);
	}
 
	void merge(pNode &t, pNode l, pNode r) {
		propagate(l);
		propagate(r);
		if(!l || !r) t = (l ? l : r);
		else if(l->prio > r->prio)
			merge(l->r, l->r, r), t = l;
		else
			merge(r->l, l, r->l), t = r;
		update(t);
	}
 
	pNode insert(int key, T val) {
		pNode n = new Node(val), t;
		split(root, key, root, t);
		merge(root, root, n);
		merge(root, root, t);
		return n;
	}
 
	pNode emplace_back(T val) {
		pNode n = new Node(val);
		merge(root, root, n);
		return n;
	}
 
	void reverse(int l, int r) {
		pNode L, R;
		split(root, r + 1, root, R);	
		split(root, l, L, root);
		add_lazy(root);
		merge(root, L, root);
		merge(root, root, R);
	}
 
	T find_rec(int key, pNode t) {
		propagate(t);
		if(key < cnt(t->l))
			return find_rec(key, t->l);
		else if(key == cnt(t->l))
			return t->val;
		else
			return find_rec(key - cnt(t->l) - 1, t->r);
	}
 
	T find(int key) { 
		return find_rec(key, root);
	}
 
	void prop_up(pNode t) {
		if(!t) return;
		prop_up(t->p);
		propagate(t);
	}
	int where(pNode t) {
		if(!t->p) return cnt(t->l);
		if(t == t->p->r) 
			return where(t->p) + cnt(t->l) + 1;
		else
			return where(t->p) - cnt(t->r) - 1;
	}
};
 
int main() {
	cin.tie(0)->sync_with_stdio(0);
 
	int T;
	cin >> T;
 
	REP(_t, T) {
		int n, m;
		cin >> n >> m;
 
		Treap<int> perm;
		vector<Treap<int>::pNode> ptr(n);
		REP(i, n) {
			int x;
			cin >> x;
			x--;
			ptr[x] = perm.emplace_back(x);
		}
 
		Treap<int> perm_ptr;
		vector<Treap<int>::pNode> ptr2(n);
		REP(i, n) {
			ptr2[i] = perm_ptr.emplace_back(i);
		}
 
		REP(j, m) {
			int op;
			cin >> op;
 
			if(op == 1) {
				int L, R;
				cin >> L >> R;
				L--, R--;
 
				perm.reverse(L, R);
			}
			else if(op == 2) {
				int L, R;
				cin >> L >> R;
				L--, R--;
 
				perm_ptr.reverse(L, R);
			}
			else if(op == 3) {
				int i, v;
				cin >> i >> v;
				i--, v--;
 
				auto p = perm.insert(i, ssize(ptr));
				auto p2 = perm_ptr.insert(v, ssize(ptr));
				ptr.emplace_back(p);
				ptr2.emplace_back(p2);
			}
			else if(op == 4) {
				int i;
				cin >> i;
				i--;
 
				int x = perm.find(i);
				perm_ptr.prop_up(ptr2[x]);
				cout << perm_ptr.where(ptr2[x]) + 1 << "\n";
			}
			else if(op == 5) {
				int v;
				cin >> v;
				v--;
 
				int x = perm_ptr.find(v);
				perm.prop_up(ptr[x]);
				cout << perm.where(ptr[x]) + 1 << "\n";
			}
		}
 
	}
}
