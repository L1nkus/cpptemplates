#include <bits/stdc++.h>
using namespace std;
#define whatis(x) cerr << #x << " is " << x << endl;

/* vector<array<int,5>> vec; //{a,b,floor(a,b),x,y} */
vector<vector<int>> vec; //{a,b,floor(a,b),x,y}

int mulInv(int a, int b) {
	int b0 = b;
	int x0 = 0;
	int x1 = 1;
 
	if (b == 1) {
		return 1;
	}
 
	while (a > 1) {
		int q = a / b;
		int amb = a % b;
		a = b;
		b = amb;
 
		int xqx = x1 - q * x0;
		x1 = x0;
		x0 = xqx;
	}
 
	if (x1 < 0) {
		x1 += b0;
	}
 
	return x1;
}
 
// to dziala tylko dla wzglednie pierwszych. musisz recznie conv do tego
int crt(vector<int> a, vector<int> n){
    // long longi?
    int prod = 1;
    for(int i = 0; i < n.size(); ++i)
        prod *= n[i];
 
	int sm = 0;
	for (int i = 0; i < n.size(); i++) {
		int p = prod / n[i];
		sm += a[i] * mulInv(p, n[i])*p;
        vec.push_back({n[i], a[i], p, mulInv(p,n[i]), a[i] * mulInv(p, n[i])*p});
	}
 
	/* return sm % prod; */
	return (sm % prod + prod) % prod;
}

int main(int argc, char *argv[]){
    ios_base::sync_with_stdio(0); cin.tie(0);
    /* int x, y; */
    /* int a, b; */
    /* cout << crt(a, b, &x, &y) << '\n'; */
	/* vector<int> n = { 4, 9, 25 }; */
	/* vector<int> a = { 3, 6, -2 }; */
	vector<int> n = { 3, 5, 16 };
	vector<int> a = { 1, 1, 0 };
	/* vector<int> n = { 49, 9, 25 }; */
	/* vector<int> a = { 12, 5, 21 }; */
	cout << crt(a,n) << endl;

    /* for(auto &i : vec){ */
    /*     for(auto &x: i){ */
    /*         cout << x << ' '; */
    /*     } */
    /*     cout << '\n'; */
    /* } */
    cout << '\n';
    /* cout << to_table() << '\n'; */
    /* whatis(to_table()) */
}

