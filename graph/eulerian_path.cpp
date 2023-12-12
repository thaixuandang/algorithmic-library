struct EulerPath : public std::vector<int> {
  EulerPath(const std::vector<std::vector<std::pair<int, int>>>& g,
    int start = 0) {
    int num_vertices = g.size();
    int num_edges = 0;
    for (const auto& adj : g) {
      num_edges += adj.size();
    }
    num_edges /= 2;

    std::vector<int> pointer(num_vertices);
    std::vector<bool> alive(num_edges, true);
    std::stack<int> stack;

    stack.push(start);
    reserve(num_edges + 1);

    do {
      int v = stack.top();
      int& i = pointer[v];
      while (i < g[v].size() && !alive[g[v][i].second]) {
        i++;
      }
      if (i < g[v].size()) {
        const auto& e = g[v][i];
        alive[e.second] = false;
        stack.push(e.first);
        i++;
      } else {
        push_back(v);
        stack.pop();
      }
    } while (!stack.empty());
  }
};
