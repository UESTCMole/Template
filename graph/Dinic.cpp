//my favorite version
最大流
//注意 tot初值为1
struct Edge {
  int v, flow, nxt;
}e[20005];
int tot = 1, last[1005], n, m, deep[1005];
void add(int u, int v, int w) {
  ++tot;
  e[tot].v = v; e[tot].flow = w, e[tot].nxt = last[u];
  last[u] = tot;
}
bool bfs(int S, int T) {
  memset(deep, 0, (tot+2) << 2);
  deep[S] = 1;
  queue <int> q;
  q.push(S);
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int i = last[u]; i; i = e[i].nxt) {
      if (e[i].flow && !deep[e[i].v]) {
        deep[e[i].v] = deep[u] + 1;
        q.push(e[i].v);
      }
    }
  }
  return deep[T];
}
int aim;
int dfs(int now, int flow) {
  if (now == aim) return flow;
  int f = 0;
  for (int i = last[now]; i && flow; i = e[i].nxt) {
    int v = e[i].v;
    if (e[i].flow && deep[v] == deep[now] + 1) {
      int x = dfs(v, min(flow, e[i].flow));
      e[i].flow -= x; e[i^1].flow += x; flow -= x; f += x;
    }
  }
  if (!f) deep[now] = -2;
  return f;
}
int maxflow(int S, int T) {
  aim = T; int ret = 0;
  while (bfs(S, T)) ret += dfs(S, 1<<30);
  return ret;
}
最小费用最大流
int nxt[M],sz=1,to[M],cost[M],flow[M],exsit[N];
int fir[N],f[N][N],q[N*N+10],pre[N],dis[N],n,m,k;
void add1(int x,int y,int z,int w){
	nxt[++sz]=fir[x];fir[x]=sz;
	to[sz]=y;flow[sz]=z;cost[sz]=w;
}
void add(int x,int y,int z,int w){
	add1(x,y,z,w),add1(y,x,0,-w);
	//fprintf(stderr,"%d %d %d %d\n",x,y,z,w);
}
bool spfa(int S,int T){
	memset(dis,63,sizeof dis);
	int s=0,t=1;q[1]=S;dis[S]=0;
	while(s^t){
		int v=q[++s];exsit[v]=0;
		for(int u=fir[v];u;u=nxt[u]){
			if(flow[u]&&dis[to[u]]>dis[v]+cost[u]){
				dis[to[u]]=dis[v]+cost[u];pre[to[u]]=u;
				if(!exsit[to[u]]){
					exsit[to[u]]=1;q[++t]=to[u];
				}
			}
		}
	}
	return dis[T]<=1000000000;
}
int end(int S,int T){
	int now=T,mi=1000000000;
	while(now^S){
		mi=min(mi,flow[pre[now]]);
		now=to[pre[now]^1];
	}
	now=T;int ret=0;
	while(now^S){
		ret+=mi*cost[pre[now]];
		flow[pre[now]]-=mi;
		flow[pre[now]^1]+=mi;
		now=to[pre[now]^1];
	}
	return ret;
}
int mcmf(int S,int T){
	int ret=0;
	while(spfa(S,T)){
		ret+=end(S,T);
	}
	return ret;
}
//maxflow vector version
const int INF = 1e9;
int level[max_n];
int iter[max_n];
struct edge { int to, cap, rev; };
vector < edge > G[max_n];
void add_edge(int from, int to, int cap) {
    G[from].push_back( (edge){to, cap, G[to].size()} );
    G[to].push_back( (edge){from, 0, G[from].size() - 1} );
}
void BFS(int s) {
    memset(level, -1, sizeof(level));
    queue < int > q;
    q.push(s);
    level[s] = 0;
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int i = 0; i < G[v].size(); i++) {
            edge &e = G[v][i];
            if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
    }
}
int DFS(int v, int t, int f) {
    if (v == t) return f;
    for (int &i = iter[v]; i < G[v].size(); i++) {
        edge &e = G[v][i];
        if (e.cap > 0 && level[v] < level[e.to]) {
            int d = DFS(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    if (!f) level[v] = -2;
    return 0;
}
int max_flow(int s, int t) {
    int flow = 0;
    for (;;) {
        BFS(s);
        if (level[t] < 0) return flow;
        memset(iter, 0, sizeof(iter));
        int f;
        while ((f = DFS(s, t, INF)) > 0) flow += f;
    }
}