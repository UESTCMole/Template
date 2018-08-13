struct Line {
    Point p;
    Vector v;
    double ang;
    Line() {}
    Line(Point P, Vector v) : p(P), v(v);
    bool opertaor < (const Line& L) const {
        return ang < L.ang;
    }
};

bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2) {
    double c1 = cross(a2-a1, b1-a1), c2 = cross(a2-a1, b2-a1),
           c3 = cross(b2-b1, a1-b1), c4 = cross(b2-b1, a2-b1);
    return dcmp(c1)*dcmp(c2) < 0 && dcmp(c3)*dcmp(c4) < 0;
}

Point GetLineIntersection(Point p, Vector v, Point q, Vector w) {
    Vector u = p-q;
    double t = cross(w, u) / cross(v, w);
    return p + v*t;
}

double DistanceToLine(Point p, Point a, Point b) {
    Vector v1 = b-a, v2 = p-a;
    return fabs(cross(v1, v2)) / length(v1);
}

double DistanceToSegment(Point p, Point a, Point b) {
    if (a == b) return length(p-a);
    Vector v1 = b-a, v2 = p-a, v3 = p-b;
    if (dcmp(dot(v1, v2)) < 0) return length(v2);
    else if (dcmp(dot(v1, v3)) > 0) return length(v3);
    else return fabs(cross(v1, v2)) / length(v1);
}

Point GetLineProjection(Point p, Point a, Point b) {
    Vector v = b-a;
    return a+v*(dot(v,p-a) / dot(v,v));
}

bool OnSegment(Point p, Point a1, Point a2) {
    return dcmp(cross(a1-p, a2-p)) == 0 && dcmp(dot(a1-p, a2-p)) < 0;
}

bool OnLine(Point p, Point a1, Point a2) {
    return dcmp(cross(a1-p, a2-p)) == 0;
}

double PolygonArea(Point* p, int n) {
    double area = 0;
    for (int i = 1; i < n-1; i++) area += cross(p[i]-p[0], p[i+1]-p[0]);
    return area/2;
}

