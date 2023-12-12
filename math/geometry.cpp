namespace Geometry {
  const double pi  = acos(-1.0);
  const double eps = 1e-15;

  template<typename T>
  struct Point {
    T x;
    T y;

    Point()
    : x(), y() { }

    Point(const T& x, const T& y)
    : x(x), y(y) { }

    template<typename U>
    Point(const Point<U>& p)
    : x(p.x), y(p.y) { }

    inline Point operator+(const Point& rhs) const {
      return {x + rhs.x, y + rhs.y};
    }

    inline Point operator-(const Point& rhs) const {
      return {x - rhs.x, y - rhs.y};
    }

    inline Point operator*(const T& k) const {
      return {x * k, y * k};
    }

    inline Point operator/(const T& k) const {
      return {x / k, y / k};
    }

    inline Point& operator+=(const Point& rhs) {
      return x += rhs.x, y += rhs.y, *this;
    }

    inline Point& operator-=(const Point& rhs) {
      return x -= rhs.x, y -= rhs.y, *this;
    }

    inline Point& operator*=(const T& k) {
      return x *= k, y *= k, *this;
    }

    inline Point& operator/=(const T& k) {
      return x /= k, y /= k, *this;
    }

    friend inline Point operator*(const T& k, const Point& p) {
      return {k * p.x, k * p.y};
    }

    inline T dist() {
      return sqrt(x * x + y * y);
    }
  };

  template<typename T = double>
  struct Line {
    T a;
    T b;
    T c;

    Line()
    : a(), b(), c() { }

    Line(const T& a, const T& b, const T& c)
    : a(a), b(b), c(c) { }

    template<typename U>
    Line(const Line<U>& l)
    : a(l.a), b(l.b), c(l.c) { }

    Line(const Point<T>& p, const Point<T>& q) {
      a = p.y - q.y;
      b = q.x - p.x;
      c = -(a * p.x + b * p.y);
    }
  };

  template<typename T = double>
  struct Circle {
    Point<T> c;
    T r;

    Circle()
    : c(), r() { }

    Circle(const Point<T>& c, const T& r)
    : c(c), r(r) { }
  };

  template<typename T>
  inline std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
    return os << '(' << p.x << ", " << p.y << ')';
  }

  template<typename T>
  inline std::ostream& operator<<(std::ostream& os, const Line<T>& l) {
    return os << '(' << l.a << ", " << l.b << ", " << l.c << ')';
  }

  template<typename T>
  inline std::ostream& operator<<(std::ostream& os, const Circle<T>& c) {
    return os << '(' << c.c << ", " << c.r << ')';
  }

  template<typename T>
  inline int sign(const T& x) {
    return x < -eps ? -1 : (x > eps ? 1 : 0);
  }

  template<typename T>
  inline T sqr(const T& x) {
    return x * x;
  }

  template<typename T>
  inline T det(const T& x, const T& y, const T& u, const T& v) {
    return x * v - y * u;
  }

  inline double angle(const Point<double>& p) {
    return atan2(p.y, p.x);
  }

  template<typename T>
  inline T dot(const Point<T>& p, const Point<T>& q) {
    return p.x * q.x + p.y * q.y;
  }

  template<typename T>
  inline T cross(const Point<T>& p, const Point<T>& q) {
    return p.x * q.y - p.y * q.x;
  }

  template<typename T>
  inline T dist(const Point<T>& p, const Point<T>& q) {
    return sqrt(sqr(p.x - q.x) + sqr(p.y - q.y));
  }

  template<typename T>
  inline T dist(const Point<T>& p, const Line<T>& l) {
    return abs(l.a * p.x + l.b * p.y + l.c) / sqrt(l.a * l.a + l.b * l.b);
  }

  template<typename T>
  inline T dist2(const Point<T>& p, const Point<T>& q) {
    return sqr(p.x - q.x) + sqr(p.y - q.y);
  }

  template<typename T>
  inline T dist2(const Point<T>& p, const Line<T>& l) {
    return sqr(l.a * p.x + l.b * p.y + l.c) / (l.a * l.a + l.b * l.b);
  }

  template<typename T>
  inline T area(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
    return abs(cross(a, b) + cross(b, c) + cross(c, a)) / 2;
  }

  template<typename T>
  inline T area2(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
    return cross(a, b) + cross(b, c) + cross(c, a);
  }

  template<typename T>
  inline int ccw(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
    return sign(cross(b - a, c - b));
  }

  template<typename T>
  inline Point<T> rotate(const Point<T>& p, const T& a) {
    return {p.x * cos(a) - p.y * sin(a), p.x * sin(a) + p.y * cos(a)};
  }

  template<typename T>
  inline Point<T> rotate(const Point<T>& p, const Point<T>& c, const T& a) {
    return c + rotate(p - c, a);
  }

  template<typename T>
  inline std::vector<Point<T>> intersect(const Line<T>& u, const Line<T>& v) {
    std::vector<Point<T>> res;
    T d = det(u.a, u.b, v.a, v.b);
    T dx = det(u.b, u.c, v.b, v.c);
    T dy = det(u.c, u.a, v.c, v.a);
    if (d == 0) {
      return dx == 0 && dy == 0 ? res.resize(2) : (void)0, res;
    }
    return {{dx / d, dy / d}};
  }

  template<typename T>
  inline std::vector<Point<T>> intersect(const Line<T>& l, const Circle<T>& c) {
    std::vector<Point<T>> res;
    if (dist(c.c, l) > c.r) {
      return {};
    }
    Point<T> i = intersect(l, Line<T>(c.c, c.c + Point<T>(l.a, l.b))).front();
    Point<T> dir = Point<T>(-l.b, l.a) * sqrt((c.r * c.r - dist2(c.c, i)) / (l.a * l.a + l.b * l.b));
    if (dir.dist() < eps) {
      return {i};
    }
    return dir.dist() < eps ? res = {i} : res = {i + dir, i - dir};
  }

  template<typename T>
  inline std::vector<Point<T>> intersect(const Circle<T>& u, Circle<T>& v) {
    std::vector<Point<T>> res;
    T d = dist(u.c, v.c);
    if (d == 0) {
      return u.r == v.r ? res.resize(3) : (void)0, res;
    }
    T a = (sqr(u.r) - sqr(v.r) + sqr(d)) / (2 * d);
    T h = sqr(u.r) - sqr(a);
    if (h < 0) {
      return 0;
    }
    h = sqrt(h);
    Point<T> w = v.c - u.c;
    Point<T> i = u.c + w * (a / d);
    w = Point<T>(-w.y, w.x) * (h / d);
    return h == 0 ? res = {i} : res = {i + w, i - w};
  }
}
