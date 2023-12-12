template<const int& mod>
class Modular {
  int value;

  static long long inverse(int a) {
    int v = 0, u = 1, b = mod;
    while (a != 0) {
      int q = b / a;
      b -= q * a, std::swap(a, b);
      v -= q * u, std::swap(v, u);
    }
    assert(b == 1 && "a and mod must be coprime");
    return v;
  }

public:
  Modular() : value() { }

  template<typename T>
  Modular(const T& x) : value(x % mod) { if (value < 0) value += mod; }

  template<typename T>
  explicit operator T() const { return value; }

  Modular& operator+=(const Modular& x) { if ((value += x.value) >= mod) value -= mod; return *this; }
  Modular& operator-=(const Modular& x) { if ((value -= x.value) < 0) value += mod; return *this; }
  Modular& operator*=(const Modular& x) { value = value * (long long)x.value % mod; return *this; }
  Modular& operator/=(const Modular& x) { value = value * inverse(x.value) % mod; return *this; }
  Modular& operator++() { if (++value == mod) value = 0; return *this; }
  Modular& operator--() { if (--value < 0) value = mod - 1; return *this; }

  Modular operator++(int) { Modular temp = *this; ++*this; return temp; }
  Modular operator--(int) { Modular temp = *this; --*this; return temp; }
  Modular operator-() const { return {-value}; }

  // Be careful! The following operators will be executed if a parameter is Modular
  friend Modular operator+(const Modular& x, const Modular& y) { return {x.value + y.value}; }
  friend Modular operator-(const Modular& x, const Modular& y) { return {x.value - y.value}; }
  friend Modular operator*(const Modular& x, const Modular& y) { return {x.value * (long long)y.value}; }
  friend Modular operator/(const Modular& x, const Modular& y) { return {x.value * inverse(y.value)}; }
  friend bool operator==(const Modular& x, const Modular& y) { return x.value == y.value; }
  friend bool operator!=(const Modular& x, const Modular& y) { return x.value != y.value; }
  friend bool operator<=(const Modular& x, const Modular& y) { return x.value <= y.value; }
  friend bool operator>=(const Modular& x, const Modular& y) { return x.value >= y.value; }
  friend bool operator<(const Modular& x, const Modular& y) { return x.value < y.value; }
  friend bool operator>(const Modular& x, const Modular& y) { return x.value > y.value; }

  friend std::istream& operator>>(std::istream& is, Modular& x) { return is >> x.value; }
  friend std::ostream& operator<<(std::ostream& os, const Modular& x) { return os << x.value; }
};
