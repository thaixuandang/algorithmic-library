struct PrefixFunction : public std::vector<int> {
  PrefixFunction(const std::string& s) {
    std::vector<int>& p = *this;
    int n = s.size();
    p.resize(n);
    int k = p.front() = 0;
    for (int i = 1; i < n; ++i) {
      while (k > 0 && s[k] != s[i]) {
        k = p[k - 1];
      }
      p[i] = k += s[k] == s[i];
    }
  }
};
