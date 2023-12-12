template<typename W, typename D>
class HeavyLightDecomposition {
#define VERTEX            first
#define WEIGHT            second
#define POINTER_START_AT  0

  typedef D data_s;
  typedef W weight_t;

  data_s ds;
  std::vector<int> size;
  std::vector<int> level;
  std::vector<int> parent;
  std::vector<int> head;
  std::vector<int> index;
  std::vector<weight_t> weight;

public:
  template<typename T>
  HeavyLightDecomposition(const std::vector<std::vector<T>>& tree) {
    int n = tree.size();
    int pointer = POINTER_START_AT;
    size.resize(n);
    level.resize(n);
    parent.resize(n);
    head.resize(n);
    index.resize(n);
    weight.resize(n);
    std::function<void(int, int)> dfs = [&](int v, int p) {
      size[v] = 1;
      for (const T& e : tree[v]) {
        if (e.VERTEX != p) {
          parent[e.VERTEX] = v;
          level[e.VERTEX] = level[v] + 1;
          dfs(e.VERTEX, v);
          size[v] += size[e.VERTEX];
        }
      }
    };
    std::function<void(int, int, int)> decompose = [&](int v, int p, int h) {
      head[v] = h;
      index[v] = pointer++;
      T heavy{-1, 0};
      for (const T& e : tree[v]) {
        if (e.VERTEX != p && (heavy.VERTEX == -1 || size[e.VERTEX] > size[heavy.VERTEX])) {
          heavy = e;
        }
      }
      if (~heavy.VERTEX) {
        decompose(heavy.VERTEX, v, h);
        weight[index[heavy.VERTEX]] = heavy.WEIGHT; // modify for vertex path
      }
      for (const T& e : tree[v]) {
        if (e.VERTEX != p && e.VERTEX != heavy.VERTEX) {
          decompose(e.VERTEX, v, e.VERTEX);
          weight[index[e.VERTEX]] = e.WEIGHT; // modify for vertex path
        }
      }
    };
    // edit to weight[0] = <weight of vertex 0> for vertex path
    dfs(0, 0);
    decompose(0, 0, 0);
    ds.build(weight); // need modify
  }

  weight_t query(int u, int v) { // need modify
#ifndef NDEBUG
    int n = size.size();
    assert(u >= 0 && u < n);
    assert(v >= 0 && v < n);
#endif // NDEBUG
    int hu = head[u];
    int hv = head[v];
    weight_t result; // need modify
    while (hu != hv) {
      if (level[hu] > level[hv]) {
        std::swap(u, v), std::swap(hu, hv);
      }
      ds.query(index[hv], index[v] + 1); // need modify *
    }
    if (index[u] > index[v]) {
      std::swap(u, v);
    }
    ds.query(index[u] + 1, index[v] + 1); // need modify *
    // edit to ds.query(index[u], index[v] + 1) for vertex path *
    // *: on range style [first, last)
    return result; // need modify
  }
#undef VERTEX
#undef WEIGHT
#undef POINTER_START_AT
};
