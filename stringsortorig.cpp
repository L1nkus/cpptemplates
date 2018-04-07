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

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    auto f = ifstream("cain.txt");
    vector<string> vec;
    vec.reserve(2000000);
    string tmp;
    while(f >> tmp)
        vec.pb(tmp);
    //copy_n(istream_iterator<string>(f),10000,back_inserter(vec));
    vector<string> newvec[101];
    //unordered_map<int,vector<string> > mp;
    for(auto &i:vec)
        newvec[i.size()].pb(i);
    for(auto &i:newvec)
        sort(i.begin(),i.end());
    for(auto &x:newvec)
        for(auto &i:x)
            cout << i << '\n';
    /*for(auto &i:vec)
        mp[i.size()].pb(i);
    for(auto &i:mp)
        sort(i.second.begin(),i.second.begin());
    for(auto &x:mp)
        for(auto &i:x.second)
            cout << i << '\n';*/
}

