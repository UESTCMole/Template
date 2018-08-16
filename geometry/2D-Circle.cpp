struct Circle {
    Point c;
    double r;
    Circle(Point c, double r) : c(c), r(r) {}
    Point point(double a) {
        return Point(c.x + cos(a)*r, c.y + sin(a)*r);
    }
};

int getLineCircleIntersectioni(Line L, Circle C, double& t1, double& t2, vector<Point>& sol) {
    double a = L.v.x, b = L.p.x - C.c.x, c = L.v.y, d = L.p.y - C.c.y;
    double e = a*a + c*c, f = 2*(a*b+c*d), g = b*b+d*d-C.r*C.r;
    double delta = f*f-4*e*g;
    if (dcmp(delta) < 0) return 0;
    if (dcmp(delta) == 0) {
        t1 = t2 = -f/(2*e);
        sol.push_back(L.point(t1));
        return 1;
    }
    t1 = (-f-sqrt(delta))/(2*e);sol.push_back(L.point(t1));
    t2 = (-f+sqrt(delta))/(2*e);sol.push_back(L.point(t2));
    return 2;
}

double angle(Vector v) { return atan2(v.y, v.x); }

int getCircleCircleIntersection(Circle C1, Circle C2, vector<Point>& sol) {
    double d = length(C1.c-C2.c);
    if (dcmp(d) == 0) {
        if (dcmp(C1.r-C2.r) == 0) return -1;//重合
        return 0;
    }
    if (dcmp(C1.r+C2.r-d)<0) return 0;
    if (dcmp(fabs(C1.r-C2.r)-d) > 0) return 0;

    double a = angle(C2.c-C1.c);
    double da = acos((C1.r*C1.r+d*d-C2.r*C2.r) / (2*C1.r*d));
    Point p1 = C1.point(a-da), p2 = C1.point(a+da);

    sol.push_back(p1);
    if (p1 == p2) return 1;
    sol.push_back(p2);
    return 2;
}

//Point to Circle
int getTangents(Point p, Circle C, Vector* v) {
    Vector u = C.c-p;
    double dist = length(u);
    if (dist < C.r) return 0;
    else if (dcmp(dist-C.r) == 0) {
        v[0] = rotate(u, pi/2);
        return 1;
    } else {
        double ang = asin(C.r/dist);
        v[0] = rotate(u, -ang);
        v[1] = rotate(u, ang);
        return 2;
    }
}

//Circle to Circle
int getTangents(Circle A, Circle B, Point* a, Point* b) {
    int cnt = 0;
    if (A.r < B.r) { swap(A, B); swap(a, b); }
    int d2 = (A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y);
    int rdiff = A.r-B.r;
    int rsum = A.r+B.r;
    if (d2 < rdiff*rdiff) return 0; //内含

    double base = atan2(B.y-A.y, B.x-A.x);
    if (d2 == 0 && A.r == B.r) return -1; //无限条切线
    if (d2 == rdiff*rdiff) { //内切一条切线
        a[cnt] = A.point(base); b[cnt] = B.point(base); cnt++;
        return 1;
    }
    //有外共切线
    double ang = acos((A.r-B.r) / sqrt(d2));
    a[cnt] = A.point(base+ang); b[cnt] = B.point(base+ang); cnt++;
    a[cnt] = A.point(base-ang); b[cnt] = B.point(base-ang); cnt++;
    if (d2 == rsum*rsum) {//一条内共切线
        a[cnt] = A.point(base); b[cnt] = B.point(pi+base); cnt++;
    } 
    else if (d2 > rsum*rsum) { //两条内共切线
        double ang = acos((A.r+B.r) / sqrt(d2));
        a[cnt] = A.point(base+ang); b[cnt] = B.point(pi+base+ang); cnt++;
        a[cnt] = A.point(base-ang); b[cnt] = B.point(pi+base-ang); cnt++;
    }
    return cnt;
}

double Circle_Circle_Area_of_overlap(Circle c1, Circle c2){
    double d=Length(c1.c-c2.c);
    if(dcmp(c1.r+c2.r-d)<=0) return 0;
    if(dcmp(fabs(c1.r-c2.r)-d)>=0){
        double minr = min(c1.r,c2.r);
        return PI*minr*minr;
    }
    double x=(d*d + c1.r*c1.r - c2.r*c2.r)/(2*d);
    double t1=acos(x/c1.r);
    double t2=acos((d-x)/c2.r);
    return c1.r*c1.r*t1 + c2.r*c2.r*t2 - d*c1.r*sin(t1);
}
