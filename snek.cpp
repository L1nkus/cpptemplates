#include <bits/stdc++.h>
#define pb push_back #define mp make_pair
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

bool isvisited(vector<bool> visited[]){
    FOR(i,0,n)
        FOR(x,0,n)
            if(!visited[i][x])
                return false;
    return true;
}

void snek(vector<bool> visited[], pi pos){
    //cout << "X: " << pos.F << " Y: " << pos.S << '\n';
    if(pos.F == n-1 && pos.S == n-1){
        //cout << "REACHED\n";
        if(isvisited(visited)){
            ans++;
            return;
        }
        else
            return;
    }
    if( pos.F>0 && pos.F<n-1 && (pos.S == 0 || pos.S == n-1) && !visited[pos.F-1][pos.S] && !visited[pos.F+1][pos.S])
        return;
    if( pos.S>0 && pos.S<n-1 && (pos.F == 0 || pos.F == n-1) && !visited[pos.F][pos.S-1] && !visited[pos.F][pos.S+1])
        return;
    if( pos.F>0 && pos.F<n-1 && pos.S>0 && pos.S<n-1 && (( visited[pos.F][pos.S-1] && visited[pos.F][pos.S+1] && !visited[pos.F-1][pos.S] && !visited[pos.F+1][pos.S] ) || (visited[pos.F-1][pos.S] && visited[pos.F+1][pos.S] && !visited[pos.F][pos.S-1] && !visited[pos.F][pos.S+1] )))
        return;
    if(pos.F && !visited[pos.F-1][pos.S]){
        visited[pos.F-1][pos.S]=1;
        snek(visited,{pos.F-1,pos.S});
        visited[pos.F-1][pos.S]=0;
    }
    if(pos.F<n-1 && !visited[pos.F+1][pos.S]){
        visited[pos.F+1][pos.S]=1;
        snek(visited,{pos.F+1,pos.S});
        visited[pos.F+1][pos.S]=0;
    }
    //cout << "  X: " << pos.F << " Y: " << pos.S << " " << s  << " " << !visited[pos.F][pos.S-1] << '\n';
    if(pos.S>0 && !visited[pos.F][pos.S-1]){
        visited[pos.F][pos.S-1]=1;
        snek(visited,{pos.F,pos.S-1});
        visited[pos.F][pos.S-1]=0;
    }
    //auto s = pos.S<n-1;
    //cout << "  X: " << pos.F << " Y: " << pos.S << " " << s  << " " << !visited[pos.F][pos.S+1] << '\n';
    if(pos.S<n-1 && !visited[pos.F][pos.S+1]){
        visited[pos.F][pos.S+1]=1;
        snek(visited,{pos.F,pos.S+1});
        visited[pos.F][pos.S+1]=0;
    }
    return;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    vector<bool> visited[n];
    FORR(i,visited)
        i.resize(n,0);
    if(n==1)
        REE(1);
    visited[0][0]=true;
    visited[0][1]=true;
    snek(visited, {0,1});
    cout << ans*2 << '\n';

}

