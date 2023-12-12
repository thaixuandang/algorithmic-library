template<bool S> // S iff g is simple graph
struct BridgeBlockForest : public std::vector<std::vector<int>> {
  BridgeBlockForest(const std::vector<std::vector<int>>& g) {
    std::vector<std::vector<int>>& f = *this;
    int n = g.size();
    int counter = 0;
    int index = 0;
    std::vector<int> num(n, -1);
    std::vector<int> low(n);
    std::stack<int> s;
    std::vector<int> block(n);
    std::function<void(int, int)> dfs = [&](int u, int p) {
      num[u] = low[u] = counter++;
      s.push(u);
      for (int v : g[u]) {
        if (v != p) {
          if (num[v] == -1) {
            dfs(v, u);
            low[u] = std::min(low[u], low[v]);
          } else {
            low[u] = std::min(low[u], num[v]);
          }
        }
      }
      if (num[u] == low[u]) {
        int v;
        do {
          v = s.top(), num[v] = n;
          s.pop();
          block[v] = index;
        } while (v != u);
        ++index;
      }
    };
    for (int i = 0; i < n; ++i) {
      if (num[i] == -1) {
        dfs(i, -1);
      }
    }
    f.resize(index);
    for (int u = 0; u < n; ++u) {
      for (int v : g[u]) {
        if (block[u] != block[v]) {
          f[block[u]].push_back(block[v]);
        }
      }
    }
  }
};

template<>
struct BridgeBlockForest<false> : public std::vector<std::vector<int>> {
  // for each edge, first is vertex to and second is index of edge
  BridgeBlockForest(const std::vector<std::vector<std::pair<int, int>>>& g) {
    std::vector<std::vector<int>>& f = *this;
    int n = g.size();
    int counter = 0;
    int index = 0;
    std::vector<int> num(n, -1);
    std::vector<int> low(n);
    std::stack<int> s;
    std::vector<int> block(n);
    std::function<void(int, int)> dfs = [&](int u, int j) {
      num[u] = low[u] = counter++;
      s.push(u);
      for (int i = 0; i < g[u].size(); ++i) {
        int v = g[u][i].first;
        int k = g[u][i].second;
        if (k != j) {
          if (num[v] == -1) {
            dfs(v, k);
            low[u] = std::min(low[u], low[v]);
          } else {
            low[u] = std::min(low[u], num[v]);
          }
        }
      }
      if (num[u] == low[u]) {
        int v;
        do {
          v = s.top(), num[v] = n;
          s.pop();
          block[v] = index;
        } while (v != u);
        ++index;
      }
    };
    for (int i = 0; i < n; ++i) {
      if (num[i] == -1) {
        dfs(i, -1);
      }
    }
    f.resize(index);
    for (int u = 0; u < n; ++u) {
      for (const std::pair<int, int>& i : g[u]) {
        int v = i.first;
        if (block[u] != block[v]) {
          f[block[u]].push_back(block[v]);
        }
      }
    }
  }
};
