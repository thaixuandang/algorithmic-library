template<typename T>
T egcd(T a, T b, T& x, T& y) {
  x = 1, y = 0;
  T u = 0, v = 1;
  while (b != 0) {
    T q = a / b;
    a -= q * b, swap(a, b);
    x -= q * u, swap(x, u);
    y -= q * v, swap(y, v);
  }
  return a;
}