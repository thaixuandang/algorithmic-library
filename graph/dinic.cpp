template<typename T>
class Dinic {
  struct Edge {
    int to;
    T cap;
    T flow;
  };

  int n;
  int s;
  int t;
  std::vector<std::vector<int>> g;
  std::vector<Edge> edges;

public:
  static constexpr T inf = std::numeric_limits<T>::max();

  Dinic(int n, int s, int t)
  : n(n), s(s), t(t), g(n) {
    assert(s >= 0 && s < n);
    assert(t >= 0 && t < n);
  }

  inline void add(int u, int v, const T& cap) {
    assert(u >= 0 && u < n);
    assert(v >= 0 && v < n);
    g[u].push_back(edges.size());
    edges.push_back({v, cap, 0});
    g[v].push_back(edges.size());
    edges.push_back({u, 0, 0});
  }

  T maxflow() {
    T total = 0;
    std::vector<int> level(n);
    std::vector<int> pointer(n);
    auto exist_path = [&] {
      std::fill(level.begin(), level.end(), n);
      std::queue<int> q;
      level[s] = 0, q.push(s);
      while (q.size()) {
        int v = q.front();
        q.pop();
        for (int i : g[v]) {
          Edge& e = edges[i];
          if (level[e.to] == n && e.cap > e.flow) {
            level[e.to] = level[v] + 1, q.push(e.to);
            if (e.to == t) {
              return true;
            }
          }
        }
      }
      return false;
    };
    std::function<T(int, T)> augment_flows = [&](int v, T f) {
      if (v == t) {
        return f;
      }
      for (int& i = pointer[v]; i < g[v].size(); ++i) {
        int j = g[v][i];
        Edge& e = edges[j];
        if (level[e.to] == level[v] + 1 && e.cap > e.flow) {
          T delta = augment_flows(e.to, std::min(f, e.cap - e.flow));
          if (delta > 0) {
            e.flow += delta;
            edges[j ^ 1].flow -= delta;
            return delta;
          }
        }
      }
      return (T)0;
    };
    while (exist_path()) {
      std::fill(pointer.begin(), pointer.end(), 0);
      while (T delta = augment_flows(s, inf)) {
        total += delta;
      }
    }
    return total;
  }
};
