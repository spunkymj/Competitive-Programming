// You are given an array(of integers) of length n.
// You are required to answer q queries.

// Queries can be of two types
// 0. 0 pos val : In this you have to update arr[pos] to val.
// 1. 1 l r: In this query u have to find the sum of all elements in this interval.

// Sum of elements in interval [l, r] means sum of all arr[i] for which i is in range [l, r].



#include <bits/stdc++.h>
using namespace std;

//=======================================================================
#define ll long long
#define vi vector<ll>
#define vpi vector<pair<ll, ll>>
#define mod 1e9 + 7

// segment tree template

class SGTree
{
  vector<int> seg;

public:
  SGTree(int n)
  {
    seg.resize(4 * n + 1, 0);
  }

  void build(int idx, int low, int high, vector<int> &arr)
  {
    if (low == high)
    {
      seg[idx] = arr[low];
      return;
    }

    int mid = low + ((high - low) / 2);
    build(2 * idx + 1, low, mid, arr);
    build(2 * idx + 2, mid + 1, high, arr);
    seg[idx] = (seg[2 * idx + 1]+seg[2 * idx + 2]);
  }

  int query(int idx, int low, int high, int l, int r)
  {

    // no overlap
    if (high < l || low > r)
    {
      return 0;
    }

    // complete overlap
    if (low >= l && high <= r)
    {
      return seg[idx];
    }

    // partial overlap
    int mid = low + ((high - low) / 2);
    int left = query(2 * idx + 1, low, mid, l, r);
    int right = query(2 * idx + 2, mid + 1, high, l, r);
    return (left+right);
  }

  void update(int idx, int low, int high, int i, int val)
  {
    if (low == high)
    {
      seg[idx] = val;
      return;
    }

    int mid = low + ((high - low) / 2);
    if (i <= mid)
    {
      update(2 * idx + 1, low, mid, i, val);
    }
    else
    {
      update(2 * idx + 2, mid + 1, high, i, val);
    }

    seg[idx] = (seg[2 * idx + 1]+seg[2 * idx + 2]);
  }
};

void solve()
{
  int n;
  cin >> n;
  vector<int> arr1(n, 0);
  for (int i = 0; i < n; i++)
  {
    cin >> arr1[i];
  }
  SGTree seg(4 * n);
  seg.build(0, 0, n - 1, arr1);

  int q;
  cin >> q;
  while (q--)
  {
    int type;
    cin >> type;
    if (type == 1)
    {
      int l,r;
      cin>>l>>r;
      int sum = seg.query(0, 0, n - 1, l, r);
      cout << sum << endl;
    }
    else
    {
      int i, val;
      cin >> i >> val;
      seg.update(0, 0, n - 1, i, val);
    }
  }
}

int main()
{
  int t;
  cin >> t;
  while (t--)
  {
    solve();
  }
  return 0;
}
