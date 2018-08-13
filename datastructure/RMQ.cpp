int a[50005];
int d[50005][30][2];//d(i,j,k)表示i开始长度为2^j的元素中最小值(k==0)，最大值(k==1)

void RMQ_init() {
    for (int i = 0; i < n; i++) d[i][0][0] = d[i][0][1] = a[i];
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 0; i + (1 << j) - 1 < n; i++) {
            d[i][j][0] = min(d[i][j-1][0], d[i + (1 << (j-1))][j-1][0]);
            d[i][j][1] = max(d[i][j-1][1], d[i + (1 << (j-1))][j-1][1]);
        }
    }
}

int RMQ_query(int l, int r) {
    int k = 0;
    while ((1 << (k + 1)) <= r - l + 1) k++;
    return max(d[l][k][1], d[r-(1<<k)+1][k][1]) - min(d[l][k][0], d[r-(1<<k)+1][k][0]);
}