bool erdos_gallai(std::vector<int> degs) {
  std::sort(degs.rbegin(), degs.rend());
  int n = degs.size();
  int sum = 0, sum_less_than_k = 0;
  int w = n - 1;
  for (int k = 0; k < n; ++k) {
    sum += degs[k];
    while (w >= 0 && degs[w] <= k) {
      sum_less_than_k += degs[w];
      w--;
    }
    if (sum > (k + 1) * max(k, w) + sum_less_than_k) {
      return false;
    }
  }
  return sum % 2 == 0;
}

std::vector<std::pair<int, int>> construct_graph(std::vector<int> degs) {
  if (!erdos_gallai(degs)) {
    return {{-1, -1}};
  }
  std::vector<std::pair<int, int>> edges;
  int n = degs.size();
  std::vector<int> id(n);
  for (int i = 0; i < n; ++i) {
    id[i] = i;
  }
  std::sort(id.begin(), id.end(), [&](int x, int y) {
    return degs[x] > degs[y];
  });
  for (int i = 0, v = id[0]; i < n && degs[v] > 0; v = id[++i]) {
    int low = i + degs[v], high = n;
    while (low + 1 < high) {
      int mid = (low + high) / 2;
      if (degs[id[mid]] == degs[id[low]]) {
        low = mid;
      } else {
        high = mid;
      }
    }
    while (degs[v] > 0 && degs[id[i + degs[v]]] == degs[id[low]]) {
      int u = id[low];
      edges.emplace_back(u, v);
      degs[u]--, degs[v]--;
      low--;
    }
    for (int j = i + degs[v]; j > i; --j) {
      int u = id[j];
      edges.emplace_back(u, v);
      degs[u]--;
    }
  }
  return edges;
}