#include <cmath>

namespace Math {
    const double PI = 4 * atan(1);
    const double Epsilon = 1e-6;

    double asin(double arg) {
        return ::asin(std::max(-1.0, std::min(1.0, arg)));
    }

    double acos(double arg) {
        return ::acos(std::max(-1.0, std::min(1.0, arg)));
    }

    double degToRad(double deg) {
        return deg / 180 * PI;
    }

    double radToDeg(double rad) {
        return rad / PI * 180;
    }

    bool areEq(double a, double b) {
        return fabs((a - b) / std::max(1.0, b)) < Math::Epsilon;
    }
}

class Vector2DI {
private:
    long long X;
    long long Y;
public:
    Vector2DI() {
        this->X = 0;
        this->Y = 0;
    }

    Vector2DI(long long X, long long Y) {
        this->X = X;
        this->Y = Y;
    }

    void setX(long long X) {
        this->X = X;
    }

    long long getX() const {
        return this->X;
    }

    void setY(long long Y) {
        this->Y = Y;
    }

    long long getY() const {
        return this->Y;
    }

    double getNorm() const {
        return sqrt(this->getX() * this->getX() + this->getY() * this->getY());
    }

    long long dotProductWith(const Vector2DI &arg) const {
        return this->getX() * arg.getX() + this->getY() * arg.getY();
    }

    double angleWith(const Vector2DI &arg) const {
        return Math::acos(this->dotProductWith(arg) / (this->getNorm() * arg.getNorm()));
    }
};

class Vector2DD {
private:
    double X;
    double Y;
public:
    Vector2DD() {
        this->X = 0;
        this->Y = 0;
    }

    Vector2DD(double X, double Y) {
        this->X = X;
        this->Y = Y;
    }

    Vector2DD(const Vector2DI &arg) {
        this->X = arg.getX();
        this->Y = arg.getY();
    }

    void setX(double X) {
        this->X = X;
    }

    double getX() const {
        return this->X;
    }

    void setY(double Y) {
        this->Y = Y;
    }

    double getY() const {
        return this->Y;
    }

    double getNorm() const {
        return sqrt(this->getX() * this->getX() + this->getY() * this->getY());
    }

    double dotProductWith(const Vector2DD &arg) const {
        return this->getX() * arg.getX() + this->getY() * arg.getY();
    }

    double angleWith(const Vector2DD &arg) const {
        return Math::acos(this->dotProductWith(arg) / (this->getNorm() * arg.getNorm()));
    }
};

class Point2DI {
private:
    long long X;
    long long Y;
public:
    Point2DI() {
        this->X = 0;
        this->Y = 0;
    }

    Point2DI(long long X, long long Y) {
        this->X = X;
        this->Y = Y;
    }

    Point2DI(const Vector2DI &arg) {
        this->X = arg.getX();
        this->Y = arg.getY();
    }

    bool operator ==(const Point2DI &arg) const {
        return this->X == arg.getX() && this->Y == arg.getY();
    }

    bool operator !=(const Point2DI &arg) const {
        return !(*this == arg);
    }

    void setX(long long X) {
        this->X = X;
    }

    long long getX() const {
        return this->X;
    }

    void setY(long long Y) {
        this->Y = Y;
    }

    long long getY() const {
        return this->Y;
    }

    double distanceTo(const Point2DI &arg) const {
        long long dx = this->X - arg.X;
        long long dy = this->Y - arg.Y;
        return sqrt(dx * dx + dy * dy);
    }

    long long getPointSign(const Point2DI &A, const Point2DI &B) const {
        return A.getX() * B.getY() + B.getX() * this->Y + this->getX() * A.getY() - A.getX() * this->getY() - B.getX() * A.getY() - this->getX() * B.getY();
    }

    bool areCollinear(const Point2DI &A, const Point2DI &B) const {
        return this->getPointSign(A, B) == 0;
    }

    double getTriangleSurface(const Point2DI &A, const Point2DI &B) const {
        return (A.getX() * B.getY() + B.getX() * this->getY() + this->getX() * A.getY() - A.getX() * this->getY() - B.getX() * A.getY() - this->getX() * B.getY()) / 2.0;
    }

    Vector2DI getVectorWith(const Point2DI &arg) const {
        return Vector2DI(arg.getX() - this->getX(), arg.getY() - this->getY());
    }

    double getAngle(const Point2DI &B, const Point2DI &C) const {
        Vector2DI AB = this->getVectorWith(B);
        Vector2DI AC = this->getVectorWith(C);
        double answer = AB.angleWith(AC);
        return answer;
    }

    Point2DI getSymetricOf(const Point2DI &arg) const {
        return Point2DI(2 * this->getX() - arg.getX(), 2 * this->getY() - arg.getY());
    }
};

Point2DI operator +(const Point2DI &a, const Point2DI &b) {
    return Point2DI(a.getX() + b.getX(), a.getY() + b.getY());
}

Point2DI operator -(const Point2DI &a, const Point2DI &b) {
    return Point2DI(a.getX() - b.getX(), a.getY() - b.getY());
}

Point2DI operator *(long long a, const Point2DI &b) {
    return Point2DI(a * b.getX(), a * b.getY());
}

Point2DI operator *(const Point2DI &a, long long b) {
    return Point2DI(a.getX() * b, a.getY() * b);
}

Point2DI operator +=(Point2DI &a, const Point2DI &b) {
    return a = a + b;
}

Point2DI operator -=(Point2DI &a, const Point2DI &b) {
    return a = a - b;
}

Point2DI operator *=(Point2DI &a, long long b) {
    return a = a * b;
}

class Point2DD {
private:
    double X;
    double Y;
public:
    Point2DD() {
        this->X = 0;
        this->Y = 0;
    }

    Point2DD(double X, double Y) {
        this->X = X;
        this->Y = Y;
    }

    Point2DD(const Vector2DD &arg) {
        this->X = arg.getX();
        this->Y = arg.getY();
    }

    Point2DD(const Point2DI &arg) {
        this->X = arg.getX();
        this->Y = arg.getY();
    }

    bool operator ==(const Point2DD &arg) const {
        return Math::areEq(this->getX(), arg.getX())
            && Math::areEq(this->getY(), arg.getY());
    }

    bool operator !=(const Point2DD &arg) const {
        return !(*this == arg);
    }

    void setX(double X) {
        this->X = X;
    }

    double getX() const {
        return this->X;
    }

    void setY(double Y) {
        this->Y = Y;
    }

    double getY() const {
        return this->Y;
    }

    double distanceTo(const Point2DD &arg) const {
        double dx = this->getX() - arg.getX();
        double dy = this->getY() - arg.getY();
        return sqrt(dx * dx + dy * dy);
    }

    double getPointSign(const Point2DD &A, const Point2DD &B) const {
        return A.getX() * B.getY() + B.getX() * this->getY() + this->getX() * A.getY() - A.getX() * this->getY() - B.getX() * A.getY() - this->getX() * B.getY();
    }

    bool areCollinear(const Point2DD &A, const Point2DD &B) const {
        return Math::areEq(this->getPointSign(A, B), 0);
    }

    double getTriangleSurface(const Point2DD &A, const Point2DD &B) const {
        return (A.getX() * B.getY() + B.getX() * this->getY() + this->getX() * A.getY() - A.getX() * this->getY() - B.getX() * A.getY() - this->getX() * B.getY()) / 2.0;
    }

    Vector2DD getVectorWith(const Point2DD &arg) const {
        return Vector2DD(arg.X - this->X,
                         arg.Y - this->Y);
    }

    double getAngle(const Point2DD &B, const Point2DD &C) const {
        Vector2DD AB = this->getVectorWith(B);
        Vector2DD AC = this->getVectorWith(C);
        double answer = AB.angleWith(AC);
        return answer;
    }

    Point2DD getSymetricOf(const Point2DD &arg) const {
        return Point2DD(2 * this->X - arg.X,
                        2 * this->Y - arg.Y);
    }
};

Point2DD operator +(const Point2DD &a, const Point2DD &b) {
    return Point2DD(a.getX() + b.getX(), a.getY() + b.getY());
}

Point2DD operator -(const Point2DD &a, const Point2DD &b) {
    return Point2DD(a.getX() - b.getX(), a.getY() - b.getY());
}

Point2DD operator *(double a, const Point2DD &b) {
    return Point2DD(a * b.getX(), a * b.getY());
}

Point2DD operator *(const Point2DD &a, double b) {
    return Point2DD(a.getX() * b, a.getY() * b);
}

Point2DD operator /(const Point2DD &a, double b) {
    return Point2DD(a.getX() / b, a.getY() / b);
}

Point2DD operator +=(Point2DD &a, const Point2DD &b) {
    return a = a + b;
}

Point2DD operator -=(Point2DD &a, const Point2DD &b) {
    return a = a - b;
}

Point2DD operator *=(Point2DD &a, double b) {
    return a = a * b;
}

Point2DD operator /=(Point2DD &a, double b) {
    return a = a / b;
}

class Point2DP {
private:
    double distance;
    double angle;
public:
    Point2DP() {
        this->distance = 0;
        this->angle = 0;
    }

    Point2DP(const double X, const double Y) {
        this->distance = sqrt(X * X + Y * Y);
        this->angle = atan2(Y, X);
    }

    Point2DP(const Point2DD &arg) {
        *this = Point2DP(arg.getX(), arg.getY());
    }

    void setDistance(double distance) {
        this->distance = distance;
    }

    double getDistance() {
        return this->distance;
    }

    void setAngle(double angle) {
        this->angle = angle;
    }

    double getAngle() {
        return this->angle;
    }

    Point2DD getPoint2DD() {
        return Point2DD(
            this->distance * cos(this->angle),
            this->distance * sin(this->angle));
    }
};

class Line2DI {
private:
    long long A;
    long long B;
    long long C;
    double norm;

    double computeNorm() {
        return sqrt(this->A * this->A + this->B * this->B);
    }
public:
    Line2DI(const Point2DI &A, const Point2DI &B) {
        this->A = A.getY() - B.getY();
        this->B = B.getX() - A.getX();
        this->C = A.getX() * B.getY() - B.getX() * A.getY();
        this->norm = this->computeNorm();
    }

    Line2DI(const long long A, const long long B, const long long C) {
        this->A = A;
        this->B = B;
        this->C = C;
        this->norm = this->computeNorm();
    }

    long long getA() const {
        return this->A;
    }

    long long getB() const {
        return this->B;
    }

    long long getC() const {
        return this->C;
    }

    double distanceTo(const Point2DD &arg) const {
        return fabs(this->getA() * arg.getX() + this->getB() * arg.getY() + this->getC()) / this->norm;
    }

    bool isParallelWith(const Line2DI &arg) const {
        return this->getA() * arg.getB() == arg.getA() * this->getB();
    }

    bool isTheSameAs(const Line2DI &arg) const {
        return this->isParallelWith(arg)
            && this->A * arg.getC() == arg.getA() * this->getC()
            && this->B * arg.getC() == arg.getB() * this->getC();
    }

    Point2DD intersectWith(const Line2DI &arg) const {
        if (this->isParallelWith(arg)) {
            throw "Lines don't intersect.";
        }
        Point2DD sol = Point2DD();
        sol.setX((double)(arg.getC() * this->getB() - this->getC() * arg.getB()) / (this->getA() * arg.getB() - this->getB() * arg.getA()));
        sol.setY((double)(arg.getC() * this->getA() - this->getC() * arg.getA()) / (this->getB() * arg.getA() - this->getA() * arg.getB()));
        return sol;
    }

    long long getPointSign(const Point2DI &arg) const {
        return this->getA() * arg.getX() + this->getB() * arg.getY() + this->getC();
    }

    double getPointSign(const Point2DD &arg) const {
        return this->getA() * arg.getX() + this->getB() * arg.getY() + this->getC();
    }

    bool contains(const Point2DI &arg) const {
        return this->getPointSign(arg) == 0;
    }

    bool contains(const Point2DD &arg) const {
        return Math::areEq(this->getPointSign(arg), 0);
    }

    Line2DI getPerpendicular(const Point2DI &arg) const {
        return Line2DI(
                this->getB(), -this->getA(),
                -(this->getB() * arg.getX() - this->getA() * arg.getY()));
    }

    Line2DI getParallel(const Point2DI &arg) const {
        return Line2DI(this->getA(), this->getB(),
            -(this->getA() * arg.getX() + this->getB() * arg.getY()));
    }

    Point2DD getProjection(const Point2DI &arg) const {
        return this->intersectWith(this->getPerpendicular(arg));
    }
};

class Line2DD {
private:
    double A;
    double B;
    double C;

    void normalize() {
        double norm = sqrt(this->A * this->A + this->B * this->B);
        this->A /= norm;
        this->B /= norm;
        this->C /= norm;
    }
public:
    Line2DD(const Point2DD &A, const Point2DD &B) {
        this->A = A.getY() - B.getY();
        this->B = B.getX() - A.getX();
        this->C = A.getX() * B.getY() - B.getX() * A.getY();
        this->normalize();
    }

    Line2DD(const double A, const double B, const double C) {
        this->A = A;
        this->B = B;
        this->C = C;
        this->normalize();
    }

    Line2DD(const Line2DI &arg) {
        this->A = arg.getA();
        this->B = arg.getB();
        this->C = arg.getC();
    }

    double getA() const {
        return this->A;
    }

    double getB() const {
        return this->B;
    }

    double getC() const {
        return this->C;
    }

    double distanceTo(const Point2DD &arg) const {
        return fabs(this->getA() * arg.getX() + this->getB() * arg.getY() + this->C);
    }

    bool isParallelWith(const Line2DD &arg) const {
        return Math::areEq(this->getA() * arg.getB() - arg.getA() * this->getB(), 0);
    }

    bool isTheSameAs(const Line2DD &arg) const {
        return this->isParallelWith(arg)
            && Math::areEq(this->getA() * arg.getC() - arg.getA() * this->getC(), 0)
            && Math::areEq(this->getB() * arg.getC() - arg.getB() * this->getC(), 0);
    }

    Point2DD intersectWith(const Line2DD &arg) const {
        if (this->isParallelWith(arg)) {
            throw "Lines are parallel.";
        }
        Point2DD sol;
        sol.setX((arg.getC() * this->getB() - this->getC() * arg.getB()) / (this->getA() * arg.getB() - this->getB() * arg.getA()));
        sol.setY((arg.getC() * this->getA() - this->getC() * arg.getA()) / (this->getB() * arg.getA() - this->getA() * arg.getB()));
        return sol;
    }

    double getPointSign(const Point2DD &arg) const {
        return this->getA() * arg.getX() + this->getB() * arg.getY() + this->getC();
    }

    bool contains(const Point2DD &arg) const {
        return Math::areEq(this->getPointSign(arg), 0);
    }

    Line2DD getPerpendicular(const Point2DD &arg) const {
        return Line2DD(
                this->getB(), -this->getA(),
                -(this->getB() * arg.getX() - this->getA() * arg.getY()));
    }

    Line2DD getParallel(const Point2DD &arg) const {
        return Line2DD(this->getA(), this->getB(),
            -(this->getA() * arg.getX() + this->getB() * arg.getY()));
    }

    Point2DD getProjection(const Point2DD &arg) const {
        return this->intersectWith(this->getPerpendicular(arg));
    }

    Point2DD getSymetricOf(const Point2DD &arg) const {
        return this->getProjection(arg).getSymetricOf(arg);
    }

    Point2DD getPointAtDistance(const Point2DD &arg, const double distance) const {
        return Point2DD(
                arg.getX() + this->getB() * distance,
                arg.getY() - this->getA() * distance);
    }
};

class Segment2DI {
private:
    Point2DI A;
    Point2DI B;
    Line2DI  L;
public:
    Segment2DI(const Point2DI &A, const Point2DI &B) : L(A, B) {
        this->A = A;
        this->B = B;
    }

    Line2DI getLine() {
        return this->L;
    }

    Point2DD getMiddle() {
        return Point2DD((A.getX() + B.getX()) / 2.0, (A.getY() + B.getY()) / 2.0);
    }

    Point2DD intersectWith(const Segment2DI &B) const {
        Point2DD aa, ab, ba, bb, sol;
        aa = Point2DD(this->A);
        ab = Point2DD(this->B);
        ba = Point2DD(B.A);
        bb = Point2DD(B.B);
        try {
            sol = this->L.intersectWith(B.L);
            if (!Math::areEq(aa.distanceTo(sol) + sol.distanceTo(ab), aa.distanceTo(ab))
             || !Math::areEq(ba.distanceTo(sol) + sol.distanceTo(bb), ba.distanceTo(bb))) {
                throw 0;
            }
        } catch (const char* s) {
            double DA = aa.distanceTo(ab);
            double DB = ba.distanceTo(bb);
            double DAA = aa.distanceTo(ba);
            double DAB = aa.distanceTo(bb);
            double DBA = ab.distanceTo(ba);
            double DBB = ab.distanceTo(bb);
            if ((Math::areEq(DA + DAA + DB, DBB) && !Math::areEq(DAA, 0))
             || (Math::areEq(DA + DAB + DB, DBA) && !Math::areEq(DAB, 0))
             || (Math::areEq(DA + DBA + DB, DAB) && !Math::areEq(DBA, 0))
             || (Math::areEq(DA + DBB + DB, DAA) && !Math::areEq(DBB, 0))) {
                throw "Segments don't intersect.";
            }
            if ((Math::areEq(DA + DB, DBB) && Math::areEq(DAA, 0))
             || (Math::areEq(DA + DB, DBA) && Math::areEq(DAB, 0))) {
                sol = aa;
            }
            if ((Math::areEq(DA + DB, DAB) && Math::areEq(DBA, 0))
             || (Math::areEq(DA + DB, DAA) && Math::areEq(DBB, 0))) {
                sol = ab;
            }
        } catch (int &i) {
            throw "Segments don't intersect.";
        }
        return sol;
    }

    bool contains(const Point2DI &arg) const {
        return this->L.contains(arg)
            && Math::areEq(arg.distanceTo(this->A) + arg.distanceTo(this->B), this->A.distanceTo(this->B));
    }

    bool contains(const Point2DD &arg) const {
        return this->L.contains(arg)
            && Math::areEq(arg.distanceTo(this->A) + arg.distanceTo(this->B), this->A.distanceTo(this->B));
    }

    double distanceTo(const Point2DI &arg) const {
        if (this->contains(this->L.getProjection(arg))) {
            return this->L.distanceTo(arg);
        } else {
            return std::min(arg.distanceTo(this->A), arg.distanceTo(this->B));
        }
    }
};

class Segment2DD {
private:
    Point2DD A;
    Point2DD B;
    Line2DD  L;
public:
    Segment2DD(const Point2DD &A, const Point2DD &B) : L(A, B) {
        this->A = A;
        this->B = B;
    }

    Line2DD getLine() {
        return this->L;
    }

    Point2DD getMiddle() {
        return Point2DD((A.getX() + B.getX()) / 2.0, (A.getY() + B.getY()) / 2.0);
    }

    bool isIntersectingWith(const Segment2DD &B) const {
        Point2DD aa, ab, ba, bb, sol;
        aa = this->A;
        ab = this->B;
        ba = B.A;
        bb = B.B;
        if (this->L.isParallelWith(B.L)) {
            if (this->L.isTheSameAs(B.L)) {
                double DA = aa.distanceTo(ab);
                double DB = ba.distanceTo(bb);
                double DAA = aa.distanceTo(ba);
                double DAB = aa.distanceTo(bb);
                double DBA = ab.distanceTo(ba);
                double DBB = ab.distanceTo(bb);
                if ((Math::areEq(DA + DAA + DB, DBB) && !Math::areEq(DAA, 0))
                 || (Math::areEq(DA + DAB + DB, DBA) && !Math::areEq(DAB, 0))
                 || (Math::areEq(DA + DBA + DB, DAB) && !Math::areEq(DBA, 0))
                 || (Math::areEq(DA + DBB + DB, DAA) && !Math::areEq(DBB, 0))) {
                    return false;
                } else {
                    return true;
                }
            } else {
                return false;
            }
        } else {
            sol = this->L.intersectWith(B.L);
            return Math::areEq(aa.distanceTo(sol) + sol.distanceTo(ab), aa.distanceTo(ab))
                && Math::areEq(ba.distanceTo(sol) + sol.distanceTo(bb), ba.distanceTo(bb));
        }
    }

    Point2DD intersectWith(const Segment2DD &B) const {
        Point2DD aa, ab, ba, bb, sol;
        aa = this->A;
        ab = this->B;
        ba = B.A;
        bb = B.B;
        try {
            sol = this->L.intersectWith(B.L);
            if (!Math::areEq(aa.distanceTo(sol) + sol.distanceTo(ab), aa.distanceTo(ab))
             || !Math::areEq(ba.distanceTo(sol) + sol.distanceTo(bb), ba.distanceTo(bb))) {
                throw 0;
            }
        } catch (const char* &s) {
            double DA = aa.distanceTo(ab);
            double DB = ba.distanceTo(bb);
            double DAA = aa.distanceTo(ba);
            double DAB = aa.distanceTo(bb);
            double DBA = ab.distanceTo(ba);
            double DBB = ab.distanceTo(bb);
            if ((Math::areEq(DA + DAA + DB, DBB) && !Math::areEq(DAA, 0))
             || (Math::areEq(DA + DAB + DB, DBA) && !Math::areEq(DAB, 0))
             || (Math::areEq(DA + DBA + DB, DAB) && !Math::areEq(DBA, 0))
             || (Math::areEq(DA + DBB + DB, DAA) && !Math::areEq(DBB, 0))) {
                throw "Segments don't intersect";
            }
            if ((Math::areEq(DA + DB, DBB) && Math::areEq(DAA, 0))
             || (Math::areEq(DA + DB, DBA) && Math::areEq(DAB, 0))) {
                sol = aa;
            }
            if ((Math::areEq(DA + DB, DAB) && Math::areEq(DBA, 0))
             || (Math::areEq(DA + DB, DAA) && Math::areEq(DBB, 0))) {
                sol = ab;
            }
        } catch (int &s) {
            throw "Segments don't intersect";
        }
        return sol;
    }

    bool contains(const Point2DD &arg) const {
        return this->L.contains(arg)
            && Math::areEq(this->A.distanceTo(arg) + arg.distanceTo(this->B), this->A.distanceTo(this->B));
    }

    double distanceTo(const Point2DD &arg) const {
        if (this->contains(this->L.getProjection(arg))) {
            return this->L.distanceTo(arg);
        } else {
            return std::min(arg.distanceTo(this->A), arg.distanceTo(this->B));
        }
    }
};

class Triangle2DD {
private:
    Point2DD A;
    Point2DD B;
    Point2DD C;

public:
    Triangle2DD(const Point2DD &A, const Point2DD &B, const Point2DD &C) {
        this->A = A;
        this->B = B;
        this->C = C;
    }

    void setA(const Point2DD &A) {
        this->A = A;
    }

    Point2DD getA() const {
        return this->A;
    }

    void setB(const Point2DD &B) {
        this->B = B;
    }

    Point2DD getB() const {
        return this->B;
    }

    void setC(const Point2DD &C) {
        this->C = C;
    }

    Point2DD getC() const {
        return this->C;
    }

    double getArea() {
        return fabs(this->A.getTriangleSurface(this->B, this->C));
    }

    Point2DD getCircumcenter() { // circumscribed circle center
        Line2DD AB(A, B);
        Line2DD BC(B, C);
        Line2DD ABmed = AB.getPerpendicular((A + B) / 2);
        Line2DD BCmed = BC.getPerpendicular((B + C) / 2);
        return ABmed.intersectWith(BCmed);
    }

    Point2DD getOrthocenter() { // nine-point circle center
        Line2DD AB(A, B);
        Line2DD BC(B, C);
        Line2DD ABalt = AB.getPerpendicular(C);
        Line2DD BCalt = BC.getPerpendicular(A);
        return ABalt.intersectWith(BCalt);
    }

    Point2DD getCentroid() { // center of mass
        return (A + B + C) / 3;
    }
};
