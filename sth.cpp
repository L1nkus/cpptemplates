#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define ll long long
#define ull unsigned long long
#define all(a) (a.begin()),(a.end())
#define ZERO(a) meset(a,0,sizeof(a))
#define FOR(x,val,to) for(int x=(val);x<int((to));x++)
#define FORE(x,val,to) for(auto x=(val);x<=(to);x++)
#define FORR(x,arr) for(auto &x: arr)
#define FORRC(x,arr) for(auto const &x: arr)
#define PRINT(arr) {copy((arr).begin(), (arr).end(), ostream_iterator<int>(cout, " "));cout<<'\n';}
#define REE(s_) {cout<<s_<<'\n';return 0;} //print s_ and terminate program
#define GETVEC(vec,amount) copy_n(istream_iterator<int>(cin),(n),back_inserter((vec)))
#define GET(arr) for(auto &i: (arr)) cin>>i
#define INF 2139062143 //127 in memset -> memset(arr,127,size)
#define SINF 1061109567 //Safe INF, for graphs or 2d arrays 63 in memset(arr,63,size)
#define LL_INF 7234017283807667300 //100 in memset(arr,100,size) !!!must be LL
#define whatis(x) cerr << #x << " is " << x << endl;
typedef std::pair<int,int> pi;
typedef std::vector<long long> vll;
typedef std::vector<std::vector<int> > vvi;
using namespace std;

template<class T> ostream& operator<<(ostream &os, vector<T> V) {
  os<<"[";for(auto const &vv:V)os<<vv<<","; os<<"]";
  return os;
}
template<class L, class R> ostream& operator<<(ostream &os, pair<L, R> P) {
  os<<"("<<P.first<<","<<P.second<<")";
  return os;
}

const int sz = 1e5+2;
int t[sz*2];
int n;

int query(int l, int r){
    l += n;
    r += n;
    int ans = 0;
    for(;l < r;l/=2, r/=2){
        if(l&1)
            ans = max(ans, t[l++]);
        if(r&1)
            ans = max(ans , t[--r]);
    }
    return ans;
}

void modify(int pos, int val){
    pos += n;
    t[pos] = val;
    for(;pos > 1;pos/=2){
        t[pos/2] = max(t[pos], t[pos^1]);
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    vector<int> arr{4,1,5,6,12,4};
    n = arr.size();
    auto p = arr.begin();
    for(auto i = t+n; i < t+2*n; ++i)
        *i = *p++;
    for(int i = n-1; i > 0; --i)
        t[i] = max(t[i*2], t[i*2+1]);
    int l = 2, r = 4;
    cout << query(l-1, r);
}

