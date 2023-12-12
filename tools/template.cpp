#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#ifndef LOCAL
#define debug(...) (void)0
#endif

using namespace std;

namespace __gnu_pbds {
  template<typename T>
  using ordered_set = tree<
    T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; 
}

using __gnu_pbds::ordered_set;
using int128 = __int128;

template<typename T>
bool maximize(T& target, const T& value) 
{ return target < value ? (target = value, true) : false; }

template<typename T>
bool minimize(T& target, const T& value)
{ return target > value ? (target = value, true) : false; }

istream& operator>>(istream& is, int128& x)
{ long long y; is >> y, x = y; return is; }

ostream& operator<<(ostream& os, const int128& x) 
{ assert(x >= LONG_LONG_MIN && x <= LONG_LONG_MAX); return os << (long long)x; }
 
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  
  return 0;
}
