#include <cmath>

namespace Math {
  const double PI = 4.0 * atan(1.0);
  const double Epsilon = 1e-6;

  double asin(const double arg) {
    return ::asin(std::max(-1.0, std::min(1.0, arg)));
  }

  double acos(const double arg) {
    return ::acos(std::max(-1.0, std::min(1.0, arg)));
  }

  const double DEG_TO_RAD = PI / 180.0;
  double degToRad(const double deg) {
    return deg * DEG_TO_RAD;
  }

  const double RAD_TO_DEG = 180.0 / PI;
  double radToDeg(const double rad) {
    return rad * RAD_TO_DEG;
  }

  bool areEq(const double a, const double b) {
    return fabs((a - b) / std::max(1.0, b)) < Math::Epsilon;
  }

  bool isZero(const double a) {
    return fabs(a) < Math::Epsilon;
  }

  template<class C>
  void sort(C &a, C &b) {
    if (a > b) {
      std::swap(a, b);
    }
  }
}

class Point2DI {
private:
  long long X;
  long long Y;

public:
  Point2DI() {
    this->X = 0;
    this->Y = 0;
  }

  Point2DI(const long long X, const long long Y) {
    this->X = X;
    this->Y = Y;
  }

  void setX(const long long X) {
    this->X = X;
  }

  long long getX() const {
    return this->X;
  }

  void setY(const long long Y) {
    this->Y = Y;
  }

  long long getY() const {
    return this->Y;
  }

  double getNorm() const {
    return sqrt(this->X * this->X + this->Y * this->Y);
  }

  long long dotProductWith(const Point2DI &arg) const {
      return this->X * arg.X + this->Y * arg.Y;
  }

  double angleWith(const Point2DI &arg) const {
      return Math::acos(this->dotProductWith(arg) / (this->getNorm() * arg.getNorm()));
  }

  double distanceTo(const Point2DI &arg) const {
    long long dx = this->X - arg.X;
    long long dy = this->Y - arg.Y;
    return sqrt(dx * dx + dy * dy);
  }

  long long getAreaSgn2(const Point2DI &A, const Point2DI &B) const {
    return A.X * (B.Y - this->Y)
         + B.X * (this->Y - A.Y)
         + this->X * (A.Y - B.Y);
  }

  bool areCollinear(const Point2DI &A, const Point2DI &B) const {
    return this->getAreaSgn2(A, B) == 0;
  }

  double getAngle(const Point2DI &B, const Point2DI &C) const {
    Point2DI AB(B.X - this->X, B.Y - this->Y);
    Point2DI AC(C.X - this->X, C.Y - this->Y);
    return AB.angleWith(AC);
  }

  Point2DI getSymetricOf(const Point2DI &arg) const {
    return Point2DI(2 * this->X - arg.X,
                    2 * this->Y - arg.Y);
  }
};

bool operator ==(const Point2DI &a, const Point2DI &b) {
  return a.getX() == b.getX() && a.getY() == b.getY();
}

bool operator !=(const Point2DI &a, const Point2DI &b) {
  return !(a == b);
}

Point2DI operator +(const Point2DI &a, const Point2DI &b) {
  return Point2DI(a.getX() + b.getX(), a.getY() + b.getY());
}

Point2DI operator -(const Point2DI &a, const Point2DI &b) {
  return Point2DI(a.getX() - b.getX(), a.getY() - b.getY());
}

Point2DI operator +(const Point2DI &a) {
  return a;
}

Point2DI operator -(const Point2DI &a) {
  return Point2DI(-a.getX(),
                  -a.getY());
}

Point2DI operator *(const long long a, const Point2DI &b) {
  return Point2DI(a * b.getX(), a * b.getY());
}

Point2DI operator *(const Point2DI &a, const long long b) {
  return Point2DI(a.getX() * b, a.getY() * b);
}

Point2DI operator +=(Point2DI &a, const Point2DI &b) {
  return a = a + b;
}

Point2DI operator -=(Point2DI &a, const Point2DI &b) {
  return a = a - b;
}

Point2DI operator *=(Point2DI &a, const long long b) {
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

  Point2DD(const double X, const double Y) {
    this->X = X;
    this->Y = Y;
  }

  Point2DD(const Point2DI &arg) {
    this->X = arg.getX();
    this->Y = arg.getY();
  }

  void setX(const double X) {
    this->X = X;
  }

  double getX() const {
    return this->X;
  }

  void setY(const double Y) {
    this->Y = Y;
  }

  double getY() const {
    return this->Y;
  }

  double getNorm() const {
    return sqrt(this->X * this->X + this->Y * this->Y);
  }

  double dotProductWith(const Point2DD &arg) const {
    return this->X * arg.X + this->Y * arg.Y;
  }

  double angleWith(const Point2DD &arg) const {
    return Math::acos(this->dotProductWith(arg) / (this->getNorm() * arg.getNorm()));
  }

  double distanceTo(const Point2DD &arg) const {
    double dx = this->X - arg.X;
    double dy = this->Y - arg.Y;
    return sqrt(dx * dx + dy * dy);
  }

  double getAreaSgn2(const Point2DD &A, const Point2DD &B) const {
    return A.X * (B.Y - this->Y)
         + B.X * (this->Y - A.Y)
         + this->X * (A.Y - B.Y);
  }

  bool areCollinear(const Point2DD &A, const Point2DD &B) const {
    return Math::isZero(this->getAreaSgn2(A, B));
  }

  double getAngle(const Point2DD &B, const Point2DD &C) const {
    Point2DD AB(B.X - this->X, B.Y - this->Y);
    Point2DD AC(C.X - this->X, C.Y - this->Y);
    return AB.angleWith(AC);
  }

  Point2DD getSymetricOf(const Point2DD &arg) const {
    return Point2DD(2.0 * this->X - arg.X,
                    2.0 * this->Y - arg.Y);
  }
};

bool operator ==(const Point2DD &a, const Point2DD &b) {
  return Math::areEq(a.getX(), b.getX())
      && Math::areEq(a.getY(), b.getY());
}

bool operator !=(const Point2DD &a, const Point2DD &b) {
  return !(a == b);
}

Point2DD operator +(const Point2DD &a, const Point2DD &b) {
  return Point2DD(a.getX() + b.getX(), a.getY() + b.getY());
}

Point2DD operator -(const Point2DD &a, const Point2DD &b) {
  return Point2DD(a.getX() - b.getX(), a.getY() - b.getY());
}

Point2DD operator +(const Point2DD &a) {
  return a;
}

Point2DD operator -(const Point2DD &a) {
  return Point2DD(-a.getX(), -a.getY());
}

Point2DD operator *(const double a, const Point2DD &b) {
  return Point2DD(a * b.getX(), a * b.getY());
}

Point2DD operator *(const Point2DD &a, const double b) {
  return Point2DD(a.getX() * b, a.getY() * b);
}

Point2DD operator /(const Point2DD &a, const double b) {
  return a * (1.0 / b);
}

Point2DD operator +=(Point2DD &a, const Point2DD &b) {
  return a = a + b;
}

Point2DD operator -=(Point2DD &a, const Point2DD &b) {
  return a = a - b;
}

Point2DD operator *=(Point2DD &a, const double b) {
  return a = a * b;
}

Point2DD operator /=(Point2DD &a, const double b) {
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

  void setDistance(const double distance) {
    this->distance = distance;
  }

  double getDistance() const {
    return this->distance;
  }

  void setAngle(const double angle) {
    this->angle = angle;
  }

  double getAngle() const {
    return this->angle;
  }

  Point2DD getPoint2DD() const {
    return Point2DD(this->distance * cos(this->angle),
                    this->distance * sin(this->angle));
  }
};

class Line2DI {
private:
  long long A;
  long long B;
  long long C;
  double invNorm;

  void normalize() {
    this->invNorm = 1.0 / sqrt(this->A * this->A + this->B * this->B);
  }

public:
  Line2DI(const Point2DI &A, const Point2DI &B) {
    this->A = A.getY() - B.getY();
    this->B = B.getX() - A.getX();
    this->C = A.getX() * B.getY() - B.getX() * A.getY();
    this->normalize();
  }

  Line2DI(const long long A, const long long B, const long long C) {
    this->A = A;
    this->B = B;
    this->C = C;
    this->normalize();
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

  Point2DI getNormal() const {
    return Point2DI(this->getA(), this->getB());
  }

  bool isParallelWith(const Line2DI &arg) const {
    return this->A * arg.B == arg.A * this->B;
  }

  bool isTheSameAs(const Line2DI &arg) const {
    return this->isParallelWith(arg)
        && this->A * arg.C == arg.A * this->C
        && this->B * arg.C == arg.B * this->C;
  }

  Point2DD intersectWith(const Line2DI &arg) const {
    return Point2DD(((double)arg.C * this->B - (double)this->C * arg.B) / (this->A * arg.B - this->B * arg.A),
                    ((double)arg.C * this->A - (double)this->C * arg.A) / (this->B * arg.A - this->A * arg.B));
  }

  long long getPointSign(const Point2DI &arg) const {
    return this->A * arg.getX() + this->B * arg.getY() + this->C;
  }

  double getPointSign(const Point2DD &arg) const {
    return this->A * arg.getX() + this->B * arg.getY() + this->C;
  }

  double distanceTo(const Point2DI &arg) const {
    return abs(this->getPointSign(arg)) * this->invNorm;
  }

  double distanceTo(const Point2DD &arg) const {
    return fabs(this->getPointSign(arg)) * this->invNorm;
  }

  bool contains(const Point2DI &arg) const {
    return this->getPointSign(arg) == 0;
  }

  bool contains(const Point2DD &arg) const {
    return Math::isZero(this->getPointSign(arg));
  }

  Line2DI getPerpendicular(const Point2DI &arg) const {
    return Line2DI(this->B, -this->A,
      -(this->B * arg.getX() - this->A * arg.getY()));
  }

  Line2DI getParallel(const Point2DI &arg) const {
    return Line2DI(this->A, this->B,
      -(this->A * arg.getX() + this->B * arg.getY()));
  }

  Point2DD getProjection(const Point2DI &arg) const {
    return this->intersectWith(this->getPerpendicular(arg));
  }

  Point2DD getPointAtDistance(const Point2DD &arg, const double distance) const {
    return Point2DD(arg.getX() + this->B * distance * this->invNorm,
                    arg.getY() - this->A * distance * this->invNorm);
  }
};

class Line2DD {
private:
  double A;
  double B;
  double C;
  double invNorm;

  void normalize() {
    this->invNorm = 1.0 / sqrt(this->A * this->A + this->B * this->B);
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

  Point2DD getNormal() const {
    return Point2DD(this->getA(), this->getB());
  }

  bool isParallelWith(const Line2DD &arg) const {
    return Math::areEq(this->A * arg.B, arg.A * this->B);
  }

  bool isTheSameAs(const Line2DD &arg) const {
    return this->isParallelWith(arg)
        && Math::areEq(this->A * arg.C, arg.A * this->C)
        && Math::areEq(this->B * arg.C, arg.B * this->C);
  }

  Point2DD intersectWith(const Line2DD &arg) const {
    return Point2DD((arg.C * this->B - this->C * arg.B) / (this->A * arg.B - this->B * arg.A),
                    (arg.C * this->A - this->C * arg.A) / (this->B * arg.A - this->A * arg.B));
  }

  double getPointSign(const Point2DD &arg) const {
    return this->A * arg.getX() + this->B * arg.getY() + this->C;
  }

  double distanceTo(const Point2DD &arg) const {
    return fabs(this->getPointSign(arg)) * this->invNorm;
  }

  bool contains(const Point2DD &arg) const {
    return Math::isZero(this->getPointSign(arg) * this->invNorm);
  }

  Line2DD getPerpendicular(const Point2DD &arg) const {
    return Line2DD(this->B, -this->A,
      -(this->B * arg.getX() - this->A * arg.getY()));
  }

  Line2DD getParallel(const Point2DD &arg) const {
    return Line2DD(this->A, this->B,
      -(this->A * arg.getX() + this->B * arg.getY()));
  }

  Point2DD getProjection(const Point2DD &arg) const {
    return this->intersectWith(this->getPerpendicular(arg));
  }

  Point2DD getSymetricOf(const Point2DD &arg) const {
    return this->getProjection(arg).getSymetricOf(arg);
  }

  Point2DD getPointAtDistance(const Point2DD &arg, const double distance) const {
    return Point2DD(arg.getX() + this->B * distance * this->invNorm,
                    arg.getY() - this->A * distance * this->invNorm);
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

  Point2DI getA() const {
    return this->A;
  }

  Point2DI getB() const {
    return this->B;
  }

  Line2DI getLine() const {
    return this->L;
  }

  bool isParallelWith(const Segment2DI &B) const {
    return this->L.isParallelWith(B.L);
  }

  bool isIntersectingWithP(const Segment2DI &B) const {
    if (this->L.isTheSameAs(B.L)) {
      long long AAX = this->A.getX(), ABX = this->B.getX(); Math::sort(AAX, ABX);
      long long AAY = this->A.getY(), ABY = this->B.getY(); Math::sort(AAY, ABY);
      long long BAX = B.A.getX(), BBX = B.B.getX(); Math::sort(BAX, BBX);
      long long BAY = B.A.getY(), BBY = B.B.getY(); Math::sort(BAY, BBY);
      return (BAX <= ABX) & (AAX <= BBX)
           & (BAY <= ABY) & (AAY <= BBY);
    } else {
      return false;
    }
  }

  bool isIntersectingWithNonP(const Segment2DI &B) const {
    long long aa = B.L.getPointSign(this->A);
    long long ab = B.L.getPointSign(this->B);
    long long ba = this->L.getPointSign(B.A);
    long long bb = this->L.getPointSign(B.B);
    Math::sort(aa, ab);
    Math::sort(ba, bb);
    return (aa <= 0) & (0 <= ab)
         & (ba <= 0) & (0 <= bb);
  }

  Point2DD intersectWith(const Segment2DI &B) const {
    return this->L.intersectWith(B.L);
  }

  bool contains(const Point2DI &arg) const {
    if (this->L.contains(arg)) {
      long long minX = this->A.getX(), maxX = this->B.getX(); Math::sort(minX, maxX);
      long long minY = this->A.getY(), maxY = this->B.getY(); Math::sort(minY, maxY);
      return (minX <= arg.getX()) & (arg.getX() <= maxX)
           & (minY <= arg.getY()) & (arg.getY() <= maxY);
    } else {
      return false;
    }
  }

  bool contains(const Point2DD &arg) const {
    if (this->L.contains(arg)) {
      long long minX = this->A.getX(), maxX = this->B.getX(); Math::sort(minX, maxX);
      long long minY = this->A.getY(), maxY = this->B.getY(); Math::sort(minY, maxY);
      return (minX <= arg.getX()) & (arg.getX() <= maxX)
           & (minY <= arg.getY()) & (arg.getY() <= maxY);
    } else {
      return false;
    }
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

  Point2DD getA() const {
    return this->A;
  }

  Point2DD getB() const {
    return this->B;
  }

  Line2DD getLine() const {
    return this->L;
  }

  bool isParallelWith(const Segment2DD &B) const {
    return this->L.isParallelWith(B.L);
  }

  bool isIntersectingWithP(const Segment2DD &B) const {
    if (this->L.isTheSameAs(B.L)) {
      double AAX = this->A.getX(), ABX = this->B.getX(); Math::sort(AAX, ABX);
      double AAY = this->A.getY(), ABY = this->B.getY(); Math::sort(AAY, ABY);
      double BAX = B.A.getX(), BBX = B.B.getX(); Math::sort(BAX, BBX);
      double BAY = B.A.getY(), BBY = B.B.getY(); Math::sort(BAY, BBY);
      return (BAX <= ABX) & (AAX <= BBX)
           & (BAY <= ABY) & (AAY <= BBY);
    } else {
      return false;
    }
  }

  bool isIntersectingWithNonP(const Segment2DD &B) const {
    double aa = B.L.getPointSign(this->A);
    double ab = B.L.getPointSign(this->B);
    double ba = this->L.getPointSign(B.A);
    double bb = this->L.getPointSign(B.B);
    Math::sort(aa, ab);
    Math::sort(ba, bb);
    return (aa <= 0) & (0 <= ab)
         & (ba <= 0) & (0 <= bb);
  }

  Point2DD intersectWith(const Segment2DD &B) const {
    return this->L.intersectWith(B.L);
  }

  bool contains(const Point2DD &arg) const {
    if (this->L.contains(arg)) {
      double minX = this->A.getX(), maxX = this->B.getX(); Math::sort(minX, maxX);
      double minY = this->A.getY(), maxY = this->B.getY(); Math::sort(minY, maxY);
      return (minX <= arg.getX()) & (arg.getX() <= maxX)
           & (minY <= arg.getY()) & (arg.getY() <= maxY);
    } else {
      return false;
    }
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

  double getArea() const {
    return fabs(this->A.getAreaSgn2(this->B, this->C)) / 2.0;
  }

  Point2DD getCircumcenter() const { // circumscribed circle center
    Line2DD AB(A, B);
    Line2DD BC(B, C);
    Line2DD ABmed = AB.getPerpendicular((A + B) / 2);
    Line2DD BCmed = BC.getPerpendicular((B + C) / 2);
    return ABmed.intersectWith(BCmed);
  }

  Point2DD getOrthocenter() const { // nine-point circle center
    Line2DD AB(A, B);
    Line2DD BC(B, C);
    Line2DD ABalt = AB.getPerpendicular(C);
    Line2DD BCalt = BC.getPerpendicular(A);
    return ABalt.intersectWith(BCalt);
  }

  Point2DD getCentroid() const { // center of mass
    return (A + B + C) / 3;
  }
};


#include <algorithm>
#include <vector>
class Geometry {
private:
  static bool cmpByYX(const Point2DI &A, const Point2DI &B) {
    return (A.getY() < B.getY())
        || (A.getY() == B.getY() && A.getX() < B.getX());
  }

  static bool cmpByYX(const Point2DD &A, const Point2DD &B) {
    return (A.getY() < B.getY())
        || (A.getY() == B.getY() && A.getX() < B.getX());
  }

  static bool cmpByNorm(const Point2DI &A, const Point2DI &B) {
    return A.getX() * A.getX() + A.getY() * A.getY()
         < B.getX() * B.getX() + B.getY() * B.getY();
  }

  static bool cmpByNorm(const Point2DD &A, const Point2DD &B) {
    return A.getX() * A.getX() + A.getY() * A.getY()
         < B.getX() * B.getX() + B.getY() * B.getY();
  }

  static bool eqByPolarAngle(const Point2DI &A, const Point2DI &B) {
    return A.getX() * B.getY() == A.getY() * B.getX();
  }

  static bool eqByPolarAngle(const Point2DD &A, const Point2DD &B) {
    return A.getX() * B.getY() == A.getY() * B.getX();
  }

  static bool cmpByPolarAngleAndNormI(const Point2DI &A, const Point2DI &B) {
    return (A.getX() * B.getY() - A.getY() * B.getX() > 0)
        || (A.getX() * B.getY() - A.getY() * B.getX() == 0 && cmpByNorm(A, B));
  }

  static bool cmpByPolarAngleAndNormD(const Point2DD &A, const Point2DD &B) {
    return (A.getX() * B.getY() - A.getY() * B.getX() > 0)
        || (A.getX() * B.getY() - A.getY() * B.getX() == 0 && cmpByNorm(A, B));
  }

public:
  static long long areaSgn2(const Point2DI &A, const Point2DI &B, const Point2DI &C) {
    return A.getAreaSgn2(B, C);
  }

  static double areaSgn2(const Point2DD &A, const Point2DD &B, const Point2DD &C) {
    return A.getAreaSgn2(B, C);
  }

  static std::vector<Point2DI> convexHull(std::vector<Point2DI> points) {
    for (int i = 1; i < (int)points.size(); i++) {
      if (!cmpByYX(points[0], points[i])) {
        std::swap(points[0], points[i]);
      }
    }
    Point2DI T = points[0];
    for (Point2DI &point : points) {
      point -= T;
    }
    std::sort(points.begin() + 1, points.end(), cmpByPolarAngleAndNormI);

    std::vector<Point2DI> newPoints;
    newPoints.push_back(points[0]);
    newPoints.push_back(points[1]);
    for (int i = 2; i < (int)points.size(); i++) {
      if (eqByPolarAngle(points[i - 1], points[i])) {
        newPoints.pop_back();
      }
      newPoints.push_back(points[i]);
    }

    points = newPoints;
    for (Point2DI &point : points) {
      point += T;
    }

    std::vector<Point2DI> convexHull;
    for (const Point2DI &point : points) {
      while (convexHull.size() >= 2 && areaSgn2(
        convexHull.end()[-2], convexHull.end()[-1], point) < 0) {
        convexHull.pop_back();
      }
      convexHull.push_back(point);
    }
    return convexHull;
  }

  static std::vector<Point2DD> convexHull(std::vector<Point2DD> points) {
    for (int i = 1; i < (int)points.size(); i++) {
      if (!cmpByYX(points[0], points[i])) {
        std::swap(points[0], points[i]);
      }
    }
    Point2DD T = points[0];
    for (Point2DD &point : points) {
      point -= T;
    }
    std::sort(points.begin() + 1, points.end(), cmpByPolarAngleAndNormD);

    std::vector<Point2DD> newPoints;
    newPoints.push_back(points[0]);
    newPoints.push_back(points[1]);
    for (int i = 2; i < (int)points.size(); i++) {
      if (eqByPolarAngle(points[i - 1], points[i])) {
        newPoints.pop_back();
      }
      newPoints.push_back(points[i]);
    }

    points = newPoints;
    for (Point2DD &point : points) {
      point += T;
    }

    std::vector<Point2DD> convexHull;
    for (const Point2DD &point : points) {
      while (convexHull.size() >= 2 && areaSgn2(
        convexHull.end()[-2], convexHull.end()[-1], point) < 0) {
        convexHull.pop_back();
      }
      convexHull.push_back(point);
    }
    return convexHull;
  }

  static long long areaSgn2(const std::vector<Point2DI> &points) {
    long long answer = 0;
    int sz = points.size();
    for (int i = 1; i + 1 < sz; i++) {
      answer += points[0].getAreaSgn2(points[i], points[(i + 1) % sz]);
    }
    return answer;
  }

  static double areaSgn2(const std::vector<Point2DD> &points) {
    double answer = 0.0;
    int sz = points.size();
    for (int i = 1; i + 1 < sz; i++) {
      answer += points[0].getAreaSgn2(points[i], points[(i + 1) % sz]);
    }
    return answer;
  }
};
