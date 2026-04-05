const int MAX_N = 1 << 17;

int a[MAX_N];
int b[MAX_N];
int c[2 * MAX_N];
int d[2 * MAX_N];

void add(int* a, int* b, int* c, int N) {
  for (int i = 0; i < N; i++) {
    c[i] = a[i] + b[i];
    if (c[i] >= MOD) {
      c[i] -= MOD;
    }
  }
}

void add_self(int* a, int* b, int N) {
  for (int i = 0; i < N; i++) {
    a[i] += b[i];
    if (a[i] >= MOD) {
      a[i] -= MOD;
    }
  }
}

void sub(int* a, int* b, int* c, int N) {
  for (int i = 0; i < N; i++) {
    c[i] = a[i] - b[i];
    if (c[i] < 0) {
      c[i] += MOD;
    }
  }
}

void sub_self(int* a, int* b, int N) {
  for (int i = 0; i < N; i++) {
    a[i] -= b[i];
    if (a[i] < 0) {
      a[i] += MOD;
    }
  }
}

void multiply(int* a, int* b, int* c, int* d, int N) {
  if (N <= 8) {
    for (int i = 0; i < 2 * N; i++) {
      c[i] = 0;
    }
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        c[i + j] += (long long)a[i] * b[j] % MOD;
        if (c[i + j] >= MOD) {
          c[i + j] -= MOD;
        }
      }
    }
  } else {
    int* A = a + N / 2;
    int* B = a;
    int* C = b + N / 2;
    int* D = b;
    int* AC = c + N;
    int* BD = c;
    int* ApB = d;
    int* CpD = d + N / 2;
    int* ApBmCpD = d + N;
    add(A, B, ApB, N / 2);
    add(C, D, CpD, N / 2);
    multiply(ApB, CpD, ApBmCpD, AC, N / 2);
    multiply(A, C, AC, d, N / 2);
    multiply(B, D, BD, d, N / 2);
    sub_self(ApBmCpD, AC, N);
    sub_self(ApBmCpD, BD, N);
    add_self(c + N / 2, ApBmCpD, N);
  }
}
