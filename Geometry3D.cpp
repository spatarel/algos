#include <cmath>

class Math {
public:
    static const double PI;

    static const double Epsilon;

    static long long abs(long long val){
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

    static long long min(long long arg1, long long arg2) {
        if (arg1 < arg2) {
            return arg1;
        } else {
            return arg2;
        }
    }

    static double min(double arg1, double arg2) {
        if (arg1 < arg2) {
            return arg1;
        } else {
            return arg2;
        }
    }
};

const double Math::PI = 3.14159265358979323846264338327950288419716939937510;

const double Math::Epsilon = 0.000001;

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

    Point3DI(const long long X, const long long Y, const long long Z) {
        this->X = X;
        this->Y = Y;
        this->Z = Z;
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

    void setZ(long long Y) {
        this->Z = Z;
    }

    long long getZ() const {
        return this->Z;
    }

    double distanceTo(const Point3DI *arg) const {
        return sqrt((double)
                (this->X - arg->X) * (this->X - arg->X) +
                (this->Y - arg->Y) * (this->Y - arg->Y) +
                (this->Z - arg->Z) * (this->Z - arg->Z));
    }
};

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
        this->X = (double)arg.getX();
        this->Y = (double)arg.getY();
        this->Z = (double)arg.getZ();
    }

    Point3DD(const double X, const double Y, const double Z) {
        this->X = X;
        this->Y = Y;
        this->Z = Z;
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

    void setZ(double Y) {
        this->Z = Z;
    }

    double getZ() const {
        return this->Z;
    }

    double distanceTo(const Point3DD *arg) const {
        return sqrt((double)
                (this->X - arg->X) * (this->X - arg->X) +
                (this->Y - arg->Y) * (this->Y - arg->Y) +
                (this->Z - arg->Z) * (this->Z - arg->Z));
    }

    double distanceTo(const Point3DI *arg) const {
        return sqrt((double)
                (this->X - arg->getX()) * (this->X - arg->getX()) +
                (this->Y - arg->getY()) * (this->Y - arg->getY()) +
                (this->Z - arg->getZ()) * (this->Z - arg->getZ()));
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
        return sqrt((double)this->A * this->A + this->B * this->B + this->C * this->C);
    }
public:
    Plane3DI(const Point3DI *A, const Point3DI *B, const Point3DI *C) {
        this->A = A->getY() * B->getZ() - A->getZ() * B->getY() - A->getY() * C->getZ() + B->getY() * C->getZ() + A->getZ() * C->getY() - B->getZ() * C->getY();
        this->B = A->getX() * B->getZ() + A->getZ() * B->getX() + A->getX() * C->getZ() - B->getX() * C->getZ() - A->getZ() * C->getX() + B->getZ() * C->getX();
        this->C = A->getX() * B->getY() - A->getY() * B->getX() - A->getX() * C->getY() + B->getX() * C->getY() + A->getY() * C->getX() - B->getY() * C->getX();
        this->D =-A->getX() * B->getY() * C->getZ() + A->getY() * B->getX() * C->getZ() + A->getX() * B->getZ() * C->getY() - A->getZ() * B->getX() * C->getY() - A->getY() * B->getZ() * C->getX() + A->getZ() * B->getY() * C->getX();
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

    double distanceTo(const Point3DI *arg) const {
        return Math::abs(this->A * arg->getX() + this->B * arg->getY() + this->C * arg->getZ() + this->D) / this->norm;
    }

    long long getPointSign(const Point3DI *arg) const {
        return this->A * arg->getX() + this->B * arg->getY() + this->C * arg->getZ() + this->D;
    }

    double getPointSign(const Point3DD *arg) const {
        return this->A * arg->getX() + this->B * arg->getY() + this->C * arg->getZ() + this->D;
    }

    bool contains(const Point3DI *arg) const {
        return this->getPointSign(arg) == 0;
    }

    bool contains(const Point3DD *arg) const {
        return this->getPointSign(arg) < Math::Epsilon;
    }
};

