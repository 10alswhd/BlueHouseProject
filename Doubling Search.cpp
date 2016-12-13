#define MAXN 100000
#define MAX_LOG 17
typedef vector<int >::iterator VIT;
int pa[MAX_LOG+1][MAXN+5],dep[MAXN+5];
vector<int >G[MAXN+5];
void dfs(int x,int p){
	pa[0][x]=p;
	for(int i=0;i+1<MAX_LOG;++i){
		pa[i+1][x]=pa[i][pa[i][x]];
	}
	for(VIT i=G[x].begin();i!=G[x].end();++i){
		if(*i==p)continue;
		dep[*i]=dep[x]+1;
		dfs(*i,x);
	}
}
inline int find_lca(int a,int b){
	if(dep[a]>dep[b])swap(a,b);
	for(int i=dep[b]-dep[a],k=0;i;i/=2){
		if(i&1)b=pa[k][b];
		++k;
	}
	if(a==b)return a;
	for(int i=MAX_LOG;i>=0;--i){
		if(pa[i][a]!=pa[i][b]){
			a=pa[i][a];
			b=pa[i][b];
		}
	}
	return pa[0][a];
}
