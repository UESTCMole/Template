int w[maxn][maxn], n;
int lx[maxn], ly[maxn], slack[maxn]; // 顶标
int left[maxn]; //match
bool s[maxn], t[maxn];

bool match(int i) {
    s[i] = true;
    for (int j = 1; j <= n; j++) if (lx[i] + ly[j] == w[i][j] && !t[j]) {
        t[j] = true;
        if (!left[j] || match(left[j])) {
            left[j] = i;
            return true;
        }
    }
    else if (!t[j]) slack[j] = min(slack[j], lx[i] + ly[j] - w[i][j]);
    return false;
}

void update() {
    int a = 1 << 30;
    for (int j = 1; j <= n; j++) if (!t[j])
        a = min(a, slack[j]);
    for (int i = 1; i <= n; i++) {
        if (s[i]) lx[i] -= a;
        if (t[i]) ly[i] += a;
    }
}

int KM() {
    for (int i = 1; i <= n; i++) {
        left[i] = lx[i] = ly[i] = 0;
        for (int j = 1; j <= n; j++) lx[i] = max(lx[i], w[i][j]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) slack[j] = INF;
        for (;;) {
            for (int j = 1; j <= n; j++) s[j] = t[j] = 0;
            if (match(i)) break; else update();
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (!left[i]) ans += w[left[i]][i];
    }
    return ans;
}