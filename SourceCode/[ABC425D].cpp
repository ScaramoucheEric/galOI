#include<iostream>
#include<algorithm>
#include<vector>
#include<cassert>
using namespace std;
int H,W;
string S[3<<17];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>H>>W;
	vector<pair<int,int> >Q,nQ;
	for(int i=0;i<H;i++)
	{
		cin>>S[i];
		for(int j=0;j<W;j++)if(S[i][j]=='.')Q.push_back(make_pair(i,j));
	}
	const int d[5]={0,1,0,-1};
	while(!Q.empty())
	{
		nQ.clear();
		for(auto[i,j]:Q)
		{
			int c=0;
			for(int r=0;r<4;r++)
			{
				int x=i+d[r],y=j+d[r+1];
				if(x>=0&&y>=0&&x<H&&y<W&&S[x][y]=='#')c++;
			}
			if(c==1)nQ.push_back(make_pair(i,j));
		}
		Q.clear();
		for(auto[i,j]:nQ)
		{
			S[i][j]='#';
			for(int r=0;r<4;r++)
			{
				int x=i+d[r],y=j+d[r+1];
				if(x>=0&&y>=0&&x<H&&y<W&&S[x][y]=='.')Q.push_back(make_pair(x,y));
			}
		}
		sort(Q.begin(),Q.end());
		Q.erase(unique(Q.begin(),Q.end()),Q.end());
	}
	int cnt=0;

    for (int i = 0; i < H; i ++ ) {
        for (int j = 0; j < S[i].size(); j ++ )
            cout << (cnt += S[i][j] == '#') << " ";
        cout << endl;
    }

    for (int i = 0; i < H; i ++ ) {
        cout << S[i] << endl;
    }
	cout<<cnt<<endl;
}
