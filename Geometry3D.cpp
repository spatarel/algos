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
    return fabs(a - b) / std::max(1.0, fabs(b)) < Math::Epsilon;
  }

  bool isZero(const double a) {
    return fabs(a) < Math::Epsilon;
  }
}

class Point3DI {
private:
  long long X;
  long long Y;
  long long Z;

public:
  Point3DI() {
    this->X = 0;
    this->Y = 0;
    this->Z = 0;
  }

  Point3DI(const long long &X, const long long &Y, const long long &Z) {
    this->X = X;
    this->Y = Y;
    this->Z = Z;
  }

  void setX(const long long &X) {
    this->X = X;
  }

  long long getX() const {
    return this->X;
  }

  void setY(const long long &Y) {
    this->Y = Y;
  }

  long long getY() const {
    return this->Y;
  }

  void setZ(const long long &Y) {
    this->Z = Z;
  }

  long long getZ() const {
    return this->Z;
  }

  double getNorm() const {
    return sqrt(this->X * this->X + this->Y * this->Y + this->Z * this->Z);
  }

  long long dotProductWith(const Point3DI &arg) const {
    return this->X * arg.X + this->Y * arg.Y + this->Z * arg.Z;
  }

  Point3DI crossProductWith(const Point3DI &arg) const {
    return Point3DI(this->Y * arg.Z - this->Z * arg.Y,
                    this->Z * arg.X - this->X * arg.Z,
                    this->X * arg.Y - this->Y * arg.X);
  }

  double angleWith(const Point3DI &arg) const {
    return Math::acos(this->dotProductWith(arg) / (this->getNorm() * arg.getNorm()));
  }

  long long distanceToSq(const Point3DI& arg) const {
    long long dx = this->X - arg.X;
    long long dy = this->Y - arg.Y;
    long long dz = this->Z - arg.Z;
    return dx * dx + dy * dy + dz * dz;
  }

  double distanceTo(const Point3DI& arg) const {
    return sqrt(this->distanceToSq(arg));
  }

  bool areCollinear(const Point3DI &B, const Point3DI &C) const {
    Point3DI AB(B.X - this->X, B.Y - this->Y, B.Z - this->Z);
    Point3DI AC(C.X - this->X, C.Y - this->Y, C.Z - this->Z);
    return AB.X * AC.Y == AC.X * AB.Y
        && AB.X * AC.Z == AC.X * AB.Z
        && AB.Y * AC.Z == AC.Y * AB.Z;
  }

  double getAngle(const Point3DI &B, const Point3DI &C) const {
    Point3DI AB(B.X - this->X, B.Y - this->Y, B.Z - this->Z);
    Point3DI AC(C.X - this->X, C.Y - this->Y, C.Z - this->Z);
    return AB.angleWith(AC);
  }

  Point3DI getSymetricOf(const Point3DI &arg) const {
    return Point3DI(2 * this->X - arg.X,
                    2 * this->Y - arg.Y,
                    2 * this->Z - arg.Z);
  }
};

bool operator ==(const Point3DI &a, const Point3DI &b) {
  return a.getX() == b.getX()
      && a.getY() == b.getY()
      && a.getZ() == b.getZ();
}

bool operator !=(const Point3DI &a, const Point3DI &b) {
  return !(a == b);
}

Point3DI operator +(const Point3DI &a, const Point3DI &b) {
  return Point3DI(a.getX() + b.getX(),
                  a.getY() + b.getY(),
                  a.getZ() + b.getZ());
}

Point3DI operator -(const Point3DI &a, const Point3DI &b) {
  return Point3DI(a.getX() - b.getX(),
                  a.getY() - b.getY(),
                  a.getZ() - b.getZ());
}

Point3DI operator +(const Point3DI &a) {
  return a;
}

Point3DI operator -(const Point3DI &a) {
  return Point3DI(-a.getX(),
                  -a.getY(),
                  -a.getZ());
}

Point3DI operator *(const long long a, const Point3DI &b) {
  return Point3DI(a * b.getX(),
                  a * b.getY(),
                  a * b.getZ());
}

Point3DI operator *(const Point3DI &a, const long long b) {
  return Point3DI(a.getX() * b,
                  a.getY() * b,
                  a.getZ() * b);
}

Point3DI operator +=(Point3DI &a, const Point3DI &b) {
  return a = a + b;
}

Point3DI operator -=(Point3DI &a, const Point3DI &b) {
  return a = a - b;
}

Point3DI operator *=(Point3DI &a, const long long b) {
  return a = a * b;
}

class Point3DD {
private:
  double X;
  double Y;
  double Z;

public:
  Point3DD() {
    this->X = 0;
    this->Y = 0;
    this->Z = 0;
  }

  Point3DD(const Point3DI &arg) {
    this->X = arg.getX();
    this->Y = arg.getY();
    this->Z = arg.getZ();
  }

  Point3DD(const double &X, const double &Y, const double &Z) {
    this->X = X;
    this->Y = Y;
    this->Z = Z;
  }

  Point3DD(const Point3DD &arg) {
    this->X = arg.getX();
    this->Y = arg.getY();
    this->Z = arg.getZ();
  }

  void setX(const double &X) {
    this->X = X;
  }

  double getX() const {
    return this->X;
  }

  void setY(const double &Y) {
    this->Y = Y;
  }

  double getY() const {
    return this->Y;
  }

  void setZ(const double &Z) {
    this->Z = Z;
  }

  double getZ() const {
    return this->Z;
  }

  double getNorm() const {
    return sqrt(this->X * this->X + this->Y * this->Y + this->Z * this->Z);
  }

  double dotProductWith(const Point3DD &arg) const {
    return this->X * arg.X + this->Y * arg.Y + this->Z * arg.Z;
  }

  Point3DD crossProductWith(const Point3DD &arg) const {
    return Point3DD(this->Y * arg.Z - this->Z * arg.Y,
                    this->Z * arg.X - this->X * arg.Z,
                    this->X * arg.Y - this->Y * arg.X);
  }

  double angleWith(const Point3DD &arg) const {
    return Math::acos(this->dotProductWith(arg) / (this->getNorm() * arg.getNorm()));
  }

  double distanceToSq(const Point3DD& arg) const {
    double dx = this->X - arg.X;
    double dy = this->Y - arg.Y;
    double dz = this->Z - arg.Z;
    return dx * dx + dy * dy + dz * dz;
  }

  double distanceTo(const Point3DD& arg) const {
    return sqrt(this->distanceToSq(arg));
  }

  bool areCollinear(const Point3DD &B, const Point3DD &C) const {
    Point3DD AB(B.X - this->X, B.Y - this->Y, B.Z - this->Z);
    Point3DD AC(C.X - this->X, C.Y - this->Y, C.Z - this->Z);
    return Math::areEq(AB.X * AC.Y, AC.X * AB.Y)
        && Math::areEq(AB.X * AC.Z, AC.X * AB.Z)
        && Math::areEq(AB.Y * AC.Z, AC.Y * AB.Z);
  }

  double getAngle(const Point3DD &B, const Point3DD &C) const {
    Point3DD AB(B.X - this->X, B.Y - this->Y, B.Z - this->Z);
    Point3DD AC(C.X - this->X, C.Y - this->Y, C.Z - this->Z);
    return AB.angleWith(AC);
  }

  Point3DD getSymetricOf(const Point3DD &arg) const {
    return Point3DD(2.0 * this->X - arg.X,
                    2.0 * this->Y - arg.Y,
                    2.0 * this->Z - arg.Z);
  }
};

bool operator ==(const Point3DD &a, const Point3DD &b) {
  return Math::areEq(a.getX(), b.getX())
      && Math::areEq(a.getY(), b.getY())
      && Math::areEq(a.getZ(), b.getZ());
}

bool operator !=(const Point3DD &a, const Point3DD &b) {
  return !(a == b);
}

Point3DD operator +(const Point3DD &a, const Point3DD &b) {
  return Point3DD(a.getX() + b.getX(),
                  a.getY() + b.getY(),
                  a.getZ() + b.getZ());
}

Point3DD operator -(const Point3DD &a, const Point3DD &b) {
  return Point3DD(a.getX() - b.getX(),
                  a.getY() - b.getY(),
                  a.getZ() - b.getZ());
}

Point3DD operator +(const Point3DD &a) {
  return a;
}

Point3DD operator -(const Point3DD &a) {
  return Point3DD(-a.getX(),
                  -a.getY(),
                  -a.getZ());
}

Point3DD operator *(const double a, const Point3DD &b) {
  return Point3DD(a * b.getX(),
                  a * b.getY(),
                  a * b.getZ());
}

Point3DD operator *(const Point3DD &a, const double b) {
  return Point3DD(a.getX() * b,
                  a.getY() * b,
                  a.getZ() * b);
}

Point3DD operator /(const Point3DD &a, const double b) {
  return a * (1.0 / b);
}

Point3DD operator +=(Point3DD &a, const Point3DD &b) {
  return a = a + b;
}

Point3DD operator -=(Point3DD &a, const Point3DD &b) {
  return a = a - b;
}

Point3DD operator *=(Point3DD &a, const double b) {
  return a = a * b;
}

Point3DD operator /=(Point3DD &a, const double b) {
  return a = a / b;
}

class Point3DP {
private:
  double distance;
  double latitude;
  double longitude;

public:
  Point3DP() {
    this->distance = 0;
    this->latitude = 0;
    this->longitude = 0;
  }

  Point3DP(const double X, const double Y, const double Z) {
    this->distance = sqrt(X * X + Y * Y + Z * Z);
    this->latitude = Math::asin(Z / this->distance); // -PI/2..PI/2
    this->longitude = atan2(Y, X);                   //  -PI .. PI
  }

  Point3DP(const Point3DD &arg) {
    *this = Point3DP(arg.getX(), arg.getY(), arg.getZ());
  }

  void setDistance(const double distance) {
    this->distance = distance;
  }

  double getDistance() const {
    return this->distance;
  }

  void setLatitude(const double latitude) {
    this->latitude = latitude;
  }

  double getLatitude() const {
    return this->latitude;
  }

  void setLongitude(const double longitude) {
    this->longitude = longitude;
  }

  double getLongitude() const {
    return this->longitude;
  }

  Point3DD getPoint3DD() const {
    return Point3DD(
      this->distance * cos(this->latitude) * cos(this->longitude),
      this->distance * cos(this->latitude) * sin(this->longitude),
      this->distance * sin(this->latitude));
  }
};

class Plane3DI {
private:
  long long A;
  long long B;
  long long C;
  long long D;
  double invNorm;

  void normalize() {
    this->invNorm = 1.0 / sqrt((double)this->A * this->A
                             + (double)this->B * this->B
                             + (double)this->C * this->C);
  }

public:
  Plane3DI(const Point3DI& A, const Point3DI& B, const Point3DI& C) {
    this->A = + B.getY() * C.getZ()
              - A.getY() * C.getZ()
              - B.getZ() * C.getY()
              + A.getZ() * C.getY()
              + A.getY() * B.getZ()
              - A.getZ() * B.getY();

    this->B = + A.getX() * C.getZ()
              - B.getX() * C.getZ()
              - A.getX() * B.getZ()
              + A.getZ() * B.getX()
              + B.getZ() * C.getX()
              - A.getZ() * C.getX();

    this->C = + A.getX() * B.getY()
              - A.getY() * B.getX()
              - A.getX() * C.getY()
              + B.getX() * C.getY()
              + A.getY() * C.getX()
              - B.getY() * C.getX();

    this->D = - A.getX() * B.getY() * C.getZ()
              + A.getY() * B.getX() * C.getZ()
              + A.getX() * B.getZ() * C.getY()
              - A.getZ() * B.getX() * C.getY()
              - A.getY() * B.getZ() * C.getX()
              + A.getZ() * B.getY() * C.getX();
    this->normalize();
  }

  Plane3DI(const long long A, const long long B, const long long C, const long long D) {
    this->A = A;
    this->B = B;
    this->C = C;
    this->D = D;
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

  long long getD() const {
    return this->D;
  }

  Point3DI getNormal() const {
    return Point3DI(this->getA(), this->getB(), this->getC());
  }

  long long getPointSign(const Point3DI& arg) const {
    return this->A * arg.getX() + this->B * arg.getY() + this->C * arg.getZ() + this->D;
  }

  double getPointSign(const Point3DD& arg) const {
    return this->A * arg.getX() + this->B * arg.getY() + this->C * arg.getZ() + this->D;
  }

  double distanceTo(const Point3DI& arg) const {
    return abs(this->getPointSign(arg)) * this->invNorm;
  }

  double distanceTo(const Point3DD& arg) const {
    return fabs(this->getPointSign(arg)) * this->invNorm;
  }

  bool contains(const Point3DI& arg) const {
    return this->getPointSign(arg) == 0;
  }

  bool contains(const Point3DD& arg) const {
    return Math::isZero(this->getPointSign(arg));
  }

  Point3DD getProjection(const Point3DD &arg) const {
    double p = (double)this->getPointSign(arg)
             / (this->A * this->A + this->B * this->B + this->C * this->C);
    return Point3DD(arg.getX() - p * this->getNormal().getX(),
                    arg.getY() - p * this->getNormal().getY(),
                    arg.getZ() - p * this->getNormal().getZ());
  }
};

class Plane3DD {
private:
  double A;
  double B;
  double C;
  double D;
  double invNorm;

  void normalize() {
    this->invNorm = 1.0 / sqrt(this->A * this->A
                             + this->B * this->B
                             + this->C * this->C);
  }

public:
  Plane3DD(const Point3DD& A, const Point3DD& B, const Point3DD& C) {
    this->A = + B.getY() * C.getZ()
              - A.getY() * C.getZ()
              - B.getZ() * C.getY()
              + A.getZ() * C.getY()
              + A.getY() * B.getZ()
              - A.getZ() * B.getY();

    this->B = + A.getX() * C.getZ()
              - B.getX() * C.getZ()
              - A.getX() * B.getZ()
              + A.getZ() * B.getX()
              + B.getZ() * C.getX()
              - A.getZ() * C.getX();

    this->C = + A.getX() * B.getY()
              - A.getY() * B.getX()
              - A.getX() * C.getY()
              + B.getX() * C.getY()
              + A.getY() * C.getX()
              - B.getY() * C.getX();

    this->D = - A.getX() * B.getY() * C.getZ()
              + A.getY() * B.getX() * C.getZ()
              + A.getX() * B.getZ() * C.getY()
              - A.getZ() * B.getX() * C.getY()
              - A.getY() * B.getZ() * C.getX()
              + A.getZ() * B.getY() * C.getX();
    this->normalize();
  }

  Plane3DD(const double A, const double B, const double C, const double D) {
    this->A = A;
    this->B = B;
    this->C = C;
    this->D = D;
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

  double getD() const {
    return this->D;
  }

  Point3DD getNormal() const {
    return Point3DD(this->getA(), this->getB(), this->getC());
  }

  double getPointSign(const Point3DD& arg) const {
    return this->A * arg.getX() + this->B * arg.getY() + this->C * arg.getZ() + this->D;
  }

  double distanceTo(const Point3DD& arg) const {
    return fabs(this->getPointSign(arg)) * this->invNorm;
  }

  bool contains(const Point3DD& arg) const {
    return Math::isZero(this->getPointSign(arg));
  }

  Point3DD getProjection(const Point3DD &arg) const {
    double p = this->getPointSign(arg)
             / (this->A * this->A + this->B * this->B + this->C * this->C);
    return Point3DD(arg.getX() - p * this->getNormal().getX(),
                    arg.getY() - p * this->getNormal().getY(),
                    arg.getZ() - p * this->getNormal().getZ());
  }
};
