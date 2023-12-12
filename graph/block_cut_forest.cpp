class BlockCutForest : public std::vector<std::vector<int>> {
  std::vector<std::vector<int>> blocks;
  std::vector<int> cuts;

public:
  BlockCutForest(const std::vector<std::vector<int>>& g) {
    std::vector<std::vector<int>>& f = *this;
    int n = g.size();
    int counter = 0;
    std::vector<int> num(n, -1);
    std::vector<int> low(n);
    std::stack<int> s;
    std::vector<bool> is_cut(n);
    std::vector<int> index(n);
    std::function<void(int, int)> dfs = [&](int u, int p) {
      num[u] = low[u] = counter++;
      int child_count = 0;
      for (int v : g[u]) {
        if (v != p) {
          if (num[v] == -1) {
            s.push(v);
            dfs(v, u);
            low[u] = std::min(low[u], low[v]);
            ++child_count;
            if (low[v] >= num[u]) {
              is_cut[u] = true;
              blocks.push_back(std::vector<int>(1, u));
              int w;
              do {
                w = s.top(), s.pop();
                blocks.back().push_back(w);
              } while (w != v);
            }
          } else {
            low[u] = std::min(low[u], num[v]);
          }
        }
      }
      if (p == -1) {
        is_cut[u] = child_count >= 2;
      }
    };
    for (int i = 0; i < n; ++i) {
      if (num[i] == -1) {
        dfs(i, -1);
      }
    }
    int pointer = blocks.size();
    for (int i = 0; i < n; ++i) {
      if (is_cut[i]) {
        cuts.push_back(i);
        index[i] = pointer++;
      }
    }
    f.resize(blocks.size() + cuts.size());
    for (int i = 0; i < blocks.size(); ++i) {
      const std::vector<int>& b = blocks[i];
      for (int v : b) {
        if (is_cut[v]) {
          f[i].push_back(index[v]);
          f[index[v]].push_back(i);
        }
      }
    }
  }
};
