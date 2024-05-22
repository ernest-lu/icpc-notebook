/**
 * Author: Ernest Lu
 * Source: Me
 * Description: debug
 * Status: tested
 */
#pragma once

void dbg_out() { cout << endl; }
template <typename Head, typename... Tail> void dbg_out(Head H, Tail... T) {
  cout << ' ' << H;
  dbg_out(T...);
}

template <typename T, typename = void> struct is_iterable : false_type {};
template <typename T>
struct is_iterable<
    T, void_t<decltype(begin(declval<T>())), decltype(end(declval<T>()))>>
    : true_type {};
template <typename T>
typename enable_if<is_iterable<T>::value && !is_same<T, string>::value,
                   ostream &>::type
operator<<(ostream &cout, T const &v);
template <typename A, typename B>
ostream &operator<<(ostream &cout, pair<A, B> const &p) {
  return cout << "(" << p.f << ", " << p.s << ")";
}
template <typename T>
typename enable_if<is_iterable<T>::value && !is_same<T, string>::value,
                   ostream &>::type
operator<<(ostream &cout, T const &v) {
  cout << "[";
  for (auto it = v.begin(); it != v.end();) {
    cout << *it;
    if (++it != v.end())
      cout << ", ";
  }
  return cout << "]";
}

#ifdef LOCAL
#define debug(...) cout << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define debug(...) "zzz"
#endif