#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=4e6+10;
ll read(){
	ll res=0;int op=1;char ch=getchar();
	while(ch<'0'||'9'<ch){if(ch=='-')op=-op;ch=getchar();}
	while('0'<=ch&&ch<='9'){res=res*10+ch-'0';ch=getchar();}
	return res*op;
}
void write(ll x){
	if(x<0){putchar('-');x=-x;}
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
struct node{
	ll w[N],lzy[N],cnt[N];
	ll sum[N],spa;
	map<ll,int>mpl,mpr;
	void push_up(int u,int L,int R){
		if(cnt[u])w[u]=sum[R]-sum[L-1];
		else w[u]=w[u*2]+w[u*2+1];
	}
	void make_tag(int u,int L,int R,ll x){
		cnt[u]+=x;
		if(cnt[u])w[u]=sum[R]-sum[L-1];
		else w[u]=w[u*2]+w[u*2+1];
	}
	bool In(int L,int R,int l,int r){
		return l<=L&&R<=r;
	}
	bool Out(int L,int R,int l,int r){
		return R<l||r<L;
	}
	void init(vector<ll>num){
		spa=num.size();
		sum[0]=0;
		for(int i=1;i<=spa;i++)sum[i]=sum[i-1]+num[i-1];
	}
	void update(int u,int L,int R,int l,int r,int typ){
		if(In(L,R,l,r)){
			make_tag(u,L,R,typ);
			return ;
		}
		else if(!Out(L,R,l,r)){
			int M=(L+R)/2;
			update(u*2,L,M,l,r,typ);
			update(u*2+1,M+1,R,l,r,typ);
			push_up(u,L,R);
		}
	}
	ll ask(int u,int L,int R,int l,int r){
		if(In(L,R,l,r))return w[u];
		else if(!Out(L,R,l,r)){
			int M=(L+R)/2;
			return ask(u*2,L,M,l,r)+ask(u*2+1,M+1,R,l,r);
		}
		else return 0;
	}
	void update(ll l,ll r,int typ){
		int idl=mpl[l],idr=mpr[r];
		update(1,1,spa,idl,idr,typ);
	}
	void insert(int l,int r,int id){
		mpl.insert(make_pair(l,id));
		mpr.insert(make_pair(r,id));
	}
	void print(int u,int L,int R){
		cout<<u<<"["<<L<<","<<R<<"]"<<":"<<w[u]<<" "<<cnt[u]<<" "<<endl;
		if(L==R)return ;
		int M=(L+R)/2;
		print(u*2,L,M);
		print(u*2+1,M+1,R);
	}
}tr;
struct _{
	int l,r,y,typ;
	bool operator<(const _ &a)const {
		return y<a.y;
	}
}; 
map<ll,int>mp;
vector<_>num, line[N/10]; 
vector<int>xx,yy;
vector<ll> len;
int main(){
	int n=read();
	for(int i=1;i<=n;i++){
		int l=read(),d=read(),r=read(),h=read();
		num.push_back((_){l,r,h,-1});
		num.push_back((_){l,r,d,1});
		xx.push_back(l);
		xx.push_back(r);
		yy.push_back(h);
		yy.push_back(d);
	}
	sort(num.begin(),num.end());
	sort(xx.begin(),xx.end());
	sort(yy.begin(),yy.end());
	int l=unique(xx.begin(),xx.end())-xx.begin();
	int ly=unique(yy.begin(),yy.end())-yy.begin();
	for(int i=0;i<ly;i++)mp.insert(make_pair(yy[i],i+1));
	for(int i=0;i<num.size();i++)line[mp[num[i].y]].push_back(num[i]);
	for(int i=1;i<l;i++){
		len.push_back(xx[i]-xx[i-1]);
		tr.insert(xx[i-1],xx[i],i);
	}
	tr.init(len);
	ll ans=0;
	for(int i=1,last=yy[0];i<=ly;i++){
		ans+=(yy[i-1]-last)*tr.ask(1,1,tr.spa,1,tr.spa);
		for(int j=0;j<line[i].size();j++)tr.update(line[i][j].l,line[i][j].r,line[i][j].typ);
		last=yy[i-1];
	}
	write(ans);
	return 0;
}
