template<typename T>
class RangeMinimumQuery {
  std::vector<std::vector<T>> a;

public:
  RangeMinimumQuery(const std::vector<T>& v) {
    assert(v.size() > 0);
    int n = v.size();
    int k = std::__lg(n) + 1;
    a.resize(k, std::vector<T>(n));
    for (int i = 0; i < n; ++i) {
      a[0][i] = v[i];
    }
    for (int j = 1; j < k; ++j) {
      for (int i = 0; i + (1 << j) <= n; ++i) {
        a[j][i] = std::min(a[j - 1][i], a[j - 1][i + (1 << j - 1)]);
      }
    }
  }

  T query(int l, int r) {
    assert(l < r);
    int k = std::__lg(r - l);
    return std::min(a[k][l], a[k][r - (1 << k)]);
  }
};
