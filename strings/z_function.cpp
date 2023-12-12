struct ZFunction : public std::vector<int> {
  ZFunction(const std::string& s) {
    std::vector<int>& z = *this;
    int n = s.size();
    z.resize(n);
    z.front() = n;
    for (int i = 1, f = 1, l = 1; i < n; ++i) {
      if (i < l) {
        z[i] = std::min(z[i - f], l - i);
      }
      while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
        ++z[i];
      }
      if (i + z[i] > l) {
        f = i;
        l = i + z[i];
      }
    }
  }
};
