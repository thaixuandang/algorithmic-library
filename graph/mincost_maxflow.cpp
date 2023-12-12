template<typename T>
class MincostMaxflow {
  struct Edge {
    int to;
    T cap;
    T cost;
    T flow;
  };

  int n;
  int s;
  int t;
  std::vector<std::vector<int>> g;
  std::vector<Edge> edges;

public:
  const T inf = std::numeric_limits<T>::max();

  MincostMaxflow(int n, int s, int t)
  : n(n), s(s), t(t), g(n) {
    assert(s >= 0 && s < n);
    assert(t >= 0 && t < n);
  }

  inline void add(int u, int v, const T& cap, const T& cost) {
    assert(u >= 0 && u < n);
    assert(v >= 0 && v < n);
    g[u].push_back(edges.size());
    edges.push_back({v, cap, cost, 0});
    g[v].push_back(edges.size());
    edges.push_back({u, 0, -cost, 0});
  }

  std::pair<T, T> get() {
    T cost = 0;
    T flow = 0;
    std::vector<T> dist(n);
    std::vector<int> from(n);

    auto exist_path = [&] {
      std::fill(dist.begin(), dist.end(), inf);
      std::queue<int> q;
      std::vector<bool> inq(n);
      dist[s] = 0;
      q.push(s), inq[s] = true;
      while (q.size()) {
        int v = q.front();
        q.pop();
        inq[v] = false;
        for (int i : g[v]) {
          Edge& e = edges[i];
          if (e.cap > e.flow && dist[e.to] > dist[v] + e.cost) {
            dist[e.to] = dist[v] + e.cost;
            from[e.to] = i;
            if (!inq[e.to]) {
              q.push(e.to), inq[e.to] = true;
            }
          }
        }
      }
      return dist[t] < inf;
    };

    auto augment_flow = [&] {
      T delta = inf;
      for (int v = t, i; v != s; v = edges[i ^ 1].to) {
        i = from[v];
        delta = min(delta, edges[i].cap - edges[i].flow);
      }
      for (int v = t, i; v != s; v = edges[i ^ 1].to) {
        i = from[v];
        edges[i].flow += delta;
        edges[i ^ 1].flow -= delta;
      }
      return delta;
    };

    while (exist_path()) {
      T delta = augment_flow();
      cost += dist[t] * delta;
      flow += delta;
    }
    return {cost, flow};
  }
};
