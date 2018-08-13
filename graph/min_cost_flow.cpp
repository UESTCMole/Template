//using dijkstra
const int INF = 1e9;
typedef pair < int, int > P;
struct edge {
    int to, cap, cost, rev;
};
int V, h[MAX_V], dist[MAX_V], prevv[MAX_V], preve[MAX_V];//前驱节点和前驱边
vector < edge > G[MAX_V];

void add_edge(int from, int to, int cap, int cost) {
    edge e;
    e.to = to; e.cap = cap; e.cost = cost; e.rev = G[to].size();
    G[from].push_back(e);
    e.to = from; e.cap = 0; e.cost = -cost; e.rev = G[from].size()-1;
    G[to].push_back(e);
}

int min_cost_flow(int s, int t, int f) {
    int ans = 0;
    for (int i = 0; i < V; i++) h[i] = 0;
    while (f > 0) { //如果算最大流，就不用判断f
        priority_queue < P, vector<P>, greater<P> > que;
        for (int i = 0; i < V; i++) dist[i] = INF; // V 顶点数
        dist[s] = 0;
        que.push(P(0, s));
        while (!que.empty()) {
            P p = que.top(); que.pop();
            int v = p.second;
            if (dist[v] < p.first) continue;
            for (int i = 0; i < G[v].size(); i++) {
                edge &e = G[v][i];
                if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
                    dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                    prevv[e.to] = v;
                    preve[e.to] = i;
                    que.push(P(dist[e.to], e.to));
                }
            }
        }

        if (dist[t] == INF) return -1; // 不能继续增广

        for (int v = 0; v < V; v++) h[v] += dist[v]; // 保证势的非负性

        int d = f;
        for (int v = t; v != s; v = prevv[v]) d = min(d, G[prevv[v]][preve[v]].cap);
        f -= d;
        ans += d * h[t];
        for (int v = t; v != s; v = prevv[v]) {
            edge &e = G[prevv[v]][preve[v]];
            e.cap -= d;
            G[v][e.rev].cap += d;
        }
    }
    return ans;
}

//using spfa
const int INF = 1e9;
struct edge {
    int to, cap, cost, rev;
};
int V, h[MAX_V], dist[MAX_V], prevv[MAX_V], preve[MAX_V];//前驱节点和前驱边
vector < edge > G[MAX_V];
int inq[MAX_V];

void add_edge(int from, int to, int cap, int cost) {
    edge e;
    e.to = to; e.cap = cap; e.cost = cost; e.rev = G[to].size();
    G[from].push_back(e);
    e.to = from; e.cap = 0; e.cost = -cost; e.rev = G[from].size()-1;
    G[to].push_back(e);
}

int min_cost_flow(int s, int t, int f) {
    int ans = 0;
    while (f > 0) {
        queue <int> q;
        for (int i = 0; i < V; i++) dist[i] = INF; //V 顶点数
        memset(inq, 0, sizeof(inq));
        dist[s] = 0, inq[s] = 1;
        q.push(s);
        while (!que.empty()) {
            int v = q.front(); q.pop();
            inq[v] = 0;
            for (int i = 0; i < G[v].size(); i++) {
                edge &e = G[v][i];
                if (e.cap > 0 && dist[e.to] > dist[v] + e.cost) {
                    dist[e.to] = dist[v] + e.cost;
                    q.push(e.to);
                    inq[e.to] = 1;
                    prevv[e.to] = v;
                    preve[e.to] = i;
                }
            }
        }

        if (dist[t] == INF) return -1;

        int d = f;
        for (int v = t; v != s; v = prevv[v]) d = min(d, G[prevv[v]][preve[v]].cap);
        f -= d;
        ans += d * dist[t];
        for (int v = t; v != s; v = prevv[v]) {
            edge &e = G[prevv[v]][preve[v]];
            e.cap -= d;
            G[v][e.rev].cap += d;
        }
    }
    return ans;
}
