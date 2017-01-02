struct GCDResult {
  int gcd;
  int coefA;
  int coefB;
};

GCDResult gcd(int no1, int no2) {
  GCDResult one = GCDResult{no1, 1, 0};
  GCDResult two = GCDResult{no2, 0, 1};
  GCDResult three;
  while (one.gcd % two.gcd != 0) {
    int quotient = one.gcd / two.gcd;
    three.gcd = one.gcd % two.gcd;
    three.coefA = one.coefA - quotient * two.coefA;
    three.coefB = one.coefB - quotient * two.coefB;
    one = two;
    two = three;
  }
  return two;
}

struct ChEquation {
  int quotient;
  int reminder;
};

ChEquation solve(ChEquation eq1, ChEquation eq2) {
  GCDResult gcdAnswer = gcd(eq1.quotient, eq2.quotient);
  int coef1 = eq2.quotient / gcdAnswer.gcd;
  int coef2 = eq1.quotient / gcdAnswer.gcd;
  int reminder1 = eq1.reminder * coef1;
  int reminder2 = eq2.reminder * coef2;
  ChEquation answer;
  answer.quotient = eq1.quotient * coef1;
  gcdAnswer = gcd(coef1, coef2);
  reminder1 = ((long long)reminder1 * gcdAnswer.coefA) % answer.quotient;
  reminder1 = ((long long)reminder1 + answer.quotient) % answer.quotient;
  reminder2 = ((long long)reminder2 * gcdAnswer.coefB) % answer.quotient;
  reminder2 = ((long long)reminder2 + answer.quotient) % answer.quotient;
  answer.reminder = (reminder1 + reminder2) % answer.quotient;
  return answer;
}
