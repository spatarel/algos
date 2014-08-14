#include <cstdio>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

class Math {
public:
    static const double PI;

    static const double Epsilon;

    static long long abs(long long val) {
        if (val > 0) {
            return  val;
        } else {
            return -val;
        }
    }

    static double abs(double val) {
        if (val > 0) {
            return  val;
        } else {
            return -val;
        }
    }
};

const double Math::PI = 3.14159265358979323846264338327950288419716939937510;

const double Math::Epsilon = 0.000001;

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
        return sqrt((double)this->getX() * this->getX() + this->getY() * this->getY());
    }

    long long dotProductWith(const Vector2DI &arg) const {
        return this->getX() * arg.getX() + this->getY() * arg.getY();
    }

    double angleWith(const Vector2DI &arg) const {
        return acos((double)this->dotProductWith(arg) / (this->getNorm() * arg.getNorm()));
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
        return sqrt((double)this->getX() * this->getX() + this->getY() * this->getY());
    }

    double dotProductWith(const Vector2DD &arg) const {
        return this->getX() * arg.getX() + this->getY() * arg.getY();
    }

    double angleWith(const Vector2DD &arg) const {
        return acos((double)this->dotProductWith(arg) / (this->getNorm() * arg.getNorm()));
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

    bool equalsTo(const Point2DI &arg) const {
        return this->X == arg.getX() && this->Y == arg.getY();
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
        return sqrt((double)(this->X - arg.X) * (this->X - arg.X) + (this->Y - arg.Y) * (this->Y - arg.Y));
    }

    long long getPointSign(const Point2DI &A, const Point2DI &B) const {
        return A.getX() * B.getY() + B.getX() * this->Y + this->getX() * A.getY() - A.getX() * this->getY() - B.getX() * A.getY() - this->getX() * B.getY();
    }

    bool areCollinear(const Point2DI &A, const Point2DI &B) const {
        return Math::abs(this->getPointSign(A, B)) == 0;
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

    Point2DD(const Point2DI &arg) {
        this->X = (double)arg.getX();
        this->Y = (double)arg.getY();
    }

    bool equalsTo(const Point2DD &arg) const {
        return Math::abs(this->getX() - arg.getX()) < Math::Epsilon &&
                Math::abs(this->getY() - arg.getY()) < Math::Epsilon;
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
        return sqrt((double)(this->getX() - arg.getX()) * (this->getX() - arg.getX()) + (this->getY() - arg.getY()) * (this->getY() - arg.getY()));
    }

    double distanceTo(const Point2DI &arg) const {
        return sqrt((double)(this->getX() - arg.getX()) * (this->getX() - arg.getX()) + (this->getY() - arg.getY()) * (this->getY() - arg.getY()));
    }

    double getPointSign(const Point2DD &A, const Point2DD &B) const {
        return A.getX() * B.getY() + B.getX() * this->getY() + this->getX() * A.getY() - A.getX() * this->getY() - B.getX() * A.getY() - this->getX() * B.getY();
    }

    bool areCollinear(const Point2DD &A, const Point2DD &B) const {
        return Math::abs(this->getPointSign(A, B)) < Math::Epsilon;
    }

    double getTriangleSurface(const Point2DD &A, const Point2DD &B) const {
        return (A.getX() * B.getY() + B.getX() * this->getY() + this->getX() * A.getY() - A.getX() * this->getY() - B.getX() * A.getY() - this->getX() * B.getY()) / 2.0;
    }

    Vector2DD getVectorWith(const Point2DD &arg) const {
        return Vector2DD(arg.getX() - this->getX(), arg.getY() - this->getY());
    }

    double getAngle(const Point2DD &B, const Point2DD &C) const {
        Vector2DD AB = this->getVectorWith(B);
        Vector2DD AC = this->getVectorWith(C);
        double answer = AB.angleWith(AC);
        return answer;
    }

    Point2DD getSymetricOf(const Point2DD &arg) const {
        return Point2DD(2 * this->getX() - arg.getX(), 2 * this->getY() - arg.getY());
    }
};

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
        this->distance = sqrt((double)(X * X + Y * Y));
        if (Y >= 0) {
            this->angle = acos(X / this->distance);
        } else {
            this->angle = 2 * Math::PI - acos(X / this->distance);
        }
    }

    Point2DP(const Point2DD &arg) {
        this->distance = sqrt((double)(arg.getX() * arg.getX() + arg.getY() * arg.getY()));
        if (arg.getY() >= 0) {
            this->angle = acos(arg.getX() / this->distance);
        } else {
            this->angle = 2 * Math::PI - acos(arg.getX() / this->distance);
        }
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
};

class Line2DI {
private:
    long long A;
    long long B;
    long long C;
    double norm;

    double computeNorm() {
        return sqrt((double)this->A * this->A + this->B * this->B);
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

    double distanceTo(const Point2DI &arg) const {
        return Math::abs(this->getA() * arg.getX() + this->getB() * arg.getY() + this->getC()) / this->norm;
    }

    bool isParallelWith(const Line2DI &arg) const {
        return this->getA() * arg.getB() == arg.getA() * this->getB();
    }

    bool isTheSameAs(const Line2DI &arg) const {
        return this->isParallelWith(arg) &&
                this->A * arg.getC() == arg.getA() * this->getC() &&
                this->B * arg.getC() == arg.getB() * this->getC();
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
        return this->getPointSign(arg) < Math::Epsilon;
    }

    Line2DI getPerpendicular(const Point2DI &arg) const {
        return Line2DI(
                this->getB(), -this->getA(),
                -(this->getB() * arg.getX() - this->getA() * arg.getY()));
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
        double norm = sqrt((double)this->A * this->A + this->B * this->B);
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
        return Math::abs(this->getA() * arg.getX() + this->getB() * arg.getY() + this->C);
    }

    bool isParallelWith(const Line2DD &arg) const {
        return Math::abs(this->getA() * arg.getB() - arg.getA() * this->getB()) < Math::Epsilon;
    }

    bool isTheSameAs(const Line2DD &arg) const {
        return this->isParallelWith(arg) &&
                Math::abs(this->getA() * arg.getC() - arg.getA() * this->getC()) < Math::Epsilon &&
                Math::abs(this->getB() * arg.getC() - arg.getB() * this->getC()) < Math::Epsilon;
    }

    Point2DD intersectWith(const Line2DD &arg) const {
        if (this->isParallelWith(arg)) {
            throw "Lines are parallel.";
        }
        Point2DD sol;
        sol.setX((double)(arg.getC() * this->getB() - this->getC() * arg.getB()) / (this->getA() * arg.getB() - this->getB() * arg.getA()));
        sol.setY((double)(arg.getC() * this->getA() - this->getC() * arg.getA()) / (this->getB() * arg.getA() - this->getA() * arg.getB()));
        return sol;
    }

    double getPointSign(const Point2DD &arg) const {
        return this->getA() * arg.getX() + this->getB() * arg.getY() + this->getC();
    }

    bool contains(const Point2DD &arg) const {
        return Math::abs(this->getPointSign(arg)) < Math::Epsilon;
    }

    Line2DD getPerpendicular(const Point2DD &arg) const {
        return Line2DD(
                this->getB(), -this->getA(),
                -(this->getB() * arg.getX() - this->getA() * arg.getY()));
    }

    Point2DD getProjection(const Point2DD &arg) const {
        return this->intersectWith(this->getPerpendicular(arg));
    }

    Point2DD getSymetricOf(const Point2DD &arg) const {
        return this->getProjection(arg).getSymetricOf(arg);
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
            if (Math::abs(aa.distanceTo(sol) + sol.distanceTo(ab) - aa.distanceTo(ab)) > Math::Epsilon ||
                    Math::abs(ba.distanceTo(sol) + sol.distanceTo(bb) - ba.distanceTo(bb)) > Math::Epsilon) {
                throw 0;
            }
        } catch (string &s) {
            double DA = aa.distanceTo(ab);
            double DB = ba.distanceTo(bb);
            double DAA = aa.distanceTo(ba);
            double DAB = aa.distanceTo(bb);
            double DBA = ab.distanceTo(ba);
            double DBB = ab.distanceTo(bb);
            if ((Math::abs(DA + DAA + DB - DBB) <= Math::Epsilon && DAA > Math::Epsilon) ||
                (Math::abs(DA + DAB + DB - DBA) <= Math::Epsilon && DAB > Math::Epsilon) ||
                (Math::abs(DA + DBA + DB - DAB) <= Math::Epsilon && DBA > Math::Epsilon) ||
                (Math::abs(DA + DBB + DB - DAA) <= Math::Epsilon && DBB > Math::Epsilon)) {
            	throw "Segments don't intersect.";
            }
            if ((Math::abs(DA + DB - DBB) <= Math::Epsilon && DAA <= Math::Epsilon) ||
                (Math::abs(DA + DB - DBA) <= Math::Epsilon && DAB <= Math::Epsilon)) {
                sol = aa;
            }
            if ((Math::abs(DA + DB - DAB) <= Math::Epsilon && DBA <= Math::Epsilon) ||
                (Math::abs(DA + DB - DAA) <= Math::Epsilon && DBB <= Math::Epsilon)) {
                sol = ab;
            }
        } catch (int &i) {
        	throw "Segments don't intersect.";
        }
        return sol;
    }

    bool contains(const Point2DI &arg) const {
        return this->L.contains(arg) &&
                Math::abs(arg.distanceTo(this->A) + arg.distanceTo(this->B) - this->A.distanceTo(this->B)) < Math::Epsilon;
    }

    bool contains(const Point2DD &arg) const {
        return this->L.contains(arg) &&
                Math::abs(arg.distanceTo(this->A) + arg.distanceTo(this->B) - this->A.distanceTo(this->B)) < Math::Epsilon;
    }

    double distanceTo(const Point2DI &arg) const {
        if (this->contains(this->L.getProjection(arg))) {
            return this->L.distanceTo(arg);
        } else {
            return min(arg.distanceTo(this->A), arg.distanceTo(this->B));
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

    Point2DD intersectWith(const Segment2DD &B) const {
        Point2DD aa, ab, ba, bb, sol;
        aa = this->A;
        ab = this->B;
        ba = B.A;
        bb = B.B;
        try {
        	sol = this->L.intersectWith(B.L);
            if (Math::abs(aa.distanceTo(sol) + sol.distanceTo(ab) - aa.distanceTo(ab)) > Math::Epsilon ||
                    Math::abs(ba.distanceTo(sol) + sol.distanceTo(bb) - ba.distanceTo(bb)) > Math::Epsilon) {
                throw 0;
            }
        } catch (string &s) {
            double DA = aa.distanceTo(ab);
            double DB = ba.distanceTo(bb);
            double DAA = aa.distanceTo(ba);
            double DAB = aa.distanceTo(bb);
            double DBA = ab.distanceTo(ba);
            double DBB = ab.distanceTo(bb);
            if ((Math::abs(DA + DAA + DB - DBB) <= Math::Epsilon && DAA > Math::Epsilon) ||
                (Math::abs(DA + DAB + DB - DBA) <= Math::Epsilon && DAB > Math::Epsilon) ||
                (Math::abs(DA + DBA + DB - DAB) <= Math::Epsilon && DBA > Math::Epsilon) ||
                (Math::abs(DA + DBB + DB - DAA) <= Math::Epsilon && DBB > Math::Epsilon)) {
            	throw "Segments don't intersect";
            }
            if ((Math::abs(DA + DB - DBB) <= Math::Epsilon && DAA <= Math::Epsilon) ||
                (Math::abs(DA + DB - DBA) <= Math::Epsilon && DAB <= Math::Epsilon)) {
                sol = aa;
            }
            if ((Math::abs(DA + DB - DAB) <= Math::Epsilon && DBA <= Math::Epsilon) ||
                (Math::abs(DA + DB - DAA) <= Math::Epsilon && DBB <= Math::Epsilon)) {
                sol = ab;
            }
        } catch (int &s) {
        	throw "Segments don't intersect";
        }
        return sol;
    }

    bool contains(const Point2DD &arg) const {
        return this->L.contains(arg) &&
                Math::abs(this->A.distanceTo(arg) + arg.distanceTo(this->B) - this->A.distanceTo(this->B)) < Math::Epsilon;
    }

    double distanceTo(const Point2DD &arg) const {
        if (this->contains(this->L.getProjection(arg))) {
            return this->L.distanceTo(arg);
        } else {
            return min(arg.distanceTo(this->A), arg.distanceTo(this->B));
        }
    }
};

class TriangleD {
private:
	Point2DD A;
	Point2DD B;
	Point2DD C;

public:
	TriangleD(const Point2DD &A, const Point2DD &B, const Point2DD &C) {
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
		return this->A.getTriangleSurface(this->B, this->C);
	}

	Point2DD getCircumscribedCircleCenter() {
		Segment2DD AB = Segment2DD(A, B);
		Segment2DD BC = Segment2DD(B, C);
		Line2DD ABmed = AB.getLine().getPerpendicular(AB.getMiddle());
		Line2DD BCmed = BC.getLine().getPerpendicular(BC.getMiddle());
		return ABmed.intersectWith(BCmed);
	}
};
