class Twosat {
  std::vector<std::vector<int>> g;

public:
  Twosat(int n)
  : g(n << 1) { }

  inline void add(int u, bool x, int v, bool y) {
#ifndef NDEBUG
    int n = g.size() / 2;
    assert(u >= 0 && u < n);
    assert(v >= 0 && v < n);
#endif // NDEBUG
    u = u << 1 | x;
    v = v << 1 | y;
    g[u ^ 1].push_back(v);
    g[v ^ 1].push_back(u);
  }

  bool get(std::vector<int>& res) {
    int n = g.size();
    int counter = 0;
    int index = 0;
    std::vector<int> num(n, -1);
    std::vector<int> low(n);
    std::vector<int> comp(n);
    std::stack<int> s;
    std::function<void(int)> dfs = [&](int u) {
      num[u] = low[u] = counter++;
      s.push(u);
      for (int v : g[u]) {
        if (num[v] == -1) {
          dfs(v);
          low[u] = std::min(low[u], low[v]);
        } else {
          low[u] = std::min(low[u], num[v]);
        }
      }
      if (low[u] == num[u]) {
        int v;
        do {
          v = s.top(), num[v] = n;
          s.pop();
          comp[v] = index;
        } while (v != u);
        ++index;
      }
    };
    for (int i = 0; i < n; ++i) {
      if (num[i] == -1) {
        dfs(i);
      }
    }
    res.clear();
    for (int i = 0; i < n; i += 2) {
      if (comp[i] == comp[i ^ 1]) {
        res.clear();
        return false;
      }
      if (comp[i] > comp[i ^ 1]) {
        res.push_back(i >> 1);
      }
    }
    return true;
  }
};
