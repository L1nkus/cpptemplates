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
#define PRINT(arr) copy((arr).begin(), (arr).end(), ostream_iterator<int>(cout, " "))
#define REE(s_) {cout<<s_<<'\n';return 0;} //print s_ and terminate program
#define GETVEC(vec,amount) copy_n(istream_iterator<int>(cin),(n),back_inserter((vec)))
#define GET(arr) for(auto &i: (arr)) cin>>i
#define MEMSET_INF 127 //2139062143 (USE FOR MEMSET) - memset(arr,MEMSET_INF,size)
#define INF 2139062143 //for comparison
#define ULL_INF 18446744073709551614 //for comparison
#define F first
#define S second
typedef std::pair<int,int> pi;
typedef std::vector<int> vi;
typedef std::vector<std::string> vs;
typedef std::vector<long long> vll;
typedef std::vector<std::vector<int> > vvi;
using namespace std;

int n;
vector<int> arr;
vector<int> vec;

void subset(int k){
    if(k == (int)arr.size()){
        FORR(i,vec)
            cout << i << ' ';
        cout << '\n';
        return;
    }
    subset(k+1);
    vec.push_back(arr[k]);
    subset(k+1);
    vec.pop_back();
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    string str;
    cin >> n;
    arr.resize(n);
    FOR(i,0,n)
        arr[i] = i+1;
    //subset(0);
    for(int b=0;b<(1<<n);b++){
        vector<int> v;
        for(int i=0;i<n;i++){
            if(b&(1<<i)) v.pb(arr[i]);
        }
        PRINT(v);
        cout << '\n';
    }
}

