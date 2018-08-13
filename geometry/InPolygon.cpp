int InPolygon(Point p, vector<Point> poly) {
    int wn = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        if (OnSegment(p, poly[i], poly[(i+1)%n])) return -1; // 在边界
        int k = dcmp(cross(poly[(i+1)%n] - poly[i], p-poly[i]));
        int d1 = dcmp(poly[i].y - p.y);
        int d2 = dcmp(poly[(i+1)%n].y - p.y);
        if (k > 0 && d1 <= 0 && d2 > 0) wn++;
        if (k < 0 && d1 > 0 && d2 <= 0) wn--;
    }
    if (wn!=0) return 1//内部
    return 0; //外部
}

