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
#define MEMSET_INF 127 //2139062143 (USE FOR MEMSET) - memset(arr,MEMSET_INF,size)
#define INF 2139062143 //for comparison
#define ULL_INF 18446744073709551614 //for comparison
#define f first
#define s second
#define wtf(x) cerr << #x << " is " << x << endl;
#define whaits wtf
#define alive cerr << "STH" << endl;
typedef std::pair<int,int> pi;
typedef std::vector<int> vi;
typedef std::vector<std::string> vs;
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


int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, sum;
    cin >> n >> sum;
    int coins[n]; GET(coins);
    //sum = 99999999;
    //n = 10;
    //coins={1, 2, 3, 9984, 132, 22, 344, 421, 1244, 11,};
    //vector<int> arr(1'000'000'00,INF);
    vector<int> arr(1'000'000'00,0);
    //static int parent[1'000'000'00];
    //memset(&arr[0],MEMSET_INF,100000000*4);
    //arr[0] = 0;
    arr[0] = 1;
    /*FORE(i,1,sum){
        int cur =  INF;
        FORRC(x,coins){
            if(i-x<0) continue;
            if(arr[i-x]+1 < cur){
                cur = arr[i-x]+1;
                parent[i] = x;
            }
        }
        arr[i] = cur;
    }*/
    FORE(i,1,sum){
        FORRC(x,coins){
            if(i-x<0) continue;
            //if(arr[i-x] == 0) continue;
            arr[i] += arr[i-x];
        }
    }
    /*FORE(i,0,sum){
        FORRC(x,coins){
            if(i+x>sum) continue;
            if(arr[i] == 0) continue;
            ++arr[i+x];
        }
    }*/
    for(auto i =arr.begin(); i != arr.begin()+10;++i)
        cout << *i << ' ';
    cout << '\n';
    cout << arr[sum] << '\n';
    /*int cur = sum;
    while(cur){
        cout << parent[cur] << ' ' ;
        cur -= parent[cur];
    }*/
    cout << '\n';
}

