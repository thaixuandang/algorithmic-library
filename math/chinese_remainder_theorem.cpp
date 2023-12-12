template<typename T, bool E = false>
class ChineseRemainder {
  static_assert(std::is_signed<T>::value);

  T m1 = 1;
  T r1 = 0;

  static T egcd(T a, T b, T& u) {
    u = 1;
    T v = 0;
    while (b != 0) {
      T q = a / b;
      a -= q * b, std::swap(a, b);
      u -= q * v, std::swap(u, v);
    }
    assert(E || a == 1);
    return a;
  }

  T mul(T a, T b, const T& mod) {
    if (a < 0) {
      a += mod;
    }
    if (b < 0) {
      b += mod;
    }
    if ((a | b) <= INT_MAX) {
      return (long long)a * b % mod;
    }
    long long c = (long double)a * b / mod;
    a = a * b - c * mod;
    if (a < 0) {
      a += mod;
    }
    return a;
  }

public:
  inline bool add(T m2, const T& r2) {
    assert(m2 > r2 && r2 >= 0);
    T q, g = egcd(m1, m2, q);
    if ((r2 - r1) % g) {
      return false;
    }
    m2 /= g;
    r1 += m1 * mul(q, (r2 - r1) / g % m2, m2);
    m1 *= m2;
    if (r1 >= m1) {
      r1 -= m1;
    }
    return true;
  }

  const T& get_mod() const { return m1; }

  operator T() const { return r1; }
};
