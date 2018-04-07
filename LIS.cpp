#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//Non decreasing, last in output

int main() {
	int n;
	cin >> n;
    int in[n],dit[n],ans = 1;;
	int d[n];
    d[0] = 0x7f7f7f7f;
	for (int i = 0; i < n; i++) {
        cin >> in[i];
        int *it = upper_bound(d,d+ans,in[i]);
        *it = in[i];
        ans = max(ans,int(it-d+1));
        dit[i] = it-d+1;
	}
    cout << ans << '\n';
    int out[ans];
	for (int i = n; ~--i;) {
		if (dit[i] == ans) {
            out[--ans] = in[i];
        }
	}
    for(const int &i: out)
        cout << i << ' ';
}

