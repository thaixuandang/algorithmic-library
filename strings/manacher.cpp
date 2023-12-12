struct Manacher : public std::vector<int> {
  Manacher(const std::string& s) {
    std::vector<int>& r = *this;
    int n = s.size();
    r.resize(n, 1);
    for (int i = 1, c = 1, f = 1; i < n; ++i) {
      if (i < f) {
        r[i] = std::min(r[2 * c - i], f - i);
      }
      while (i - r[i] >= 0 && i + r[i] < n && s[i - r[i]] == s[i + r[i]]) {
        ++r[i];
      }
      if (i + r[i] > f) {
        c = i;
        f = i + r[i];
      }
    }
  }
};
