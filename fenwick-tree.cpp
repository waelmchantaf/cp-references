#include <bits/stdc++.h>
using namespace std;
struct BIT {
  int sz; // TAKE CARE OF ZERO INDEX!!
  vector<int> pre;

  BIT(int X) {
    sz = X;

    pre.clear();
    pre.resize(sz + 1, 0);
  }

  void update(int x, int val) {
    for (; x <= sz; x += (x & (-x)))
      pre[x] += val;

    return;
  }

  int get(int x) {
    long long res = 0;
    for (; x > 0; x -= (x & (-x)))
      res += pre[x];

    return res;
  }
};
