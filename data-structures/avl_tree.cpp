template<typename T, typename Compare = std::less<T>>
class AVLTree {
  struct Node {
    T key;
    Node* left;
    Node* right;
    int height;

    ~Node() {
      delete left;
      delete right;
    }
  };

  Node* root;
  Compare comp;

  inline int height(Node* p) {
    return p ? p->height : -1;
  }

  inline void update(Node* p) {
    p->height = 1 + std::max(height(p->left), height(p->right));
  }

  inline int balance_factor(Node* p) {
    return height(p->right) - height(p->left);
  }

  void rotate_left(Node*& p) {
    Node* q = p->right;
    p->right = q->left;
    update(p);
    q->left = p;
    update(q);
    p = q;
  }

  void rotate_right(Node*& p) {
    Node* q = p->left;
    p->left = q->right;
    update(p);
    q->right = p;
    update(q);
    p = q;
  }

  void rebalance(Node*& p, Node*& q) {
    update(p);
    int bfp = balance_factor(p);
    if (abs(bfp) > 1) {
      int bfq = balance_factor(q);
      if (bfq != 0 && (bfp < 0) != (bfq < 0)) {
        bfp < 0 ? rotate_left(q) : rotate_right(q);
      }
      bfp < 0 ? rotate_right(p) : rotate_left(p);
    }
  }

  void insert(Node*& p, const T& x) {
    Node*& q = comp(x, p->key) ? p->left : p->right;
    if (q) {
      insert(q, x);
    } else {
      q = new Node{x};
    }
    rebalance(p, q);
  }

  Node* find_max(Node* p) {
    return p->right ? find_max(p->right) : p;
  }

  bool erase(Node*& p, const T& x) {
    bool less = comp(x, p->key);
    bool greater = comp(p->key, x);
    bool erased = less && p->left && erase(p->left, x)
      || greater && p->right && erase(p->right, x);
    if (!(less || greater)) {
      if (p->left && p->right) {
        Node* q = find_max(p->left);
        p->key = q->key;
        erased = erase(p->left, q->key);
      } else {
        Node* q = p;
        p = p->left ? p->left : p->right;
        q->left = q->right = nullptr;
        delete q;
        return true;
      }
    }
    if (erased) {
      rebalance(p, greater ? p->left : p->right);
    }
    return erased;
  }

  bool find(Node* p, const T& x) {
    bool less = comp(x, p->key);
    bool greater = comp(p->key, x);
    if (less && p->left) {
      return find(p->left, x);
    }
    if (greater && p->right) {
      return find(p->right, x);
    }
    return !(less || greater);
  }

public:
  AVLTree()
  : root() { }

  ~AVLTree() {
    delete root;
  }

  void insert(const T& x) {
    if (root) {
      insert(root, x);
    } else {
      root = new Node{x};
    }
  }

  bool erase(const T& x) {
    return root ? erase(root, x) : false;
  }

  bool find(const T& x) {
    return root ? find(root, x) : false;
  }
};
