#include <bits/stdc++.h>

using namespace std;

mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());

long long rand(const long long& low, const long long& high) {
  assert(low <= high);
  return rng() % (high - low + 1) + low;
}

// write code from here

int main() {
  
  return 0;
}
