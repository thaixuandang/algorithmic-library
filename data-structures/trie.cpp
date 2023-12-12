class Trie {
  int cnt;
  std::vector<std::pair<char, Trie*>> children;

public:
  Trie* insert(const std::string& s) {
    Trie* ptr = this;
    for (char c : s) {
      Trie* nxt = nullptr;
      for (std::pair<char, Trie*>& p : ptr->children) {
        if (p.first == c) {
          nxt = p.second;
          break;
        }
      }
      if (nxt == nullptr) {
        ptr->children.push_back({c, new Trie()});
        nxt = ptr->children.back().second;
      }
      ptr = nxt;
    }
    ++(ptr->cnt);
    return ptr;
  }

  int erase(const std::string& s) {
    Trie* ptr = this;
    for (char c : s) {
      Trie* nxt = nullptr;
      for (std::pair<char, Trie*>& p : ptr->children) {
        if (p.first == c) {
          nxt = p.second;
          break;
        }
      }
      if (nxt == nullptr) {
        return 0;
      }
      ptr = nxt;
    }
    int res = ptr->cnt;
    ptr->cnt = 0;
    return res;
  }

  int count(const std::string& s) {
    Trie* ptr = this;
    for (char c : s) {
      Trie* nxt = nullptr;
      for (std::pair<char, Trie*>& p : ptr->children) {
        if (p.first == c) {
          nxt = p.second;
          break;
        }
      }
      if (nxt == nullptr) {
        return 0;
      }
      ptr = nxt;
    }
    return ptr->cnt;
  }
};
