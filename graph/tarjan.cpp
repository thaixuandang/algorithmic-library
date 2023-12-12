struct Tarjan : public std::vector<int> {
  Tarjan(const std::vector<std::vector<int>>& g) {
    std::vector<int>& comp = *this;
    int n = g.size();
    int counter = 0;
    int index = 0;
    comp.resize(n);
    std::vector<int> num(n, -1);
    std::vector<int> low(n);
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
  }
};
