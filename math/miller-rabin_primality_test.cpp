template<typename T>
bool is_prime(T n, int rep = 5) {
  if (rep == 0 || n == 2) {
    return true;
  }
  if (n < 2 || n % 2 == 0) {
    return false;
  }
  T m = n - 1;
  while (m % 2 == 0) {
    m /= 2;
  }
  static std::mt19937_64 rng(
    std::chrono::system_clock::now().time_since_epoch().count());
  T a = 2 + rng() % (n - 2);
  T b = 1, k = m;
  auto mul = [&](T x, T y)->T {
    if (n <= UINT_MAX) {
      return (unsigned long long)x * y % n;
    }
    T res = 0;
    while (y > 0) {
      if (y & 1) {
        if ((res += x) >= n) {
          res -= n;
        }
      }
      if ((x += x) >= n) {
        x -= n;
      }
      y >>= 1;
    }
    return res;
  };
  while (k > 0) {
    if (k & 1) {
      b = mul(b, a);
    };
    a = mul(a, a), k >>= 1;
  }
  if (b == 1) {
    return is_prime(n, rep - 1);
  }
  while ((m *= 2) < n) {
    if (b == n - 1) {
      return is_prime(n, rep - 1);
    }
    b = mul(b, b);
  }
  return false;
}
