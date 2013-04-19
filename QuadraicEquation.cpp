class QuadraicEquation {
private:
    double a;
    double b;
    double c;

    double x1;
    double x2;
public:
    void setA(double a) {
        this->a = a;
    }

    void setB(double b) {
        this->b = b;
    }

    void setC(double c) {
        this->c = c;
    }

    int solve() {
        double delta = this->b * this->b - 4.0 * this->a * this->c;
        if (-1e-10 <= delta && delta <= 1e-10) {
            this->x1 = this->x2 = -this->b / (2.0 * this->a);
            return 1;
        } else if (delta < 0) {
            return 0;
        } else {
            this->x1 = (-this->b + sqrt(delta)) / (2.0 * this->a);
            this->x2 = (-this->b - sqrt(delta)) / (2.0 * this->a);
            return 2;
        }
    }

    double getX1() {
        return this->x1;
    }

    double getX2() {
        return this->x2;
    }
};
