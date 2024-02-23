/**
 * Author: Me
 * Date: 2024-02-13
 * Source: me
 * Description: Lazy segtree with templated info
 */

#pragma once
template <typename T, typename Merge = plus<T>, typename LazyOp = ll>
struct lazy_seg {
  /*
          T: Info semigroup
          operation: T x T => T
          id: T x 1 = T, 1 x T = T
  */
  /*
          LazyOp:
          mapping: F o S => S
          composition: F o F => F
          id: id o S = S for all S
  */
  int n;
  vector<T> tr;
  vector<LazyOp> lazy_inc;
  Merge merge;

  void pull(int z) { tr[z] = merge(tr[2 * z], tr[2 * z + 1]); };

  lazy_seg(int n) : n(n), tr(4 * n + 5), lazy_inc(4 * n + 5), merge(Merge()) {}

  lazy_seg(const vector<T> &a) : lazy_seg((int)a.size()) {
    function<void(int, int, int)> build = [&](int z, int l, int r) {
      if (l == r) {
        tr[z] = T(a[l]);
        return;
      }
      int m = (l + r) >> 1;
      build(2 * z, l, m);
      build(2 * z + 1, m + 1, r);
      pull(z);
    };
    build(1, 0, n - 1);
  }

  void push(int z, int l, int r) {
    tr[z] += lazy_inc[z];
    if (l < r) {
      for (int i = 0; i < 2; i++) {
        lazy_inc[2 * z + i] += lazy_inc[z];
      }
    }
    lazy_inc[z] = LazyOp{};
  }

  void set(int z, int l, int r, int qg, const T &val) {
    push(z, l, r);
    if (l > qg or r < qg)
      return;
    if (l == r and l == qg) {
      tr[z] = val;
      return;
    }
    int m = (l + r) >> 1;
    set(2 * z, l, m, qg, val);
    set(2 * z + 1, m + 1, r, qg, val);
    pull(z);
  }

  void up_inc(int z, int l, int r, int ql, int qr, const LazyOp &val) {
    push(z, l, r);
    if (ql > qr)
      return;
    if (ql == l && qr == r) {
      lazy_inc[z] += val;
      push(z, l, r);
      return;
    }
    int m = (l + r) >> 1;
    up_inc(2 * z, l, m, ql, min(qr, m), val);
    up_inc(2 * z + 1, m + 1, r, max(ql, m + 1), qr, val);
    pull(z);
  };

  T query(int z, int l, int r, int ql, int qr) {
    push(z, l, r);
    if (ql > qr)
      return T{};
    if (ql == l && qr == r) {
      return tr[z];
    }
    int m = (l + r) >> 1;
    return merge(query(2 * z, l, m, ql, min(qr, m)),
                 query(2 * z + 1, m + 1, r, max(ql, m + 1), qr));
  };

  void up_inc(int l, int r, const LazyOp &val) {
    return up_inc(1, 0, n - 1, l, r, val);
  }
  void set(int g, const T &val) { return set(1, 0, n - 1, g, val); }
  T query(int l, int r) { return query(1, 0, n - 1, l, r); }
};
