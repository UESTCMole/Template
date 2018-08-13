//去掉边上的点，把7、12行<=换成<

int ConvexHull(Point* p, int n, Point* ch) {
    sort(p, p+n);
    int m = 0;
    for (int i = 0; i < n; i++) {
        while (m > 1 && dcmp(cross(ch[m-1]-ch[m-2], p[i]-ch[m-2])) <= 0) m--;
        ch[m++] = p[i];
    }
    int k = m;
    for (int i = n-2; i >= 0; i--) {
        while (m > k && dcmp(cross(ch[m-1]-ch[m-2], p[i]-ch[m-2])) <= 0) m--;
        ch[m++] = p[i];
    }
    if (n > 1) m--;
    return m;
}