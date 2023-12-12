class HopcroftKarp {
  int m;
  int n;
  std::vector<std::vector<int>> g;

public:
  HopcroftKarp(int m, int n)
  : m(m), n(n), g(m) { }

  inline void add(int x, int y) {
    assert(x >= 0 && x < m);
    assert(y >= 0 && y < n);
    g[x].push_back(y);
  }

  int max_matching() {
    int res = 0;
    std::vector<int> level(m);
    std::vector<int> pointer(m);
    std::vector<int> match(n, -1);
    auto exist_path = [&] {
      std::queue<int> q;
      std::fill(level.begin(), level.end(), 0);
      for (int i = 0; i < n; ++i) {
        if (match[i] != -1) {
          level[match[i]] = m;
        }
      }
      for (int i = 0; i < m; ++i) {
        if (level[i] == 0) {
          q.push(i);
        }
      }
      while (q.size()) {
        int x = q.front();
        q.pop();
        for (int y : g[x]) {
          int z = match[y];
          if (z != -1) {
            if (level[z] == m) {
              level[z] = level[x] + 1;
              q.push(z);
            }
          } else {
            return true;
          }
        }
      }
      return false;
    };
    std::function<bool(int)> augment_matching = [&](int x) {
      for (int& i = pointer[x]; i < g[x].size(); ++i) {
        int y = g[x][i];
        int z = match[y];
        if (z != -1) {
          if (level[z] == level[x] + 1 && augment_matching(z)) {
            match[y] = x;
            return true;
          }
        } else {
          match[y] = x;
          return true;
        }
      }
      return false;
    };
    while (exist_path()) {
      std::fill(pointer.begin(), pointer.end(), 0);
      for (int i = 0; i < m; ++i) {
        if (level[i] == 0) {
          res += augment_matching(i);
        }
      }
    }
    return res;
  }
};
