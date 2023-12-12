template<typename Tp, typename Compare = std::less<Tp>>
class LiChaoTree {
  struct Line {
    Tp a;
    Tp b;

    Line()
    : a(), b(inf) { }

    Line(const Tp& a, const Tp& b)
    : a(a), b(b) { }

    Tp get(const Tp& x) const {
      return a * x + b;
    }
  };

  int n;
  std::vector<Tp> vals;
  std::vector<Line> tree;

  static constexpr Compare comp = Compare();
  static constexpr Tp inf = comp(std::numeric_limits<Tp>::min(),
                                 std::numeric_limits<Tp>::max()) ? std::numeric_limits<Tp>::max() :
                            std::numeric_limits<Tp>::min();

  void optimize(Tp& target, const Tp& value) const {
    if (comp(value, target)) {
      target = value;
    }
  }

  void update(int root, Line ln, int start, int size) {
    const Tp& first = vals[start];
    const Tp& middle = vals[start + size];
    bool better_first = comp(ln.get(first), tree[root].get(first));
    bool better_middle = comp(ln.get(middle), tree[root].get(middle));
    if (better_middle) {
      std::swap(tree[root], ln);
    }
    if (size) {
      if (better_first != better_middle) {
        update(root << 1, ln, start, size >> 1);
      } else {
        const Tp& last = vals[start + (size << 1)];
        if (comp(ln.get(last), tree[root].get(last))) {
          update(root << 1 | 1, ln, start + size, size >> 1);
        }
      }
    }
  }

  void add(const Line& ln, const Tp& first, const Tp& last) {
    int f_bound = std::lower_bound(vals.begin(), vals.end(), first) - vals.begin();
    int l_bound = std::upper_bound(vals.begin(), vals.end(), last) - vals.begin();
    int f = f_bound + n;
    int l = l_bound + n;
    for (int sz = 1; f < l; f >>= 1, l >>= 1, sz <<= 1) {
      if (f & 1) {
        update(f++, ln, f_bound, sz >> 1);
        f_bound += sz;
      }
      if (l & 1) {
        l_bound -= sz;
        update(--l, ln, l_bound, sz >> 1);
      }
    }
  }

public:
  LiChaoTree(const std::vector<Tp>& v)
  : n(v.size()), vals(v), tree(n * 2) {
    vals.push_back(std::numeric_limits<Tp>::max());
  }

  void add(const Tp& a, const Tp& b, const Tp& first, const Tp& last) {
    add(Line(a, b), first, last);
  }

  Tp query(const Tp& x) const {
    Tp res = inf;
    for (int i = std::lower_bound(vals.begin(), vals.end(), x) - vals.begin() + n;
         i > 0; i >>= 1) {
      optimize(res, tree[i].get(x));
    }
    return res;
  }
};

template<typename Tp, typename Compare>
constexpr Compare LiChaoTree<Tp, Compare>::comp;
