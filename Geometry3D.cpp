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

class Vector3DI {
private:
    long long X;
    long long Y;
    long long Z;
public:
    Vector3DI() {
        this->X = 0;
        this->Y = 0;
        this->Z = 0;
    }

    Vector3DI(const long long &X, const long long &Y, const long long &Z) {
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

    void setZ(const long long &Z) {
        this->Z = Z;
    }

    long long getZ() const {
        return this->Z;
    }

    double getNorm() const {
        return sqrt(this->X * this->X + this->Y * this->Y + this->Z * this->Z);
    }

    long long dotProductWith(const Vector3DI &arg) const {
        return this->X * arg.getX() + this->Y * arg.getY() + this->Z * arg.getZ();
    }

    Vector3DI crossProductWith(const Vector3DI &arg) const {
        return Vector3DI(
            this->Y * arg.getZ() - this->Z * arg.getY(),
            this->Z * arg.getX() - this->X * arg.getZ(),
            this->X * arg.getY() - this->Y * arg.getX());
    }

    double angleWith(const Vector3DI &arg) const {
        return Math::acos(this->dotProductWith(arg) / (this->getNorm() * arg.getNorm()));
    }
};

class Vector3DD {
private:
    double X;
    double Y;
    double Z;
public:
    Vector3DD() {
        this->X = 0;
        this->Y = 0;
        this->Z = 0;
    }

    Vector3DD(const double &X, const double &Y, const double &Z) {
        this->X = X;
        this->Y = Y;
        this->Z = Z;
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

    double dotProductWith(const Vector3DD &arg) const {
        return this->X * arg.getX() + this->Y * arg.getY() + this->Z * arg.getZ();
    }

    Vector3DD crossProductWith(const Vector3DD &arg) const {
        return Vector3DD(
            this->Y * arg.getZ() - this->Z * arg.getY(),
            this->Z * arg.getX() - this->X * arg.getZ(),
            this->X * arg.getY() - this->Y * arg.getX());
    }

    double angleWith(const Vector3DD &arg) const {
        return Math::acos(this->dotProductWith(arg) / (this->getNorm() * arg.getNorm()));
    }
};

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

    Point3DI(const Vector3DI &arg) {
        this->X = arg.getX();
        this->Y = arg.getY();
        this->Z = arg.getZ();
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

    double distanceTo(const Point3DI& arg) const {
        return sqrt((this->X - arg.X) * (this->X - arg.X) +
                    (this->Y - arg.Y) * (this->Y - arg.Y) +
                    (this->Z - arg.Z) * (this->Z - arg.Z));
    }
};

Point3DI operator +(const Point3DI &a, const Point3DI &b) {
    return Point3DI(a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
}

Point3DI operator -(const Point3DI &a, const Point3DI &b) {
    return Point3DI(a.getX() - b.getX(), a.getY() - b.getY(), a.getZ() - b.getZ());
}

Point3DI operator *(long long a, const Point3DI &b) {
    return Point3DI(a * b.getX(), a * b.getY(), a * b.getZ());
}

Point3DI operator *(const Point3DI &a, long long b) {
    return Point3DI(a.getX() * b, a.getY() * b, a.getZ() * b);
}

Point3DI operator +=(Point3DI &a, const Point3DI &b) {
    return a = a + b;
}

Point3DI operator -=(Point3DI &a, const Point3DI &b) {
    return a = a - b;
}

Point3DI operator *=(Point3DI &a, long long b) {
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

    Point3DD(const Vector3DD &arg) {
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

    double distanceTo(const Point3DD& arg) const {
        return sqrt((this->X - arg.X) * (this->X - arg.X) +
                    (this->Y - arg.Y) * (this->Y - arg.Y) +
                    (this->Z - arg.Z) * (this->Z - arg.Z));
    }

    Vector3DD getVectorWith(const Point3DD &arg) const {
        return Vector3DD(arg.X - this->X,
                         arg.Y - this->Y,
                         arg.Z - this->Z);
    }

    double getAngle(const Point3DD &B, const Point3DD &C) const {
        Vector3DD AB = this->getVectorWith(B);
        Vector3DD AC = this->getVectorWith(C);
        double answer = AB.angleWith(AC);
        return answer;
    }

    Point3DD getSymetricOf(const Point3DD &arg) const {
        return Point3DD(2 * this->X - arg.X,
                        2 * this->Y - arg.Y,
                        2 * this->Z - arg.Z);
    }
};

Point3DD operator +(const Point3DD &a, const Point3DD &b) {
    return Point3DD(a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
}

Point3DD operator -(const Point3DD &a, const Point3DD &b) {
    return Point3DD(a.getX() - b.getX(), a.getY() - b.getY(), a.getZ() - b.getZ());
}

Point3DD operator *(double a, const Point3DD &b) {
    return Point3DD(a * b.getX(), a * b.getY(), a * b.getZ());
}

Point3DD operator *(const Point3DD &a, double b) {
    return Point3DD(a.getX() * b, a.getY() * b, a.getZ() * b);
}

Point3DD operator /(const Point3DD &a, double b) {
    return Point3DD(a.getX() / b, a.getY() / b, a.getZ() / b);
}

Point3DD operator +=(Point3DD &a, const Point3DD &b) {
    return a = a + b;
}

Point3DD operator -=(Point3DD &a, const Point3DD &b) {
    return a = a - b;
}

Point3DD operator *=(Point3DD &a, double b) {
    return a = a * b;
}

Point3DD operator /=(Point3DD &a, double b) {
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

    void setDistance(double distance) {
        this->distance = distance;
    }

    double getDistance() {
        return this->distance;
    }

    void setLatitude(double latitude) {
        this->latitude = latitude;
    }

    double getLatitude() {
        return this->latitude;
    }

    void setLongitude(double longitude) {
        this->longitude = longitude;
    }

    double getLongitude() {
        return this->longitude;
    }

    Point3DD getPoint3DD() {
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
    double norm;

    double computeNorm() {
        return sqrt(this->A * this->A
                  + this->B * this->B
                  + this->C * this->C);
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
        this->norm = this->computeNorm();
    }

    Plane3DI(long long A, long long B, long long C, long long D) {
        this->A = A;
        this->B = B;
        this->C = C;
        this->D = D;
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

    long long getD() const {
        return this->D;
    }

    double distanceTo(const Point3DI& arg) const {
        return abs(this->A * arg.getX() + this->B * arg.getY() + this->C * arg.getZ() + this->D) / this->norm;
    }

    long long getPointSign(const Point3DI& arg) const {
        return this->A * arg.getX() + this->B * arg.getY() + this->C * arg.getZ() + this->D;
    }

    double getPointSign(const Point3DD& arg) const {
        return this->A * arg.getX() + this->B * arg.getY() + this->C * arg.getZ() + this->D;
    }

    bool contains(const Point3DI& arg) const {
        return this->getPointSign(arg) == 0;
    }

    bool contains(const Point3DD& arg) const {
        return Math::areEq(this->getPointSign(arg), 0);
    }

    Vector3DI getNormal() const {
        return Vector3DI(this->getA(), this->getB(), this->getC());
    }
};

class Plane3DD {
private:
    double A;
    double B;
    double C;
    double D;
    double norm;

    double computeNorm() {
        return sqrt(this->A * this->A
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
        this->norm = this->computeNorm();
    }

    Plane3DD(double A, double B, double C, double D) {
        this->A = A;
        this->B = B;
        this->C = C;
        this->D = D;
        this->norm = this->computeNorm();
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

    double distanceTo(const Point3DD& arg) const {
        return abs(this->A * arg.getX() + this->B * arg.getY() + this->C * arg.getZ() + this->D) / this->norm;
    }

    double getPointSign(const Point3DD& arg) const {
        return this->A * arg.getX() + this->B * arg.getY() + this->C * arg.getZ() + this->D;
    }

    bool contains(const Point3DD& arg) const {
        return Math::areEq(this->getPointSign(arg), 0);
    }

    Vector3DD getNormal() const {
        return Vector3DD(this->getA(), this->getB(), this->getC());
    }
};
