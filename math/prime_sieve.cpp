class PrimeSieve : public std::vector<int> {
  std::vector<int> p;

public:
  PrimeSieve(int n)
  : p(n + 1, -1) {
    std::vector<int>& primes = *this;
    for (int i = 2; i <= n; ++i) {
      if (p[i] == -1) {
        p[i] = size();
        push_back(i);
      }
      for (int j = 0; j <= p[i] && primes[j] * i <= n; ++j) {
        p[primes[j] * i] = j;
      }
    }
  }
};
