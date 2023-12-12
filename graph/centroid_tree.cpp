class CentroidTree : public std::vector<std::vector<int>> {
  int root;

public:
  CentroidTree(const std::vector<std::vector<int>>& g) {
    std::vector<std::vector<int>> &t = *this;
    int n = g.size();
    std::vector<bool> alive(n, true);
    std::vector<int> size(n);
    resize(n);
    std::function<void(int, int)> compute_size = [&](int u, int p) {
      size[u] = 1;
      for (int v : g[u]) {
        if (alive[v] && v != p) {
          compute_size(v, u);
          size[u] += size[v];
        }
      }
    };
    std::function<void(int&)> find_centroid = [&](int& r) {
      compute_size(r, -1);
      int half = size[r] / 2;
      int p = -1;
      for (;;) {
        int w = -1;
        for (int v : g[r]) {
          if (alive[v] && v != p) {
            if (w == -1 || size[v] > size[w]) {
              w = v;
            }
          }
        }
        if (w == -1 || size[w] <= half) {
          return;
        }
        p = r, r = w;
      }
    };
    // need modify
    std::function<int(int)> decompose = [&](int r) {
      find_centroid(r);
      alive[r] = false;
      // need modfiy
      for (int v : g[r]) {
        if (alive[v]) {
          // need modify
          t[r].push_back(decompose(v));
        }
      }
      return r;
    };
    root = decompose(0);
  }
};
