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

int binary_search(vector<int> vec, int n){
    int it = vec.size()/2;
    int lower = 0;
    int upper = vec.size()-1;
    while(n!=vec[it]){
        if(vec[it]<n)
            lower = it+1;
        else
            upper = it;
        it = (lower+upper)/2;
    }
    return it;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    vector<int> vec{33,11,77,54,76};
    sort(all(vec));
    //int n=33;
    FORR(n,vec)
    cout << binary_search(vec, n)+1;
}

