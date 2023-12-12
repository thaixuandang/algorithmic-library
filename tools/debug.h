#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <sstream>
#include <type_traits>
#include <utility>
#include <string>
#include <tuple>
#include <bitset>
#include <ctime>

namespace std {
  template<typename T, typename _ = void>
  struct IsSequence : public false_type { };

  template<typename T>
  struct IsSequence<T, void_t<decltype(T{}.begin()), decltype(T{}.end())>>
    : public true_type { };
  
  template<typename T>
  typename enable_if<!IsSequence<T>::value, string>::type
  inline to_string(const T& x) {
    ostringstream stream;
    stream << x;
    return stream.str();
  }

  template<typename T>
  typename enable_if<IsSequence<T>::value, string>::type
  inline to_string(const T& x) {
    bool first = true;
    string res = "{";
    for (const typename T::value_type& y : x) {
      if (!first) {
        res += ", ";
      }
      first = false;
      res += to_string(y);
    }
    return res += '}';
  }
  
  inline string to_string(bool x) {
    return x ? "true" : "false";
  }

  inline string to_string(char x) {
    return string("'") + x + "'";
  }
  
  inline string to_string(const string& x) {
    return '"' + x + '"';
  }

  inline string to_string(const char* x) {
    return to_string(string(x));
  }

  template<typename T1, typename T2>
  inline string to_string(const pair<T1, T2>& x) {
    return '(' + to_string(x.first) + ", " + to_string(x.second) + ')';
  }

  template<typename T1, typename T2, typename T3>
  inline string to_string(const tuple<T1, T2, T3>& x) {
    return '(' + to_string(get<0>(x)) + ", " + to_string(get<1>(x)) + ", " +
      to_string(get<2>(x)) + ')';
  }

  template<typename T1, typename T2, typename T3, typename T4>
  inline string to_string(const tuple<T1, T2, T3, T4>& x) {
    return '(' + to_string(get<0>(x)) + ", " + to_string(get<1>(x)) + ", " +
      to_string(get<2>(x)) + ", " + to_string(get<3>(x)) + ')';
  }
}

namespace debug {
  const struct Timer {
    ~Timer() {
      std::cerr << "\nThe execution time is " <<
        double(clock()) / CLOCKS_PER_SEC << " seconds." << std::endl;
    }
  } timer;

  inline std::string text() {
    return "\n";
  }

  template<typename H, typename... T>
  std::string text(const H& head, const T&... tail) {
    return " " + std::to_string(head) + text(tail...);
  }

  template<typename... T>
  void watch(int line, std::string vals_name, const T&... vals) {
    std::string str_vals = text(vals...);
    std::cerr << line << ": [" << vals_name << "] =" << str_vals;
  }
}

#define debug(...) debug::watch(__LINE__, #__VA_ARGS__, __VA_ARGS__)

#endif
