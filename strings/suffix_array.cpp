class SuffixArray : public std::vector<int> {
  static constexpr int alpha = 256;

public:
  template<typename S>
  SuffixArray(const S& s) {
    std::vector<int>& a = *this;
    int n = s.size();
    a.resize(n);
    std::vector<int> b(n);
    std::vector<int> group(n);
    std::vector<int> start(n);
    std::vector<bool> diff(n);
    if (n * std::__lg(n) > alpha) {
      std::vector<int> cnt(alpha);
      for (int i = 0; i < n; ++i) {
        cnt[s[i]]++;
      }
      std::partial_sum(cnt.begin(), cnt.end(), cnt.begin());
      for (int i = 0; i < n; ++i) {
        a[--cnt[s[i]]] = i;
      }
    } else {
      for (int i = 0; i < n; ++i) {
        a[i] = i;
      }
      sort(a.begin(), a.end(), [&s](int i, int j) {
        return s[i] < s[j];
      });
    }
    diff[0] = true;
    for (int i = 1; i < n; ++i) {
      diff[i] = s[a[i]] != s[a[i - 1]];
    }
    for (int k = 1; k < n; k *= 2) {
      b.clear(), start.clear();
      for (int i = n - k; i < n; ++i) {
        b.push_back(i);
      }
      for (int i = 0; i < n; ++i) {
        if (a[i] >= k) {
          b.push_back(a[i] - k);
        }
        if (diff[i]) {
          start.push_back(i);
        }
        group[a[i]] = start.size() - 1;
      }
      if (start.size() == n) {
        break;
      }
      for (int i = 0; i < n; ++i) {
        a[start[group[b[i]]]++] = b[i];
      }
      int pre = -1;
      for (int i = 0; i < n; ++i) {
        int cur = a[i] + k < n ? group[a[i] + k] : -1;
        if (cur != pre) {
          diff[i] = true, pre = cur;
        }
      }
    }
  }
  
  template<typename S>
  std::vector<int> get_lcp(const S& s) {
    std::vector<int>& a = *this;
    int n = size();
    std::vector<int> pos(n);
    for (int i = 0; i < n; ++i) {
      pos[a[i]] = i;
    }
    std::vector<int> lcp(n);
    int k = 0;
    for (int i = 0; i < n; ++i) {
      if (pos[i] > 0) {
        int j = a[pos[i] - 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) {
          k++;
        }
        lcp[pos[i]] = k;
        if (k > 0) {
          k--;
        }
      }
    }
    return lcp;
  }
};
