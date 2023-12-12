struct SMatrix : public std::vector<std::vector<int>> {
  static constexpr int mod = 1e9L + 7;

  SMatrix(int n)
  : std::vector<std::vector<int>>(n, std::vector<int>(n)) { }

  static SMatrix unit(int n) {
    SMatrix res(n);
    for (int i = 0; i < n; ++i) {
      res[i][i] = 1;
    }
    return res;
  }

  SMatrix operator*(const SMatrix& b) const {
    const SMatrix& a = *this;
    int n = size();
    SMatrix c(n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
          c[i][j] = (c[i][j] + (long long)a[i][k] * b[k][j]) % mod;
        }
      }
    }
    return c;
  }

  SMatrix power(int k) {
    SMatrix a = *this;
    SMatrix res = SMatrix::unit(size());
    while (k > 0) {
      if (k & 1) {
        res = res * a;
      }
      a = a * a, k >>= 1;
    }
    return res;
  }
};
