class DisjointSet {
  std::vector<int> p;

public:
  DisjointSet(int n)
  : p(n, -1) { }

  int root(int x) {
    return p[x] < 0 ? x : p[x] = root(p[x]);
  }

  bool unite(int x, int y) {
#ifndef NDEBUG
    int n = p.size();
    assert(x >= 0 && x < n);
    assert(y >= 0 && y < n);
#endif // NDEBUG
    if ((x = root(x)) != (y = root(y))) {
      int& rx = p[x];
      int& ry = p[y];
      if (rx == ry) {
        --rx, ry = x;
      } else {
        rx < ry ? ry = x : rx = y;
      }
      return true;
    }
    return false;
  }
};
