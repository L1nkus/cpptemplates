#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int maxn=100000,maxt=200000;
 
// Fastest solution to https://codeforces.com/group/NHALkPSUcR/contest/103145/problem/F
// ~1s vs >= 2s of treaps, sqrts.
int te,n,Q,a[maxn+5],ID[maxn+5],who[2][maxt+5];
struct SplayTree{
	int pl,ro,son[maxt+5][2],fa[maxt+5],si[maxt+5];bool flip[maxt+5];
	int cmp(int p,int &k){
		if (k<=si[son[p][0]]) return 0;
		if (k==si[son[p][0]]+1) return -1;
		k-=si[son[p][0]]+1;return 1;
	}
	void Pushup(int p) {si[p]=si[son[p][0]]+1+si[son[p][1]];}
	int newnode() {pl++;son[pl][0]=son[pl][1]=fa[pl]=flip[pl]=0;si[pl]=1;return pl;}
	int BuildA(int L,int R,int pre=0){
		if (L>R) return 0; int mid=L+(R-L>>1),now=newnode();
		who[0][now]=ID[a[mid]];who[1][ID[a[mid]]]=now;
		son[now][0]=BuildA(L,mid-1,now);son[now][1]=BuildA(mid+1,R,now);fa[now]=pre;
		Pushup(now);return now;
	}
	int BuildB(int L,int R,int pre=0){
		if (L>R) return 0; int mid=L+(R-L>>1),now=newnode();
		ID[mid]=now;
		son[now][0]=BuildB(L,mid-1,now);son[now][1]=BuildB(mid+1,R,now);fa[now]=pre;
		Pushup(now);return now;
	}
	void Rotate(int &p,int d){
		int t=son[p][d];son[p][d]=son[t][d^1];son[t][d^1]=p;Pushup(p);Pushup(t);
		if (son[p][d]) fa[son[p][d]]=p;fa[t]=fa[p];fa[p]=t;p=t;
	}
	void Addflip(int p) {if (!p) return;swap(son[p][0],son[p][1]);flip[p]^=1;}
	void Pushdown(int p) {if (flip[p]) Addflip(son[p][0]),Addflip(son[p][1]),flip[p]^=1;}
	void debug(int p){
		if (!p) return;Pushdown(p);
		debug(son[p][0]);debug(son[p][1]);
	}
	void Splay(int &p,int k){
		int d=cmp(p,k);Pushdown(p);if (d<0) return;
		int &t=son[p][d],f=cmp(t,k);Pushdown(t);
		if (~f) Splay(son[t][f],k),d==f?Rotate(p,d):Rotate(t,f);Rotate(p,d);
	}
	int Askkth(int p,int k){
		int d=cmp(p,k);Pushdown(p);
		return ~d?Askkth(son[p][d],k):p;
	}
	int Askrk(int p){
		static int top,stk[maxt+5];
		top=0;for (int i=p,f=fa[i];i!=ro;i=f,f=fa[i]) stk[++top]=fa[i];
		while (top) Pushdown(stk[top]),top--;
		int rk=si[son[p][0]]+1;
		for (int f=fa[p];p!=ro;p=f,f=fa[p])
			if (p==son[f][1]) rk+=si[son[f][0]]+1;
		Splay(ro,rk);return rk;
	}
	int getseg(int L,int R){
		L--;R++;Splay(ro,L);cmp(ro,R);Splay(son[ro][1],R);
		return son[son[ro][1]][0];
	}
	int Insert(int x){
		int now=newnode();getseg(x,x-1);
		son[son[ro][1]][0]=now;fa[now]=son[ro][1];
		Pushup(son[ro][1]);Pushup(ro);return now;
	}
}A,B;
 
#define EOLN(x) ((x)==10 || (x)==13 || (x)==EOF)
inline char readc(){
	static char buf[100000],*l=buf,*r=buf;
	return l==r && (r=(l=buf)+fread(buf,1,100000,stdin),l==r)?EOF:*l++;
}
template<typename T> int readi(T &x){
	T tot=0;char ch=readc(),lst='+';
	while (!isdigit(ch)) {if (ch==EOF) return EOF;lst=ch;ch=readc();}
	while (isdigit(ch)) tot=(tot<<3)+(tot<<1)+(ch^48),ch=readc();
	lst=='-'?x=-tot:x=tot;return EOLN(ch);
}
int main(){
	for (readi(te);te;te--){
		readi(n);readi(Q);
		a[0]=0;for (int i=1;i<=n;i++) readi(a[i]);a[n+1]=n+1;
		B.pl=0;B.ro=B.BuildB(0,n+1);
		A.pl=0;A.ro=A.BuildA(0,n+1);
		while (Q--){
			int tp,L,R;readi(tp);readi(L);L++;
			if (tp==1){
				readi(R);R++;
				A.Addflip(A.getseg(L,R));
			} else if (tp==2){
				readi(R);R++;
				B.Addflip(B.getseg(L,R));
			} else if (tp==3){
				readi(R);R++;
				int a=A.Insert(L),b=B.Insert(R);
				who[0][a]=b;who[1][b]=a;
			} else if (tp==4){
				int p=who[0][A.Askkth(A.ro,L)];
				printf("%d\n",B.Askrk(p)-1);
			} else {
				int p=who[1][B.Askkth(B.ro,L)];
				printf("%d\n",A.Askrk(p)-1);
			}
		}
	}
	return 0;
}
