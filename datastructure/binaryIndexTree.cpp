int n, a[MAX_N], b[MAX_N];

ll sum(int i) {
    ll res = 0;
    while (i > 0) {
        res += b[i];
        i -= i&(-i);
    }
    return res;
}

void add(int i, int x) {
    while (i <= n) {
        a[i] += x;
        i += i&(-i);
    }
}

//二维
单点修改，区间询问（二维）
void insert(int x,int y,int z){
	for(int i=x;i<=n;i+=lowbit(i)){
		for(int j=y;j<=n;j+=lowbit(j)){
			v[i][j]+=z;
		}
	}
}
int query(int x,int y){
	int ans=0;
	for(int i=x;i;i-=lowbit(i)){
		for(int j=y;j;j-=lowbit(j)){
			ans+=v[i][j];
		}
	}
	return ans;
}

