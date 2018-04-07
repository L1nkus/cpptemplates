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

int ans=0;
int n;

inline void rec(int row, bool horiz[], bool diag1[], bool diag2[], int pos[]){
    //cout << "ROW: " << row << " POS: " << pos << '\n';
    if(row++==n-1){
        ++ans;
        FOR(e,0,n)
            cout << pos[e]+1 << '\n';
        cout.put('\n');
        return;
    }
    FOR(x,0,n){
        //cout << "POS: " << x << " ROW: " << row << " Diag1: " << x+row+1 << "(" << diag1[x+row+1] << ") Diag2: " << row+n-x << "("<<diag2[row+n-x]<<")"<< '\n';
        if(!horiz[x] && !diag1[x+row+1] && !diag2[row+n-x]){
            diag1[x+row+1] = diag2[row+n-x] = horiz[x] = true;
            pos[row] = x;
            rec(row,horiz,diag1,diag2, pos);
            diag1[x+row+1] = diag2[row+n-x] = horiz[x] = false;
        }
    }
    return;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //cin >> n;
    n = 4;
    bool horiz[n+1]; bool diag1[2*n]; bool diag2[2*n];
    memset(horiz,0,n+1);
    memset(diag1,0,n << 1);
    memset(diag2,0,n << 1);
    int pos[n];
    FOR(i,0,n){
        diag1[i+1] = diag2[n-i] = horiz[i] = true;
        pos[0] = i;
        rec(0,horiz,diag1,diag2,pos);
        diag1[i+1] = diag2[n-i] = horiz[i] = false;
    }
    cout << ans << '\n';

}

